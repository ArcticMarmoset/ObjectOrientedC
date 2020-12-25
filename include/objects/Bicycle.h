#ifndef OBJECTS_BYCICLE_H
#define OBJECTS_BYCICLE_H

#include "objects/IVehicle.h"

typedef struct Bicycle Bicycle;

struct Bicycle
{
    const struct IVehicle__vtable *vtable;
    char *Name;
};

void Bicycle_Ctor(Bicycle *this);

#endif
