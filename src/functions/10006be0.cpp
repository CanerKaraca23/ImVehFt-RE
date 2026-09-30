#include <cstdint>
#include <cstddef>
#include "gta_sa_address_access.hpp"

extern std::uint32_t DAT_10024ec8;
extern double DAT_10024ec0;
extern float DAT_1003c1f8;
extern float DAT_1003bc1c;
extern float _DAT_10024ed8;
extern double _DAT_10024e88;
extern double _DAT_10024ed0;
extern std::uint32_t _DAT_10024eec;
extern double _DAT_10024ee0;
extern float _DAT_10024ef8;
extern float _DAT_10024f28;
extern double _DAT_10024f30;
extern float _DAT_10024f38;
extern float _DAT_10024f10;

extern "C" long double __stdcall FUN_10008d20();
extern "C" std::uint64_t __fastcall FUN_1001ba40(
    void*,
    std::uint32_t);
extern "C" void __fastcall FUN_100073f0(
    void*,
    std::uint32_t,
    void*,
    float,
    float,
    float,
    std::uint32_t,
    float);

using RegisterCorona = void(__cdecl*)(
    std::uint32_t,
    void*,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    const void*,
    float,
    float,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t,
    float,
    std::uint32_t,
    float,
    std::uint32_t,
    float,
    std::uint32_t,
    std::uint32_t);

