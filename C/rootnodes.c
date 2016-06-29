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
    
    for (int i = 0; i < count; i++) {
        long startingOffset = ftell(datFile);
        int length = 0;
        do {
            length++;
        } while (fgetc(datFile)!= 0x00);
        RootNode *rootNode = &rootNodes[i];
        rootNode->string = malloc(length);
        fseek(datFile, startingOffset, SEEK_SET);
        fgets(rootNode->string, length, datFile);
        fseek(datFile, 1, SEEK_CUR);
    }
}

void RootNodes_destroy(RootNode *rootNodes) {
    assert(rootNodes != NULL);
    free(rootNodes);
}
void RootNodes_print(RootNode *rootNodes, uint32_t count) {
    for (int i = 0; i < count; i++) {
        RootNode *rootNode = &rootNodes[i];
        printf("\nrootNode[%d]->dataOffset: %#.08x\n", i+1, (rootNode->dataOffset));
        printf("rootNode[%d]->stringOffset: %#.08x\n", i+1, (rootNode->stringOffset));
        printf("rootNode[%d]->string: %s\n", i+1, (rootNode->string));
    }
}