#include "SteeringWheel.h"
#include <cmath>

#define CTimer_m_snTimeInMilliseconds (*reinterpret_cast<uint32_t*>(0xB7CB84))

// GTA SA math & RenderWare matrix rotate functions
typedef float (__cdecl* tGetATanOfXY)(float x, float y);
typedef void (__thiscall* tRwMatrixRotate)(void* matrix, float angle);
typedef void (__cdecl* tRwMatrixUpdate)(void* dst, void* src, void* parent);
typedef uint8_t (__thiscall* tGetCarDamage)(void* damageManager, uint8_t component);
typedef void (__cdecl* tRwAtomicSetFlags)(void* atomic, void* callback, int flag);
typedef void (__cdecl* tRwFrameForAllObjects)(void* frame, void* callback, int flag);

static tGetATanOfXY GetATanOfXY = reinterpret_cast<tGetATanOfXY>(0x53CC70);
static tRwMatrixRotate RwMatrixRotateY = reinterpret_cast<tRwMatrixRotate>(0x59AFE0);
static tRwMatrixRotate RwMatrixRotateZ = reinterpret_cast<tRwMatrixRotate>(0x59B020);
static tRwMatrixRotate RwMatrixRotateX = reinterpret_cast<tRwMatrixRotate>(0x59AFA0);
static tRwMatrixUpdate RwMatrixMultiply = reinterpret_cast<tRwMatrixUpdate>(0x7F18B0);
static tGetCarDamage GetPanelStatus = reinterpret_cast<tGetCarDamage>(0x6C2180);
static tGetCarDamage GetDoorStatus = reinterpret_cast<tGetCarDamage>(0x6C2230);

// sub_10003FE0: Sets RpAtomic flags (+2: 4 = rpATOMICRENDER, 0 = hidden)
static void* __cdecl SetAtomicRenderFlag(void* atomic, void* a2) {
    int flag = reinterpret_cast<intptr_t>(a2);
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(atomic) + 2) = (flag != 0) ? 4 : 0;
    return atomic;
}

// sub_10003FB0: Traverses frame objects and sets atomic render flag recursively
static void* __cdecl FrameSetAtomicVisibility(void* frame, void* a2) {
    reinterpret_cast<void*(__cdecl*)(void*, void*, void*)>(0x7F1200)(frame, SetAtomicRenderFlag, a2);
    reinterpret_cast<void*(__cdecl*)(void*, void*, void*)>(0x7F0DC0)(frame, FrameSetAtomicVisibility, a2);
    return frame;
}

// sub_10006A50: Updates steering wheel rotation angle based on CVehicle::m_fSteerAngle (0x494)
void CSteeringWheel::Update(void* pVehicle) {
    if (!pVehicle)
        return;

    tIvfVehicleExtended* pExtended = CVehicleData::GetExtended(pVehicle);
    if (!pExtended || !pExtended->pSteerWheelFrame)
        return;

    float fSteerAngle = *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(pVehicle) + 1172); // 0x494 m_fSteerAngle
    float fAngle = pExtended->fSteerMultiplier * fSteerAngle * -2.5f;

    void* pModelling = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pExtended->pSteerWheelFrame) + 16);
    RwMatrixRotateY(pModelling, fAngle);
}

