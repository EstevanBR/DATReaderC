struct BoneStructureRoot
{
    //http://wiki.tockdom.com/wiki/HAL_DAT_(File_Format)#Bone_Structures_.28Root_Structure.29
    uint32_t stringOffset;
    uint32_t unknownFlags;
    uint32_t childBoneStructOffset;
    uint32_t nextBoneStructOffset;
    uint32_t objectStructOffset;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    float scale_x;
    float scale_y;
    float scale_z;
    float location_x;
    float location_y;
    float location_z;
    uint32_t inverseBindMatrixOffset;
    uint32_t pointerUnknown;
};
typedef struct BoneStructureRoot BoneStructureRoot;
struct BoneStructureRoot *BoneStructureRoots_create(uint32_t offset);
void GetBoneStructureRoots(RootNode *rootNodes, uint32_t count, BoneStructureRoot *boneStructureRoots, FILE *datFile);
void BoneStructureRoots_destroy(BoneStructureRoot *boneStructureRoots);
void BoneStructureRoots_print(BoneStructureRoot *boneStructureRoots, uint32_t count);