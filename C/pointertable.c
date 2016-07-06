#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>
#include "byteswap.h"
#include "pointertable.h"

#define DATA_BLOCK 0x20

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

PointerTable* GetPointersFromPointerTable(FILE *datFile, uint32_t pointerTableOffset, uint32_t count) {
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
        printf(""KGRN"%#.8lx "KNRM, (unsigned long) pointerTable[i]);
        if (i % 9 == 8) {
            printf("\n");
        }
    }
}
void PointerTable_destroy(PointerTable *pointerTable) {
    assert(pointerTable != NULL);
    free(pointerTable);
}