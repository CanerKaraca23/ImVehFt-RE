#include <cstdint>

extern void* ExceptionList;
extern char DAT_00ba67a4;
extern char DAT_00ba677a;
extern char DAT_00ba68a4;
extern char DAT_00ba68a5;
extern std::int32_t DAT_1003bd90;
extern float _DAT_00c17044;
extern float _DAT_00c17048;
extern float _DAT_10024f70;
extern float _DAT_10024f78;
extern float _DAT_10024f80;

extern "C" std::int32_t __stdcall FUN_10001630();
extern "C" std::uint32_t __stdcall FUN_10010140(float, float, float, float);
extern "C" std::uint32_t __stdcall FUN_10010180();

void __stdcall FUN_10008000()
{
    void* local_10;
    std::uint8_t* puStack_c;
    std::int32_t local_8;

    local_8 = -1;
    puStack_c = reinterpret_cast<std::uint8_t*>(0x10020848);
    local_10 = ExceptionList;
    ExceptionList = reinterpret_cast<void*>(&local_10);

    reinterpret_cast<void(__stdcall*)()>(
        static_cast<std::uintptr_t>(0x727230))();

    local_8 = 0;

    if ((DAT_00ba67a4 != '\0') &&
        (DAT_00ba677a == '\0') &&
        (DAT_00ba68a4 != '\0') &&
        ((DAT_00ba68a5 == '"') || (DAT_00ba68a5 == ')')))
    {
        if (DAT_1003bd90 == 0)
        {
            DAT_1003bd90 = FUN_10001630();
        }
        else
        {
            const std::uint32_t uVar4 = FUN_10010180();
            const float fVar1 = static_cast<float>(_DAT_00c17048);
            const float fVar3 =
                static_cast<float>(_DAT_10024f80) *
                fVar1 *
                static_cast<float>(_DAT_10024f78);
            const float fVar2 =
                fVar1 *
                static_cast<float>(_DAT_10024f70) *
                static_cast<float>(_DAT_10024f78);

            const std::uint32_t uVar5 = FUN_10010140(
                static_cast<float>(_DAT_00c17044) - fVar2,
                fVar1 - fVar2,
                static_cast<float>(_DAT_00c17044) - fVar3,
                fVar1 - fVar3);

            reinterpret_cast<void(__stdcall*)(std::uint32_t, std::uint32_t)>(
                static_cast<std::uintptr_t>(0x728350))(uVar5, uVar4);
        }
    }

    local_8 = -1;

    reinterpret_cast<void(__stdcall*)()>(
        static_cast<std::uintptr_t>(0x7281e0))();

    ExceptionList = local_10;
}