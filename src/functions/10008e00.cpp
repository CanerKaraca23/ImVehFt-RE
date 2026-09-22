#include <cstdint>

extern std::int32_t DAT_1003c248;
extern std::int32_t* _DAT_00b74494;


extern "C" std::int32_t __stdcall FUN_10009360();

extern "C" std::int32_t __stdcall FUN_10008e00(void)
{
    std::int32_t in_EAX;
    __asm mov in_EAX, eax
    const std::int32_t iVar1 = DAT_1003c248;
    const std::int32_t iVar2 = FUN_10009360();

    return *reinterpret_cast<std::int32_t*>(
               *reinterpret_cast<std::int32_t*>(
                   static_cast<std::uintptr_t>(iVar2) + 0x48u) +
               ((in_EAX - *_DAT_00b74494) / 0xA18) * 4) +
           iVar1;
}