#include <cstdint>

extern std::uint32_t _DAT_1003c400;
extern const char* _DAT_1003c3f0;
extern std::uint8_t DAT_1003c3f4;
extern std::uint8_t DAT_1003c3f5;
extern std::uint8_t DAT_1003c3f6;
extern std::uint8_t DAT_1003c3f7;
extern std::uint8_t DAT_1003c3f8;
extern std::uint8_t DAT_1003c3f9;

extern "C" void __stdcall FUN_10009120();
extern "C" int* __cdecl FUN_10009060(int*, std::uint8_t*, int);
extern "C" void __cdecl FUN_10008e40(void*);

struct FUN_10009610_this { void __thiscall invoke(int param_1, int param_2); };

void FUN_10009610_this::invoke(int param_1, int param_2)
{
    void* this_ = static_cast<void*>(this);
    void* local_8 = this_;
    std::uint8_t* unaff_EDI;

#if defined(_MSC_VER) && defined(_M_IX86)
    __asm mov unaff_EDI, edi
#elif defined(__GNUC__) && defined(__i386__)
    register std::uint8_t* edi_value __asm__("edi");
    unaff_EDI = edi_value;
#else
#error "FUN_10009610 requires an incoming EDI register value"
#endif

    if ((_DAT_1003c400 & 1u) == 0u)
    {
        _DAT_1003c400 = _DAT_1003c400 | 1u;
        _DAT_1003c3f0 = "Unknown Plugin Name";
        DAT_1003c3f9 = 0;
        DAT_1003c3f8 = 0;
        DAT_1003c3f7 = 0;
        DAT_1003c3f6 = 0;
        DAT_1003c3f5 = 0;
        DAT_1003c3f4 = 0;
        FUN_10009120();
    }

    int* piVar2 = FUN_10009060(
        reinterpret_cast<int*>(&local_8),
        unaff_EDI,
        static_cast<int>(reinterpret_cast<std::uintptr_t>(this_)));

    std::uint32_t uVar1 = _DAT_1003c400 & 1u;

    *reinterpret_cast<int*>(param_1 + param_2 * 4) = *piVar2;

    if (uVar1 == 0u)
    {
        _DAT_1003c400 = _DAT_1003c400 | 1u;
        _DAT_1003c3f0 = "Unknown Plugin Name";
        DAT_1003c3f9 = 0;
        DAT_1003c3f8 = 0;
        DAT_1003c3f7 = 0;
        DAT_1003c3f6 = 0;
        DAT_1003c3f5 = 0;
        DAT_1003c3f4 = 0;
        FUN_10009120();
    }

    FUN_10008e40(unaff_EDI + 5);
}