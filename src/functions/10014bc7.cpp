#include <cstddef>
#include <cstdint>

struct TidDataLocaleView
{
    std::uint8_t reserved_00[0x68];
    void* ptmbcinfo;
    void* ptlocinfo;
    std::uint32_t ownlocale;
};

static_assert(offsetof(TidDataLocaleView, ptmbcinfo) == 0x68);
static_assert(offsetof(TidDataLocaleView, ptlocinfo) == 0x6c);
static_assert(offsetof(TidDataLocaleView, ownlocale) == 0x70);

using pthreadlocinfo = void*;
extern std::uint32_t DAT_100299c0;
extern void* PTR_DAT_10029c08;
extern "C" TidDataLocaleView* __cdecl __getptd(void);
extern "C" void __cdecl __lock(int);
extern "C" std::int32_t* __cdecl __updatetlocinfoEx_nolock(
    std::uint32_t*, std::int32_t*);
extern "C" void __cdecl __amsg_exit(int);
extern "C" void __stdcall FUN_10014c34(void);

extern "C" pthreadlocinfo __cdecl ___updatetlocinfo(void)
{
    TidDataLocaleView* p_Var1;
    pthreadlocinfo ptVar2;

    p_Var1 = __getptd();

    if (((p_Var1->ownlocale & DAT_100299c0) == 0) ||
        (p_Var1->ptlocinfo == nullptr))
    {
        __lock(0x0C);

        ptVar2 = reinterpret_cast<pthreadlocinfo>(
            &p_Var1->ptlocinfo);

        __updatetlocinfoEx_nolock(
            reinterpret_cast<std::uint32_t*>(ptVar2),
            reinterpret_cast<std::int32_t*>(PTR_DAT_10029c08));

        FUN_10014c34();
    }
    else
    {
        p_Var1 = __getptd();
        ptVar2 = p_Var1->ptlocinfo;
    }

    if (ptVar2 == nullptr)
    {
        __amsg_exit(0x20);
    }

    return ptVar2;
}