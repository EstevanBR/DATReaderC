#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "rootnodes.h"
#include "byteswap.h"

#define DATA_BLOCK 0x20

struct RootNode *RootNodes_create (uint32_t count) {
    RootNode *rootNodes = malloc(sizeof(struct RootNode) * count);
    assert(rootNodes != NULL);
    return rootNodes;
};

void getRootNodes(RootNode *rootNodes, FILE *datFile, uint32_t offset, uint32_t count) {
    assert(datFile != NULL);
    fseek(datFile, offset, SEEK_SET);
    for (int i = 0; i < count; i++) {
        RootNode *rootNode = &rootNodes[i];
        fread(&rootNode->dataOffset, sizeof(rootNode->dataOffset), 1, datFile);
        fread(&rootNode->stringOffset, sizeof(rootNode->stringOffset), 1, datFile);
        rootNode->dataOffset = byteswap32(rootNode->dataOffset);
        rootNode->stringOffset = byteswap32(rootNode->stringOffset);
    }
    int stringTableOffset = ftell(datFile);
    printf("\nstring table offset = %d\n", stringTableOffset);
    fseek(datFile, 0, SEEK_END);
    int stringTableLength = ftell(datFile) - stringTableOffset;
    printf("\nfile size = %ld\n", ftell(datFile));
    printf("length of stringTable is %d\n", stringTableLength);
    fseek(datFile, -stringTableLength, SEEK_END);
    RootNode *rootNode1 = &rootNodes[0];
    RootNode *rootNode2 = &rootNodes[1];
    printf("\nrootNodeNext.stringOffset%"PRIu32, rootNode1->stringOffset);
    printf("\nrootNodeNext.stringOffset%"PRIu32, rootNode2->stringOffset);
    uint32_t length = rootNode2->stringOffset - rootNode1->stringOffset;
    printf("\nlength = %"PRIu32, length); // you might need to be doing the above line in the loop
    // for (int i = 0; i < count-1; i++) {
    //     RootNode *rootNode = &rootNodes[i];
    //     if (i+1 < count) {
    //         RootNode *rootNodeNext = &rootNodes[i+1];
    //         printf("rootNodeNext.stringOffset%"PRIu32, rootNodeNext->stringOffset);
    //         uint32_t length = rootNodeNext->stringOffset;
    //         fread(rootNode->string, sizeof(char) * (length-1), 1, datFile);
    //     }
        
    // }
    printf("cursor: %#lx\n", ftell(datFile));
}

void RootNodes_destroy(RootNode *rootNodes) {
    assert(rootNodes != NULL);
    free(rootNodes);
}
void RootNodes_print(RootNode *rootNodes, uint32_t count) {
    for (int i = 0; i < count; i++) {
        RootNode *rootNode = &rootNodes[i];
        printf("\nrootNode[%d]->dataOffset: %#.08x\n", i+1, (rootNode->dataOffset));
        printf("rootNode[%d]->stringOffset: %#.08x", i+1, (rootNode->stringOffset));
        //printf("rootNode[%d]->string: %s", i+1, (rootNode->string));
    }
}