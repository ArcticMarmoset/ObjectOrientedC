#ifndef INHERITANCE_VEHICLE_H
#define INHERITANCE_VEHICLE_H

#include "common.h"

typedef struct IVehicle IVehicle;

struct IVehicle__vtable
{
    dtor_pointer_type Dtor;

    void         (*Start)(IVehicle *this);
    void         (*Stop)(IVehicle *this);
    void         (*Go)(IVehicle *this);
    const char * (*GetName)(IVehicle *this);
};

struct IVehicle
{
    const struct IVehicle__vtable *vtable;
};

#endif
