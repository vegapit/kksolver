#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint8_t size;
    uint16_t * values;
} Vector;

Vector * vector_create();
void vector_push(Vector * vector, uint16_t value);
uint16_t vector_get(Vector * vector, uint8_t index);

#endif