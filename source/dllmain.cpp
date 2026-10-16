#include "common.h"
#include "Log.h"
#include "Hooks.h"
#include "CustomPlates.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hinstDLL);

        char szModulePath[MAX_PATH] = { 0 };
        GetModuleFileNameA(hinstDLL, szModulePath, sizeof(szModulePath));

        // 1. Initialize Log
        CLog::Initialise(szModulePath);

        // 2. Install early engine hook at 0x5BD779
        CHooks::InstallEarlyHooks();

        CLog::Write("ImVehFt %s early attachment complete.", IVF_VERSION_STRING);
        return TRUE;
    }
    else if (fdwReason == DLL_PROCESS_DETACH) {
        CLog::Write("ImVehFt shutting down.");
        CCustomPlates::Shutdown();
        CLog::Close();
        return TRUE;
    }

    return TRUE;
}
