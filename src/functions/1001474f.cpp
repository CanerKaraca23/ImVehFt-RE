#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <windows.h>
#include <stdio.h>
using undefined = unsigned char;
using undefined4 = std::uint32_t;
using uint = std::uint32_t;
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined8 = std::uint64_t;
extern "C" int* __cdecl __errno(void);
extern "C" void __cdecl __SEH_prolog4(std::uint32_t, int);
extern "C" void __stdcall __SEH_epilog4(void);
extern "C" void* __cdecl __malloc_crt(std::size_t);
extern "C" int __cdecl __setmbcp_nolock(int, int);
#include <cstddef>
#include <cstdint>
#include <windows.h>

using byte = std::uint8_t;
struct __pthreadlocinfo;
using pthreadlocinfo = __pthreadlocinfo*;
struct __pthreadmbcinfo
{
    LONG refcount;                         // Ghidra: [base + 0x00]
    std::uint32_t mbcodepage;              // Ghidra: [base + 0x04]
    std::uint32_t ismbcodepage;            // Ghidra: [base + 0x08]
    std::uint16_t mbulinfo[8];             // Ghidra: reads words at +0x10..+0x18
    std::uint8_t mbctype[0x101];           // Ghidra: copy loop reads base + 0x1c
    std::uint8_t mbcasemap[0x100];         // Ghidra: copy loop reads base + 0x11d
    std::uint8_t reserved_21d[3];
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
static_assert(offsetof(__pthreadmbcinfo, refcount) == 0x00);
static_assert(offsetof(__pthreadmbcinfo, mbcodepage) == 0x04);
static_assert(offsetof(__pthreadmbcinfo, ismbcodepage) == 0x08);
static_assert(offsetof(__pthreadmbcinfo, mbulinfo) == 0x0c);
static_assert(offsetof(__pthreadmbcinfo, mbctype) == 0x1c);
static_assert(offsetof(__pthreadmbcinfo, mbcasemap) == 0x11d);
static_assert(sizeof(__pthreadmbcinfo) == 0x220);
static_assert(offsetof(__ptiddata_impl, ptmbcinfo) == 0x68);
static_assert(offsetof(__ptiddata_impl, ptlocinfo) == 0x6c);
static_assert(offsetof(__ptiddata_impl, _ownlocale) == 0x70);

extern LONG DAT_100299c0;
extern LONG DAT_100294a0;
extern void* PTR_DAT_100298c8;
extern std::uint32_t _DAT_10039a68;
extern std::uint32_t _DAT_10039a6c;
extern std::uint32_t _DAT_10039a70;
extern std::uint16_t DAT_10039a5c;
extern byte DAT_100296c0;
extern byte DAT_100297c8;
extern "C" _ptiddata __cdecl __getptd(void);
extern "C" pthreadmbcinfo __cdecl ___updatetmbcinfo(void);
extern "C" void __cdecl __lock(int);
extern "C" void __cdecl _free(void*);
extern "C" void __stdcall FUN_100148b0(void);

extern "C" int __cdecl getSystemCP(void);

static int __cdecl getSystemCP_from_esi(int code_page)
{
    int result;
    __asm {
        push esi
        mov esi, code_page
        call getSystemCP
        mov result, eax
        pop esi
    }
    return result;
}

int __cdecl __setmbcp(int _CodePage)
{
    _ptiddata p_Var1;
    int iVar2;
    pthreadmbcinfo ptVar3;
    LONG LVar4;
    int* piVar5;
    int iVar6;
    pthreadmbcinfo ptVar7;
    pthreadmbcinfo ptVar8;
    int local_24;

    __SEH_prolog4(0x10028390u, 0x14);

    local_24 = -1;
    p_Var1 = __getptd();
    ___updatetmbcinfo();

    ptVar3 = p_Var1->ptmbcinfo;
    iVar2 = getSystemCP_from_esi(_CodePage);

    if (static_cast<std::uint32_t>(iVar2) == ptVar3->mbcodepage)
    {
        local_24 = 0;
    }
    else
    {
        ptVar3 = (pthreadmbcinfo)__malloc_crt(0x220);

        if (ptVar3 != (pthreadmbcinfo)0)
        {
            ptVar7 = p_Var1->ptmbcinfo;
            ptVar8 = ptVar3;

            for (iVar6 = 0x88; iVar6 != 0; iVar6 = iVar6 + -1)
            {
                ptVar8->refcount = ptVar7->refcount;
                ptVar7 = (pthreadmbcinfo)&ptVar7->mbcodepage;
                ptVar8 = (pthreadmbcinfo)&ptVar8->mbcodepage;
            }

            ptVar3->refcount = 0;
            local_24 = __setmbcp_nolock(iVar2, (int)ptVar3);

            if (local_24 == 0)
            {
                LVar4 =
                    InterlockedDecrement(&p_Var1->ptmbcinfo->refcount);

                if ((LVar4 == 0) &&
                    (p_Var1->ptmbcinfo !=
                     (pthreadmbcinfo)&DAT_100294a0))
                {
                    _free(p_Var1->ptmbcinfo);
                }

                p_Var1->ptmbcinfo = ptVar3;
                InterlockedIncrement(&ptVar3->refcount);

                if (((p_Var1->_ownlocale & 2) == 0) &&
                    (((byte)DAT_100299c0 & 1) == 0))
                {
                    __lock(0xd);

                    _DAT_10039a68 = ptVar3->mbcodepage;
                    _DAT_10039a6c = ptVar3->ismbcodepage;
                    _DAT_10039a70 = *(undefined4*)ptVar3->mbulinfo;

                    for (iVar2 = 0; iVar2 < 5; iVar2 = iVar2 + 1)
                    {
                        (&DAT_10039a5c)[iVar2] =
                            ptVar3->mbulinfo[iVar2 + 2];
                    }

                    for (iVar2 = 0; iVar2 < 0x101; iVar2 = iVar2 + 1)
                    {
                        (&DAT_100296c0)[iVar2] =
                            ptVar3->mbctype[iVar2 + 4];
                    }

                    for (iVar2 = 0; iVar2 < 0x100; iVar2 = iVar2 + 1)
                    {
                        (&DAT_100297c8)[iVar2] =
                            ptVar3->mbcasemap[iVar2 + 4];
                    }

                    LVar4 =
                        InterlockedDecrement(
                            (LONG*)PTR_DAT_100298c8);

                    if ((LVar4 == 0) &&
                        (PTR_DAT_100298c8 != &DAT_100294a0))
                    {
                        _free(PTR_DAT_100298c8);
                    }

                    PTR_DAT_100298c8 = (undefined*)ptVar3;
                    InterlockedIncrement(&ptVar3->refcount);
                    FUN_100148b0();
                }
            }
            else if (local_24 == -1)
            {
                if (ptVar3 !=
                    (pthreadmbcinfo)&DAT_100294a0)
                {
                    _free(ptVar3);
                }

                piVar5 = __errno();
                *piVar5 = 0x16;
            }
        }
    }

    __SEH_epilog4();
    return local_24;
}