// sub_10006360: Updates independent brake calipers (hub_rf, hub_lf, hub_rm, hub_lm, hub_rb, hub_lb)
void CSteeringWheel::UpdateBrakeCalipers(void* pVehicle) {
    if (!pVehicle)
        return;

    uint32_t vehType = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(pVehicle) + 1428); // 0x594
    if (vehType != 0 && vehType != 2 && vehType != 11 && vehType != 1)
        return;

    tIvfVehicleExtended* pExtended = CVehicleData::GetExtended(pVehicle);
    if (!pExtended)
        return;

    uintptr_t vehBase = reinterpret_cast<uintptr_t>(pVehicle);
    uintptr_t* wheelNodes = reinterpret_cast<uintptr_t*>(vehBase + 1616); // 0x650 m_aWheelNodes in CAutomobile

    // Hub RF (front right wheel = index 0)
    if (pExtended->pHubRF && wheelNodes[0]) {
        uintptr_t wn = wheelNodes[0];
        float rot = GetATanOfXY(*reinterpret_cast<float*>(wn + 16), *reinterpret_cast<float*>(wn + 20));
        void* pHub = pExtended->pHubRF;
        RwMatrixRotateZ(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 16), rot);
        memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 64), reinterpret_cast<void*>(wn + 64), 12);
        void* pParent = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(pHub) + 4);
        if (pParent) {
            RwMatrixMultiply(
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 80),
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 16),
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pParent) + 16)
            );
        }
    }

    // Hub LF (front left wheel = index 3)
    if (pExtended->pHubLF && wheelNodes[3]) {
        uintptr_t wn = wheelNodes[3];
        float rot = GetATanOfXY(*reinterpret_cast<float*>(wn + 16), *reinterpret_cast<float*>(wn + 20)) - 3.14159265f;
        void* pHub = pExtended->pHubLF;
        RwMatrixRotateZ(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 16), rot);
        memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 64), reinterpret_cast<void*>(wn + 64), 12);
        void* pParent = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(pHub) + 4);
        if (pParent) {
            RwMatrixMultiply(
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 80),
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 16),
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pParent) + 16)
            );
        }
    }

    // Hub RM (middle right wheel = index 1)
    if (pExtended->pHubRM && wheelNodes[1]) {
        uintptr_t wn = wheelNodes[1];
        float rot = GetATanOfXY(*reinterpret_cast<float*>(wn + 16), *reinterpret_cast<float*>(wn + 20));
        void* pHub = pExtended->pHubRM;
        RwMatrixRotateZ(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 16), rot);
        memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 64), reinterpret_cast<void*>(wn + 64), 12);
        void* pParent = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(pHub) + 4);
        if (pParent) {
            RwMatrixMultiply(
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 80),
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 16),
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pParent) + 16)
            );
        }
    }

    // Hub LM (middle left wheel = index 4)
    if (pExtended->pHubLM && wheelNodes[4]) {
        uintptr_t wn = wheelNodes[4];
        float rot = GetATanOfXY(*reinterpret_cast<float*>(wn + 16), *reinterpret_cast<float*>(wn + 20)) - 3.14159265f;
        void* pHub = pExtended->pHubLM;
        RwMatrixRotateZ(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 16), rot);
        memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 64), reinterpret_cast<void*>(wn + 64), 12);
        void* pParent = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(pHub) + 4);
        if (pParent) {
            RwMatrixMultiply(
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 80),
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 16),
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pParent) + 16)
            );
        }
    }

    // Hub RB (rear right wheel = index 2)
    if (pExtended->pHubRB && wheelNodes[2]) {
        uintptr_t wn = wheelNodes[2];
        float rot = GetATanOfXY(*reinterpret_cast<float*>(wn + 16), *reinterpret_cast<float*>(wn + 20));
        void* pHub = pExtended->pHubRB;
        RwMatrixRotateZ(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 16), rot);
        memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 64), reinterpret_cast<void*>(wn + 64), 12);
        void* pParent = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(pHub) + 4);
        if (pParent) {
            RwMatrixMultiply(
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 80),
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 16),
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pParent) + 16)
            );
        }
    }

    // Hub LB (rear left wheel = index 5)
    if (pExtended->pHubLB && wheelNodes[5]) {
        uintptr_t wn = wheelNodes[5];
        float rot = GetATanOfXY(*reinterpret_cast<float*>(wn + 16), *reinterpret_cast<float*>(wn + 20)) - 3.14159265f;
        void* pHub = pExtended->pHubLB;
        RwMatrixRotateZ(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 16), rot);
        memcpy(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 64), reinterpret_cast<void*>(wn + 64), 12);
        void* pParent = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(pHub) + 4);
        if (pParent) {
            RwMatrixMultiply(
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 80),
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHub) + 16),
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pParent) + 16)
            );
        }
    }
}

