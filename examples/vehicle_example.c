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
    vehicle->vtable->Start(vehicle); // "You turn the key in your Unknown Car"
    vehicle->vtable->Go(vehicle);    // "You set your Unknown Car to park"
    vehicle->vtable->Stop(vehicle);  // "You hit the gas in your Unknown Car"
    vehicle->vtable->Dtor(vehicle);
    free(vehicle);
    {
        Bicycle *bicycle = malloc(sizeof(Bicycle));
        Bicycle_Ctor(bicycle);
        vehicle = (IVehicle *)bicycle;
    }
    vehicle->vtable->Start(vehicle); // "You hop on your Unknown Bicycle"
    vehicle->vtable->Go(vehicle);    // "You start pedaling on your Unknown Bicycle"
    vehicle->vtable->Stop(vehicle);  // "You hop off your Unknown Bicycle"
    vehicle->vtable->Dtor(vehicle);
    free(vehicle);
}
