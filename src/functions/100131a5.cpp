#include <cstdint>

extern "C" void __cdecl FUN_10017cd2(int lock_number);
extern "C" void __stdcall LeaveCriticalSection(void* critical_section);

void __cdecl __unlock_file2(int _Index, void* _File)
{
    if (_Index < 0x14)
    {
        auto* flags = reinterpret_cast<std::uint32_t*>(
            reinterpret_cast<std::uint8_t*>(_File) + 0x0c);

        *flags = *flags & 0xffff7fff;

        FUN_10017cd2(_Index + 0x10);
        return;
    }

    LeaveCriticalSection(
        reinterpret_cast<std::uint8_t*>(_File) + 0x20);
}