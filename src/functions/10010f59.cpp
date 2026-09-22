#include <cstdint>

struct _tiddata;
using _ptiddata = _tiddata*;
using pthreadlocinfo = void*;

extern "C"
{
    void __cdecl __SEH_prolog4(...);
    void __cdecl __SEH_epilog4(...);
    int __cdecl __heap_init();
    int __cdecl __mtinit();
    void __cdecl __RTC_Initialize();
    char* __cdecl GetCommandLineA();
    char* __cdecl ___crtGetEnvironmentStringsA();
    int __cdecl __ioinit();
    int __cdecl __setargv();
    int __stdcall FUN_100168fe();
    int __cdecl __cinit(int);
    void __cdecl __ioterm();
    void __cdecl __mtterm();
    void __cdecl __heap_term();
    void __cdecl __cexit();
    void __stdcall FUN_10011032();
    void __cdecl ___set_flsgetvalue();
    _ptiddata __cdecl __calloc_crt(std::uint32_t, std::uint32_t);
    void* __stdcall DecodePointer(void*);
    void __cdecl __initptd(_ptiddata, pthreadlocinfo);
    std::uint32_t __stdcall GetCurrentThreadId();
    void __cdecl _free(void*);
    void __cdecl __freeptd(_ptiddata);
}

using InitializePtdFunction = int (__cdecl *)(std::uint32_t, _ptiddata);

extern int DAT_100399f0;
extern int DAT_10039a38;
extern char* DAT_1003d558;
extern char* DAT_100399f4;
extern void* DAT_10039a7c;
extern std::uint32_t DAT_10029c0c;

struct _tiddata
{
    std::uint32_t _tid;
    std::uint32_t _thandle;
};

std::uint32_t __stdcall __CRT_INIT_12(
    std::uint32_t param_1,
    int param_2,
    int param_3)
{
    int init_result = 0;
    int result = 0;
    _ptiddata ptd = nullptr;
    void* decodedPointer = nullptr;
    InitializePtdFunction initializePtd = nullptr;

    (void)param_1;
    __SEH_prolog4();

    if (param_2 == 1)
    {
        init_result = __heap_init();

        if (init_result != 0)
        {
            init_result = __mtinit();

            if (init_result != 0)
            {
                __RTC_Initialize();

                DAT_1003d558 = GetCommandLineA();
                DAT_100399f4 = ___crtGetEnvironmentStringsA();

                init_result = __ioinit();

                if (init_result >= 0)
                {
                    init_result = __setargv();

                    if (init_result >= 0)
                    {
                        init_result = FUN_100168fe();

                        if (init_result >= 0)
                        {
                            init_result = __cinit(0);

                            if (init_result == 0)
                            {
                                DAT_100399f0 = DAT_100399f0 + 1;
                                result = 1;
                                goto finish;
                            }
                        }
                    }

                    __ioterm();
                }
            }

            __mtterm();
        }

        __heap_term();
    }
    else if (param_2 == 0)
    {
        if (DAT_100399f0 > 0)
        {
            DAT_100399f0 = DAT_100399f0 - 1;

            if (DAT_10039a38 == 0)
            {
                __cexit();
            }

            if (param_3 == 0)
            {
                __ioterm();
                __mtterm();
                __heap_term();
            }

            FUN_10011032();
            result = 1;
            goto finish;
        }
    }
    else
    {
        if (param_2 != 2)
        {
            if (param_2 != 3)
            {
                result = 1;
                goto finish;
            }

            __freeptd(nullptr);
            result = 1;
            goto finish;
        }

        ___set_flsgetvalue();

        ptd = __calloc_crt(1, 0x214);

        if (ptd != nullptr)
        {
            decodedPointer = DecodePointer(DAT_10039a7c);
            initializePtd =
                reinterpret_cast<InitializePtdFunction>(decodedPointer);

            init_result = (*initializePtd)(DAT_10029c0c, ptd);

            if (init_result != 0)
            {
                __initptd(ptd, nullptr);

                ptd->_tid = GetCurrentThreadId();
                ptd->_thandle = 0xffffffffu;
                result = 1;
                goto finish;
            }

            _free(ptd);
        }
    }

finish:
    __SEH_epilog4();
    return static_cast<std::uint32_t>(result);
}
