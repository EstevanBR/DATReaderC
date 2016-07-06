#include <inttypes.h>
#include "byteswap.h"
#include <stdio.h>
// int main(int argc, char const *argv[])
// {
//     littleEndian();
//     return 0;
// }
uint32_t byteswap32(uint32_t num32) {
    if (littleEndian()) {
        return ((num32>>3*8)&0x000000ff)| // move byte 3 to byte 0
               ((num32<<1*8)&0x00ff0000)| // move byte 1 to byte 2
               ((num32>>1*8)&0x0000ff00)| // move byte 2 to byte 1
               ((num32<<3*8)&0xff000000); // byte 0 to byte 3
    } else {
        return num32;
    }
}

uint16_t byteswap16(uint16_t num16) {
    if (littleEndian()) {
        return  ((num16 & 0xff00) >> 8)|
                ((num16 & 0x00ff) << 8);
    } else {
        return num16;
    }
}

float floatSwap(float floatIn) {
    if (littleEndian()) {
    uint32_t num32 = *(uint32_t *)&floatIn;
    num32 = ((num32>>3*8)&0x000000ff)| // move byte 3 to byte 0
            ((num32<<1*8)&0x00ff0000)| // move byte 1 to byte 2
            ((num32>>1*8)&0x0000ff00)| // move byte 2 to byte 1
            ((num32<<3*8)&0xff000000); // byte 0 to byte 3
    floatIn = *(float *)&num32;
    return floatIn;
    } else {
        return floatIn;
    }
}

int littleEndian(void) {
    FILE *fp = fopen("endian", "rb");
    uint32_t bigHex[1];
    bigHex[0] = 0x3f800000;
    fseek(fp, 0, SEEK_SET);
    uint32_t readHex[1];
    float readFloat[1];
    fread(readFloat, sizeof(uint32_t), 1, fp);
    readHex[0] = *(uint32_t *)&readFloat[0];
    fclose(fp);
    int little = 0;
    if (*(uint32_t*)&readFloat[0] == bigHex[0]) {
        //printf("%f, %f\n", readFloat[0], *(float *)& bigHex[0]);
        //printf("BIG ENDIAN:    %#.08x is %#.08x\n", bigHex[0], readHex[0]);
        little = 1;
    } else if (*(uint32_t*)&readFloat[0] != bigHex[0]){
        //printf("%f, %f\n", readFloat[0], *(float *)& bigHex[0]);
        //printf("LITTLE ENDIAN: %#.08x is not %#.08x\n", bigHex[0], readHex[0]);
        little = -1;
    }
    return little;
}