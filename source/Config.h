#pragma once
#include "common.h"

class CConfig {
public:
    // [MAIN]
    static bool bSampFix;
    static bool bDisableBeamShape;
    static uint32_t nTurnlightsDelay;
    static uint32_t nTurnlightsPeriod; // 2 * nTurnlightsDelay

    // [CONTROL]
    static uint32_t nKeyFog;         // Default: 'J' (0x4A)
    static uint32_t nKeyTurnLeft;    // Default: 'Z' (0x5A)
    static uint32_t nKeyTurnRight;   // Default: 'C' (0x43)
    static uint32_t nKeyHazard;      // Default: 'X' (0x58)
    static uint32_t nKeyTurnOff;     // Default: VK_SHIFT (0x10)
    static uint32_t nKeyHeadlight;   // Default: 'G' (0x47)

public:
    static void Read();
};
