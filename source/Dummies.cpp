#include "Dummies.h"
#include "EML.h"
#include "Config.h"
#include "Log.h"
#include <cstring>
#include <cstdio>

// RenderWare and GTA function typedefs
typedef const char* (__cdecl* tGetFrameNodeName)(void* frame);
typedef void* (__cdecl* tRwFrameForAllChildren)(void* frame, void* (__cdecl* callback)(void*, void*), void* data);

static tGetFrameNodeName GetFrameNodeName = reinterpret_cast<tGetFrameNodeName>(0x72FB30);
static tRwFrameForAllChildren RwFrameForAllChildren = reinterpret_cast<tRwFrameForAllChildren>(0x7F0DC0);

// sub_10004000: Assigns damage tracking component ID & type to dummy structure
void CDummies::AttachDummyToVehiclePart(void* pData) {
    uint8_t* a1 = reinterpret_cast<uint8_t*>(pData);
    void* frame = *reinterpret_cast<void**>(a1);
    if (!frame) return;

    void* parentFrame = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(frame) + 4);
    if (!parentFrame) {
        a1[4] = 6;
        return;
    }

    const char* v1 = GetFrameNodeName(parentFrame);
    if (!v1) {
        a1[4] = 6;
        return;
    }

    if (strncmp(v1, "dummy", 5) == 0) {
        void* grandParentFrame = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(parentFrame) + 4);
        if (grandParentFrame) {
            const char* gName = GetFrameNodeName(grandParentFrame);
            if (gName) v1 = gName;
        }
    }

    if (strcmp(v1, "door_rf_dummy") == 0) {
        *reinterpret_cast<uint16_t*>(a1 + 4) = 770;
    } else if (strcmp(v1, "door_lf_dummy") == 0) {
        *reinterpret_cast<uint16_t*>(a1 + 4) = 514;
    } else if (strcmp(v1, "door_rr_dummy") == 0) {
        *reinterpret_cast<uint16_t*>(a1 + 4) = 1282;
    } else if (strcmp(v1, "door_lr_dummy") == 0) {
        *reinterpret_cast<uint16_t*>(a1 + 4) = 1026;
    } else if (strcmp(v1, "bonnet_dummy") == 0) {
        *reinterpret_cast<uint16_t*>(a1 + 4) = 3;
    } else if (strcmp(v1, "boot_dummy") == 0) {
        *reinterpret_cast<uint16_t*>(a1 + 4) = 260;
    } else if (strcmp(v1, "bump_front_dummy") == 0) {
        *reinterpret_cast<uint16_t*>(a1 + 4) = 1280;
    } else if (strcmp(v1, "bump_rear_dummy") == 0) {
        *reinterpret_cast<uint16_t*>(a1 + 4) = 1536;
    } else if (strcmp(v1, "wing_rf_dummy") == 0) {
        *reinterpret_cast<uint16_t*>(a1 + 4) = 256;
    } else if (strcmp(v1, "wing_lf_dummy") == 0) {
        *reinterpret_cast<uint16_t*>(a1 + 4) = 0;
    } else {
        a1[4] = 6;
    }
}

// sub_100046F0: Parses light dummy name and populates tIvfLight
bool CDummies::ParseLightDummy(void* pFrame, tIvfVehicleExtended* pExtended) {
    const char* v2 = GetFrameNodeName(pFrame);
    if (!v2 || pExtended->numLights >= 50)
        return false;

    uint32_t r = 0, g = 0, b = 0;
    uint32_t v9 = 0;
    uint32_t v10 = 3;
    uint32_t v14 = 0;
    uint8_t lightType = 0;

    if (strncmp(v2, "indicator", 9) == 0 || strncmp(v2, "turnl", 5) == 0) {
        v14 = 0;
        r = 240; g = 180; b = 0;
        v9 = 5;

        if (strstr(v2, "_lf")) lightType = IVF_LIGHT_INDICATOR_LF;
        else if (strstr(v2, "_rf")) lightType = IVF_LIGHT_INDICATOR_RF;
        else if (strstr(v2, "_lr")) lightType = IVF_LIGHT_INDICATOR_LR;
        else if (strstr(v2, "_rr")) lightType = IVF_LIGHT_INDICATOR_RR;
        else if (strstr(v2, "_lm")) lightType = IVF_LIGHT_INDICATOR_LM;
        else if (strstr(v2, "_rm")) lightType = IVF_LIGHT_INDICATOR_RM;
        else lightType = IVF_LIGHT_INDICATOR_RM;
    }
    else if (strncmp(v2, "breakl", 6) == 0) {
        v14 = 1;
        r = 200; g = 0; b = 0;
        if (strstr(v2, "_l")) {
            lightType = IVF_LIGHT_BRAKE_L;
            pExtended->hasBrakeL = 1;
        } else {
            lightType = IVF_LIGHT_BRAKE_R;
            pExtended->hasBrakeR = 1;
        }
    }
    else if (strncmp(v2, "fogl", 4) == 0) {
        v14 = 0;
        r = 200; g = 200; b = 220;
        v10 = 6;
        lightType = (strstr(v2, "_l") != nullptr) ? IVF_LIGHT_FOG_L : IVF_LIGHT_FOG_R;
    }
    else if (strncmp(v2, "revl", 4) == 0 || strncmp(v2, "reversingl", 10) == 0) {
        v14 = 1;
        r = 255; g = 255; b = 255;
        lightType = (strstr(v2, "_l") != nullptr) ? IVF_LIGHT_REVERSE_L : IVF_LIGHT_REVERSE_R;
    }
    else if (strncmp(v2, "light_n", 7) == 0) {
        v14 = 2;
        r = 255; g = 255; b = 255;
        lightType = IVF_LIGHT_NIGHT;
    }
    else {
        return false;
    }

    tIvfLight& light = pExtended->lights[pExtended->numLights++];
    light.frame = pFrame;

    const char* prm = strstr(v2, "prm");
    if (prm) {
        sscanf(prm, "prm%2X%2X%2X%1X%1X%1X", &r, &g, &b, &v14, &v10, &v9);
    }

    light.light_type = lightType;
    light.flagMode = static_cast<uint8_t>(v10);
    light.flagPat = static_cast<uint8_t>(v9);
    light.flagParam = static_cast<uint8_t>(v14);
    light.color_r = static_cast<uint8_t>(r);
    light.color_g = static_cast<uint8_t>(g);
    light.color_b = static_cast<uint8_t>(b);

    AttachDummyToVehiclePart(&light);
    return true;
}

