#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "byteswap.h"
#include "inttypes.h"
#include "rootnodes.h"
#include "bonestructure.h"

#define DATA_BLOCK 0x20
float ReverseFloat( const float inFloat );
struct BoneStructureRoot *BoneStructureRoots_create(uint32_t count) {
    BoneStructureRoot *boneStructureRoots = malloc(sizeof(struct BoneStructureRoot) * count);
    assert(boneStructureRoots != NULL);
    return boneStructureRoots;
}

void GetBoneStructureRoots(RootNode *rootNodes, uint32_t count, BoneStructureRoot *boneStructureRoots, FILE *datFile) {
    assert(datFile != NULL);
    for (int i = 0; i < count; ++i)
    {
        RootNode *rootNode = &rootNodes[i];
        fseek(datFile, rootNode->dataOffset+DATA_BLOCK, SEEK_SET);
        BoneStructureRoot *boneStructureRoot = &boneStructureRoots[i];

        fread(&boneStructureRoot->stringOffset, sizeof(boneStructureRoot->stringOffset), 1, datFile);
        fread(&boneStructureRoot->unknownFlags, sizeof(boneStructureRoot->unknownFlags), 1, datFile);
        fread(&boneStructureRoot->childBoneStructOffset, sizeof(boneStructureRoot->childBoneStructOffset), 1, datFile);
        fread(&boneStructureRoot->nextBoneStructOffset, sizeof(boneStructureRoot->nextBoneStructOffset), 1, datFile);
        fread(&boneStructureRoot->objectStructOffset, sizeof(boneStructureRoot->objectStructOffset), 1, datFile);
        fread(&boneStructureRoot->rotation_x, sizeof(boneStructureRoot->rotation_x), 1, datFile);
        fread(&boneStructureRoot->rotation_y, sizeof(boneStructureRoot->rotation_y), 1, datFile);
        fread(&boneStructureRoot->rotation_z, sizeof(boneStructureRoot->rotation_z), 1, datFile);
        fread(&boneStructureRoot->scale_x, sizeof(boneStructureRoot->scale_x), 1, datFile);
        fread(&boneStructureRoot->scale_y, sizeof(boneStructureRoot->scale_y), 1, datFile);
        fread(&boneStructureRoot->scale_z, sizeof(boneStructureRoot->scale_z), 1, datFile);
        fread(&boneStructureRoot->location_x, sizeof(boneStructureRoot->location_x), 1, datFile);
        fread(&boneStructureRoot->location_y, sizeof(boneStructureRoot->location_y), 1, datFile);
        fread(&boneStructureRoot->location_z, sizeof(boneStructureRoot->location_z), 1, datFile);
        fread(&boneStructureRoot->inverseBindMatrixOffset, sizeof(boneStructureRoot->inverseBindMatrixOffset), 1, datFile);
        fread(&boneStructureRoot->pointerUnknown, sizeof(boneStructureRoot->pointerUnknown), 1, datFile);
        
        boneStructureRoot->stringOffset=byteswap32(boneStructureRoot->stringOffset);
        boneStructureRoot->unknownFlags=byteswap32(boneStructureRoot->unknownFlags);
        boneStructureRoot->childBoneStructOffset=byteswap32(boneStructureRoot->childBoneStructOffset);
        boneStructureRoot->nextBoneStructOffset=byteswap32(boneStructureRoot->nextBoneStructOffset);
        boneStructureRoot->objectStructOffset=byteswap32(boneStructureRoot->objectStructOffset);
        
        uint32_t temp32;

        temp32 = *(uint32_t *)&boneStructureRoot->rotation_x;
        temp32 = byteswap32(temp32);
        boneStructureRoot->rotation_x = *(float *)&temp32;

        temp32 = *(uint32_t *)&boneStructureRoot->rotation_y;
        temp32 = byteswap32(temp32);
        boneStructureRoot->rotation_y = *(float *)&temp32;

        temp32 = *(uint32_t *)&boneStructureRoot->rotation_z;
        temp32 = byteswap32(temp32);
        boneStructureRoot->rotation_z = *(float *)&temp32;

        temp32 = *(uint32_t *)&boneStructureRoot->scale_x;
        temp32 = byteswap32(temp32);
        boneStructureRoot->scale_x = *(float *)&temp32;

        temp32 = *(uint32_t *)&boneStructureRoot->scale_y;
        temp32 = byteswap32(temp32);
        boneStructureRoot->scale_y = *(float *)&temp32;

        temp32 = *(uint32_t *)&boneStructureRoot->scale_z;
        temp32 = byteswap32(temp32);
        boneStructureRoot->scale_z = *(float *)&temp32;

        temp32 = *(uint32_t *)&boneStructureRoot->location_x;
        temp32 = byteswap32(temp32);
        boneStructureRoot->location_x = *(float *)&temp32;

        temp32 = *(uint32_t *)&boneStructureRoot->location_y;
        temp32 = byteswap32(temp32);
        boneStructureRoot->location_y = *(float *)&temp32;

        temp32 = *(uint32_t *)&boneStructureRoot->location_z;
        temp32 = byteswap32(temp32);
        boneStructureRoot->location_z = *(float *)&temp32;

        boneStructureRoot->inverseBindMatrixOffset=byteswap32(boneStructureRoot->inverseBindMatrixOffset);
        boneStructureRoot->pointerUnknown=byteswap32(boneStructureRoot->pointerUnknown);
    }
}