extern "C" void __cdecl FUN_10006be0_impl(
    int param_1,
    std::uint32_t param_2,
    char param_3,
    std::uint8_t param_4,
    std::uint8_t param_5,
    std::uint32_t param_6,
    std::uint8_t param_7,
    float param_8,
    char param_9,
    float param_10,
    char param_11,
    float param_12,
    std::uint32_t raw_stack_local_1c_bits,
    std::uint32_t incoming_EAX)
{
    (void)param_6;
    (void)param_12;

    struct RwFrameLayout
    {
        std::uint8_t rw_object_header[4];
        std::uint32_t parent_frame;
        std::uint8_t in_dirty_list_link[8];
        std::uint32_t modelling[16];
        std::uint32_t ltm[16];
    };

    static_assert(offsetof(RwFrameLayout, parent_frame) == 0x04);
    static_assert(offsetof(RwFrameLayout, in_dirty_list_link) == 0x08);
    static_assert(offsetof(RwFrameLayout, modelling) == 0x10);
    static_assert(offsetof(RwFrameLayout, ltm) == 0x50);

    using MatrixMultiply = void*(__cdecl*)(
        void*,
        const void*,
        const void*);

    const auto* rw_frame = reinterpret_cast<const RwFrameLayout*>(
        static_cast<std::uintptr_t>(param_1));

    std::uint8_t frame[0xe8];

    auto* local_ec = frame + 0x00;
    auto* local_ac = frame + 0x40;
    auto* local_7c = frame + 0x74;
    auto* local_6c = frame + 0x84;
    auto* local_3c = frame + 0xb0;
    auto* local_28 = reinterpret_cast<std::uint32_t*>(frame + 0xc4);
    auto* local_24 = reinterpret_cast<std::uint32_t*>(frame + 0xc8);
    auto* local_20 = reinterpret_cast<std::uint32_t*>(frame + 0xcc);
    auto* local_1c = reinterpret_cast<float*>(frame + 0xd0);
    auto* local_18 = frame + 0xd8;
    auto* local_14 = reinterpret_cast<float*>(frame + 0xdc);
    auto* local_c = reinterpret_cast<float*>(frame + 0xe0);
    auto* local_8 = frame + 0xe4;
    auto* bStack_5 = frame + 0xe7;

    // Preserve the untouched stack slot as bits. The target does not load it
    // on entry; a floating FLD/FSTP here would spuriously set x87 DE for a
    // denormal value even on paths that never read this local.
    *reinterpret_cast<std::uint32_t*>(local_1c) = raw_stack_local_1c_bits;

    const float original_corona_radius = param_8;
    const auto register_corona = reinterpret_cast<RegisterCorona>(0x006fc580);
    const auto corona_id = static_cast<std::uint32_t>(param_3) +
        0xff00u + incoming_EAX;
    auto* const corona_position = local_3c + 4;

    if (!(param_8 > 0.0f) && !(param_10 > 0.0f))
        return;

    if (param_9 == '\0')
    {
        auto* destination =
            reinterpret_cast<std::uint32_t*>(local_6c);

        for (int iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1)
        {
            *destination = rw_frame->modelling[0x10 - iVar3];
            destination = destination + 1;
        }
    }
    else
    {
        const auto parent_matrix = reinterpret_cast<const void*>(
            static_cast<std::uintptr_t>(rw_frame->parent_frame) + 0x10u);

        reinterpret_cast<MatrixMultiply>(0x007f18b0)(
            local_6c,
            rw_frame->modelling,
            parent_matrix);
    }

    {
        auto* destination =
            reinterpret_cast<std::uint32_t*>(local_ac);

        for (int iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1)
        {
            *destination = rw_frame->ltm[0x10 - iVar3];
            destination = destination + 1;
        }
    }

    reinterpret_cast<void(__cdecl*)(void*, std::uint32_t, void*)>(
        0x0040fe60)(local_18, param_2, local_7c);

    reinterpret_cast<void(__cdecl*)()>(0x0059c910)();

    reinterpret_cast<void(__cdecl*)(void*, const void*)>(
        0x007f2070)(local_ec, local_ac);

    std::uint32_t extraout_EDX;

    __asm
    {
        push local_18
        push local_ec
        push local_18
        mov eax, 0x0059c790
        call eax
        add esp, 12
        mov extraout_EDX, edx
    }

    std::uint32_t uVar4;

    if (param_8 > 0.0f)
    {
        if ((param_11 == '\x03') || (param_11 == '\x04'))
        {
            std::uint8_t use_default_alpha;

            __asm
            {
                mov eax, local_14
                fld _DAT_10024f28
                fld dword ptr [eax]
                fcom
                fnstsw ax
                test ah, 5
                setp al
                mov use_default_alpha, al
                fstp st(0)
                fstp st(0)
            }

            if (use_default_alpha == 0)
            {
                __asm
                {
                    mov eax, local_14
                    fld _DAT_10024f38
                    fcomp dword ptr [eax]
                    fnstsw ax
                    test ah, 5
                    setp al
                    mov use_default_alpha, al
                }
            }

            if (use_default_alpha != 0)
            {
                param_8 = static_cast<float>(param_7);
                uVar4 = extraout_EDX;
            }
            else
            {
                if (*local_14 < 0.0f)
                    *local_14 = static_cast<float>(
                        static_cast<double>(*local_14) * _DAT_10024f30);

                uVar4 = static_cast<std::uint32_t>(param_7);
                param_8 =
                    (static_cast<float>(uVar4) +
                     static_cast<float>(uVar4)) *
                    *local_14;
            }

            std::uint32_t alpha_result;
            __asm
            {
                fld param_8
                mov ecx, local_3c
                mov edx, uVar4
                call FUN_1001ba40
                mov alpha_result, eax
            }
            const auto corona_alpha = static_cast<std::uint8_t>(alpha_result);

            register_corona(
                corona_id,
                reinterpret_cast<void*>(static_cast<std::uintptr_t>(incoming_EAX)),
                param_4,
                param_5,
                param_6,
                corona_alpha,
                corona_position,
                original_corona_radius,
                _DAT_10024f10,
                1,
                0,
                1,
                0,
                0,
                0.0f,
                0,
                _DAT_10024f28,
                0,
                param_12,
                0,
                0);
        }
        else
        {
            if (param_11 == '\x02')
            {
                register_corona(
                    corona_id,
                    reinterpret_cast<void*>(static_cast<std::uintptr_t>(incoming_EAX)),
                    param_4,
                    param_5,
                    param_6,
                    param_7,
                    corona_position,
                    original_corona_radius,
                    _DAT_10024f10,
                    1,
                    0,
                    1,
                    0,
                    0,
                    0.0f,
                    0,
                    _DAT_10024f28,
                    0,
                    param_12,
                    0,
                    0);
                goto LAB_10006e94;
            }

            if (param_11 != '\0')
                *local_14 = static_cast<float>(
                    static_cast<double>(*local_14) * _DAT_10024f30);

            if (!(*local_14 > 0.0f))
                goto LAB_10006e94;

            uVar4 = extraout_EDX;

            const bool scaled_alpha_input = *local_14 < _DAT_10024f28;
            if (scaled_alpha_input)
                uVar4 = static_cast<std::uint32_t>(param_7);

            param_8 =
                static_cast<float>(static_cast<std::uint32_t>(param_7));

            std::uint32_t alpha_result;
            if (scaled_alpha_input)
            {
                const std::uint32_t alpha_integer = param_7;
                __asm
                {
                    mov eax, local_14
                    fld dword ptr [eax]
                    fild alpha_integer
                    fadd st(0), st(0)
                    fmulp st(1), st(0)
                    mov ecx, local_3c
                    mov edx, uVar4
                    call FUN_1001ba40
                    mov alpha_result, eax
                }
            }
            else
            {
                const std::uint32_t alpha_integer = param_7;
                __asm
                {
                    fild alpha_integer
                    mov ecx, local_3c
                    mov edx, uVar4
                    call FUN_1001ba40
                    mov alpha_result, eax
                }
            }
            const auto corona_alpha = static_cast<std::uint8_t>(alpha_result);

            register_corona(
                corona_id,
                reinterpret_cast<void*>(static_cast<std::uintptr_t>(incoming_EAX)),
                param_4,
                param_5,
                param_6,
                corona_alpha,
                corona_position,
                original_corona_radius,
                _DAT_10024f10,
                1,
                0,
                1,
                0,
                0,
                0.0f,
                0,
                _DAT_10024f28,
                0,
                param_12,
                0,
                0);
        }
    }

LAB_10006e94:
    if (!(param_10 > 0.0f))
        return;

    if (param_11 != '\x03')
    {
        if ((param_11 == '\x02') || (param_11 == '\x04'))
        {
            *local_1c = 1.0f;
            param_8 = DAT_1003c1f8;
        }
        else
        {
            *local_1c = _DAT_10024ef8;
            param_8 = DAT_1003bc1c;
        }
    }

    const double fVar1 = _DAT_10024e88;

    *local_28 = 0;
    *local_24 = _DAT_10024eec;
    *local_20 = 0;

    reinterpret_cast<void(__cdecl*)(void*, int, void*, void*)>(
        0x0054eef0)(local_18, 1, local_ac, local_28);

    auto* const scene_value = reinterpret_cast<volatile float*>(0x00c812a8);
    float fVar2;

    if (*scene_value < _DAT_10024ee0)
        fVar2 = _DAT_10024ed8;
    else
        fVar2 = *scene_value;

    int rounded_value;

    const std::uint32_t first_round_operand = param_6 & 0xffu;
    std::uint16_t saved_fpu_control_word;
    std::uint16_t truncating_fpu_control_word;
    __asm
    {
        fnstcw saved_fpu_control_word
        mov ax, saved_fpu_control_word
        or ax, 0c00h
        mov truncating_fpu_control_word, ax
        fld fVar2
        fild first_round_operand
        fmulp st(1), st(0)
        fld qword ptr _DAT_10024ed0
        fmul st(0), st(1)
        fldcw truncating_fpu_control_word
        fistp rounded_value
        fldcw saved_fpu_control_word
        fstp st(0)
    }

    uVar4 = static_cast<std::uint32_t>(rounded_value);

    local_8[0] = static_cast<std::uint8_t>(uVar4);
    local_8[1] = static_cast<std::uint8_t>(uVar4 >> 8);

    std::uint16_t in_FPUControlWord;

    __asm
    {
        fnstcw in_FPUControlWord
    }

    local_8[2] =
        static_cast<std::uint8_t>(in_FPUControlWord);

    const std::uint32_t second_round_operand = param_5 & 0xffu;
    __asm
    {
        fld fVar2
        fild second_round_operand
        fmulp st(1), st(0)
        fld qword ptr _DAT_10024ed0
        fmul st(0), st(1)
        fldcw truncating_fpu_control_word
        fistp rounded_value
        fldcw saved_fpu_control_word
        fstp st(0)
    }

    const auto second_round_byte = static_cast<std::uint8_t>(rounded_value);

    const std::uint32_t third_round_operand = param_4 & 0xffu;
    __asm
    {
        fld fVar2
        fild third_round_operand
        fmulp st(1), st(0)
        fld qword ptr _DAT_10024ed0
        fmul st(0), st(1)
        fldcw truncating_fpu_control_word
        fistp rounded_value
        fldcw saved_fpu_control_word
        fstp st(0)
    }

    *local_c = static_cast<float>(rounded_value);
    *bStack_5 = static_cast<std::uint8_t>(rounded_value);

    // The original x86 code stores the param_5 rounded byte into the high
    // byte of its param_8 stack slot after pushing param_8 as an outgoing
    // argument. Preserve the already-pushed value separately.
    const float pushed_param_8 = param_8;
    reinterpret_cast<std::uint8_t*>(&param_8)[3] = second_round_byte;

    const std::uint32_t uVar8 = DAT_10024ec8;
    const long double fVar7 = FUN_10008d20();

    float rounded_world_value;
    float scaled_world_value;
    __asm
    {
        mov eax, local_1c
        fld param_10
        fsub fVar1
        fstp rounded_world_value
        fld rounded_world_value
        fmul dword ptr [eax]
        fstp scaled_world_value
    }
    param_10 = rounded_world_value;
    *local_c = scaled_world_value;

    FUN_100073f0(
        reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(second_round_byte)),
        static_cast<std::uint32_t>(*bStack_5),
        local_18,
        *local_c,
        param_10,
        static_cast<float>(
            fVar7 + static_cast<long double>(DAT_10024ec0)),
        uVar8,
        pushed_param_8);
}

