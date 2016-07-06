#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "byteswap.h"
#include "inttypes.h"
#include "rootnodes.h"
#include "bonestructure.h"
#include "object.h"

#define DATA_BLOCK 0x20

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

struct ObjectStruct *ObjectStruct_create(void) {
    ObjectStruct *objectStruct = malloc(sizeof(struct ObjectStruct));
    assert(objectStruct != NULL);
    return objectStruct;
}

void GetObjectStruct(ObjectStruct *objectStruct, uint32_t offset, FILE *datFile) {
    fseek(datFile, offset+DATA_BLOCK, SEEK_SET);
    printf("\nbefore getting object, file is at "KRED"%#.08lx"KNRM, ftell(datFile));
    assert(objectStruct != NULL);
    assert(datFile != NULL);
    fread(&objectStruct->stringOffset, sizeof(objectStruct->stringOffset), 1, datFile);
    fread(&objectStruct->nextObjectOffset, sizeof(objectStruct->nextObjectOffset), 1, datFile);
    fread(&objectStruct->materialStructOffset, sizeof(objectStruct->materialStructOffset), 1, datFile);
    fread(&objectStruct->meshStructOffset, sizeof(objectStruct->meshStructOffset), 1, datFile);
    objectStruct->stringOffset=byteswap32(objectStruct->stringOffset);
    objectStruct->nextObjectOffset=byteswap32(objectStruct->nextObjectOffset);
    objectStruct->materialStructOffset=byteswap32(objectStruct->materialStructOffset);
    objectStruct->meshStructOffset=byteswap32(objectStruct->meshStructOffset);
}

void ObjectStruct_print (ObjectStruct *objectStruct) {
    assert(objectStruct != NULL);
    printf("\nobjectStruct->stringOffset "KRED"%#.08x"KNRM, objectStruct->stringOffset);
    printf("\nobjectStruct->nextObjectOffset "KRED"%#.08x"KNRM, objectStruct->nextObjectOffset);
    printf("\nobjectStruct->materialStructOffset "KRED"%#.08x"KNRM, objectStruct->materialStructOffset);
    printf("\nobjectStruct->meshStructOffset "KRED"%#.08x\n"KNRM, objectStruct->meshStructOffset);
}

void ObjectStruct_destroy(ObjectStruct *objectStruct) {
    assert(objectStruct != NULL);
    free(objectStruct);
}