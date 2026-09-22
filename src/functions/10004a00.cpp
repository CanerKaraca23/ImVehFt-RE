#include <cstdint>


extern std::uint32_t _DAT_10024ea8;

extern "C" std::uint32_t* __cdecl FUN_10010ed0(std::uint32_t*, char*);
extern int __cdecl FID_conflict__sscanf(char*, char*, ...);
extern "C" void __stdcall FUN_10004000();

extern "C" void __fastcall FUN_10004a00(std::uint32_t* param_1)
{
    std::uint32_t in_EAX;
    std::uint32_t* unaff_ESI;
    __asm mov in_EAX, eax
    __asm mov unaff_ESI, esi
    std::uint32_t& field_00 =
        *reinterpret_cast<std::uint32_t*>(param_1 + 0);
    std::uint32_t& field_08_raw =
        *reinterpret_cast<std::uint32_t*>(param_1 + 2);
    float* field_08 =
        reinterpret_cast<float*>(&field_08_raw);
    std::int32_t& field_0C =
        *reinterpret_cast<std::int32_t*>(param_1 + 3);
    std::uint16_t& field_14 =
        *reinterpret_cast<std::uint16_t*>(param_1 + 5);

    std::uint32_t* puVar2;
    std::uint32_t uVar1;
    float* puVar3;
    std::int32_t* puVar4;

    field_00 = in_EAX;
    field_14 = 0;

    puVar2 = FUN_10010ed0(unaff_ESI, const_cast<char*>("_"));
    uVar1 = _DAT_10024ea8;

    if (puVar2 != nullptr)
    {
        puVar4 = &field_0C;
        puVar3 = field_08;

        puVar2 = FUN_10010ed0(unaff_ESI, const_cast<char*>("_"));
        FID_conflict__sscanf(
            reinterpret_cast<char*>(puVar2),
            const_cast<char*>("_%f_%d"),
            puVar3,
            puVar4);

        FUN_10004000();
        return;
    }

    field_0C = 0x9c4;
    field_08_raw = uVar1;

    FUN_10004000();
}