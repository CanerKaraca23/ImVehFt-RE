#include <cstdint>

extern "C" int __cdecl _strcmp(char* _Str1, char* _Str2)
{
    std::uint16_t uVar1;
    std::uint32_t uVar2;
    std::uint8_t bVar3;
    std::uint8_t bVar4;
    bool bVar5;

    if ((reinterpret_cast<std::uintptr_t>(_Str1) & 3u) != 0) {
        if ((reinterpret_cast<std::uintptr_t>(_Str1) & 1u) != 0) {
            bVar4 = static_cast<std::uint8_t>(*_Str1);
            _Str1 = _Str1 + 1;
            bVar5 = bVar4 < static_cast<std::uint8_t>(*_Str2);

            if (bVar4 != static_cast<std::uint8_t>(*_Str2)) {
                goto LAB_10013b94;
            }

            _Str2 = _Str2 + 1;

            if (bVar4 == 0) {
                return 0;
            }

            if ((reinterpret_cast<std::uintptr_t>(_Str1) & 2u) == 0) {
                goto LAB_10013b60;
            }
        }

        uVar1 = *reinterpret_cast<std::uint16_t*>(_Str1);
        _Str1 = _Str1 + 2;

        bVar4 = static_cast<std::uint8_t>(uVar1);
        bVar5 = bVar4 < static_cast<std::uint8_t>(*_Str2);

        if (bVar4 != static_cast<std::uint8_t>(*_Str2)) {
            goto LAB_10013b94;
        }

        if (bVar4 == 0) {
            return 0;
        }

        bVar4 = static_cast<std::uint8_t>(uVar1 >> 8);
        bVar5 = bVar4 < static_cast<std::uint8_t>(_Str2[1]);

        if (bVar4 != static_cast<std::uint8_t>(_Str2[1])) {
            goto LAB_10013b94;
        }

        if (bVar4 == 0) {
            return 0;
        }

        _Str2 = _Str2 + 2;
    }

LAB_10013b60:
    while (true) {
        uVar2 = *reinterpret_cast<std::uint32_t*>(_Str1);

        bVar4 = static_cast<std::uint8_t>(uVar2);
        bVar5 = bVar4 < static_cast<std::uint8_t>(*_Str2);

        if (bVar4 != static_cast<std::uint8_t>(*_Str2)) {
            break;
        }

        if (bVar4 == 0) {
            return 0;
        }

        bVar4 = static_cast<std::uint8_t>(uVar2 >> 8);
        bVar5 = bVar4 < static_cast<std::uint8_t>(_Str2[1]);

        if (bVar4 != static_cast<std::uint8_t>(_Str2[1])) {
            break;
        }

        if (bVar4 == 0) {
            return 0;
        }

        bVar4 = static_cast<std::uint8_t>(uVar2 >> 0x10);
        bVar5 = bVar4 < static_cast<std::uint8_t>(_Str2[2]);

        if (bVar4 != static_cast<std::uint8_t>(_Str2[2])) {
            break;
        }

        bVar3 = static_cast<std::uint8_t>(uVar2 >> 0x18);

        if (bVar4 == 0) {
            return 0;
        }

        bVar5 = bVar3 < static_cast<std::uint8_t>(_Str2[3]);

        if (bVar3 != static_cast<std::uint8_t>(_Str2[3])) {
            break;
        }

        _Str2 = _Str2 + 4;
        _Str1 = _Str1 + 4;

        if (bVar3 == 0) {
            return 0;
        }
    }

LAB_10013b94:
    return static_cast<int>(static_cast<unsigned int>(bVar5) * -2 + 1);
}