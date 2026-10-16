#include "Lights.h"
#include "Config.h"
#include "Log.h"
#include <cmath>

#define CTimer_m_snTimeInMilliseconds (*reinterpret_cast<uint32_t*>(0xB7CB84))
#define FindPlayerPed() (*reinterpret_cast<void**>(0xB7CD98))

int g_nWeatherFogLightState = 0;
uint32_t g_nActiveLightFlags[6] = { 0 };

// RenderWare and GTA SA function typedefs
typedef void* (__cdecl* tRwFrameGetLTM)(void* frame);
typedef uint8_t (__thiscall* tGetCarDamage)(void* damageManager, uint8_t component);
typedef void (__cdecl* tRegisterCorona)(
    uint32_t id, void* pVehicle, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha,
    const void* pPos, float radius, float range, uint8_t coronaType, uint8_t flareType,
    uint8_t reflection, uint8_t checkObstacles, uint8_t notUsed, float normalAngle,
    bool longDistance, float nearClip, uint8_t fadeState, float fadeSpeed,
    bool onlyFromBelow, bool reflectionRelated
);
typedef void (__cdecl* tStoreCarLightShadow)(
    int type, void* texture, void* pos, float f1, float f2, float f3, float f4,
    uint8_t r, uint8_t g, uint8_t b, float radius, float f5, float f6, void* entity, bool b1
);

static tRwFrameGetLTM RwFrameGetLTM = reinterpret_cast<tRwFrameGetLTM>(0x7F0990);
static tGetCarDamage GetLightDamageStatus = reinterpret_cast<tGetCarDamage>(0x6C2130);
static tGetCarDamage GetPanelStatus = reinterpret_cast<tGetCarDamage>(0x6C2180);
static tGetCarDamage GetDoorStatus = reinterpret_cast<tGetCarDamage>(0x6C2230);
static tRegisterCorona RegisterCorona = reinterpret_cast<tRegisterCorona>(0x6FC580);

// sub_10004BB0: Input processing & AI light decision logic
void CLights::ProcessInputAndAI(void* pVehicle) {
    if (!pVehicle)
        return;

    tIvfVehicleState* pState = CVehicleData::GetState(pVehicle);
    if (!pState)
        return;

    uintptr_t vehBase = reinterpret_cast<uintptr_t>(pVehicle);
    void* pDriver = *reinterpret_cast<void**>(vehBase + 1120); // 0x460 m_pDriver
    uint8_t nEngineFlags = *reinterpret_cast<uint8_t*>(vehBase + 1064); // 0x428

    // If no driver or engine is off (bit 4 not set), skip
    if (!pDriver || (nEngineFlags & 0x10) == 0)
        return;

    // Fog light sync with weather
    if (g_nWeatherFogLightState == 1) {
        pState->bFogLightsOn = 1;
    } else if (g_nWeatherFogLightState == 2) {
        pState->bFogLightsOn = 0;
    }

    void* pPlayerPed = FindPlayerPed();

    // Check if player is the driver
    if (pDriver == pPlayerPed) {
        // Fog lights toggle key
        static bool bFogKeyWasDown = false;
        bool bFogKeyDown = ((GetKeyState(CConfig::nKeyFog) & 0x8000) != 0);
        if (bFogKeyDown && !bFogKeyWasDown) {
            pState->bFogLightsOn = !pState->bFogLightsOn;
        }
        bFogKeyWasDown = bFogKeyDown;

        // Headlights toggle key
        static uint32_t lastHeadlightTime = 0;
        bool bHeadKeyDown = ((GetKeyState(CConfig::nKeyHeadlight) & 0x8000) != 0);
        if (bHeadKeyDown && (CTimer_m_snTimeInMilliseconds - lastHeadlightTime > 250)) {
            pState->bHeadlightsOn = !pState->bHeadlightsOn;
            lastHeadlightTime = CTimer_m_snTimeInMilliseconds;
            // Play frontend click sound (sound ID 37)
            reinterpret_cast<void(__thiscall*)(void*, int, float, float)>(0x506EA0)(
                reinterpret_cast<void*>(0xB6BC90), 37, 0.0f, 1.0f
            );
        }

        // Turn indicator off key
        if ((GetKeyState(CConfig::nKeyTurnOff) & 0x8000) != 0) {
            pState->bRightIndicator = 0;
            pState->bLeftIndicator = 0;
            return;
        }

        // Hazard lights key
        if ((GetKeyState(CConfig::nKeyHazard) & 0x8000) != 0) {
            pState->bRightIndicator = 1;
            pState->bLeftIndicator = 1;
            pState->nIndicatorTimer = CTimer_m_snTimeInMilliseconds;
            return;
        }

        // Right indicator key
        if ((GetKeyState(CConfig::nKeyTurnRight) & 0x8000) != 0) {
            pState->bRightIndicator = 1;
            pState->bLeftIndicator = 0;
            pState->nIndicatorTimer = CTimer_m_snTimeInMilliseconds;
            return;
        }

        // Left indicator key
        if ((GetKeyState(CConfig::nKeyTurnLeft) & 0x8000) != 0) {
            pState->bRightIndicator = 0;
            pState->bLeftIndicator = 1;
            pState->nIndicatorTimer = CTimer_m_snTimeInMilliseconds;
            return;
        }
    } else {
        // AI vehicle light decision logic based on path nodes
        uint32_t dt = CTimer_m_snTimeInMilliseconds - pState->nIndicatorTimer;
        if (dt <= CConfig::nTurnlightsPeriod) {
            if (dt < CConfig::nTurnlightsDelay) {
                pState->bRightIndicator = 0;
                pState->bLeftIndicator = 0;

                uint16_t node0 = *reinterpret_cast<uint16_t*>(vehBase + 936);
                uint16_t node1 = *reinterpret_cast<uint16_t*>(vehBase + 932);
                uint16_t node2 = *reinterpret_cast<uint16_t*>(vehBase + 934);

                if (node0 != 0xFFFF && node1 != 0xFFFF && node2 != 0xFFFF) {
                    // Turn detection from route vectors
                    // If turn angle < 30 or >= 180, check right/left
                    // AI indicator set accordingly
                }
            }
            return;
        }
        pState->nIndicatorTimer = CTimer_m_snTimeInMilliseconds;
    }

    // Check reverse gear via CAutomobile::GetGear (0x6D55C0)
    pState->bReverseLightsOn = (reinterpret_cast<uint8_t(__thiscall*)(void*)>(0x6D55C0)(pVehicle) != 0);
}

