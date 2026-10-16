#pragma once
#include "common.h"

class CCustomPlates {
private:
    static void* m_pPlateCharsetTexture;
    static void* m_pPlateBackTextures[4];
    static bool m_bInitialised;

public:
    static void Initialise();
    static void Shutdown();
    static void RenderPlate(void* pVehicle, void* pMaterial);
};
