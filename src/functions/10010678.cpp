#include <cstdio>

extern "C" void __cdecl __SEH_prolog4();
extern "C" int* __cdecl __errno();
extern "C" void __stdcall FUN_1001189f();
extern "C" FILE* __cdecl __getstream();
extern "C" FILE* __cdecl __openfile(
    char* _Filename,
    char* _Mode,
    int _ShFlag,
    FILE* _Stream);
extern "C" void __stdcall FUN_1001072a();
extern "C" void __cdecl __local_unwind4(
    void* _FrameInfo,
    int _TryLevel,
    int _ExceptionCode);
extern "C" void __cdecl __SEH_epilog4();

extern unsigned char DAT_10028228;
extern unsigned char DAT_10029490;

FILE* __cdecl __fsopen(char* _Filename, char* _Mode, int _ShFlag)
{
    char local_14[8];
    unsigned int uStack_c;
    unsigned char* local_8;

    __SEH_prolog4();

    local_8 = &DAT_10028228;
    uStack_c = 0x10010684;

    if (_Filename == nullptr || _Mode == nullptr || *_Mode == '\0') {
        *__errno() = 0x16;
        FUN_1001189f();
    } else {
        FILE* stream = __getstream();

        if (stream == nullptr) {
            *__errno() = 0x18;
        } else {
            local_8 = nullptr;

            if (*_Filename != '\0') {
                stream = __openfile(_Filename, _Mode, _ShFlag, stream);
                local_8 = reinterpret_cast<unsigned char*>(0xfffffffe);
                FUN_1001072a();
                __SEH_epilog4();
                return stream;
            }

            *__errno() = 0x16;

            __local_unwind4(
                &DAT_10029490,
                reinterpret_cast<int>(local_14),
                0xfffffffe);
        }
    }

    __SEH_epilog4();
    return nullptr;
}