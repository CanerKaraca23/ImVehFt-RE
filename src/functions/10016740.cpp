#include <cstddef>
#include <cstdint>

extern "C" int DAT_1003c414;
extern "C" void* __cdecl __VEC_memzero(void* destination, std::size_t size);

extern "C" void* __cdecl _memset(
    void* _Dst,
    int _Val,
    std::size_t _Size)
{
    std::uint32_t uVar1;
    std::uint32_t uVar3;
    std::size_t sVar4;
    std::uint32_t* puVar5;

    if (_Size == 0)
    {
        return _Dst;
    }

    uVar1 = static_cast<std::uint32_t>(_Val) & 0xffu;

    if ((static_cast<char>(_Val) == '\0') &&
        (0x7f < _Size) &&
        (DAT_1003c414 != 0))
    {
        return __VEC_memzero(_Dst, _Size);
    }

    puVar5 = static_cast<std::uint32_t*>(_Dst);

    if (3 < _Size)
    {
        uVar3 =
            static_cast<std::uint32_t>(
                -static_cast<std::int32_t>(
                    reinterpret_cast<std::uintptr_t>(_Dst))) &
            3u;

        sVar4 = _Size;

        if (uVar3 != 0)
        {
            sVar4 = _Size - uVar3;

            do
            {
                *reinterpret_cast<char*>(puVar5) = static_cast<char>(_Val);
                puVar5 = reinterpret_cast<std::uint32_t*>(
                    reinterpret_cast<std::uintptr_t>(puVar5) + 1);
                uVar3 = uVar3 - 1;
            }
            while (uVar3 != 0);
        }

        uVar1 = uVar1 * 0x1010101u;
        _Size = sVar4 & 3u;
        uVar3 = static_cast<std::uint32_t>(sVar4 >> 2);

        if (uVar3 != 0)
        {
            for (; uVar3 != 0; uVar3 = uVar3 - 1)
            {
                *puVar5 = uVar1;
                puVar5 = puVar5 + 1;
            }

            if (_Size == 0)
            {
                return _Dst;
            }
        }
    }

    do
    {
        *reinterpret_cast<char*>(puVar5) = static_cast<char>(uVar1);
        puVar5 = reinterpret_cast<std::uint32_t*>(
            reinterpret_cast<std::uintptr_t>(puVar5) + 1);
        _Size = _Size - 1;
    }
    while (_Size != 0);

    return _Dst;
}