#pragma once
#include "common.h"

struct tEmlLightStep {
    uint8_t stepFlags;
    uint16_t stepDelayMs;
};

struct tEmlProfile {
    uint16_t modelId;
    uint8_t numLights;
    std::string name;
};

class CEml {
public:
    static void Initialise();
    static bool ReadEmlFile(const char* szPath);
    static void* FindProfile(int16_t modelId);
    static void Process(void* pVehicle);
};
