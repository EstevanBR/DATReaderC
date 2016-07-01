struct ObjectStruct
{
    uint32_t stringOffset;
    uint32_t nextObjectOffset;
    uint32_t materialStructOffset;
    uint32_t meshStructOffset;  
};
typedef struct ObjectStruct ObjectStruct;
struct ObjectStruct *ObjectStruct_create(void);
void GetObjectStruct(ObjectStruct *objectStruct, uint32_t offset, FILE *datFile);
void ObjectStruct_print (ObjectStruct *objectStruct);
void ObjectStruct_destroy(ObjectStruct *objectStruct);