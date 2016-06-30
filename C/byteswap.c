#include <inttypes.h>
#include "byteswap.h"
uint32_t byteswap32(uint32_t num32) {
    return ((num32>>3*8)&0x000000ff)| // move byte 3 to byte 0
           ((num32<<1*8)&0x00ff0000)| // move byte 1 to byte 2
           ((num32>>1*8)&0x0000ff00)| // move byte 2 to byte 1
           ((num32<<3*8)&0xff000000); // byte 0 to byte 3
}

uint16_t byteswap16(uint16_t num16) {
    return  ((num16 & 0xff00) >> 8)|
            ((num16 & 0x00ff) << 8);
}

float floatSwap(float floatIn) {
    uint32_t num32 = *(uint32_t *)&floatIn;
    num32 = ((num32>>3*8)&0x000000ff)| // move byte 3 to byte 0
            ((num32<<1*8)&0x00ff0000)| // move byte 1 to byte 2
            ((num32>>1*8)&0x0000ff00)| // move byte 2 to byte 1
            ((num32<<3*8)&0xff000000); // byte 0 to byte 3
    floatIn = *(float *)&num32;
    return floatIn;
}