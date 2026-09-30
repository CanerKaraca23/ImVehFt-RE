#include "imvehft_image_aliases.hpp"
#include <cstddef>
#include <cstdint>
#include <exception>

extern "C" int __cdecl FUN_10010893(std::size_t size);
[[noreturn]] extern void __stdcall __CxxThrowException_8(
    void* exception_object,
    void* throw_info
);
extern void* DAT_10028608;

struct ExceptionStorage
{
    void* __thiscall construct(char** param_1);
};

extern "C" int __fastcall FUN_1000d400(std::uint32_t param_1)
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
    reinterpret_cast<ExceptionStorage*>(local_14)->construct(&local_8);

    local_14[0] = reinterpret_cast<void*>(static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_10022250));

    __CxxThrowException_8(local_14, &DAT_10028608);
}
