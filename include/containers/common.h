#ifndef CONTAINERS_COMMON_H
#define CONTAINERS_COMMON_H

#define VA_ARGS(...) , ##__VA_ARGS__

typedef void * ctor_pointer_type;
typedef void * dtor_pointer_type;

struct object__vtable
{
    void (*destroy)();
};

#endif
