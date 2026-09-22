#include <Windows.h>
#include <cstddef>
#include <cstdint>

struct PtdInitPrefix { DWORD _tid; DWORD _thandle; };
static_assert(offsetof(PtdInitPrefix, _tid) == 0x00);
static_assert(offsetof(PtdInitPrefix, _thandle) == 0x04);
using _ptiddata = PtdInitPrefix*;
using pthreadlocinfo = void*;

extern FARPROC DAT_10039a74, DAT_10039a78, DAT_10039a7c, DAT_10039a80;
extern DWORD DAT_10029c10, DAT_10029c0c;
extern "C" LPVOID WINAPI TlsGetValue_exref(DWORD);
extern "C" BOOL WINAPI TlsSetValue_exref(DWORD, LPVOID);
extern "C" BOOL WINAPI TlsFree_exref(DWORD);
extern "C" void CALLBACK LAB_10014c49(PVOID);
extern "C" void __stdcall __freefls_4(void*);
extern "C" void __cdecl __mtterm(void);
extern "C" void __cdecl __init_pointers(void);
extern "C" int __cdecl __mtinitlocks(void);
extern "C" void* __cdecl __calloc_crt(std::size_t, std::size_t);
extern "C" void __cdecl __initptd(_ptiddata, pthreadlocinfo);

extern "C" int __cdecl __mtinit(void)
{
    HMODULE hModule;
    BOOL BVar1;
    int iVar2;
    _ptiddata _Ptd;
    DWORD DVar4;
    _ptiddata p_Var6;

    hModule = GetModuleHandleW(L"KERNEL32.DLL");
    if (hModule == static_cast<HMODULE>(0)) {
        __mtterm();
        return 0;
    }

    DAT_10039a74 = GetProcAddress(hModule, "FlsAlloc");
    DAT_10039a78 = GetProcAddress(hModule, "FlsGetValue");
    DAT_10039a7c = GetProcAddress(hModule, "FlsSetValue");
    DAT_10039a80 = GetProcAddress(hModule, "FlsFree");

    if (((DAT_10039a74 == static_cast<FARPROC>(0)) ||
         (DAT_10039a78 == static_cast<FARPROC>(0))) ||
        (DAT_10039a7c == static_cast<FARPROC>(0)) ||
        (DAT_10039a80 == static_cast<FARPROC>(0))) {
        DAT_10039a78 = reinterpret_cast<FARPROC>(&TlsGetValue_exref);
        DAT_10039a74 = reinterpret_cast<FARPROC>(&LAB_10014c49);
        DAT_10039a7c = reinterpret_cast<FARPROC>(&TlsSetValue_exref);
        DAT_10039a80 = reinterpret_cast<FARPROC>(&TlsFree_exref);
    }

    DAT_10029c10 = TlsAlloc();
    if ((DAT_10029c10 != 0xffffffff) &&
        ((BVar1 = TlsSetValue(
              DAT_10029c10,
              reinterpret_cast<LPVOID>(DAT_10039a78)),
          BVar1 != 0))) {
        __init_pointers();

        DAT_10039a74 = reinterpret_cast<FARPROC>(EncodePointer(DAT_10039a74));
        DAT_10039a78 = reinterpret_cast<FARPROC>(EncodePointer(DAT_10039a78));
        DAT_10039a7c = reinterpret_cast<FARPROC>(EncodePointer(DAT_10039a7c));
        DAT_10039a80 = reinterpret_cast<FARPROC>(EncodePointer(DAT_10039a80));

        iVar2 = __mtinitlocks();
        if (iVar2 != 0) {
            using FlsAllocFunction =
                DWORD(__stdcall *)(PFLS_CALLBACK_FUNCTION);

            auto pcVar5 = __freefls_4;
            auto pcVar3 = reinterpret_cast<FlsAllocFunction>(
                DecodePointer(DAT_10039a74));

            DAT_10029c0c = (*pcVar3)(pcVar5);

            if ((DAT_10029c0c != -1) &&
                ((_Ptd = static_cast<_ptiddata>(__calloc_crt(1, 0x214)),
                  _Ptd != static_cast<_ptiddata>(0)))) {
                iVar2 = DAT_10029c0c;
                p_Var6 = _Ptd;

                using FlsSetValueFunction =
                    BOOL(__stdcall *)(DWORD, LPVOID);

                FlsSetValueFunction pcVar4 = reinterpret_cast<FlsSetValueFunction>(
                    DecodePointer(DAT_10039a7c));

                iVar2 = (*pcVar4)(iVar2, p_Var6);
                if (iVar2 != 0) {
                    __initptd(_Ptd, static_cast<pthreadlocinfo>(0));

                    DVar4 = GetCurrentThreadId();
                    _Ptd->_thandle = 0xffffffff;
                    _Ptd->_tid = DVar4;
                    return 1;
                }
            }
        }

        __mtterm();
    }

    return 0;
}