// sub_10004430: Traverses clump node hierarchy and classifies each dummy
void* __cdecl CDummies::FindDummiesCallback(void* pFrame, void* pData) {
    tIvfVehicleExtended* pExtended = reinterpret_cast<tIvfVehicleExtended*>(pData);
    if (!pFrame || !pExtended)
        return pFrame;

    const char* szName = GetFrameNodeName(pFrame);
    if (szName) {
        if (!ParseLightDummy(pFrame, pExtended)) {
            // Brake calipers
            if (strcmp(szName, "hub_rf") == 0) { pExtended->pHubRF = pFrame; }
            else if (strcmp(szName, "hub_lf") == 0) { pExtended->pHubLF = pFrame; }
            else if (strcmp(szName, "hub_rm") == 0) { pExtended->pHubRM = pFrame; }
            else if (strcmp(szName, "hub_lm") == 0) { pExtended->pHubLM = pFrame; }
            else if (strcmp(szName, "hub_rb") == 0) { pExtended->pHubRB = pFrame; }
            else if (strcmp(szName, "hub_lb") == 0) { pExtended->pHubLB = pFrame; }
            // Active spoilers
            else if (strncmp(szName, "movspoiler", 10) == 0) {
                for (int i = 0; i < 3; ++i) {
                    if (!pExtended->spoilers[i].frame) {
                        tIvfSpoiler& sp = pExtended->spoilers[i];
                        sp.frame = pFrame;
                        sp.state = 0;
                        sp.isDamaged = 0;
                        const char* under = strstr(szName, "_");
                        if (under) {
                            sscanf(under, "_%f_%u", &sp.maxAngle, &sp.moveDuration);
                        } else {
                            sp.maxAngle = 25.0f;
                            sp.moveDuration = 2500;
                        }
                        AttachDummyToVehiclePart(&sp);
                        break;
                    }
                }
            }
            // Extras
            else if (strncmp(szName, "extra", 5) == 0 && szName[5] != '_') {
                for (int i = 0; i < 5; ++i) {
                    if (!pExtended->extras[i].frame) {
                        pExtended->extras[i].frame = pFrame;
                        AttachDummyToVehiclePart(&pExtended->extras[i]);
                        break;
                    }
                }
            }
            // Steering wheel
            else if (strncmp(szName, "movsteer", 8) == 0) {
                pExtended->pSteerWheelFrame = pFrame;
                pExtended->fSteerMultiplier = 1.0f;
                if (szName[8] == '_') {
                    sscanf(szName + 9, "%f", &pExtended->fSteerMultiplier);
                }
            }
        }
    }

    RwFrameForAllChildren(pFrame, FindDummiesCallback, pData);
    return pFrame;
}

// sub_100042C0: Called on 0x6D6A58 hook to rebuild all model nodes and IVF dummy bindings
int CDummies::SetupModelNodes(void* pVehicle, int a2) {
    // 1. Call original CAutomobile::SetupModelNodes (0x6D10E0)
    reinterpret_cast<void(__thiscall*)(void*, int)>(0x6D10E0)(pVehicle, a2);

    // 2. Fetch extended vehicle data structure
    tIvfVehicleState* pState = CVehicleData::GetState(pVehicle);
    tIvfVehicleExtended* pExtended = CVehicleData::GetExtended(pVehicle);
    if (!pState || !pExtended)
        return 0;

    pExtended->Reset();
    pState->bHeadlightsOn = 0;
    pState->bReverseLightsOn = 0;
    pState->nIndicatorTimer = 0;

    // 3. Find EML profile for model
    int16_t modelId = *reinterpret_cast<int16_t*>(reinterpret_cast<uintptr_t>(pVehicle) + 34);
    pExtended->pEmlProfile = CEml::FindProfile(modelId);

    // 4. Clump root frame traversal
    uintptr_t pClump = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(pVehicle) + 24); // m_pRwClump
    if (pClump) {
        uintptr_t pRootFrame = *reinterpret_cast<uintptr_t*>(pClump + 4);
        if (pRootFrame) {
            RwFrameForAllChildren(reinterpret_cast<void*>(pRootFrame), FindDummiesCallback, pExtended);
        }
    }

    return 0;
}
