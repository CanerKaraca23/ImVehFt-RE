#include <Windows.h>
#include <cstdint>
#include <cstdio>

extern "C" int DAT_1003d540;
extern "C" int* DAT_1003c520;

extern "C" void __cdecl __SEH_prolog4();
extern "C" void __cdecl __SEH_epilog4();
extern "C" void __cdecl __lock(int);
extern "C" int __cdecl fclose(FILE*);
extern "C" void __cdecl _free(void*);
extern "C" void __stdcall FUN_1001826f();

extern "C" int __cdecl _fcloseall(void)
{
    __SEH_prolog4();

    int local_20 = 0;
    __lock(1);

    for (int iVar2 = 3; iVar2 < DAT_1003d540; iVar2 = iVar2 + 1)
    {
        int* slot = DAT_1003c520 + iVar2;

        if (*slot != 0)
        {
            FILE* _File = reinterpret_cast<FILE*>(
                static_cast<std::uintptr_t>(*slot));

            if ((*reinterpret_cast<int*>(_File) & 0x83) != 0)
            {
                int iVar1 = fclose(_File);

                if (iVar1 != -1)
                {
                    local_20 = local_20 + 1;
                }
            }

            if (0x13 < iVar2)
            {
                DeleteCriticalSection(
                    reinterpret_cast<LPCRITICAL_SECTION>(
                        static_cast<std::uintptr_t>(*slot) + 0x20));

                _free(reinterpret_cast<void*>(
                    static_cast<std::uintptr_t>(*slot)));

                *slot = 0;
            }
        }
    }

    FUN_1001826f();
    __SEH_epilog4();

    return local_20;
}