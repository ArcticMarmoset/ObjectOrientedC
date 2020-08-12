#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct vector vector;

struct vector__vtable
{
    void   (*reserve)(vector *this, size_t size);
    void   (*push_back)(vector *this, const void *element);
    void * (*at)(const vector *this, size_t index);
    size_t (*size)(const vector *this);
    size_t (*capacity)(const vector *this);
};

struct vector
{
    size_t capacity;
    size_t count;
    void * data;
    size_t stride;

    struct vector__vtable *vtable;
};

void vector__init(vector *this, size_t stride);

#endif
