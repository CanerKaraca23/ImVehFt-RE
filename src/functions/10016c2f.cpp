#include <cstddef>
#include <windows.h>

extern "C" void* __cdecl __malloc_crt(std::size_t size);
extern "C" void __cdecl _free(void* memory);

extern "C" LPVOID __cdecl ___crtGetEnvironmentStringsA(void)
{
    LPWCH lpWideCharStr;
    WCHAR* pWVar2;
    WCHAR* pWVar3;
    WCHAR WVar1;
    int iVar4;
    std::size_t _Size;
    LPSTR local_8;

    lpWideCharStr = ::GetEnvironmentStringsW();

    if (lpWideCharStr == static_cast<LPWCH>(0x0))
    {
        local_8 = static_cast<LPSTR>(0x0);
    }
    else
    {
        WVar1 = *lpWideCharStr;
        pWVar2 = lpWideCharStr;

        while (WVar1 != L'\0')
        {
            do
            {
                pWVar3 = pWVar2;
                pWVar2 = pWVar3 + 1;
            } while (*pWVar2 != L'\0');

            pWVar2 = pWVar3 + 2;
            WVar1 = *pWVar2;
        }

        iVar4 = static_cast<int>(pWVar2 - lpWideCharStr) + 1;

        _Size = static_cast<std::size_t>(
            ::WideCharToMultiByte(
                0,
                0,
                lpWideCharStr,
                iVar4,
                static_cast<LPSTR>(0x0),
                0,
                static_cast<LPCSTR>(0x0),
                static_cast<LPBOOL>(0x0)));

        if ((_Size == 0) ||
            (local_8 = static_cast<LPSTR>(__malloc_crt(_Size)),
             local_8 == static_cast<LPSTR>(0x0)))
        {
            ::FreeEnvironmentStringsW(lpWideCharStr);
            local_8 = static_cast<LPSTR>(0x0);
        }
        else
        {
            iVar4 = ::WideCharToMultiByte(
                0,
                0,
                lpWideCharStr,
                iVar4,
                local_8,
                static_cast<int>(_Size),
                static_cast<LPCSTR>(0x0),
                static_cast<LPBOOL>(0x0));

            if (iVar4 == 0)
            {
                _free(local_8);
                local_8 = static_cast<LPSTR>(0x0);
            }

            ::FreeEnvironmentStringsW(lpWideCharStr);
        }
    }

    return local_8;
}