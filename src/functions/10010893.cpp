#include "imvehft_image_aliases.hpp"
#include <cstddef>
#include <cstdint>

extern "C" void* __cdecl _malloc(std::size_t size);
extern "C" int __cdecl __callnewh(std::size_t size);
extern "C" int __cdecl _atexit(void (__cdecl* callback)());

extern "C" [[noreturn]] void __stdcall __CxxThrowException_8(
    void* exception_object,
    const void* throw_info);

extern std::uint32_t _DAT_100399ec;
struct ExceptionStorage {
    void** vtable;
    char* what;
    std::uint8_t do_free;
    ExceptionStorage* __thiscall copy_construct(ExceptionStorage* other);
};
struct FUN_1001023b_this
{
    void __thiscall invoke(
        const std::uint32_t* message,
        std::uint32_t unused_stack_param);
};
struct BadAllocStorage { void** vtable; char* what; std::uint8_t do_free; };
extern BadAllocStorage DAT_100399e0;
extern std::uint8_t DAT_10028608;

extern "C" void __stdcall FUN_10021267();

extern "C" void __cdecl FUN_10010893(std::size_t param_1)
{
    void* pvVar2;
    int iVar1;
    void* local_14[3];
    char* local_8;

    do
    {
        pvVar2 = _malloc(param_1);
        if (pvVar2 != nullptr)
        {
            return;
        }

        iVar1 = __callnewh(param_1);
    }
    while (iVar1 != 0);

    if ((_DAT_100399ec & 1u) == 0)
    {
        _DAT_100399ec |= 1u;

        local_8 = const_cast<char*>("bad allocation");
        reinterpret_cast<FUN_1001023b_this*>(&DAT_100399e0)->invoke(
            reinterpret_cast<const std::uint32_t*>(&local_8),
            1u);

        DAT_100399e0.vtable =
            reinterpret_cast<void**>(static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_10022250));

        _atexit(reinterpret_cast<void (__cdecl*)()>(FUN_10021267));
    }

    reinterpret_cast<ExceptionStorage*>(local_14)->copy_construct(
        reinterpret_cast<ExceptionStorage*>(&DAT_100399e0));
    local_14[0] = reinterpret_cast<void*>(static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_10022250));

    __CxxThrowException_8(local_14, &DAT_10028608);
}
