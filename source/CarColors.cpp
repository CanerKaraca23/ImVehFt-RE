#include "CarColors.h"
#include "Log.h"

std::vector<tVehicleColorProfile> CCarColors::m_profiles;

void CCarColors::Initialise() {
    m_profiles.clear();

    const char* subDirs[] = { "ImVehFt\\colors\\", "colors\\" };
    bool bFoundAny = false;

    for (const char* dir : subDirs) {
        char searchPath[MAX_PATH];
        snprintf(searchPath, sizeof(searchPath), "%s%s*.ivfc", CLog::GetPluginDir(), dir);

        WIN32_FIND_DATAA fd;
        HANDLE hFind = FindFirstFileA(searchPath, &fd);
        if (hFind != INVALID_HANDLE_VALUE) {
            bFoundAny = true;
            do {
                if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    char fullPath[MAX_PATH];
                    snprintf(fullPath, sizeof(fullPath), "%s%s%s", CLog::GetPluginDir(), dir, fd.cFileName);
                    ReadColorFile(fullPath);
                }
            } while (FindNextFileA(hFind, &fd));
            FindClose(hFind);
            break;
        }
    }
}

bool CCarColors::ReadColorFile(const char* szFilePath) {
    CLog::Write("CarColors::ReadColorFile: processing %s", szFilePath);

    FILE* f = fopen(szFilePath, "rt");
    if (!f)
        return false;

    char buffer[256];
    char tempTag[64];
    int vehicleId = -1;
    int numColors = 0;

    // Read vehicle ID
    do {
        if (!fgets(buffer, sizeof(buffer), f)) { fclose(f); return false; }
    } while (buffer[0] == '#' || buffer[0] == ';' || buffer[0] == '\n' || buffer[0] == '\r');

    sscanf(buffer, "%s %d", tempTag, &vehicleId);

    // Read num colors
    do {
        if (!fgets(buffer, sizeof(buffer), f)) { fclose(f); return false; }
    } while (buffer[0] == '#' || buffer[0] == ';' || buffer[0] == '\n' || buffer[0] == '\r');

    sscanf(buffer, "%s %d", tempTag, &numColors);

    tVehicleColorProfile profile;
    profile.vehicleModelId = static_cast<uint16_t>(vehicleId);
    profile.numColors = static_cast<uint8_t>(numColors);

    for (int i = 0; i < numColors; ++i) {
        do {
            if (!fgets(buffer, sizeof(buffer), f)) break;
        } while (buffer[0] == '#' || buffer[0] == ';' || buffer[0] == '\n' || buffer[0] == '\r');

        int r = 0, g = 0, b = 0;
        sscanf(buffer, "%d %d %d", &r, &g, &b);

        tCarColorEntry entry;
        entry.r = static_cast<uint8_t>(r);
        entry.g = static_cast<uint8_t>(g);
        entry.b = static_cast<uint8_t>(b);
        entry.a = 255;
        profile.colors.push_back(entry);
    }

    fclose(f);
    m_profiles.push_back(profile);
    return true;
}

const tVehicleColorProfile* CCarColors::GetProfile(uint16_t modelId) {
    for (const auto& p : m_profiles) {
        if (p.vehicleModelId == modelId)
            return &p;
    }
    return nullptr;
}
