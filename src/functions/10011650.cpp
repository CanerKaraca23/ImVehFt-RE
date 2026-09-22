#include <cstddef>
#include <cstdint>

extern "C" std::size_t __cdecl _strlen(char* _Str)
{
    std::uint32_t uVar1;
    std::uint32_t* puVar2;
    std::uint32_t* puVar3;

    puVar2 = reinterpret_cast<std::uint32_t*>(_Str);

    do
    {
        if ((static_cast<std::uint32_t>(
                 static_cast<std::uintptr_t>(
                     reinterpret_cast<std::uintptr_t>(puVar2))) &
             3u) == 0)
        {
            goto LAB_10011680;
        }

        uVar1 = *reinterpret_cast<const std::uint8_t*>(puVar2);
        puVar2 = reinterpret_cast<std::uint32_t*>(
            static_cast<std::int32_t>(
                reinterpret_cast<std::uintptr_t>(puVar2)) + 1);
    }
    while (static_cast<char>(uVar1) != '\0');

LAB_100116b3:
    return static_cast<std::size_t>(
        static_cast<std::int32_t>(
            reinterpret_cast<std::uintptr_t>(puVar2)) +
        (-1 - static_cast<std::int32_t>(
                  reinterpret_cast<std::uintptr_t>(_Str))));

LAB_10011680:
    do
    {
        do
        {
            puVar3 = puVar2;
            puVar2 = puVar3 + 1;
        }
        while (((*puVar3 ^ 0xffffffffu ^ *puVar3 + 0x7efefeffu) &
                0x81010100u) == 0);

        uVar1 = *puVar3;

        if (static_cast<char>(uVar1) == '\0')
        {
            return static_cast<std::size_t>(
                static_cast<std::int32_t>(
                    reinterpret_cast<std::uintptr_t>(puVar3)) -
                static_cast<std::int32_t>(
                    reinterpret_cast<std::uintptr_t>(_Str)));
        }

        if (static_cast<char>(uVar1 >> 8) == '\0')
        {
            return static_cast<std::size_t>(
                static_cast<std::int32_t>(
                    reinterpret_cast<std::uintptr_t>(puVar3)) +
                (1 - static_cast<std::int32_t>(
                         reinterpret_cast<std::uintptr_t>(_Str))));
        }

        if ((uVar1 & 0x00ff0000u) == 0)
        {
            return static_cast<std::size_t>(
                static_cast<std::int32_t>(
                    reinterpret_cast<std::uintptr_t>(puVar3)) +
                (2 - static_cast<std::int32_t>(
                         reinterpret_cast<std::uintptr_t>(_Str))));
        }
    }
    while ((uVar1 & 0xff000000u) != 0);

    goto LAB_100116b3;
}