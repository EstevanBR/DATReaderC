struct RootNode {
    uint32_t dataOffset;
    uint32_t stringOffset;
    char *string;
};
typedef struct RootNode RootNode;
struct RootNode *RootNodes_create (uint32_t count);
void getRootNodes(RootNode *rootNodes, FILE *fp, uint32_t offset, uint32_t count);
void RootNodes_destroy(RootNode *rootNodes);
void RootNodes_print(RootNode *rootNodes, uint32_t count);