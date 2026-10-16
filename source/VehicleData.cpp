#include "VehicleData.h"
#include <cstring>

tIvfVehicleState CVehicleData::ms_states[256];
tIvfVehicleExtended CVehicleData::ms_extended[256];

tIvfVehicleExtended::tIvfVehicleExtended() {
    Reset();
}

void tIvfVehicleExtended::Reset() {
    memset(this, 0, sizeof(tIvfVehicleExtended));
    fSteerMultiplier = 1.0f;
}

void tIvfVehicleState::Reset() {
    memset(this, 0, sizeof(tIvfVehicleState));
}

void CVehicleData::Initialise() {
    for (int i = 0; i < 256; ++i) {
        ms_states[i].Reset();
        ms_extended[i].Reset();
        ms_states[i].pExtended = &ms_extended[i];
    }
}

int CVehicleData::GetVehicleIndex(void* pVehicle) {
    if (!pVehicle)
        return -1;

    // In GTA SA: 0xB74494 holds pointer to CPool<CVehicle, CAutomobile> (CPools::ms_pVehiclePool)
    // CPool::m_pObjects is at offset 0 of CPool.
    // Therefore, **reinterpret_cast<uintptr_t**>(0xB74494) points to the vehicle objects array!
    uintptr_t** ppPool = reinterpret_cast<uintptr_t**>(0xB74494);
    if (!ppPool || !*ppPool)
        return -1;

    uintptr_t* pPool = *ppPool;
    if (!pPool)
        return -1;

    uintptr_t poolObjects = *pPool; // m_pObjects
    uintptr_t vehAddr = reinterpret_cast<uintptr_t>(pVehicle);
    if (vehAddr < poolObjects)
        return -1;

    int index = static_cast<int>((vehAddr - poolObjects) / 2584);
    if (index < 0 || index >= 256)
        return -1;

    return index;
}

tIvfVehicleState* CVehicleData::GetState(void* pVehicle) {
    int index = GetVehicleIndex(pVehicle);
    if (index < 0)
        return nullptr;

    tIvfVehicleState* state = &ms_states[index];
    state->pVehicle = pVehicle;
    state->pExtended = &ms_extended[index];
    return state;
}

tIvfVehicleExtended* CVehicleData::GetExtended(void* pVehicle) {
    int index = GetVehicleIndex(pVehicle);
    if (index < 0)
        return nullptr;

    return &ms_extended[index];
}

void CVehicleData::ResetVehicle(void* pVehicle) {
    int index = GetVehicleIndex(pVehicle);
    if (index >= 0) {
        ms_states[index].Reset();
        ms_extended[index].Reset();
        ms_states[index].pVehicle = pVehicle;
        ms_states[index].pExtended = &ms_extended[index];
    }
}
