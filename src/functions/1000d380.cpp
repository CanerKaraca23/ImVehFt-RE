#include <cstdint>

extern std::uint32_t extraout_ECX;

extern "C" void __stdcall FUN_100101c2(char* message);
extern "C" int __fastcall FUN_1000d400(std::uint32_t count);
extern void __cdecl FID_conflict__memcpy(
    void* destination,
    const void* source,
    std::uint32_t size
);
extern void __cdecl FUN_10010756(void* pointer);

void __stdcall FUN_1000d380(std::uint32_t param_1)
{
    std::uint32_t* unaff_ESI;
    __asm mov unaff_ESI, esi

    void* pvVar1;
    int iVar2;
    void* _Dst;
    std::uint32_t uVar3;

    uVar3 = param_1;

    if (0x3fffffffU < param_1)
    {
        FUN_100101c2(const_cast<char*>("vector<T> too long"));
        uVar3 = extraout_ECX;
    }

    if (static_cast<std::uint32_t>(
            (unaff_ESI[2] - *unaff_ESI) >> 2) < uVar3)
    {
        _Dst = reinterpret_cast<void*>(static_cast<std::uintptr_t>(FUN_1000d400(uVar3)));

        FID_conflict__memcpy(
            _Dst,
            reinterpret_cast<void*>(*unaff_ESI),
            static_cast<std::uint32_t>(
                ((unaff_ESI[1] - *unaff_ESI) >> 2) * 4));

        pvVar1 = reinterpret_cast<void*>(*unaff_ESI);
        iVar2 = unaff_ESI[1];

        if (pvVar1 != nullptr)
        {
            FUN_10010756(pvVar1);
        }

        *unaff_ESI = reinterpret_cast<int>(_Dst);
        unaff_ESI[2] =
            static_cast<int>(
                static_cast<std::uintptr_t>(
                    reinterpret_cast<std::uintptr_t>(_Dst) +
                    static_cast<std::uintptr_t>(param_1) * 4));

        unaff_ESI[1] =
            static_cast<int>(
                static_cast<std::uintptr_t>(
                    reinterpret_cast<std::uintptr_t>(_Dst) +
                    static_cast<std::uintptr_t>(
                        (iVar2 -
                         reinterpret_cast<int>(pvVar1)) >> 2) *
                    4));
    }
}