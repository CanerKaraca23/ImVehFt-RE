#include <windows.h>

extern "C" int DAT_10029c0c;
extern "C" LPVOID DAT_10039a80;
extern "C" DWORD DAT_10029c10;

extern "C" void __cdecl __mtdeletelocks(void);

extern "C" void __cdecl __mtterm(void)
{
    if (DAT_10029c0c != -1)
    {
        const int value = DAT_10029c0c;
        auto callback = reinterpret_cast<void(__cdecl *)(int)>(
            DecodePointer(DAT_10039a80));

        callback(value);
        DAT_10029c0c = -1;
    }

    if (DAT_10029c10 != 0xFFFFFFFFu)
    {
        TlsFree(DAT_10029c10);
        DAT_10029c10 = 0xFFFFFFFFu;
    }

    __mtdeletelocks();
}