// sub_10006790 & sub_100069E0: Active spoilers deployment/retraction based on vehicle speed
void CSteeringWheel::UpdateSpoilers(void* pVehicle) {
    if (!pVehicle)
        return;

    tIvfVehicleExtended* pExtended = CVehicleData::GetExtended(pVehicle);
    if (!pExtended)
        return;

    uintptr_t vehBase = reinterpret_cast<uintptr_t>(pVehicle);
    float* moveSpeed = reinterpret_cast<float*>(vehBase + 68); // 0x44 m_vecMoveSpeed
    float speed = sqrtf(moveSpeed[0] * moveSpeed[0] + moveSpeed[1] * moveSpeed[1] + moveSpeed[2] * moveSpeed[2]) * 178.0f;

    void* damageManager = reinterpret_cast<void*>(vehBase + 1440); // 0x5A0

    for (int i = 0; i < 3; ++i) {
        tIvfSpoiler& sp = pExtended->spoilers[i];
        if (!sp.frame)
            continue;

        // Check damage
        if (sp.damageType == 0) {
            if (GetPanelStatus(damageManager, sp.componentId) != 0) {
                sp.isDamaged = 1;
                continue;
            }
        } else if (sp.damageType >= 2 && sp.damageType <= 4) {
            if (GetDoorStatus(damageManager, sp.componentId) > 1) {
                sp.isDamaged = 1;
                continue;
            }
        }

        sp.isDamaged = 0;

        switch (sp.state) {
        case 0: // Retracted
            if (speed >= 125.0f) {
                sp.state = 3; // Deploying
                sp.lastMoveTime = CTimer_m_snTimeInMilliseconds;
            }
            break;

        case 1: // Deployed
            if (speed < 125.0f) {
                sp.state = 2; // Retracting
                sp.lastMoveTime = CTimer_m_snTimeInMilliseconds;
            }
            break;

        case 2: { // Retracting
            uint32_t dur = sp.moveDuration ? sp.moveDuration : 2500;
            uint32_t elapsed = CTimer_m_snTimeInMilliseconds - sp.lastMoveTime;
            float rotAngle = 0.0f;
            if (elapsed <= dur) {
                float frac = (1.0f - static_cast<float>(elapsed) / static_cast<float>(dur)) * sp.maxAngle;
                rotAngle = frac * -0.017453292f;
            } else {
                rotAngle = 0.0f;
                sp.state = 0;
            }
            RwMatrixRotateX(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(sp.frame) + 16), rotAngle);
            break;
        }

        case 3: { // Deploying
            uint32_t dur = sp.moveDuration ? sp.moveDuration : 2500;
            uint32_t elapsed = CTimer_m_snTimeInMilliseconds - sp.lastMoveTime;
            float rotAngle = 0.0f;
            if (elapsed <= dur) {
                float frac = (static_cast<float>(elapsed) / static_cast<float>(dur)) * sp.maxAngle;
                rotAngle = frac * -0.017453292f;
            } else {
                sp.state = 1;
                rotAngle = sp.maxAngle * -0.017453292f;
            }
            RwMatrixRotateX(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(sp.frame) + 16), rotAngle);
            break;
        }
        }
    }
}

// sub_10006AD0: Updates extra component visibility based on damage
void CSteeringWheel::UpdateExtras(void* pVehicle) {
    if (!pVehicle)
        return;

    uint32_t vehType = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(pVehicle) + 1428);
    if (vehType >= 2 && vehType != 11)
        return;

    tIvfVehicleExtended* pExtended = CVehicleData::GetExtended(pVehicle);
    if (!pExtended)
        return;

    void* damageManager = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pVehicle) + 1440);

    for (int i = 0; i < 5; ++i) {
        tIvfExtra& extra = pExtended->extras[i];
        if (!extra.frame || extra.componentId == 6)
            continue;

        bool bVisible = true;
        if (extra.damageType == 0) {
            bVisible = (GetPanelStatus(damageManager, extra.componentId) == 0);
        } else if (extra.damageType >= 2 && extra.damageType <= 4) {
            bVisible = (GetDoorStatus(damageManager, extra.componentId) <= 1);
        }

        int flag = bVisible ? 1 : 0;
        reinterpret_cast<void(__cdecl*)(void*, void*, int)>(0x7F1200)(extra.frame, SetAtomicRenderFlag, flag);
        reinterpret_cast<void(__cdecl*)(void*, void*, int)>(0x7F0DC0)(extra.frame, FrameSetAtomicVisibility, flag);
    }
}
