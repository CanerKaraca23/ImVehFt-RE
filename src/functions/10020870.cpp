#include <cstddef>
#include <cstdint>
#include "imvehft_image_aliases.hpp"

extern "C" std::int32_t __cdecl FUN_10010893(std::size_t size);
extern "C" int __cdecl _atexit(void (__cdecl* callback)());
struct ExceptionStorage { void* __thiscall construct(char** message); };
extern "C" [[noreturn]] void __stdcall __CxxThrowException_8(
    void* exception_object,
    std::uint8_t* throw_info);

extern "C" std::int32_t DAT_1003c25c;
extern "C" void __cdecl thunk_FUN_100013e0();

extern std::uint8_t DAT_10028608;

extern "C" void __stdcall FUN_10020870()
{
    const std::int32_t allocation = FUN_10010893(0x14);

    if (allocation != 0) {
        DAT_1003c25c = allocation;

        *reinterpret_cast<std::int32_t*>(allocation) = allocation;
        *reinterpret_cast<std::int32_t*>(DAT_1003c25c + 4) = DAT_1003c25c;

        _atexit(reinterpret_cast<void (__cdecl*)()>(thunk_FUN_100013e0));
        return;
    }

    void* exception_object[3];
    char* message = nullptr;

    reinterpret_cast<ExceptionStorage*>(exception_object)->construct(&message);
    exception_object[0] = reinterpret_cast<void*>(
        static_cast<std::uintptr_t>(IVF_IMAGE_ADDRESS_10022250));

    __CxxThrowException_8(exception_object, &DAT_10028608);
}
