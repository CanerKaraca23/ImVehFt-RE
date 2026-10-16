#pragma once
#include "common.h"

class CHooks {
public:
    static void InstallEarlyHooks();
    static void ApplyAllPatches();

    static void OnGraphicsInit();
    static void* OnVehiclePreRender(void* pVehicle);
    static void OnProcessVehicleLights(void* pVehicle);
    static void OnVehicleBlowUp(void* pVehicle);
    static void OnDriverEnter(void* pVehicle);
    static void OnDriverExit(void* pVehicle);
    static void OnWeatherChange();
};
