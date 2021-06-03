#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "vector.h"
#include "kenken.h"

// Kenken functions

Kenken * kenken_new(uint8_t grid_size, char * grid, BlockTable * blocktable) {
    Kenken * ptr = malloc( sizeof(Kenken) );
    ptr->grid_size = grid_size;
    ptr->grid = grid;
    ptr->blocktable = blocktable;
    uint8_t * pValues = malloc( sizeof(uint8_t) * grid_size * grid_size );
    for(uint8_t k = 0; k < grid_size * grid_size; k++) {
        pValues[k] = 0;
    }
    ptr->values = pValues;
    return ptr;
}

char * kenken_grid_get(Kenken * kenken, uint8_t i, uint8_t j) {
    return &kenken->grid[j*kenken->grid_size + i];
}

uint8_t * kenken_value_get(Kenken * kenken, uint8_t i, uint8_t j) {
    return &kenken->values[j*kenken->grid_size + i];
}

void kenken_value_set(Kenken * kenken, uint8_t i, uint8_t j, uint8_t val) {
    kenken->values[j*kenken->grid_size + i] = val;
}

uint8_t kenken_is_complete(Kenken * kenken) {
    for(uint8_t i = 0; i < kenken->grid_size * kenken->grid_size; i++) {
        if(kenken->values[i] == 0) { return 0; }
    }
    return 1;
}

uint8_t kenken_check_block(Kenken * kenken, char key) {
    Vector * pV = vector_create();
    uint8_t matches = 0;
    for(uint8_t i = 0; i < kenken->grid_size; i++) {
        for(uint8_t j = 0; j < kenken->grid_size; j++) {
            if( *kenken_grid_get(kenken, i, j) == key ) {
                matches += 1;
                uint16_t val = *kenken_value_get(kenken, i, j);
                if(val > 0) { vector_push(pV, val); }
            }
        }
    }
    if( matches != pV->size ) { // If block is not full, assume it is valid
        free(pV);
        return 1;
    }
    Block * pBlock = blocktable_get(kenken->blocktable, key);
    uint8_t ret = 0;
    if( pBlock->op == ADD) {
        uint16_t total = 0;
        for(uint8_t i = 0; i < pV->size; i++) {
            total += vector_get(pV, i);
        }
        if(total == pBlock->res) { ret = 1; }
    } else if ( pBlock->op == MUL ) {
        uint16_t total = 1;
        for(uint8_t i = 0; i < pV->size; i++) {
            total *= vector_get(pV, i);
        }
        if(total == pBlock->res) { ret = 1; }
    } else if ( pBlock->op == SUB ) {
        uint16_t v0 = vector_get(pV, 0);
        uint16_t v1 = vector_get(pV, 1);
        if(pBlock->res == (v0 - v1) || pBlock->res == (v1 - v0)) { ret = 1; }
    } else if( pBlock->op == DIV ) {
        uint16_t v0 = vector_get(pV, 0);
        uint16_t v1 = vector_get(pV, 1);
        if((pBlock->res == (v0 / v1) && v0 % v1 == 0) || (pBlock->res == (v1 / v0) && v1 % v0 == 0)) {
            ret = 1;
        }
    }
    free(pV);
    return ret;
}

uint8_t kenken_check_col(Kenken * kenken, uint8_t col) {
    for(uint8_t i = 0; i < kenken->grid_size; i++) {
        uint8_t val = *kenken_value_get(kenken, i, col);
        if(val == 0) {
            continue; // Ignore all zero values
        } else {
            for(uint8_t k = i + 1; k < kenken->grid_size; k++) {
                if( *kenken_value_get(kenken, k, col) == val ) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

uint8_t kenken_check_row(Kenken * kenken, uint8_t row) {
    for(uint8_t j = 0; j < kenken->grid_size; j++) {
        uint8_t val = *kenken_value_get(kenken, row, j);
        if(val == 0) {
            continue; // Ignore all zero values
        } else {
            for(uint8_t k = j + 1; k < kenken->grid_size; k++) {
                if( *kenken_value_get(kenken, row, k) == val ) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

uint8_t kenken_check_values(Kenken * kenken) {
    // Check Blocks
    for(uint8_t i = 0; i < kenken->blocktable->size; i++) {
        if(kenken_check_block(kenken, kenken->blocktable->blocks[i].key) == 0) { return 0; }
    }
    // Check Rows and Columns
    for(uint8_t k = 0; k < kenken->grid_size; k++) {
        if(kenken_check_row(kenken, k) == 0) { return 0; }
        if(kenken_check_col(kenken, k) == 0) { return 0; }
    }
    return 1;
}

void kenken_print_values(Kenken * kenken) {
    for(uint8_t j = 0; j < kenken->grid_size; j++) {
        printf("[");
        for(uint8_t i = 0; i < kenken->grid_size; i++) {
            printf("%d", *kenken_value_get(kenken, i, j));
            if( i < kenken->grid_size - 1 ) {
                printf(", ");
            } else {
                printf("]");
            }
        }
        printf("\n");
    }
}

void kenken_print_grid(Kenken * kenken) {
    for(uint8_t j = 0; j < kenken->grid_size; j++) {
        printf("[");
        for(uint8_t i = 0; i < kenken->grid_size; i++) {
            printf("%d", *kenken_grid_get(kenken, i, j));
            if( i < kenken->grid_size - 1 ) {
                printf(", ");
            } else {
                printf("]");
            }
        }
        printf("\n");
    }
}

uint8_t kenken_solve(Kenken * kenken) {
    for(uint8_t j = 0; j < kenken->grid_size; j++) {
        for(uint8_t i = 0; i < kenken->grid_size; i++) {
            if( *kenken_value_get(kenken, i, j) == 0) {
                for(uint8_t val = 1; val <= kenken->grid_size; val++) {
                    kenken_value_set(kenken, i, j, val);
                    if( kenken_check_values(kenken) > 0 ) {
                        if( kenken_is_complete(kenken) ) {
                            return 0;
                        } else {
                            if( kenken_solve(kenken) == 0 ) {
                                return 0;
                            } else {
                                kenken_value_set(kenken, i, j, 0);
                            }
                        }
                    } else {
                        kenken_value_set(kenken, i, j, 0);
                    }
                }
                return -1;
            }
        }
    }
    return 0;
}