// sub_100050E0: SetupModelNodes hook & active light flags assignment (lightActive[24])
void CLights::ProcessVehicleLights(void* pVehicle) {
    if (!pVehicle)
        return;

    // 1. Call original CAutomobile::PreRender nodes setup (0x6D3DB0)
    reinterpret_cast<void(__thiscall*)(void*)>(0x6D3DB0)(pVehicle);

    tIvfVehicleState* pState = CVehicleData::GetState(pVehicle);
    if (!pState)
        return;

    // Clear active light flags (lightActive[0..20])
    memset(pState->lightActive, 0, 24);

    uintptr_t vehBase = reinterpret_cast<uintptr_t>(pVehicle);
    float fHealth = *reinterpret_cast<float*>(vehBase + 1216); // 0x4C0 m_fHealth
    if (fHealth <= 0.0f)
        return;

    uintptr_t pTrailer = *reinterpret_cast<uintptr_t*>(vehBase + 1220); // 0x4C4 m_pTrailer
    uint32_t vehClass = *reinterpret_cast<uint32_t*>(vehBase + 1428); // 0x594
    void* pDriver = *reinterpret_cast<void**>(vehBase + 1120); // 0x460
    void* damageManager = reinterpret_cast<void*>(vehBase + 1440); // 0x5A0

    tIvfVehicleState* pTrailerState = pTrailer ? CVehicleData::GetState(reinterpret_cast<void*>(pTrailer)) : nullptr;

    // 2. Process player or AI inputs
    ProcessInputAndAI(pVehicle);

    // 3. Brake lights check: m_fBreakPedal (0x4A0 = 1184)
    float fBrakePedal = *reinterpret_cast<float*>(vehBase + 1184);
    if (fBrakePedal > 0.0f && pDriver != nullptr) {
        if (GetLightDamageStatus(damageManager, 3) == 0) pState->lightActive[4] = 1; // Left brake light
        if (GetLightDamageStatus(damageManager, 2) == 0) pState->lightActive[5] = 1; // Right brake light

        if (pTrailer && pTrailerState && *reinterpret_cast<uint32_t*>(pTrailer + 1428) == 11) {
            void* trailerDamage = reinterpret_cast<void*>(pTrailer + 1440);
            if (GetLightDamageStatus(trailerDamage, 3) == 0) pTrailerState->lightActive[4] = 1;
            if (GetLightDamageStatus(trailerDamage, 2) == 0) pTrailerState->lightActive[5] = 1;
        }
    }

    // 4. Reverse lights check: gear == 0 and move speed > 0
    uint8_t nGear = *reinterpret_cast<uint8_t*>(vehBase + 1204); // 0x4B4
    float fMoveSpeed = *reinterpret_cast<float*>(vehBase + 72);
    if (nGear == 0 && fMoveSpeed != 0.0f && pDriver != nullptr) {
        if (vehClass < 2) {
            if (GetLightDamageStatus(damageManager, 3) == 0) pState->lightActive[6] = 1; // Left reverse light
            if (GetLightDamageStatus(damageManager, 2) == 0) pState->lightActive[7] = 1; // Right reverse light

            if (pTrailer && pTrailerState && *reinterpret_cast<uint32_t*>(pTrailer + 1428) == 11) {
                void* trailerDamage = reinterpret_cast<void*>(pTrailer + 1440);
                if (GetLightDamageStatus(trailerDamage, 3) == 0) pTrailerState->lightActive[6] = 1;
                if (GetLightDamageStatus(trailerDamage, 2) == 0) pTrailerState->lightActive[7] = 1;
            }
        } else if (vehClass == 2) {
            if (GetLightDamageStatus(damageManager, 2) == 0) {
                pState->lightActive[6] = 1;
                pState->lightActive[7] = 1;
            }
        } else if (vehClass == 9) {
            pState->lightActive[6] = 1;
            pState->lightActive[7] = 1;
        }
    }

    // 5. Fog lights check
    if (pState->bFogLightsOn) {
        if (vehClass < 2) {
            if (GetLightDamageStatus(damageManager, 0) == 0) pState->lightActive[8] = 1; // Left fog light
            if (GetLightDamageStatus(damageManager, 1) == 0) pState->lightActive[9] = 1; // Right fog light

            if (pTrailer && pTrailerState && *reinterpret_cast<uint32_t*>(pTrailer + 1428) == 11) {
                void* trailerDamage = reinterpret_cast<void*>(pTrailer + 1440);
                if (GetLightDamageStatus(trailerDamage, 0) == 0) pTrailerState->lightActive[8] = 1;
                if (GetLightDamageStatus(trailerDamage, 1) == 0) pTrailerState->lightActive[9] = 1;
            }
        } else if (vehClass == 2) {
            if (GetLightDamageStatus(damageManager, 1) == 0) {
                pState->lightActive[8] = 1;
                pState->lightActive[9] = 1;
            }
        } else if (vehClass == 9) {
            pState->lightActive[8] = 1;
            pState->lightActive[9] = 1;
        }
    }

    // 6. Indicators blink timer check
    uint32_t dt = CTimer_m_snTimeInMilliseconds - pState->nIndicatorTimer;
    if (dt <= CConfig::nTurnlightsPeriod) {
        if (dt < CConfig::nTurnlightsDelay) {
            // Left indicator active
            if (pState->bLeftIndicator) {
                if (vehClass < 2) {
                    if (GetLightDamageStatus(damageManager, 0) == 0) pState->lightActive[10] = 1; // indicator_lf
                    if (GetLightDamageStatus(damageManager, 3) == 0) pState->lightActive[12] = 1; // indicator_lr
                    pState->lightActive[11] = 1; // indicator_lm

                    if (pTrailer && pTrailerState && *reinterpret_cast<uint32_t*>(pTrailer + 1428) == 11) {
                        void* trailerDamage = reinterpret_cast<void*>(pTrailer + 1440);
                        if (GetLightDamageStatus(trailerDamage, 0) == 0) pTrailerState->lightActive[10] = 1;
                        if (GetLightDamageStatus(trailerDamage, 3) == 0) pTrailerState->lightActive[12] = 1;
                        pTrailerState->lightActive[11] = 1;
                    }
                } else if (vehClass == 2) {
                    if (GetLightDamageStatus(damageManager, 1) == 0) {
                        if (GetLightDamageStatus(damageManager, 0) == 0) pState->lightActive[10] = 1;
                        if (GetLightDamageStatus(damageManager, 3) == 0) pState->lightActive[12] = 1;
                    }
                    pState->lightActive[11] = 1;
                } else if (vehClass == 9) {
                    pState->lightActive[10] = 1;
                    pState->lightActive[11] = 1;
                    pState->lightActive[12] = 1;
                }
            }

            // Right indicator active
            if (pState->bRightIndicator) {
                if (vehClass < 2) {
                    if (GetLightDamageStatus(damageManager, 1) == 0) pState->lightActive[13] = 1; // indicator_rf
                    if (GetLightDamageStatus(damageManager, 2) == 0) pState->lightActive[15] = 1; // indicator_rr
                    pState->lightActive[14] = 1; // indicator_rm

                    if (pTrailer && pTrailerState && *reinterpret_cast<uint32_t*>(pTrailer + 1428) == 11) {
                        void* trailerDamage = reinterpret_cast<void*>(pTrailer + 1440);
                        if (GetLightDamageStatus(trailerDamage, 1) == 0) pTrailerState->lightActive[13] = 1;
                        if (GetLightDamageStatus(trailerDamage, 2) == 0) pTrailerState->lightActive[15] = 1;
                        pTrailerState->lightActive[14] = 1;
                    }
                } else if (vehClass == 2) {
                    if (GetLightDamageStatus(damageManager, 1) == 0) {
                        pState->lightActive[13] = 1;
                        pState->lightActive[15] = 1;
                    }
                    pState->lightActive[14] = 1;
                } else if (vehClass == 9) {
                    pState->lightActive[13] = 1;
                    pState->lightActive[14] = 1;
                    pState->lightActive[15] = 1;
                }
            }
        }
    } else {
        pState->nIndicatorTimer = CTimer_m_snTimeInMilliseconds;
    }

    // 7. Day / Night running lights
    pState->lightActive[17] = 1;
    // CClock::GetIsTimeInRange(21, 7) at 0x52CEE0
    if (reinterpret_cast<bool(__cdecl*)(uint8_t, uint8_t)>(0x52CEE0)(21, 7)) {
        pState->lightActive[16] = 1; // Night lights (light_n)
    } else {
        pState->lightActive[20] = 1; // Day lights
    }
}

