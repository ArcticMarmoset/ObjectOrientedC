#include "containers/vector.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void   vector__reserve(vector *this, size_t size);
static void   vector__push_back(vector *this, const void *element);
static void * vector__at(const vector *this, size_t index);
static size_t vector__size(const vector *this);
static size_t vector__capacity(const vector *this);

static void   vector__grow(vector *this, size_t capacity);

static struct vector__vtable vector_vtable =
{
    .reserve    = vector__reserve,
    .push_back  = vector__push_back,
    .at         = vector__at,
    .size       = vector__size,
    .capacity   = vector__capacity,
};

void vector__init(vector *this, size_t stride)
{
    this->capacity = 0;
    this->count    = 0;
    this->stride   = stride;
    this->data     = NULL;
    this->vtable   = &vector_vtable;
}

void vector__reserve(vector *this, size_t size)
{
    vector__grow(this, size);
}

void vector__push_back(vector *this, const void *element)
{
    const size_t offset = this->count++ * this->stride;

    if (this->count > this->capacity)
    {
        vector__grow(this, this->capacity * 2);
    }

    void *const destination = (uint8_t *)this->data + offset;
    memcpy(destination, element, this->stride);
}

void *vector__at(const vector *this, size_t index)
{
    assert("Attempted to access out-of-bounds index" && (index < this->count));
    const size_t offset = index * this->stride;
    return (void *)((uint8_t *)this->data + offset);
}

size_t vector__size(const vector *this)
{
    return this->count;
}

size_t vector__capacity(const vector *this)
{
    return this->capacity;
}

void vector__grow(vector *this, size_t capacity)
{
    if (capacity < this->capacity)
    {
        return;
    }

    if (capacity == 0) capacity = 1;

    this->capacity = capacity;
    void *newAddress = realloc(this->data, this->capacity * this->stride);

    if (!newAddress)
    {
        abort();
    }

    this->data = newAddress;
}
