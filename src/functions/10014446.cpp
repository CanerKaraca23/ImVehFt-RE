#include <cstdint>
#include <windows.h>

struct __pthreadlocinfo;
using pthreadlocinfo = __pthreadlocinfo*;
struct __pthreadmbcinfo
{
    LONG refcount;
};
using pthreadmbcinfo = __pthreadmbcinfo*;
struct __ptiddata_impl
{
    std::uint8_t reserved_00[0x68];
    pthreadmbcinfo ptmbcinfo;
    pthreadlocinfo ptlocinfo;
    std::uint32_t _ownlocale;
};
using _ptiddata = __ptiddata_impl*;
static_assert(offsetof(__ptiddata_impl, ptmbcinfo) == 0x68);
static_assert(offsetof(__ptiddata_impl, ptlocinfo) == 0x6c);
static_assert(offsetof(__ptiddata_impl, _ownlocale) == 0x70);

extern LONG DAT_100299c0;
extern LONG DAT_100294a0;
extern pthreadmbcinfo PTR_DAT_100298c8;
extern "C" void __cdecl __SEH_prolog4(std::uint32_t, int);
extern "C" void __stdcall __SEH_epilog4();
extern "C" _ptiddata __cdecl __getptd();
extern "C" void __cdecl __lock(int);
extern "C" void __cdecl _free(void*);
extern "C" void __cdecl __amsg_exit(int);
extern "C" void __stdcall FUN_100144e1();

pthreadmbcinfo __cdecl ___updatetmbcinfo(void)
{
    _ptiddata p_Var1;
    LONG LVar2;
    pthreadmbcinfo lpAddend;

    __SEH_prolog4(0x10028370u, 0x0c);
    p_Var1 = __getptd();

    if (((p_Var1->_ownlocale & DAT_100299c0) == 0) ||
        (p_Var1->ptlocinfo == (pthreadlocinfo)0x0))
    {
        __lock(0xd);
        lpAddend = p_Var1->ptmbcinfo;

        if (lpAddend != (pthreadmbcinfo)PTR_DAT_100298c8)
        {
            if (lpAddend != (pthreadmbcinfo)0x0)
            {
                LVar2 = InterlockedDecrement(&lpAddend->refcount);

                if ((LVar2 == 0) &&
                    (lpAddend != (pthreadmbcinfo)&DAT_100294a0))
                {
                    _free(lpAddend);
                }
            }

            p_Var1->ptmbcinfo = (pthreadmbcinfo)PTR_DAT_100298c8;
            lpAddend = (pthreadmbcinfo)PTR_DAT_100298c8;
            InterlockedIncrement((LONG *)PTR_DAT_100298c8);
        }

        FUN_100144e1();
    }
    else
    {
        lpAddend = p_Var1->ptmbcinfo;
    }

    if (lpAddend == (pthreadmbcinfo)0x0)
    {
        __amsg_exit(0x20);
    }

    __SEH_epilog4();
    return lpAddend;
}