#ifndef OBJECTS_CAR_H
#define OBJECTS_CAR_H

#include "objects/IVehicle.h"

typedef struct Car Car;

struct Car
{
    const struct IVehicle__vtable *vtable;
    char *Name;
};

void Car_Ctor(Car *this);

#endif
