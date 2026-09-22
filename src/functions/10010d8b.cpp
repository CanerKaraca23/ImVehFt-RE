#include <cstddef>
#include <cstdint>

int __cdecl strncmp(char* _Str1, char* _Str2, std::size_t _MaxCount)
{
    std::uint8_t* pbVar1;
    std::uint32_t uVar2;
    std::uint8_t* pbVar3;
    std::uint32_t uVar4;
    std::uint32_t local_8 = 0;

    if (_MaxCount != 0)
    {
        if ((_MaxCount > 3) &&
            (pbVar1 = reinterpret_cast<std::uint8_t*>(_Str1),
             pbVar3 = reinterpret_cast<std::uint8_t*>(_Str2),
             _MaxCount != 4))
        {
            do
            {
                _Str1 = reinterpret_cast<char*>(pbVar1 + 4);
                _Str2 = reinterpret_cast<char*>(pbVar3 + 4);

                if ((*pbVar1 == 0) || (*pbVar1 != *pbVar3))
                {
                    uVar2 = static_cast<std::uint32_t>(*pbVar1);
                    uVar4 = static_cast<std::uint32_t>(*pbVar3);
                    goto LAB_10010e47;
                }

                if ((pbVar1[1] == 0) || (pbVar1[1] != pbVar3[1]))
                {
                    uVar2 = static_cast<std::uint32_t>(pbVar1[1]);
                    uVar4 = static_cast<std::uint32_t>(pbVar3[1]);
                    goto LAB_10010e47;
                }

                if ((pbVar1[2] == 0) || (pbVar1[2] != pbVar3[2]))
                {
                    uVar2 = static_cast<std::uint32_t>(pbVar1[2]);
                    uVar4 = static_cast<std::uint32_t>(pbVar3[2]);
                    goto LAB_10010e47;
                }

                if ((pbVar1[3] == 0) || (pbVar1[3] != pbVar3[3]))
                {
                    uVar2 = static_cast<std::uint32_t>(pbVar1[3]);
                    uVar4 = static_cast<std::uint32_t>(pbVar3[3]);
                    goto LAB_10010e47;
                }

                local_8 = local_8 + 4;
                pbVar1 = reinterpret_cast<std::uint8_t*>(_Str1);
                pbVar3 = reinterpret_cast<std::uint8_t*>(_Str2);
            }
            while (local_8 < _MaxCount - 4);
        }

        for (; local_8 < _MaxCount; local_8 = local_8 + 1)
        {
            if ((*_Str1 == 0) || (*_Str1 != *_Str2))
            {
                uVar2 = static_cast<std::uint32_t>(
                    static_cast<std::uint8_t>(*_Str1));
                uVar4 = static_cast<std::uint32_t>(
                    static_cast<std::uint8_t>(*_Str2));

LAB_10010e47:
                return uVar2 - uVar4;
            }

            _Str1 = _Str1 + 1;
            _Str2 = _Str2 + 1;
        }
    }

    return 0;
}