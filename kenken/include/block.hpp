#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <vector>

typedef enum{
    ADD,
    SUB,
    MUL,
    DIV
} Operation;

struct Block{
    char key;
    unsigned int res;
    Operation op;
};

typedef std::vector<Block> BlockTable;

Block get_block(const BlockTable& blocktable, char key);

#endif