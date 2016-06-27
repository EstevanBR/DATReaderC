#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>
#include "byteswap.h"
#include "pointertable.h"
#define DATA_BLOCK 0x20

PointerTable* getPointersFromPointerTable(FILE *datFile, uint32_t pointerTableOffset, uint32_t count) {
    assert(datFile != NULL);
    fseek(datFile, pointerTableOffset+DATA_BLOCK, SEEK_SET);
    PointerTable *pointers = malloc(sizeof(uint32_t) * count);
    fread(pointers, sizeof(uint32_t), count, datFile);
    for (int i = 0; i < count; i++) {
        pointers[i] = byteswap32(pointers[i]);
    }
    return pointers;
}
void PointerTable_print(PointerTable *pointerTable, uint32_t count) {
    for (int i = 0; i < count; i++) {
        printf("%#.8lx ", (unsigned long) pointerTable[i]);
        if (i % 9 == 8) {
            printf("\n");
        }
    }
}