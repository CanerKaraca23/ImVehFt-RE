#include <cstdint>

extern "C" std::int32_t __stdcall FUN_10009360();
extern "C" void __cdecl FUN_006c2130();
extern "C" std::uint64_t __fastcall FUN_1001ba40(std::uint32_t, std::uint32_t);
extern "C" void __cdecl FUN_10006360(std::int32_t);
extern "C" void __cdecl FUN_100069e0(std::int32_t);
extern "C" void __stdcall FUN_10006a50();
extern "C" void __stdcall FUN_10006ad0();
extern "C" void __cdecl FUN_10005860(std::int32_t);

extern volatile std::int32_t DAT_1003c248;
extern volatile std::uint32_t DAT_1003aedc;
extern volatile std::uint32_t DAT_1003aee0;
extern volatile std::uint32_t DAT_1003aee4;
extern volatile std::uint32_t DAT_1003aee8;
extern volatile std::uint32_t DAT_1003aeec;
extern volatile std::uint8_t DAT_1003aef0;
extern volatile std::int32_t DAT_1003aef4;
extern volatile std::uint32_t DAT_1003c1ec;
extern volatile std::int32_t DAT_1003c1fc;
extern volatile std::uint32_t DAT_1003bc78;

int __cdecl FUN_100074d0(std::int32_t param_1)
{
    volatile std::uint8_t& dat_aedc =
        *reinterpret_cast<volatile std::uint8_t*>(&DAT_1003aedc);
    volatile std::uint8_t& dat_aedd =
        *reinterpret_cast<volatile std::uint8_t*>(
            reinterpret_cast<volatile std::uint8_t*>(&DAT_1003aedc) + 1);
    volatile std::uint16_t& dat_aede =
        *reinterpret_cast<volatile std::uint16_t*>(
            reinterpret_cast<volatile std::uint8_t*>(&DAT_1003aedc) + 2);
    volatile std::uint8_t& dat_aedf =
        *reinterpret_cast<volatile std::uint8_t*>(
            reinterpret_cast<volatile std::uint8_t*>(&DAT_1003aedc) + 3);
    volatile std::uint8_t& dat_aee3 =
        *reinterpret_cast<volatile std::uint8_t*>(
            reinterpret_cast<volatile std::uint8_t*>(&DAT_1003aee0) + 3);
    volatile std::uint8_t& dat_aee4_2 =
        *reinterpret_cast<volatile std::uint8_t*>(
            reinterpret_cast<volatile std::uint8_t*>(&DAT_1003aee4) + 2);

    const std::int32_t base = DAT_1003c248;
    const std::int32_t shared = FUN_10009360();
    const std::int32_t vehicle_pool =
        *reinterpret_cast<volatile std::int32_t*>(
            static_cast<std::uintptr_t>(0x00b74494));
    const std::int32_t vehicle_objects =
        *reinterpret_cast<volatile std::int32_t*>(
            static_cast<std::uintptr_t>(
                static_cast<std::uint32_t>(vehicle_pool)));

    const std::int32_t record =
        *reinterpret_cast<volatile std::int32_t*>(
            static_cast<std::uintptr_t>(
                *reinterpret_cast<volatile std::int32_t*>(
                    static_cast<std::uintptr_t>(
                        static_cast<std::uint32_t>(shared)) + 0x48)) +
            static_cast<std::uintptr_t>(
                ((param_1 - vehicle_objects) / 0xa18) * 4));

    const std::uint32_t uVar1 =
        *reinterpret_cast<volatile std::uint32_t*>(
            static_cast<std::uintptr_t>(
                static_cast<std::uint32_t>(record + base)) + 4);

    const std::uintptr_t data =
        static_cast<std::uintptr_t>(
            static_cast<std::uint32_t>(record + base));

    const std::int32_t mode =
        *reinterpret_cast<volatile std::int32_t*>(
            static_cast<std::uintptr_t>(
                static_cast<std::uint32_t>(param_1)) + 0x594);

    DAT_1003aee0 =
        *reinterpret_cast<volatile std::uint32_t*>(data + 8);
    DAT_1003aee4 =
        *reinterpret_cast<volatile std::uint32_t*>(data + 0xc);
    DAT_1003aee8 =
        *reinterpret_cast<volatile std::uint32_t*>(data + 0x10);

    std::uint32_t edx_value =
        *reinterpret_cast<volatile std::uint32_t*>(data + 0x14);

    DAT_1003aef0 =
        *reinterpret_cast<volatile std::uint8_t*>(data + 0x18);

    dat_aede = static_cast<std::uint16_t>(uVar1 >> 16);
    dat_aedc = static_cast<std::uint8_t>(uVar1);

    DAT_1003aedc =
        ((static_cast<std::uint32_t>(dat_aede) << 16) |
         (static_cast<std::uint32_t>(
              *reinterpret_cast<volatile std::uint8_t*>(
                  static_cast<std::uintptr_t>(
                      static_cast<std::uint32_t>(param_1)) + 0x584)) << 8) |
         static_cast<std::uint32_t>(dat_aedc)) &
        0xffff01ffu;

    DAT_1003aeec = edx_value;

    if (mode == 0 || mode == 1 || mode == 2 || mode == 0xb)
    {
        std::uint8_t eax_value;

        __asm
        {
            push 1
            mov eax, 0x006c2130
            call eax
            add esp, 4
            mov eax_value, al
            mov edx_value, edx
        }

        if (eax_value != 0)
        {
            DAT_1003aedc =
                (static_cast<std::uint32_t>(dat_aede) << 16) | 0x0200u;
            DAT_1003aee4 =
                (DAT_1003aee4 & 0x00ffffffu) | 0x02000000u;
            DAT_1003aee8 =
                (DAT_1003aee8 & 0x00ffffffu) | 0x02000000u;
        }
    }

    DAT_1003aedc =
        ((static_cast<std::uint32_t>(
              *reinterpret_cast<volatile std::uint8_t*>(
                  static_cast<std::uintptr_t>(
                      static_cast<std::uint32_t>(param_1)) + 0x584) >> 1)) |
         (static_cast<std::uint32_t>(dat_aedd) << 8) |
         (static_cast<std::uint32_t>(dat_aede) << 16)) &
        0xffffff01u;

    if (mode == 0 || mode == 1 || mode == 0xb)
    {
        std::uint8_t eax_value;

        __asm
        {
            push 0
            mov eax, 0x006c2130
            call eax
            add esp, 4
            mov eax_value, al
            mov edx_value, edx
        }

        const std::uint32_t saved_aee4 = DAT_1003aee4;

        if (eax_value != 0)
        {
            DAT_1003aedc =
                (DAT_1003aedc & 0xffffff00u) | 2u;
            DAT_1003aee4 =
                (DAT_1003aee4 & 0xffffff00u) | 2u;

            const std::uint32_t value = DAT_1003aee4;

            dat_aee4_2 =
                static_cast<std::uint8_t>(saved_aee4 >> 24);

            *reinterpret_cast<volatile std::uint16_t*>(&DAT_1003aee4) =
                static_cast<std::uint16_t>(value);

            DAT_1003aee4 =
                (DAT_1003aee4 & 0xff00ffffu) | 0x00020000u;
        }
    }

    DAT_1003aedc =
        ((static_cast<std::uint32_t>(
              *reinterpret_cast<volatile std::uint8_t*>(
                  static_cast<std::uintptr_t>(
                      static_cast<std::uint32_t>(param_1)) + 0x584) >> 2)
              << 24) |
         (DAT_1003aedc & 0x00ffffffu)) &
        0x01ffffffu;

    if (mode == 0 || mode == 1 || mode == 2 || mode == 0xb)
    {
        std::uint8_t eax_value;

        __asm
        {
            push 2
            mov eax, 0x006c2130
            call eax
            add esp, 4
            mov eax_value, al
            mov edx_value, edx
        }

        if (eax_value != 0)
        {
            DAT_1003aedc =
                (2u << 24) | (DAT_1003aedc & 0x00ffffffu);
            DAT_1003aee0 =
                (DAT_1003aee0 & 0x00ffffffu) | 0x02000000u;
            DAT_1003aee8 =
                (DAT_1003aee8 & 0x00ffffffu) | 0x02000000u;
            DAT_1003aee0 =
                (DAT_1003aee0 & 0x00ffffffu) | 0x02000000u;
        }
    }

    DAT_1003aedc =
        ((static_cast<std::uint32_t>(dat_aedf) << 24) |
         (static_cast<std::uint32_t>(
              *reinterpret_cast<volatile std::uint8_t*>(
                  static_cast<std::uintptr_t>(
                      static_cast<std::uint32_t>(param_1)) + 0x584) >> 3)
              << 16) |
         (DAT_1003aedc & 0x0000ffffu)) &
        0xff01ffffu;

    if (mode == 0 || mode == 1 || mode == 0xb)
    {
        std::uint8_t eax_value;

        __asm
        {
            push 3
            mov eax, 0x006c2130
            call eax
            add esp, 4
            mov eax_value, al
            mov edx_value, edx
        }

        const std::uint32_t saved_aee0 = DAT_1003aee0;

        if (eax_value != 0)
        {
            DAT_1003aedc =
                (2u << 16) | (DAT_1003aedc & 0xff00ffffu);
            DAT_1003aee0 =
                (DAT_1003aee0 & 0xffffff00u) | 2u;

            const std::uint32_t value = DAT_1003aee0;

            DAT_1003aee8 =
                (DAT_1003aee8 & 0xffffff00u) | 2u;

            dat_aee3 =
                static_cast<std::uint8_t>(saved_aee0 >> 24);

            *reinterpret_cast<volatile std::uint16_t*>(&DAT_1003aee0) =
                static_cast<std::uint16_t>(value);

            DAT_1003aee0 =
                (DAT_1003aee0 & 0xff00ffffu) | 0x00020000u;
        }
    }

    DAT_1003aef4 =
        *reinterpret_cast<volatile std::int16_t*>(
            static_cast<std::uintptr_t>(
                static_cast<std::uint32_t>(param_1)) + 0x22);

    DAT_1003c1ec =
        *reinterpret_cast<volatile std::uint32_t*>(
            static_cast<std::uintptr_t>(
                static_cast<std::uint32_t>(param_1)) + 0x4b0);

    DAT_1003c1fc = param_1;

    const std::uint64_t hash =
        FUN_1001ba40(
            static_cast<std::uint32_t>(DAT_1003aef4),
            edx_value);

    DAT_1003bc78 =
        static_cast<std::uint32_t>(hash) & 0xfu;

    FUN_10006360(param_1);
    FUN_100069e0(param_1);
    FUN_10006a50();
    FUN_10006ad0();
    FUN_10005860(param_1);

    return param_1;
}
