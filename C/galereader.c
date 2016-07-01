#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include "fileheader.h"
#include "rootnodes.h"
#include "pointertable.h"
#include "byteswap.h"
#include "bonestructure.h"
#include "object.h"

#define DATA_BLOCK 0x20

int main(int argc, char const *argv[])
{
    FILE *datFile = fopen("PlFcGr.dat", "rb");
    if (datFile) {
        printf("opened file\n");
    } else {
        printf("there was an error!\007\n");
        return -1;
    }
    
    FileHeader *fileHeader = FileHeader_create();
    getFileHeader(fileHeader, datFile);
    FileHeader_print(fileHeader);
    
    PointerTable *pointerTable = GetPointersFromPointerTable(datFile, fileHeader->pointerTableOffset, fileHeader->pointerCount);
    PointerTable_print(pointerTable, fileHeader->pointerCount);
    
    RootNode *rootNodes = RootNodes_create(fileHeader->rootNodeCount);
    GetRootNodes(rootNodes, datFile, ftell(datFile), fileHeader->rootNodeCount);
    RootNodes_print(rootNodes, fileHeader->rootNodeCount);

    BoneStructureRoot *boneStructureRoots = BoneStructureRoots_create(fileHeader->rootNodeCount);
    GetBoneStructureRoots(rootNodes, fileHeader->rootNodeCount,boneStructureRoots, datFile);
    BoneStructureRoots_print(boneStructureRoots, fileHeader->rootNodeCount);

    ObjectStruct *objectStruct = ObjectStruct_create();;
    long offset = boneStructureRoots[0].objectStructOffset;
    do {
        GetObjectStruct(objectStruct, offset ,datFile);
        offset = objectStruct->nextObjectOffset;
        ObjectStruct_print(objectStruct);
    } while (offset != 0x0000);
    
    fclose(datFile);
    FileHeader_destroy(fileHeader);
    RootNodes_destroy(rootNodes);
    PointerTable_destroy(pointerTable);
    BoneStructureRoots_destroy(boneStructureRoots);
    ObjectStruct_destroy(objectStruct);
    printf("\nclosed file\n");
    return 0;
}

