#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "fileheader.h"
#include "byteswap.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

struct FileHeader *FileHeader_create(void) {
    FileHeader *fileHeader = malloc(sizeof(struct FileHeader));
    assert(fileHeader != NULL);
    return fileHeader;
};

void getFileHeader(FileHeader *header, FILE *datFile) {
    assert(datFile != NULL);
    fseek(datFile, 0, SEEK_SET);
    fread(&header->fileSize, sizeof(header->fileSize), 1, datFile);
    fread(&header->pointerTableOffset, sizeof(header->pointerTableOffset), 1, datFile);
    fread(&header->pointerCount, sizeof(header->pointerCount), 1, datFile);
    fread(&header->rootNodeCount, sizeof(header->rootNodeCount), 1, datFile);
    fread(&header->referenceNodeCount, sizeof(header->referenceNodeCount), 1, datFile);
    fread(&header->unknownString, sizeof(header->unknownString), 1, datFile);
    fread(&header->unknownPadding1, sizeof(header->unknownPadding1), 1, datFile);
    fread(&header->unknownPadding2, sizeof(header->unknownPadding2), 1, datFile);
    header->fileSize = byteswap32(header->fileSize);
    header->pointerTableOffset = byteswap32(header->pointerTableOffset);
    header->pointerCount = byteswap32(header->pointerCount);
    header->rootNodeCount = byteswap32(header->rootNodeCount);
    header->referenceNodeCount = byteswap32(header->referenceNodeCount);
    header->unknownPadding1 = byteswap32(header->unknownPadding1);
    header->unknownPadding2 = byteswap32(header->unknownPadding2);
}

void FileHeader_destroy(FileHeader *fileHeader) {
    assert(fileHeader != NULL);
    free(fileHeader);
}
void FileHeader_print(FileHeader *fileHeader) {
    printf("\nfileHeader->fileSize: "KRED"%"PRIu32"\n"KNRM,fileHeader->fileSize);
    printf("fileHeader->pointerTableOffset: "KRED"%#.08x\n"KNRM,fileHeader->pointerTableOffset);
    printf("fileHeader->pointerCount: "KRED"%"PRIu32"\n"KNRM,fileHeader->pointerCount);
    printf("fileHeader->rootNodeCount: "KRED"%"PRIu32"\n"KNRM,fileHeader->rootNodeCount);
    printf("fileHeader->referenceNodeCount: "KRED"%"PRIu32"\n"KNRM,fileHeader->referenceNodeCount);
    printf("fileHeader->unknownString: "KRED"%s\n"KNRM,fileHeader->unknownString);
    printf("fileHeader->unknownPadding1: "KRED"%"PRIu32"\n"KNRM,fileHeader->unknownPadding1);
    printf("fileHeader->unknownPadding2: "KRED"%"PRIu32"\n"KNRM,fileHeader->unknownPadding2);
    
}