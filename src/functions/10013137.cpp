#include <cstdint>

extern "C" void __cdecl __lock(int lock_number);
extern "C" void __stdcall EnterCriticalSection(void* critical_section);

void __cdecl __lock_file2(int _Index, void* _File)
{
    if (_Index < 0x14)
    {
        __lock(_Index + 0x10);

        auto* flags = reinterpret_cast<std::uint32_t*>(
            reinterpret_cast<std::uint8_t*>(_File) + 0x0c);

        *flags = *flags | 0x8000;
        return;
    }

    EnterCriticalSection(
        reinterpret_cast<std::uint8_t*>(_File) + 0x20);
}