#include <Windows.h>
#include <cstddef>
#include <cstdint>

struct PtdInitPrefix { DWORD _tid; DWORD _thandle; };
static_assert(offsetof(PtdInitPrefix, _tid) == 0x00);
static_assert(offsetof(PtdInitPrefix, _thandle) == 0x04);
using _ptiddata = PtdInitPrefix*;
using pthreadlocinfo = void*;



extern "C" void* __cdecl __calloc_crt(std::size_t count, std::size_t size);
extern "C" void __cdecl _free(void* memory);
extern "C" void __cdecl __initptd(_ptiddata ptd, pthreadlocinfo locale);

using fls_get_value_function = _ptiddata(__stdcall*)(DWORD);
using fls_set_value_function = int(__stdcall*)(DWORD, _ptiddata);

extern "C" LPVOID __stdcall ___set_flsgetvalue(void);

extern DWORD DAT_10029c0c;
extern void* DAT_10039a7c;

extern "C" _ptiddata __cdecl __getptd_noexit(void)
{
    DWORD dwErrCode = GetLastError();

    DWORD uVar4 = DAT_10029c0c;
    fls_get_value_function pcVar1 = reinterpret_cast<fls_get_value_function>(___set_flsgetvalue());
    _ptiddata _Ptd = pcVar1(uVar4);

    if (_Ptd == nullptr)
    {
        _Ptd = static_cast<_ptiddata>(__calloc_crt(1, 0x214));

        if (_Ptd != nullptr)
        {
            uVar4 = DAT_10029c0c;
            _ptiddata p_Var5 = _Ptd;
            pcVar1 = reinterpret_cast<fls_get_value_function>(
                DecodePointer(DAT_10039a7c));

            const int iVar2 =
                reinterpret_cast<fls_set_value_function>(pcVar1)(
                    uVar4, p_Var5);

            if (iVar2 == 0)
            {
                _free(_Ptd);
                _Ptd = nullptr;
            }
            else
            {
                __initptd(_Ptd, nullptr);

                DWORD DVar3 = GetCurrentThreadId();
                _Ptd->_thandle = 0xffffffff;
                _Ptd->_tid = DVar3;
            }
        }
    }

    SetLastError(dwErrCode);
    return _Ptd;
}