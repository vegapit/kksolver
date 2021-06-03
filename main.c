#include <stdint.h>
#include <stdlib.h>

#include "block.h"
#include "kenken.h"

int main() {
    
    uint8_t grid_size = 6;
    
    char grid[] = {
        'a', 'b', 'b', 'c', 'c', 'd',
        'a', 'e', 'c', 'c', 'f', 'd',
        'g', 'e', 'e', 'e', 'f', 'h',
        'i', 'j', 'j', 'k', 'l', 'h',
        'i', 'm', 'n', 'k', 'o', 'o',
        'm', 'm', 'm', 'p', 'p', 'o'
    };

    BlockTable * p_block_table = blocktable_create();

    blocktable_insert( p_block_table, 'a', 3, SUB);
    blocktable_insert( p_block_table, 'b', 2, DIV);
    blocktable_insert( p_block_table, 'c', 720, MUL);
    blocktable_insert( p_block_table, 'd', 2, SUB);
    blocktable_insert( p_block_table, 'e', 12, ADD);
    blocktable_insert( p_block_table, 'f', 1, SUB);
    blocktable_insert( p_block_table, 'g', 5, ADD);
    blocktable_insert( p_block_table, 'h', 1, SUB);
    blocktable_insert( p_block_table, 'i', 2, DIV);
    blocktable_insert( p_block_table, 'j', 12, MUL);
    blocktable_insert( p_block_table, 'k', 2, DIV);
    blocktable_insert( p_block_table, 'l', 5, ADD);
    blocktable_insert( p_block_table, 'm', 15, ADD);
    blocktable_insert( p_block_table, 'n', 6, ADD);
    blocktable_insert( p_block_table, 'o', 12, ADD);
    blocktable_insert( p_block_table, 'p', 5, ADD);

    Kenken * p_kenken = kenken_new(grid_size, (char *) grid, p_block_table);

    kenken_solve( p_kenken );

    kenken_print_values( p_kenken );

    return 0;
}