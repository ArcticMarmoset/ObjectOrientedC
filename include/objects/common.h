#ifndef OBJECTS_COMMON_H
#define OBJECTS_COMMON_H

#define VA_ARGS(...) , ##__VA_ARGS__

typedef void (*ctor_pointer_type)();
typedef void (*dtor_pointer_type)();

struct object__vtable
{
    dtor_pointer_type destroy;
};

#endif
