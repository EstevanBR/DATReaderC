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

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

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
        float tempFloat;
        tempFloat = boneStructureRoot->rotation_x;
        boneStructureRoot->rotation_x = floatSwap(tempFloat);
        tempFloat = boneStructureRoot->rotation_y;
        boneStructureRoot->rotation_y = floatSwap(tempFloat);
        tempFloat = boneStructureRoot->rotation_z;
        boneStructureRoot->rotation_z = floatSwap(tempFloat);
        tempFloat = boneStructureRoot->scale_x;
        boneStructureRoot->scale_x = floatSwap(tempFloat);
        tempFloat = boneStructureRoot->scale_y;
        boneStructureRoot->scale_y = floatSwap(tempFloat);
        tempFloat = boneStructureRoot->scale_z;
        boneStructureRoot->scale_z = floatSwap(tempFloat);
        tempFloat = boneStructureRoot->location_x;
        boneStructureRoot->location_x = floatSwap(tempFloat);
        tempFloat = boneStructureRoot->location_y;
        boneStructureRoot->location_y = floatSwap(tempFloat);
        tempFloat = boneStructureRoot->location_z;
        boneStructureRoot->location_z = floatSwap(tempFloat);
        boneStructureRoot->inverseBindMatrixOffset=byteswap32(boneStructureRoot->inverseBindMatrixOffset);
        boneStructureRoot->pointerUnknown=byteswap32(boneStructureRoot->pointerUnknown);
    }
}

void BoneStructureRoots_print(BoneStructureRoot *boneStructureRoots, uint32_t count) {
    for (int i = 0; i < count; ++i)
    {
        BoneStructureRoot *boneStructureRoot = &boneStructureRoots[i];
        printf("\nstringOffset: "KRED"%#.08x"KNRM, boneStructureRoot->stringOffset);
        printf("\nunknownFlags: "KRED"%#.08x"KNRM, boneStructureRoot->unknownFlags);
        printf("\nchildBoneStructOffset: "KRED"%#.08x"KNRM, boneStructureRoot->childBoneStructOffset);
        printf("\nnextBoneStructOffset: "KRED"%#.08x"KNRM, boneStructureRoot->nextBoneStructOffset);
        printf("\nobjectStructOffset: "KRED"%#.08x"KNRM, boneStructureRoot->objectStructOffset);
        printf("\nrotation_x: "KRED"%#.08f"KNRM, boneStructureRoot->rotation_x);
        printf("\nrotation_y: "KRED"%#.08f"KNRM, boneStructureRoot->rotation_y);
        printf("\nrotation_z: "KRED"%#.08f"KNRM, boneStructureRoot->rotation_z);
        printf("\nscale_x: "KRED"%#.08f"KNRM, boneStructureRoot->scale_x);
        printf("\nscale_y: "KRED"%#.08f"KNRM, boneStructureRoot->scale_y);
        printf("\nscale_z: "KRED"%#.08f"KNRM, boneStructureRoot->scale_z);
        printf("\nlocation_x: "KRED"%#.08f"KNRM, boneStructureRoot->location_x);
        printf("\nlocation_y: "KRED"%#.08f"KNRM, boneStructureRoot->location_y);
        printf("\nlocation_z: "KRED"%#.08f"KNRM, boneStructureRoot->location_z);
        printf("\ninverseBindMatrixOffset: "KRED"%#.08x"KNRM, boneStructureRoot->inverseBindMatrixOffset);
        printf("\npointerUnknown: "KRED"%#.08x\n"KNRM, boneStructureRoot->pointerUnknown);
    }
}

void BoneStructureRoots_destroy(BoneStructureRoot *boneStructureRoots) {
    assert(boneStructureRoots != NULL);
    free(boneStructureRoots);
}