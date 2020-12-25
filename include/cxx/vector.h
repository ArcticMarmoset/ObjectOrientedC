#ifndef CXX_VECTOR_H
#define CXX_VECTOR_H

#include "objects/common.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define CXX_VECTOR_EMPLACE_BACK(this, ...)                                               \
    {                                                                                    \
        const size_t offset = (this)->size * (this)->stride;                             \
        (this)->vtable->grow_one((this));                                                \
        void *const destination = (uint8_t *)(this)->data + offset;                      \
        if ((this)->element_ctor)                                                        \
        {                                                                                \
            ((ctor_pointer_type)(this)->element_ctor)(destination VA_ARGS(__VA_ARGS__)); \
        }                                                                                \
    }

typedef struct vector cxx_vector;

struct cxx_vector__vtable
{
    void         (*destroy)(cxx_vector *this);
    void         (*set_element_ctor)(cxx_vector *this, void *ctor);
    void         (*reserve)(cxx_vector *this, size_t size);
    void         (*grow_one)(cxx_vector *this);
    void         (*push_back)(cxx_vector *this, const void *element);
    void         (*pop_back)(cxx_vector *this);
    void *       (*at)(const cxx_vector *this, size_t index);
    size_t       (*size)(const cxx_vector *this);
    size_t       (*capacity)(const cxx_vector *this);
    void *       (*data)(cxx_vector *this);
    const void * (*data_const)(const cxx_vector *this);
};

struct vector
{
    const struct cxx_vector__vtable *vtable;

    void * element_ctor;

    bool   contains_objects;
    size_t capacity;
    size_t size;
    void * data;
    size_t stride;
};

void cxx_vector_init(cxx_vector *this, size_t stride, bool objects);

#endif
