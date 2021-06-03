#include "block.h"
#include <stdlib.h>
#include <stdint.h>

BlockTable * blocktable_create() {
    BlockTable * pTable = malloc( sizeof(BlockTable) );
    pTable->size = 0;
    pTable->blocks = NULL;
    return pTable;
}

void blocktable_insert(BlockTable * blocktable, char key, uint16_t res, Operation op) {
    // If block already exists, do nothing
    if( blocktable_get(blocktable, key) != NULL ){
        return;
    }
    blocktable->blocks = realloc( blocktable->blocks, sizeof(Block) * (blocktable->size + 1) );
    Block new_block = {.key=key, .res=res, .op=op};
    blocktable->blocks[blocktable->size] = new_block;
    blocktable->size++;
}

Block * blocktable_get(BlockTable * blocktable, char key) {
    for(uint8_t i = 0; i < blocktable->size; i++) {
        if( blocktable->blocks[i].key == key ) {
            return &blocktable->blocks[i];
        }
    }
    return NULL;
}