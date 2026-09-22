#include <cstdint>

extern "C" std::uintptr_t DAT_1003c420[];
extern "C" void __cdecl __unlock_fhandle(int fileHandle);

extern "C" void __stdcall FUN_10018a8b()
{
    std::int32_t ebpValue;
    std::uint32_t* esiValue;
    std::int32_t ediValue;

    __asm {
        mov ebpValue, ebp
        mov esiValue, esi
        mov ediValue, edi
    }

    if (*reinterpret_cast<std::int32_t*>(
            static_cast<std::uintptr_t>(ebpValue) - 0x1c) != ediValue) {
        if (*reinterpret_cast<std::int32_t*>(
                static_cast<std::uintptr_t>(ebpValue) - 0x20) != ediValue) {
            auto* flag = reinterpret_cast<std::uint8_t*>(
                DAT_1003c420[
                    static_cast<std::int32_t>(*esiValue) >> 5] +
                4 +
                (*esiValue & 0x1f) * 0x40);

            *flag = static_cast<std::uint8_t>(*flag & 0xfe);
        }

        __unlock_fhandle(static_cast<int>(*esiValue));
    }
}