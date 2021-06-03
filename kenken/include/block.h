#ifndef BLOCK_H
#define BLOCK_H

#include <stdint.h>
#include <stdlib.h>

typedef enum{
    ADD,
    SUB,
    MUL,
    DIV
} Operation;

typedef struct{
    char key;
    uint16_t res;
    Operation op;
} Block;

typedef struct{
    uint8_t size;
    Block * blocks;
} BlockTable;

BlockTable * blocktable_create();
void blocktable_insert(BlockTable * blocktable, char key, uint16_t res, Operation op);
Block * blocktable_get(BlockTable * blocktable, char key);

#endif