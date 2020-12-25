#include "cxx/vector.h"

#include <assert.h>
#include <string.h>

// Public
static void         cxx_vector__destroy(cxx_vector *this);

static void         cxx_vector__set_element_ctor(cxx_vector *this, void *ctor);

static void         cxx_vector__reserve(cxx_vector *this, size_t size);
static void         cxx_vector__grow_one(cxx_vector *this);
static void         cxx_vector__push_back(cxx_vector *this, const void *element);
static void         cxx_vector__pop_back(cxx_vector *this);
static void *       cxx_vector__at(const cxx_vector *this, size_t index);
static size_t       cxx_vector__size(const cxx_vector *this);
static size_t       cxx_vector__capacity(const cxx_vector *this);
static void *       cxx_vector__data(cxx_vector *this);
static const void * cxx_vector__data_const(const cxx_vector *this);

// Private
static void cxx_vector__grow(cxx_vector *this, size_t capacity);

// Implementations
static const struct cxx_vector__vtable vector_vtable =
{
    .destroy      = cxx_vector__destroy,

    .set_element_ctor = cxx_vector__set_element_ctor,

    .reserve      = cxx_vector__reserve,
    .grow_one     = cxx_vector__grow_one,
    .push_back    = cxx_vector__push_back,
    .pop_back     = cxx_vector__pop_back,
    .at           = cxx_vector__at,
    .size         = cxx_vector__size,
    .capacity     = cxx_vector__capacity,
    .data         = cxx_vector__data,
    .data_const   = cxx_vector__data_const,
};

void cxx_vector_init(cxx_vector *this, size_t stride, bool objects)
{
    this->vtable       = &vector_vtable;

    this->element_ctor = NULL;

    this->contains_objects = objects;
    this->capacity         = 0;
    this->size             = 0;
    this->stride           = stride;
    this->data             = NULL;
}

void cxx_vector__destroy(cxx_vector *this)
{
    if (this->contains_objects)
    {
        for (size_t i = 0; i < this->size; i++)
        {
            void *element = this->vtable->at(this, i);
            struct object__vtable **table = element;
            (*table)->destroy(element);
        }
    }
    free(this->data);
}

static void cxx_vector__set_element_ctor(cxx_vector *this, void *ctor)
{
    this->element_ctor = ctor;
}

void cxx_vector__reserve(cxx_vector *this, size_t size)
{
    cxx_vector__grow(this, size);
}

void cxx_vector__grow_one(cxx_vector *this)
{
    ++this->size;

    if (this->size > this->capacity)
    {
        cxx_vector__grow(this, this->capacity * 2);
    }
}

void cxx_vector__push_back(cxx_vector *this, const void *element)
{
    const size_t offset = this->size * this->stride;
    this->vtable->grow_one(this);
    void *const destination = (uint8_t *)this->data + offset;
    memcpy(destination, element, this->stride);
}

void cxx_vector__pop_back(cxx_vector *this)
{
    --this->size;
}

void *cxx_vector__at(const cxx_vector *this, size_t index)
{
    assert("`index` is within array bounds" && (index < this->size));
    const size_t offset = index * this->stride;
    return (void *)((uint8_t *)this->data + offset);
}

size_t cxx_vector__size(const cxx_vector *this)
{
    return this->size;
}

size_t cxx_vector__capacity(const cxx_vector *this)
{
    return this->capacity;
}

void cxx_vector__grow(cxx_vector *this, size_t capacity)
{
    if (capacity < this->capacity)
    {
        return;
    }

    if (capacity == 0) capacity = 1;

    this->capacity = capacity;
    void *new_address = realloc(this->data, this->capacity * this->stride);

    if (!new_address)
    {
        abort();
    }

    this->data = new_address;
}

void *cxx_vector__data(cxx_vector *this)
{
    return this->data;
}

const void *cxx_vector__data_const(const cxx_vector *this)
{
    return this->data;
}
