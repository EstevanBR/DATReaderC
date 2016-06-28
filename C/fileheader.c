#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "fileheader.h"
#include "byteswap.h"

struct FileHeader *FileHeader_create(uint32_t fileSize,uint32_t pointerTableOffset, uint32_t pointerCount,uint32_t rootNodeCount,uint32_t referenceNodeCount,char *unknownString, uint32_t unknownPadding1, uint32_t unknownPadding2) {
    FileHeader *fileHeader = malloc(sizeof(struct FileHeader));
    assert(fileHeader != NULL);
    fileHeader->fileSize = fileSize;
    fileHeader->pointerTableOffset = pointerTableOffset;
    fileHeader->pointerCount = pointerCount;
    fileHeader->rootNodeCount = rootNodeCount;
    fileHeader->referenceNodeCount = referenceNodeCount;
    strncpy(fileHeader->unknownString, unknownString, 4);
    fileHeader->unknownPadding1 = unknownPadding1;
    fileHeader->unknownPadding2 = unknownPadding2;
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
    printf("\nfileHeader->fileSize: %"PRIu32"\n",fileHeader->fileSize);
    printf("fileHeader->pointerTableOffset: %#.08x\n",fileHeader->pointerTableOffset);
    printf("fileHeader->pointerCount: %"PRIu32"\n",fileHeader->pointerCount);
    printf("fileHeader->rootNodeCount: %"PRIu32"\n",fileHeader->rootNodeCount);
    printf("fileHeader->referenceNodeCount: %"PRIu32"\n",fileHeader->referenceNodeCount);
    printf("fileHeader->unknownString: %s\n",fileHeader->unknownString);
    printf("fileHeader->unknownPadding1: %"PRIu32"\n",fileHeader->unknownPadding1);
    printf("fileHeader->unknownPadding2: %"PRIu32"\n",fileHeader->unknownPadding2);
    
}