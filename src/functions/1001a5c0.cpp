#include <cstdint>

extern "C" char* __cdecl _strpbrk(char* _Str, char* _Control)
{
    std::uint8_t abStack_28[32]{};

    while (true)
    {
        const std::uint8_t bVar1 =
            *reinterpret_cast<std::uint8_t*>(_Control);

        if (bVar1 == 0)
        {
            break;
        }

        _Control = _Control + 1;
        abStack_28[static_cast<unsigned int>(bVar1) >> 3] =
            static_cast<std::uint8_t>(
                abStack_28[static_cast<unsigned int>(bVar1) >> 3] |
                (1 << (bVar1 & 7)));
    }

    std::uint8_t* pbVar2;
    std::uint8_t bVar1;

    do
    {
        pbVar2 = reinterpret_cast<std::uint8_t*>(_Str);
        bVar1 = *pbVar2;

        if (bVar1 == 0)
        {
            return nullptr;
        }

        _Str = reinterpret_cast<char*>(pbVar2 + 1);
    }
    while ((abStack_28[static_cast<unsigned int>(bVar1) >> 3] >>
            (bVar1 & 7) &
            1) == 0);

    return reinterpret_cast<char*>(pbVar2);
}