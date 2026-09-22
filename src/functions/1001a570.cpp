#include <cstddef>
#include <cstdint>

extern "C" std::size_t __cdecl _strcspn(char* _Str, char* _Control)
{
    std::uint8_t abStack_28[32]{};
    std::uint8_t bVar1;

    while (true)
    {
        bVar1 =
            *reinterpret_cast<const std::uint8_t*>(_Control);

        if (bVar1 == 0)
        {
            break;
        }

        ++_Control;
        abStack_28[static_cast<int>(static_cast<unsigned int>(bVar1)) >> 3] =
            static_cast<std::uint8_t>(
                abStack_28[static_cast<int>(
                    static_cast<unsigned int>(bVar1)) >> 3] |
                (static_cast<std::uint8_t>(1u) << (bVar1 & 7)));
    }

    std::size_t sVar2 = static_cast<std::size_t>(0xffffffffu);

    do
    {
        sVar2 = sVar2 + 1;

        bVar1 =
            *reinterpret_cast<const std::uint8_t*>(_Str);

        if (bVar1 == 0)
        {
            return sVar2;
        }

        ++_Str;
    }
    while ((abStack_28[static_cast<int>(
                static_cast<unsigned int>(bVar1)) >> 3] >>
            (bVar1 & 7) &
            1) == 0);

    return sVar2;
}