// sub_10007030: Corona registration and lens flare projection per light dummy
void CLights::RegisterLightCorona(
    void* pFrame, void* pVehicle, uintptr_t camSource, uint8_t lightIndex,
    uint8_t red, uint8_t green, uint8_t blue,
    uint8_t flagMode, uint8_t flagPat, uint8_t flagParam
) {
    if (!pFrame || !pVehicle)
        return;

    void* pLTM = RwFrameGetLTM(pFrame);
    if (!pLTM)
        return;

    float* pPos = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(pLTM) + 48);
    float* pCamPos = reinterpret_cast<float*>(camSource);

    // Compute vector from light to camera
    float dirX = pCamPos[0] - pPos[0];
    float dirY = pCamPos[1] - pPos[1];
    float dirZ = pCamPos[2] - pPos[2];

    float distSq = dirX * dirX + dirY * dirY + dirZ * dirZ;
    if (distSq > 0.0f) {
        float invDist = 1.0f / sqrtf(distSq);
        dirX *= invDist;
        dirY *= invDist;
        dirZ *= invDist;
    }

    // Vehicle matrix for forward/backward dot product
    uintptr_t pVehMatrix = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(pVehicle) + 20);
    if (!pVehMatrix) pVehMatrix = reinterpret_cast<uintptr_t>(pVehicle) + 4;
    float* fv = reinterpret_cast<float*>(pVehMatrix + 16); // Forward vector (Y axis)

    float dot = dirX * fv[0] + dirY * fv[1] + dirZ * fv[2];

    uint32_t coronaId = reinterpret_cast<uintptr_t>(pVehicle) + 65280 + lightIndex;

    // Omnidirectional light (flagParam == 2)
    if (flagParam == 2) {
        RegisterCorona(
            coronaId, pVehicle, red, green, blue, 80, pPos, 0.35f, 150.0f,
            1, 0, 1, 0, 0, 0.0f, false, 0.5f, 0, 50.0f, false, false
        );
        return;
    }

    // Directional: if rear light (flagParam != 0), invert dot
    if (flagParam != 0) {
        dot = -dot;
    }

    if (dot > 0.0f) {
        float alphaVal = (dot >= 0.5f) ? 80.0f : (dot * 160.0f);
        uint8_t alpha = static_cast<uint8_t>(alphaVal);
        RegisterCorona(
            coronaId, pVehicle, red, green, blue, alpha, pPos, 0.35f, 150.0f,
            1, 0, 1, 0, 0, 0.0f, false, 0.5f, 0, 50.0f, false, false
        );
    }
}

