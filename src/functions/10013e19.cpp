#include <cstddef>
#include <cstdint>
#include <corecrt.h>
extern "C" void __stdcall FUN_10013ebb();

extern "C" int __cdecl flsall(int param_1)
{
    struct CRT_FILE
    {
        unsigned char padding[0x0C];
        unsigned int _flag;
    };

    extern int DAT_1003d540;
    extern void* DAT_1003c520[];

    extern void __cdecl __SEH_prolog4(...);
    extern void __stdcall __SEH_epilog4();
    extern void __cdecl __lock(int);
    extern void __cdecl __lock_file2(int, void*);
    extern int __cdecl __fflush_nolock(CRT_FILE*);
    extern void __stdcall FUN_10013eea();

    __SEH_prolog4();

    int local_20 = 0;
    int local_28 = 0;

    __lock(1);

    for (int _Index = 0; _Index < DAT_1003d540; _Index = _Index + 1)
    {
        void* file = DAT_1003c520[_Index];

        if ((file != 0) &&
            ((*reinterpret_cast<unsigned char*>(
                  reinterpret_cast<unsigned char*>(file) + 0x0C) &
              0x83) != 0))
        {
            __lock_file2(_Index, file);

            CRT_FILE* stream =
                static_cast<CRT_FILE*>(DAT_1003c520[_Index]);

            if ((stream->_flag & 0x83U) != 0U)
            {
                if (param_1 == 1)
                {
                    int iVar2 = __fflush_nolock(stream);

                    if (iVar2 != -1)
                    {
                        local_20 = local_20 + 1;
                    }
                }
                else if ((param_1 == 0) &&
                         ((stream->_flag & 2U) != 0U))
                {
                    int iVar2 = __fflush_nolock(stream);

                    if (iVar2 == -1)
                    {
                        local_28 = -1;
                    }
                }
            }

            FUN_10013ebb();
        }
    }

    FUN_10013eea();

    if (param_1 != 1)
    {
        local_20 = local_28;
    }

    __SEH_epilog4();
    return local_20;
}