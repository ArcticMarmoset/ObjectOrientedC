#include <objects/Car.h>
#include <objects/Bicycle.h>

#include <stddef.h>
#include <stdlib.h>

int main(void)
{
    IVehicle *vehicle = NULL;
    {
        Car *car = malloc(sizeof(Car));
        Car_Ctor(car);
        vehicle = (IVehicle *)car;
    }
    vehicle->vtable->Start(vehicle);
    vehicle->vtable->Go(vehicle);
    vehicle->vtable->Stop(vehicle);
    vehicle->vtable->Dtor(vehicle);
    free(vehicle);
    {
        Bicycle *bicycle = malloc(sizeof(Bicycle));
        Bicycle_Ctor(bicycle);
        vehicle = (IVehicle *)bicycle;
    }
    vehicle->vtable->Start(vehicle);
    vehicle->vtable->Go(vehicle);
    vehicle->vtable->Stop(vehicle);
    vehicle->vtable->Dtor(vehicle);
    free(vehicle);
}
