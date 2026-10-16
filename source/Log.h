#pragma once
#include "common.h"

class CLog {
private:
    static FILE* m_pFile;
    static bool m_bEnabled;
    static bool m_bInitialized;
    static char m_szPluginDir[MAX_PATH];

public:
    static void Initialise(const char* szPluginPath);
    static void Close();
    static void Write(const char* format, ...);
    static const char* GetPluginDir() { return m_szPluginDir; }
};
