#include <cstdint>


#include <cstddef>
#include <corecrt.h>
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
using LocaleUpdateCtor = void(__thiscall*)(void* self, _locale_t locale);

extern "C" void __cdecl __cropzeros_l(char* _Buf, _locale_t _Locale)
{
    alignas(std::uint32_t) std::uint8_t local_storage[0x10];

    // Ghidra 0x1001bb6e: ECX=local_storage, pushed _Locale, CALL 0x10010b1a.
    reinterpret_cast<LocaleUpdateCtor>(0x10010b1a)(local_storage, _Locale);

    char* pcVar1;
    char* pcVar2;
    char cVar3;

    cVar3 = *_Buf;
    if (cVar3 != '\0')
    {
        do
        {
            if (cVar3 == *reinterpret_cast<char*>(
                    *reinterpret_cast<std::uint32_t*>(
                        *reinterpret_cast<std::uint32_t**>(
                            *reinterpret_cast<std::uint32_t*>(local_storage) +
                            0xBC))))
            {
                break;
            }

            _Buf = _Buf + 1;
            cVar3 = *_Buf;
        } while (cVar3 != '\0');
    }

    if (*_Buf != '\0')
    {
        do
        {
            _Buf = _Buf + 1;
            cVar3 = *_Buf;
            pcVar1 = _Buf;

            if ((cVar3 == '\0') || (cVar3 == 'e'))
            {
                break;
            }
        } while (cVar3 != 'E');

        do
        {
            pcVar2 = pcVar1;
            pcVar1 = pcVar2 - 1;
        } while (*pcVar1 == '0');

        if (*pcVar1 == *reinterpret_cast<char*>(
                *reinterpret_cast<std::uint32_t*>(
                    *reinterpret_cast<std::uint32_t**>(
                        *reinterpret_cast<std::uint32_t*>(local_storage) +
                        0xBC))))
        {
            pcVar1 = pcVar2 - 2;
        }

        do
        {
            cVar3 = *_Buf;
            pcVar1 = pcVar1 + 1;
            _Buf = _Buf + 1;
            *pcVar1 = cVar3;
        } while (cVar3 != '\0');
    }

    if (*reinterpret_cast<char*>(local_storage + 0x0C) != '\0')
    {
        *reinterpret_cast<std::uint32_t*>(
            *reinterpret_cast<std::uint32_t*>(local_storage + 0x08) + 0x70) =
            *reinterpret_cast<std::uint32_t*>(
                *reinterpret_cast<std::uint32_t*>(local_storage + 0x08) + 0x70) &
            0xFFFFFFFDu;
    }
}