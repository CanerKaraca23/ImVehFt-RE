#include <cstddef>
#include <cstdint>

extern "C" std::int32_t __cdecl FUN_10010893(std::size_t size);
extern "C" int __cdecl _atexit(void (__cdecl* callback)());
using ExceptionCtor = void(__thiscall*)(void* self, char** message);
extern "C" [[noreturn]] void __stdcall __CxxThrowException_8(
    void* exception_object,
    std::uint8_t* throw_info);

extern "C" std::int32_t DAT_1003c25c;
extern "C" void __cdecl thunk_FUN_100013e0();

extern void* std_bad_alloc_vftable;
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

    // Ghidra disassembly at 0x10020870 calls the CRT constructor at 0x100102c3
    // with ECX = destination object and one stack argument (&message).
    reinterpret_cast<ExceptionCtor>(0x100102c3)(exception_object, &message);
    exception_object[0] = &std_bad_alloc_vftable;

    __CxxThrowException_8(exception_object, &DAT_10028608);
}