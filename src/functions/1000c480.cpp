#include <cstdint>

extern std::uint32_t _DAT_1003c400;
extern const char* _DAT_1003c3f0;
extern std::uint16_t _DAT_1003c3f4;
extern std::uint16_t _DAT_1003c3f6;

extern "C" void __stdcall FUN_10009120();
extern "C" int* __cdecl FUN_10009060(
    int*,
    std::uint8_t*,
    int
);

extern "C" void __cdecl FUN_1000c480_impl(
    std::int32_t* eax_input,
    int* param_1,
    int* param_2,
    int* param_3,
    int* param_4,
    int* param_5
) {
    int local_8;
    int length;
    std::uint8_t* data;
    int* result;

    if (*eax_input != 0)
    {
        length = eax_input[1];
        data = reinterpret_cast<std::uint8_t*>(*eax_input);

        if ((_DAT_1003c400 & 1u) == 0)
        {
            _DAT_1003c400 = _DAT_1003c400 | 1u;
            _DAT_1003c3f0 = "Unknown Plugin Name";
            _DAT_1003c3f6 = 0;
            _DAT_1003c3f4 = 0;
            FUN_10009120();
        }

        result = FUN_10009060(&local_8, data, length);
        *param_1 = *result;
    }

    if (*param_2 != 0)
    {
        length = param_2[1];
        data = reinterpret_cast<std::uint8_t*>(*param_2);

        if ((_DAT_1003c400 & 1u) == 0)
        {
            _DAT_1003c400 = _DAT_1003c400 | 1u;
            _DAT_1003c3f0 = "Unknown Plugin Name";
            _DAT_1003c3f6 = 0;
            _DAT_1003c3f4 = 0;
            FUN_10009120();
        }

        result = FUN_10009060(reinterpret_cast<int*>(&param_2), data, length);
        param_1[1] = *result;
    }

    if (*param_3 != 0)
    {
        length = param_3[1];
        data = reinterpret_cast<std::uint8_t*>(*param_3);

        if ((_DAT_1003c400 & 1u) == 0)
        {
            _DAT_1003c400 = _DAT_1003c400 | 1u;
            _DAT_1003c3f0 = "Unknown Plugin Name";
            _DAT_1003c3f6 = 0;
            _DAT_1003c3f4 = 0;
            FUN_10009120();
        }

        result = FUN_10009060(reinterpret_cast<int*>(&param_2), data, length);
        param_1[2] = *result;
    }

    if (*param_4 != 0)
    {
        length = param_4[1];
        data = reinterpret_cast<std::uint8_t*>(*param_4);

        if ((_DAT_1003c400 & 1u) == 0)
        {
            _DAT_1003c400 = _DAT_1003c400 | 1u;
            _DAT_1003c3f0 = "Unknown Plugin Name";
            _DAT_1003c3f6 = 0;
            _DAT_1003c3f4 = 0;
            FUN_10009120();
        }

        result = FUN_10009060(reinterpret_cast<int*>(&param_2), data, length);
        param_1[3] = *result;
    }

    if (*param_5 != 0)
    {
        length = param_5[1];
        data = reinterpret_cast<std::uint8_t*>(*param_5);

        if ((_DAT_1003c400 & 1u) == 0)
        {
            _DAT_1003c400 = _DAT_1003c400 | 1u;
            _DAT_1003c3f0 = "Unknown Plugin Name";
            _DAT_1003c3f6 = 0;
            _DAT_1003c3f4 = 0;
            FUN_10009120();
        }

        result = FUN_10009060(reinterpret_cast<int*>(&param_2), data, length);
        param_1[4] = *result;
    }
}

extern "C" __declspec(naked) void __stdcall FUN_1000c480(
    std::int32_t*, std::int32_t*, std::int32_t*, std::int32_t*, std::int32_t*)
{
    __asm {
        push ebp
        mov ebp, esp
        mov edx, eax
        push dword ptr [ebp + 24]
        push dword ptr [ebp + 20]
        push dword ptr [ebp + 16]
        push dword ptr [ebp + 12]
        push dword ptr [ebp + 8]
        push edx
        call FUN_1000c480_impl
        add esp, 24
        mov esp, ebp
        pop ebp
        ret 20
    }
}
