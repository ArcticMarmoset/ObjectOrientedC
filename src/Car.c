#include "objects/Car.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BICYCLE_DEFAULT_NAME "Unknown Car"

static void        Car__Dtor(Car *this);
static void        Car__Start(Car *this);
static void        Car__Stop(Car *this);
static void        Car__Go(Car *this);
static const char *Car__GetName(Car *this);

static const struct IVehicle__vtable car_vtable =
{
    .Dtor = Car__Dtor,

    .Start   = (void (*)(IVehicle *))Car__Start,
    .Stop    = (void (*)(IVehicle *))Car__Stop,
    .Go      = (void (*)(IVehicle *))Car__Go,
    .GetName = (const char *(*)(IVehicle *))(void (*)(IVehicle *))Car__GetName,
};

void Car_Ctor(Car *this)
{
    this->vtable = &car_vtable;
    this->Name   = malloc(sizeof(BICYCLE_DEFAULT_NAME));
    memcpy(this->Name, BICYCLE_DEFAULT_NAME, sizeof(BICYCLE_DEFAULT_NAME));
}

void Car__Dtor(Car *this)
{
    free(this->Name);
}

void Car__Start(Car *this)
{
    printf("You turn the key in your %s\n", this->vtable->GetName((IVehicle *)this));
}

void Car__Stop(Car *this)
{
    printf("You set your %s to park\n", this->vtable->GetName((IVehicle *)this));
}

void Car__Go(Car *this)
{
    printf("You hit the gas in your %s\n", this->vtable->GetName((IVehicle *)this));
}

const char *Car__GetName(Car *this)
{
    return this->Name;
}
