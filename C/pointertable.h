typedef uint32_t PointerTable;
PointerTable* getPointersFromPointerTable(FILE *datFile, uint32_t pointerTableOffset, uint32_t count);
void PointerTable_print(PointerTable *pointerTable, uint32_t count);