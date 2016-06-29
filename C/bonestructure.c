#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "byteswap.h"
#include "inttypes.h"
#include "bonestructure.h"

struct BoneStructureRoot *BoneStructureRoot_create(uint32_t offset, uint32_t stringOffset, uint32_t unknownFlags, uint32_t childBoneStructOffset, uint32_t nextBoneStructOffset, uint32_t objectStructOffset, float rotation_x, float rotation_y, float rotation_z, float scale_x, float scale_y, float scale_z, float location_x, float location_y, float location_z, uint32_t inverseBindMatrixOffset, uint32_t pointerUnknown) {
    BoneStructureRoot *boneStructureRoot = malloc(sizeof(struct BoneStructureRoot));
    assert(boneStructureRoot != NULL);
    boneStructureRoot->offset = offset;
    boneStructureRoot->stringOffset = stringOffset;
    boneStructureRoot->unknownFlags = unknownFlags;
    boneStructureRoot->childBoneStructOffset = childBoneStructOffset;
    boneStructureRoot->nextBoneStructOffset = nextBoneStructOffset;
    boneStructureRoot->objectStructOffset = objectStructOffset;
    boneStructureRoot->rotation_x = rotation_x;
    boneStructureRoot->rotation_y = rotation_y;
    boneStructureRoot->rotation_z = rotation_z;
    boneStructureRoot->scale_x = scale_x;
    boneStructureRoot->scale_y = scale_y;
    boneStructureRoot->scale_z = scale_z;
    boneStructureRoot->location_x = location_x;
    boneStructureRoot->location_y = location_y;
    boneStructureRoot->location_z = location_z;
    boneStructureRoot->inverseBindMatrixOffset = inverseBindMatrixOffset;
    boneStructureRoot->pointerUnknown = pointerUnknown;
    return boneStructureRoot;
};

void getBoneStructureRoot(BoneStructureRoot *boneStructureRoot, FILE *datFile) {
    assert(datFile != NULL);
}

void BoneStructureRoot_destroy(BoneStructureRoot *boneStructureRoot) {
    assert(boneStructureRoot != NULL);
    free(boneStructureRoot);
}
void BoneStructureRoot_print(BoneStructureRoot *boneStructureRoot) {
    printf("boneStructureRoot->fileSize: %"PRIu32"\n",boneStructureRoot->offset);
    printf("boneStructureRoot->stringOffset: %#.08x\n",boneStructureRoot->stringOffset);
    
}