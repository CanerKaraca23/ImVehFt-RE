#include <cstddef>
#include <cstdint>

extern "C" void* __cdecl _malloc(std::size_t size);
extern "C" int __cdecl __callnewh(std::size_t size);
extern "C" int __cdecl _atexit(void (__cdecl* callback)());

extern "C" [[noreturn]] void __stdcall __CxxThrowException_8(
    void* exception_object,
    const void* throw_info);

extern std::uint32_t _DAT_100399ec;
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
        using BadAllocInitFn = void (__thiscall*)(void*, const std::uint32_t*);
        reinterpret_cast<BadAllocInitFn>(static_cast<std::uintptr_t>(0x1001023b))(
            &DAT_100399e0, reinterpret_cast<const std::uint32_t*>(&local_8));

        DAT_100399e0.vtable =
            reinterpret_cast<void**>(static_cast<std::uintptr_t>(0x10022250));

        _atexit(reinterpret_cast<void (__cdecl*)()>(FUN_10021267));
    }

    using BadAllocCopyCtorFn = void* (__thiscall*)(void*, void*);
    reinterpret_cast<BadAllocCopyCtorFn>(static_cast<std::uintptr_t>(0x10010351))(
        local_14, &DAT_100399e0);
    local_14[0] = reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x10022250));

    __CxxThrowException_8(local_14, &DAT_10028608);
}