void BoneStructureRoots_print(BoneStructureRoot *boneStructureRoots, uint32_t count) {
    for (int i = 0; i < count; ++i)
    {
        BoneStructureRoot *boneStructureRoot = &boneStructureRoots[i];
        printf("\nstringOffset: %#.08x", boneStructureRoot->stringOffset);
        printf("\nunknownFlags: %#.08x", boneStructureRoot->unknownFlags);
        printf("\nchildBoneStructOffset: %#.08x", boneStructureRoot->childBoneStructOffset);
        printf("\nnextBoneStructOffset: %#.08x", boneStructureRoot->nextBoneStructOffset);
        printf("\nobjectStructOffset: %#.08x", boneStructureRoot->objectStructOffset);
        printf("\nrotation_x: %#.08f", boneStructureRoot->rotation_x);
        printf("\nrotation_y: %#.08f", boneStructureRoot->rotation_y);
        printf("\nrotation_z: %#.08f", boneStructureRoot->rotation_z);
        printf("\nscale_x: %#.08f", boneStructureRoot->scale_x);
        printf("\nscale_y: %#.08f", boneStructureRoot->scale_y);
        printf("\nscale_z: %#.08f", boneStructureRoot->scale_z);
        printf("\nlocation_x: %#.08f", boneStructureRoot->location_x);
        printf("\nlocation_y: %#.08f", boneStructureRoot->location_y);
        printf("\nlocation_z: %#.08f", boneStructureRoot->location_z);
        printf("\ninverseBindMatrixOffset: %#.08x", boneStructureRoot->inverseBindMatrixOffset);
        printf("\npointerUnknown: %#.08x\n", boneStructureRoot->pointerUnknown);
    }
}

void BoneStructureRoots_destroy(BoneStructureRoot *boneStructureRoots) {
    assert(boneStructureRoots != NULL);
    free(boneStructureRoots);
}

float ReverseFloat( const float inFloat ) {
   float retVal;
   char *floatToConvert = ( char* ) & inFloat;
   char *returnFloat = ( char* ) & retVal;

   // swap the bytes into a temporary buffer
   returnFloat[0] = floatToConvert[3];
   returnFloat[1] = floatToConvert[2];
   returnFloat[2] = floatToConvert[1];
   returnFloat[3] = floatToConvert[0];

   return retVal;
}