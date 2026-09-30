#include "imvehft_image_aliases.hpp"
#include <cstdint>

extern "C" [[noreturn]] void __stdcall __CxxThrowException_8(
    void* exception_object,
    const void* throw_info);

extern std::uint8_t DAT_100281ac;
struct ExceptionStorage { void* __thiscall construct(char** message); };

extern "C" [[noreturn]] void __stdcall FUN_100101c2(
    char* param_1)
{
    void* local_10[3];

    reinterpret_cast<ExceptionStorage*>(local_10)->construct(&param_1);
    local_10[0] = reinterpret_cast<void**>(static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_1002221C));

    __CxxThrowException_8(local_10, &DAT_100281ac);
}
