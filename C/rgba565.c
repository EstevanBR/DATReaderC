#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
void printRBGFromRGB365(uint16_t color);
struct Pixel
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    
};
typedef struct Pixel Pixel;
int main(int argc, char const *argv[])
{
    /* code */
    printRBGFromRGB365(0b1111100000000000);
    printRBGFromRGB365(0x0000);
    printRBGFromRGB365(0x40B0);
    printRBGFromRGB365(0x0078);

    return 0;
}

void printRBGFromRGB365(uint16_t color) {
    int red;
    int green;
    int blue;
    red =   (color>>11)&0b0000000000011111;
    green = (color>>05)&0b0000000000111111;
    blue =  (color>>00)&0b0000000000011111;
    Pixel *pixel = malloc(sizeof(struct Pixel));
    red *=0x08;
    green *=0x04;
    blue *=0x08;
    pixel->red = red;
    pixel->green = green;
    pixel->blue = blue;
    printf("R: %"PRIu8"\nG: %"PRIu8"\nB: %"PRIu8"\n\n", pixel->red, pixel->green, pixel->blue);
    free(pixel);
}

uint8_t lerp (uint8_t a, uint8_t b, uint8_t t) {
    float T = (float)t / 255.0f;
    return (b-a)*t + b;
}