#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include <filesystem>

// Plugin info
#define IVF_VERSION_STRING "2.1.1"
#define IVF_LOG_FILE "ImVehFt.log"
#define IVF_INI_FILE "ImVehFt\\ImVehFt.ini"

// RenderWare Plugin ID for ImVehFt Material Extension ('IVFT')
#define IVF_MATERIAL_PLUGIN_ID 0x54465649

// IVF Light Types
enum eIvfLightType : uint8_t {
    IVF_LIGHT_NONE = 0,
    IVF_LIGHT_BRAKE_L = 4,
    IVF_LIGHT_BRAKE_R = 5,
    IVF_LIGHT_REVERSE_L = 6,
    IVF_LIGHT_REVERSE_R = 7,
    IVF_LIGHT_FOG_L = 8,
    IVF_LIGHT_FOG_R = 9,
    IVF_LIGHT_INDICATOR_LF = 10,
    IVF_LIGHT_INDICATOR_LM = 11,
    IVF_LIGHT_INDICATOR_LR = 12,
    IVF_LIGHT_INDICATOR_RF = 13,
    IVF_LIGHT_INDICATOR_RM = 14,
    IVF_LIGHT_INDICATOR_RR = 15,
    IVF_LIGHT_NIGHT = 16,
    IVF_LIGHT_DAY = 20
};

// Single light entry inside IVF vehicle structure (16 bytes)
struct tIvfLight {
    void* frame;            // RwFrame* (offset 0)
    uint8_t componentId;    // offset 4
    uint8_t damageType;     // offset 5
    uint8_t flagParam;      // offset 6
    uint8_t pad7;           // offset 7
    uint8_t flagMode;       // offset 8
    uint8_t flagPat;        // offset 9
    uint8_t color_r;        // offset 10
    uint8_t color_g;        // offset 11
    uint8_t color_b;        // offset 12
    uint8_t light_type;     // offset 13 (eIvfLightType)
    uint8_t pad[2];         // offset 14, 15
};

// Extra component entry (8 bytes)
struct tIvfExtra {
    void* frame;            // RwFrame* (offset 0)
    uint8_t componentId;    // offset 4
    uint8_t damageType;     // offset 5
    uint16_t pad;           // offset 6
};

// Active spoiler entry (24 bytes)
struct tIvfSpoiler {
    void* frame;            // RwFrame* (offset 0)
    uint8_t componentId;    // offset 4
    uint8_t damageType;     // offset 5
    uint16_t pad6;          // offset 6
    float maxAngle;         // offset 8 (default 25.0f)
    uint32_t moveDuration;  // offset 12 (default 2500 ms)
    uint32_t lastMoveTime;  // offset 16
    uint8_t state;          // offset 20 (0=idle_in, 1=idle_out, 2=retracting, 3=deploying)
    uint8_t isDamaged;      // offset 21
    uint16_t pad22;         // offset 22
};
