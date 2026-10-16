#pragma once
#include "common.h"
#include "VehicleData.h"

extern int g_nWeatherFogLightState;
extern uint32_t g_nActiveLightFlags[6];

class CLights {
public:
    static void ProcessInputAndAI(void* pVehicle);
    static void ProcessVehicleLights(void* pVehicle);
    static void RenderVehicleLights(void* pVehicle);
    static void RegisterLightCorona(
        void* pFrame, void* pVehicle, uintptr_t camSource, uint8_t lightIndex,
        uint8_t red, uint8_t green, uint8_t blue,
        uint8_t flagMode, uint8_t flagPat, uint8_t flagParam
    );
    static void* MaterialCallback(void* material, void* data);
    static int DoHeadLightShadowCar(void* pVehicle, float* matrix, char side);
    static int DoHeadLightShadowBike(void* pVehicle, int a2);
    static int AddPointLightHook(
        int a1, int a2, float a3, float a4, float a5, float a6, float a7,
        float a8, float a9, float a10, float a11, float a12, int a13, int a14, int a15
    );
};
