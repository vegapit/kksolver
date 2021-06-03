#ifndef KENKEN_H
#define KENKEN_H

#include <stdint.h>
#include <stdlib.h>
#include <block.h>

typedef struct{
    uint8_t grid_size;
    char * grid;
    BlockTable * blocktable;
    uint8_t * values;
} Kenken;

Kenken * kenken_new(uint8_t grid_size, char * grid, BlockTable * blocktable);
char * kenken_grid_get(Kenken * kenken, uint8_t i, uint8_t j);
uint8_t * kenken_value_get(Kenken * kenken, uint8_t i, uint8_t j);
void kenken_value_set(Kenken * kenken, uint8_t i, uint8_t j, uint8_t val);
uint8_t kenken_is_complete(Kenken * kenken);
uint8_t kenken_check_block(Kenken * kenken, char key);
uint8_t kenken_check_row(Kenken * kenken, uint8_t col);
uint8_t kenken_check_col(Kenken * kenken, uint8_t row);
uint8_t kenken_check_values(Kenken * kenken);
void kenken_print_values(Kenken * kenken);
void kenken_print_grid(Kenken * kenken);
uint8_t kenken_solve(Kenken * kenken);

#endif