#include "Config.h"
#include "Log.h"

bool CConfig::bSampFix = false;
bool CConfig::bDisableBeamShape = true;
uint32_t CConfig::nTurnlightsDelay = 500;
uint32_t CConfig::nTurnlightsPeriod = 1000;

uint32_t CConfig::nKeyFog = 0x4A;        // 'J'
uint32_t CConfig::nKeyTurnLeft = 0x5A;   // 'Z'
uint32_t CConfig::nKeyTurnRight = 0x43;  // 'C'
uint32_t CConfig::nKeyHazard = 0x58;     // 'X'
uint32_t CConfig::nKeyTurnOff = 0x10;    // VK_SHIFT
uint32_t CConfig::nKeyHeadlight = 0x47;  // 'G'

void CConfig::Read() {
    CLog::Write("This file was created by ImVehFt.asi\nCurrent plugin version: %s", IVF_VERSION_STRING);
    CLog::Write("Reading ImVehFt.ini...");

    char iniPath[MAX_PATH];
    snprintf(iniPath, sizeof(iniPath), "%s%s", CLog::GetPluginDir(), IVF_INI_FILE);
    if (GetFileAttributesA(iniPath) == INVALID_FILE_ATTRIBUTES) {
        snprintf(iniPath, sizeof(iniPath), "%sImVehFt.ini", CLog::GetPluginDir());
    }

    bSampFix = (GetPrivateProfileIntA("MAIN", "SAMP_fix", 0, iniPath) != 0);
    bDisableBeamShape = (GetPrivateProfileIntA("MAIN", "disable_beam_shape", 1, iniPath) != 0);
    nTurnlightsDelay = GetPrivateProfileIntA("MAIN", "turnlights_delay", 500, iniPath);
    nTurnlightsPeriod = nTurnlightsDelay * 2;

    nKeyFog = GetPrivateProfileIntA("CONTROL", "key_fog", 0x4A, iniPath);
    nKeyTurnLeft = GetPrivateProfileIntA("CONTROL", "key_turnl_l", 0x5A, iniPath);
    nKeyTurnRight = GetPrivateProfileIntA("CONTROL", "key_turnl_r", 0x43, iniPath);
    nKeyHazard = GetPrivateProfileIntA("CONTROL", "key_turnl_2", 0x58, iniPath);
    nKeyTurnOff = GetPrivateProfileIntA("CONTROL", "key_turnl_0", 0x10, iniPath);
    nKeyHeadlight = GetPrivateProfileIntA("CONTROL", "key_headlight", 0x47, iniPath);

    CLog::Write("Finished.");
}
