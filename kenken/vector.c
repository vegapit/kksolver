#include "vector.h"
#include <stdint.h>
#include <stdlib.h>

Vector * vector_create() {
    Vector * pV = malloc( sizeof(Vector) );
    pV->size = 0;
    pV->values = NULL;
    return pV;
}
void vector_push(Vector * vector, uint16_t value) {
    vector->values = realloc( vector->values, (vector->size + 1) * sizeof( uint8_t ) );
    vector->values[vector->size] = value;
    vector->size++;
}

uint16_t vector_get(Vector * vector, uint8_t index) {
    return vector->values[index];
}