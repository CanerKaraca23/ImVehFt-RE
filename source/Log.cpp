#include "Log.h"
#include <cstdarg>

FILE* CLog::m_pFile = nullptr;
bool CLog::m_bEnabled = false;
bool CLog::m_bInitialized = false;
char CLog::m_szPluginDir[MAX_PATH] = { 0 };

void CLog::Initialise(const char* szPluginPath) {
    if (szPluginPath && szPluginPath[0]) {
        strcpy_s(m_szPluginDir, sizeof(m_szPluginDir), szPluginPath);
        char* lastSlash = strrchr(m_szPluginDir, '\\');
        if (lastSlash) {
            lastSlash[1] = '\0';
        }
    }
    m_bInitialized = true;

    char logPath[MAX_PATH];
    strcpy_s(logPath, sizeof(logPath), m_szPluginDir);
    strcat_s(logPath, sizeof(logPath), IVF_LOG_FILE);

    m_pFile = fopen(logPath, "w");
    if (m_pFile) {
        m_bEnabled = true;
    } else {
        MessageBoxA(nullptr, "CFile::m_bInitialised - FALSE", "CFile::Open", MB_ICONERROR);
    }
}

void CLog::Close() {
    if (m_bEnabled && m_pFile) {
        m_bEnabled = false;
        fclose(m_pFile);
        m_pFile = nullptr;
    }
}

void CLog::Write(const char* format, ...) {
    if (!m_bEnabled || !m_pFile)
        return;

    char buffer[512];
    va_list va;
    va_start(va, format);
    _vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, format, va);
    va_end(va);

    fputs(buffer, m_pFile);
    fputs("\n", m_pFile);
    fflush(m_pFile);
}
