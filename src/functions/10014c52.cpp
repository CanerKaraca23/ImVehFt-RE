#include <windows.h>

extern "C" DWORD DAT_10029c10;
extern "C" LPVOID DAT_10039a78;

extern "C" LPVOID __stdcall ___set_flsgetvalue(void)
{
    LPVOID lpTlsValue = TlsGetValue(DAT_10029c10);

    if (lpTlsValue == nullptr)
    {
        lpTlsValue = DecodePointer(DAT_10039a78);
        TlsSetValue(DAT_10029c10, lpTlsValue);
    }

    return lpTlsValue;
}