#pragma once
#include "common.h"
#include "VehicleData.h"

class CSteeringWheel {
public:
    static void Update(void* pVehicle);
    static void UpdateBrakeCalipers(void* pVehicle);
    static void UpdateSpoilers(void* pVehicle);
    static void UpdateExtras(void* pVehicle);
};
