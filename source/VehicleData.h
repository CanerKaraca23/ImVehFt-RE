#pragma once
#include "common.h"

// Extended IVF data allocated per-vehicle (0x518 = 1304 bytes)
struct tIvfVehicleExtended {
    tIvfLight lights[50];               // 0x000 - 0x31F (800 bytes)
    uint32_t numLights;                 // 0x320 (offset 800)
    uint8_t hasBrakeL;                  // 0x324 (offset 804)
    uint8_t hasBrakeR;                  // 0x325 (offset 805)
    uint8_t pad806[2];                  // 0x326 - 0x327
    tIvfExtra extras[5];                // 0x328 - 0x34F (40 bytes, offset 808-847)
    void* pEmlProfile;                  // 0x350 (offset 848)
    uint8_t emlData[320];               // 0x354 - 0x493 (offset 852-1171)
    void* pSteerWheelFrame;             // 0x494 (offset 1172, RwFrame*)
    uint32_t pad1176;                   // 0x498 (offset 1176)
    float fSteerMultiplier;             // 0x49C (offset 1180, default 1.0f)
    tIvfSpoiler spoilers[3];            // 0x4A0 - 0x4E7 (72 bytes, offset 1184-1255)
    void* pHubRF;                       // 0x4E8 (offset 1256, RwFrame*)
    uint32_t padHubRF;                  // 0x4EC
    void* pHubLF;                       // 0x4F0 (offset 1264, RwFrame*)
    uint32_t padHubLF;                  // 0x4F4
    void* pHubRM;                       // 0x4F8 (offset 1272, RwFrame*)
    uint32_t padHubRM;                  // 0x4FC
    void* pHubLM;                       // 0x500 (offset 1280, RwFrame*)
    uint32_t padHubLM;                  // 0x504
    void* pHubRB;                       // 0x508 (offset 1288, RwFrame*)
    uint32_t padHubRB;                  // 0x50C
    void* pHubLB;                       // 0x510 (offset 1296, RwFrame*)
    uint32_t padHubLB;                  // 0x514

    tIvfVehicleExtended();
    void Reset();
};

// IVF per-vehicle state (52 bytes)
struct tIvfVehicleState {
    void* pVehicle;                     // offset 0
    uint8_t lightActive[24];            // offset 4 to 27 (active flags for each light type)
    uint8_t bHeadlightsOn;              // offset 28
    uint8_t bFogLightsOn;               // offset 29
    uint8_t bRightIndicator;            // offset 30
    uint8_t bLeftIndicator;             // offset 31
    uint8_t bReverseLightsOn;           // offset 32
    uint8_t bSirenOn;                   // offset 33
    uint16_t pad34;                     // offset 34-35
    uint32_t nIndicatorTimer;           // offset 36
    tIvfVehicleExtended* pExtended;     // offset 40
    uint8_t eml_count;                  // offset 44
    uint8_t pad45[3];                   // offset 45-47
    void* eml_data;                     // offset 48

    void Reset();
};

class CVehicleData {
private:
    static tIvfVehicleState ms_states[256];
    static tIvfVehicleExtended ms_extended[256];

public:
    static void Initialise();
    static tIvfVehicleState* GetState(void* pVehicle);
    static tIvfVehicleExtended* GetExtended(void* pVehicle);
    static int GetVehicleIndex(void* pVehicle);
    static void ResetVehicle(void* pVehicle);
};