#if defined(_MSC_VER) && defined(_M_IX86)
extern "C" __declspec(naked) void __cdecl FUN_10006be0(
    int,
    std::uint32_t,
    char,
    std::uint8_t,
    std::uint8_t,
    std::uint32_t,
    std::uint8_t,
    float,
    char,
    float,
    char,
    float)
{
    __asm
    {
        push ebp
        mov ebp, esp
        sub esp, 0ech
        push ebx
        mov ebx, eax
        push esi
        push edi

        mov eax, dword ptr [ebp - 18h]
        push ebx
        push eax
        push dword ptr [ebp + 34h]
        push dword ptr [ebp + 30h]
        push dword ptr [ebp + 2ch]
        push dword ptr [ebp + 28h]
        push dword ptr [ebp + 24h]
        push dword ptr [ebp + 20h]
        push dword ptr [ebp + 1ch]
        push dword ptr [ebp + 18h]
        push dword ptr [ebp + 14h]
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0ch]
        push dword ptr [ebp + 08h]
        call FUN_10006be0_impl
        add esp, 38h

        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret
    }
}

extern "C" __declspec(naked) void __cdecl FUN_10006be0_call_bridge(
    int,
    std::uint32_t,
    char,
    std::uint8_t,
    std::uint8_t,
    std::uint32_t,
    std::uint8_t,
    float,
    char,
    float,
    char,
    float,
    std::uint32_t)
{
    __asm
    {
        push ebp
        mov ebp, esp
        mov eax, dword ptr [ebp + 38h]
        push dword ptr [ebp + 34h]
        push dword ptr [ebp + 30h]
        push dword ptr [ebp + 2ch]
        push dword ptr [ebp + 28h]
        push dword ptr [ebp + 24h]
        push dword ptr [ebp + 20h]
        push dword ptr [ebp + 1ch]
        push dword ptr [ebp + 18h]
        push dword ptr [ebp + 14h]
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0ch]
        push dword ptr [ebp + 08h]
        call FUN_10006be0
        add esp, 30h

        mov esp, ebp
        pop ebp
        ret
    }
}
#else
#error "FUN_10006be0 requires MSVC x86 entry and caller ABI bridges"
#endif
