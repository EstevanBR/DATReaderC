#include "inttypes.h"
#include "bonestructure.h"
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "byteswap.h"

struct BoneStructureRoot *BoneStructureRoot_create(uint32_t fileSize,uint32_t pointerTableOffset, uint32_t pointerCount,uint32_t rootNodeCount,uint32_t referenceNodeCount,char *unknownString, uint32_t unknownPadding1, uint32_t unknownPadding2) {
    BoneStructureRoot *boneStructureRoot = malloc(sizeof(struct BoneStructureRoot));
    assert(boneStructureRoot != NULL);
    boneStructureRoot->fileSize = fileSize;
    return boneStructureRoot;
};

void getBoneStructureRoot(BoneStructureRoot *boneStructureRoot, FILE *datFile) {
    assert(datFile != NULL);
    fseek(datFile, 0, SEEK_SET);
    fread(&header->fileSize, sizeof(header->fileSize), 1, datFile);
    header->fileSize = byteswap32(header->fileSize);
}

void BoneStructureRoot_destroy(BoneStructureRoot *boneStructureRoot) {
    assert(boneStructureRoot != NULL);
    free(boneStructureRoot);
}
void BoneStructureRoot_print(BoneStructureRoot *boneStructureRoot) {
    printf("boneStructureRoot->fileSize: %"PRIu32"\n",boneStructureRoot->fileSize);
    printf("boneStructureRoot->pointerTableOffset: %#.08x\n",boneStructureRoot->pointerTableOffset);
    
}