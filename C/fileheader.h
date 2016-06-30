struct FileHeader
{
    uint32_t fileSize;
    uint32_t pointerTableOffset;
    uint32_t pointerCount;
    uint32_t rootNodeCount;
    uint32_t referenceNodeCount;
    char     unknownString[4];
    uint32_t unknownPadding1;
    uint32_t unknownPadding2;
};
typedef struct FileHeader FileHeader;
struct FileHeader *FileHeader_create(void);
void getFileHeader(FileHeader *header, FILE *fp);
void FileHeader_destroy(FileHeader *fileHeader);
void FileHeader_print(FileHeader *fileHeader);