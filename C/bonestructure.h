struct BoneStructureRoot
{
    //http://wiki.tockdom.com/wiki/HAL_DAT_(File_Format)#Bone_Structures_.28Root_Structure.29
    uint32_t offset;
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
struct BoneStructureRoot *BoneStructureRoot_create(uint32_t offset, uint32_t stringOffset, uint32_t unknownFlags, uint32_t childBoneStructOffset, uint32_t nextBoneStructOffset, uint32_t objectStructOffset, float rotation_x, float rotation_y, float rotation_z, float scale_x, float scale_y, float scale_z, float location_x, float location_y, float location_z, uint32_t inverseBindMatrixOffset, uint32_t pointerUnknown);
void getBoneStructureRoot(BoneStructureRoot *boneStructureRoot, FILE *datFile);
void BoneStructureRoot_destroy(BoneStructureRoot *boneStructureRoot);
void BoneStructureRoot_print(BoneStructureRoot *boneStructureRoot);