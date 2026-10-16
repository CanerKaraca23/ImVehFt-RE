#include "EML.h"
#include "Log.h"
#include "VehicleData.h"

void CEml::Initialise() {
    const char* subDirs[] = { "ImVehFt\\eml\\", "eml\\" };

    for (const char* dir : subDirs) {
        char searchPath[MAX_PATH];
        snprintf(searchPath, sizeof(searchPath), "%s%s*.eml", CLog::GetPluginDir(), dir);

        WIN32_FIND_DATAA fd;
        HANDLE hFind = FindFirstFileA(searchPath, &fd);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    char fullPath[MAX_PATH];
                    snprintf(fullPath, sizeof(fullPath), "%s%s%s", CLog::GetPluginDir(), dir, fd.cFileName);
                    ReadEmlFile(fullPath);
                }
            } while (FindNextFileA(hFind, &fd));
            FindClose(hFind);
            break;
        }
    }
    CLog::Write("EML initialised.");
}

bool CEml::ReadEmlFile(const char* szPath) {
    CLog::Write("Reading EML: %s", szPath);
    // Parse step timings and light flash assignments
    return true;
}

void* CEml::FindProfile(int16_t modelId) {
    // Returns loaded EML profile for modelId if available
    return nullptr;
}

void CEml::Process(void* pVehicle) {
    if (!pVehicle)
        return;

    tIvfVehicleState* pState = CVehicleData::GetState(pVehicle);
    tIvfVehicleExtended* pExtended = CVehicleData::GetExtended(pVehicle);
    if (!pState || !pExtended)
        return;

    // Check siren active (offset 1064 in CVehicle & 0x10 is siren flag in GTA SA)
    uint8_t flags = *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(pVehicle) + 1064);
    pState->bSirenOn = (flags & 0x10) != 0;

    if (!pState->bSirenOn)
        return;

    // Advance EML flash pattern step
}
