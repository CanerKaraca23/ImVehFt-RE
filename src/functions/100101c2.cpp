#include <cstdint>

extern "C" [[noreturn]] void __stdcall __CxxThrowException_8(
    void* exception_object,
    const void* throw_info);

extern std::uint8_t DAT_100281ac;

extern "C" [[noreturn]] void __stdcall FUN_100101c2(
    char* param_1)
{
    void* local_10[3];

    using ExceptionCtorFn = void* (__thiscall*)(void*, char**);
    reinterpret_cast<ExceptionCtorFn>(static_cast<std::uintptr_t>(0x100102c3))(local_10, &param_1);
    local_10[0] = reinterpret_cast<void**>(static_cast<std::uintptr_t>(0x1002221c));

    __CxxThrowException_8(local_10, &DAT_100281ac);
}