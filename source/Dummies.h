#pragma once
#include "common.h"
#include "VehicleData.h"

class CDummies {
public:
    static void AttachDummyToVehiclePart(void* pData);
    static bool ParseLightDummy(void* pFrame, tIvfVehicleExtended* pExtended);
    static void* __cdecl FindDummiesCallback(void* pFrame, void* pData);
    static int SetupModelNodes(void* pVehicle, int a2);
};