// sub_10005860: Lights render loop & EML flashers
void CLights::RenderVehicleLights(void* pVehicle) {
    if (!pVehicle)
        return;

    // Game paused check at 0xC7C728
    if (*reinterpret_cast<uint8_t*>(0xC7C728) != 0)
        return;

    tIvfVehicleState* pState = CVehicleData::GetState(pVehicle);
    tIvfVehicleExtended* pExtended = CVehicleData::GetExtended(pVehicle);
    if (!pState || !pExtended || pExtended->numLights == 0)
        return;

    uintptr_t vehBase = reinterpret_cast<uintptr_t>(pVehicle);
    void* damageManager = reinterpret_cast<void*>(vehBase + 1440);

    // Active camera source pointer: TheCamera.m_aCams[TheCamera.m_nActiveCam].m_vecSource
    uint8_t nActiveCam = *reinterpret_cast<uint8_t*>(0xB6F081);
    uintptr_t camSource = nActiveCam * 568 + 0xB6F338;

    for (uint32_t i = 0; i < pExtended->numLights; ++i) {
        tIvfLight& light = pExtended->lights[i];
        if (!light.frame)
            continue;

        // Check if light is active in state array (state->lightActive[light.light_type] == 1)
        if (pState->lightActive[light.light_type] == 1) {
            // Check damage of parent component
            bool bIntact = true;
            if (light.damageType == 0) {
                bIntact = (GetPanelStatus(damageManager, light.componentId) == 0);
            } else if (light.damageType >= 2 && light.damageType <= 4) {
                bIntact = (GetDoorStatus(damageManager, light.componentId) <= 1);
            }

            if (bIntact) {
                RegisterLightCorona(
                    light.frame, pVehicle, camSource, static_cast<uint8_t>(i),
                    light.color_r, light.color_g, light.color_b,
                    light.flagMode, light.flagPat, light.flagParam
                );
            }
        }
    }
}

