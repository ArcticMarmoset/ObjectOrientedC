#include "objects/Bicycle.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BICYCLE_DEFAULT_NAME "Unknown Bicycle"

static void        Bicycle__Dtor(Bicycle *this);
static void        Bicycle__Start(Bicycle *this);
static void        Bicycle__Stop(Bicycle *this);
static void        Bicycle__Go(Bicycle *this);
static const char *Bicycle__GetName(Bicycle *this);

static const struct IVehicle__vtable bicycle_vtable =
{
    .Dtor = Bicycle__Dtor,

    .Start   = (void (*)(IVehicle *))Bicycle__Start,
    .Stop    = (void (*)(IVehicle *))Bicycle__Stop,
    .Go      = (void (*)(IVehicle *))Bicycle__Go,
    .GetName = (const char *(*)(IVehicle *))(void (*)(IVehicle *))Bicycle__GetName,
};

void Bicycle_Ctor(Bicycle *this)
{
    this->vtable = &bicycle_vtable;
    this->Name   = malloc(sizeof(BICYCLE_DEFAULT_NAME));
    memcpy(this->Name, BICYCLE_DEFAULT_NAME, sizeof(BICYCLE_DEFAULT_NAME));
}

void Bicycle__Dtor(Bicycle *this)
{
    free(this->Name);
}

void Bicycle__Start(Bicycle *this)
{
    printf("You hop on your %s\n", this->vtable->GetName((IVehicle *)this));
}

void Bicycle__Stop(Bicycle *this)
{
    printf("You hop off your %s\n", this->vtable->GetName((IVehicle *)this));
}

void Bicycle__Go(Bicycle *this)
{
    printf("You start pedaling on your %s\n", this->vtable->GetName((IVehicle *)this));
}

const char *Bicycle__GetName(Bicycle *this)
{
    return this->Name;
}
