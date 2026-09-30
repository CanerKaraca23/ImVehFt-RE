#include <cstdint>

using PureCallHandler = void (*)();

extern "C" void* __stdcall DecodePointer(void* pointer);
extern "C" void __cdecl __NMSG_WRITE(std::uint32_t message);
extern "C" unsigned int __cdecl __set_abort_behavior(
    std::uint32_t flags,
    std::uint32_t mask);
extern "C" [[noreturn]] void __cdecl _abort();

extern void* DAT_1003a1c0;

void __stdcall __purecall(void)
{
    const auto handler =
        reinterpret_cast<PureCallHandler>(DecodePointer(DAT_1003a1c0));

    if (handler != nullptr)
    {
        handler();
    }

    __NMSG_WRITE(0x19);
    __set_abort_behavior(0, 1);
    _abort();
}
