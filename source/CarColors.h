#pragma once
#include "common.h"

struct tCarColorEntry {
    uint8_t r, g, b, a;
};

struct tVehicleColorProfile {
    uint16_t vehicleModelId;
    uint8_t numColors;
    std::vector<tCarColorEntry> colors;
};

class CCarColors {
private:
    static std::vector<tVehicleColorProfile> m_profiles;

public:
    static void Initialise();
    static bool ReadColorFile(const char* szFilePath);
    static const tVehicleColorProfile* GetProfile(uint16_t modelId);
};