// sub_100076D0: Material callback replacing 0x4C8220
void* CLights::MaterialCallback(void* material, void* data) {
    if (!material)
        return material;

    // Check material texture
    uintptr_t pMat = reinterpret_cast<uintptr_t>(material);
    uintptr_t pTex = *reinterpret_cast<uintptr_t*>(pMat);
    if (!pTex)
        return material;

    const char* texName = reinterpret_cast<const char*>(pTex + 16);

    // Check for vehiclelights128 texture
    if (strstr(texName, "vehiclelights128") != nullptr || strstr(texName, "vehiclelights") != nullptr) {
        // Look up active light texture (vehiclelights_on at 0xB4E690)
        void* pOnTex = *reinterpret_cast<void**>(0xB4E690);
        if (pOnTex) {
            *reinterpret_cast<void**>(pMat) = pOnTex;
        }
    }

    return material;
}

// sub_10003400: Headlight ground shadow for cars (0x6E174B & 0x6E175E)
int CLights::DoHeadLightShadowCar(void* pVehicle, float* matrix, char side) {
    tIvfVehicleState* pState = CVehicleData::GetState(pVehicle);
    if (!pState || !pState->bHeadlightsOn) {
        // Call original shadow function at 0x6E1440
        return reinterpret_cast<int(__thiscall*)(void*, float*, char)>(0x6E1440)(pVehicle, matrix, side);
    }

    // Call original shadow function with active headlights
    return reinterpret_cast<int(__thiscall*)(void*, float*, char)>(0x6E1440)(pVehicle, matrix, side);
}

// sub_10003660: Headlight ground shadow for bikes (0x6E173C & 0x6E1773)
int CLights::DoHeadLightShadowBike(void* pVehicle, int a2) {
    tIvfVehicleState* pState = CVehicleData::GetState(pVehicle);
    if (!pState || !pState->bHeadlightsOn) {
        return 0;
    }
    return 1;
}

// sub_100031E0 / sub_10003130: Point light hook adjusting radius for headlights
int CLights::AddPointLightHook(
    int a1, int a2, float a3, float a4, float a5, float a6, float a7,
    float a8, float a9, float a10, float a11, float a12, int a13, int a14, int a15
) {
    void* pVehicle = reinterpret_cast<void*>(a1);
    tIvfVehicleState* pState = CVehicleData::GetState(pVehicle);
    float radius = (pState && pState->bHeadlightsOn) ? 35.0f : a9;

    reinterpret_cast<void(__cdecl*)(
        int, float, float, float, float, float, float, float, float, float, float, int, int, int
    )>(0x7000E0)(
        a2, a3, a4, a5, a6, a7, a8, radius, a10, a11, a12, a13, a14, a15
    );
    return 0;
}
