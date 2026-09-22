#include <cstddef>
#include <cstdint>
#include <exception>

extern "C" int __cdecl FUN_10010893(std::size_t size);
[[noreturn]] extern void __stdcall __CxxThrowException_8(
    void* exception_object,
    void* throw_info
);
extern void* DAT_10028608;

int __fastcall FUN_1000d400(std::uint32_t param_1)
{
    int iVar1;
    void* local_14[3];
    char* local_8;

    if (param_1 == 0U)
    {
        return 0;
    }

    if ((param_1 < 0x40000000U) &&
        (iVar1 = FUN_10010893(param_1 * 4U), iVar1 != 0))
    {
        return iVar1;
    }

    local_8 = nullptr;
    using ExceptionCtorFn = void* (__thiscall*)(void*, char**);
    reinterpret_cast<ExceptionCtorFn>(
        static_cast<std::uintptr_t>(0x100102c3))(local_14, &local_8);

    local_14[0] = reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x10022250));

    __CxxThrowException_8(local_14, &DAT_10028608);
}