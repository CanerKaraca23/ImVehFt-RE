#include <cstddef>
#include <cstdint>

using undefined4 = std::uint32_t;

struct ExtraEntry
{
    undefined4 handle;
    undefined4 reserved;
};

struct SpoilerEntry
{
    undefined4 handle;
    std::uint8_t reserved[0x14];
};

struct Context
{
    std::uint8_t reserved_000[0x328];
    ExtraEntry extra[5];                 // 0x328
    std::uint8_t reserved_350[0x144];
    undefined4 movsteer;                 // 0x494
    std::uint8_t reserved_498[4];
    float movsteer_scale;                // 0x49c
    SpoilerEntry movspoiler[3];          // 0x4a0
    undefined4 reserved_4e8;             // 0x4e8
    std::uint32_t padding_4ec;
    undefined4 reserved_4f0;             // 0x4f0
    std::uint32_t padding_4f4;
    undefined4 reserved_4f8;             // 0x4f8
    std::uint32_t padding_4fc;
    undefined4 reserved_500;             // 0x500
    std::uint32_t padding_504;
    undefined4 reserved_508;             // 0x508
    std::uint32_t padding_50c;
    undefined4 reserved_510;             // 0x510
};

static_assert(offsetof(Context, extra) == 0x328);
static_assert(offsetof(Context, movsteer) == 0x494);
static_assert(offsetof(Context, movsteer_scale) == 0x49c);
static_assert(offsetof(Context, movspoiler) == 0x4a0);
static_assert(offsetof(Context, reserved_4e8) == 0x4e8);
static_assert(offsetof(Context, reserved_4f0) == 0x4f0);
static_assert(offsetof(Context, reserved_4f8) == 0x4f8);
static_assert(offsetof(Context, reserved_500) == 0x500);
static_assert(offsetof(Context, reserved_508) == 0x508);
static_assert(offsetof(Context, reserved_510) == 0x510);

extern "C" undefined4 __cdecl FUN_100046f0(undefined4, int);
extern "C" int __cdecl strncmp(char*, char*, std::size_t);
extern "C" void __fastcall FUN_10004a00(undefined4*);
extern "C" void __stdcall FUN_10004000();
extern "C" int __cdecl FID_conflict__sscanf(char*, char*, ...);
struct FUN_10004ab0_this { void __thiscall invoke(undefined4); };

using GetStringFn = std::uint8_t* (__cdecl*)(undefined4);
using RegisterFn =
    void (__cdecl*)(undefined4, void (__cdecl*)(undefined4, int), int);

extern "C" void __cdecl FUN_10004430(undefined4 param_1, int param_2)
{
    auto get_string =
        reinterpret_cast<GetStringFn>(static_cast<std::uintptr_t>(0x72fb30));

    auto register_callback =
        reinterpret_cast<RegisterFn>(static_cast<std::uintptr_t>(0x7f0dc0));

    std::uint8_t* _Str1 = get_string(param_1);
    Context* context = reinterpret_cast<Context*>(
        static_cast<std::uintptr_t>(param_2));

    int iVar2 = static_cast<int>(FUN_100046f0(param_1, param_2));

    if (iVar2 == 0)
    {
        std::uint8_t bVar1;
        std::uint8_t* pbVar3;
        std::uint8_t* pbVar4;
        bool bVar6;

        pbVar4 = reinterpret_cast<std::uint8_t*>(0x10024884);
        pbVar3 = _Str1;

        do
        {
            bVar1 = *pbVar3;
            bVar6 = bVar1 < *pbVar4;

            if (bVar1 != *pbVar4)
            {
                iVar2 = (1 - static_cast<unsigned int>(bVar6)) -
                        static_cast<unsigned int>(bVar6 != false);
                goto compare_10004485;
            }

            if (bVar1 == 0)
                break;

            bVar1 = pbVar3[1];
            bVar6 = bVar1 < pbVar4[1];

            if (bVar1 != pbVar4[1])
            {
                iVar2 = (1 - static_cast<unsigned int>(bVar6)) -
                        static_cast<unsigned int>(bVar6 != false);
                goto compare_10004485;
            }

            pbVar3 += 2;
            pbVar4 += 2;
        }
        while (bVar1 != 0);

        iVar2 = 0;

    compare_10004485:
        if (iVar2 == 0)
        {
            context->reserved_4e8 = param_1;
        }
        else
        {
            pbVar4 = reinterpret_cast<std::uint8_t*>(0x1002488c);
            pbVar3 = _Str1;

            do
            {
                bVar1 = *pbVar3;
                bVar6 = bVar1 < *pbVar4;

                if (bVar1 != *pbVar4)
                {
                    iVar2 = (1 - static_cast<unsigned int>(bVar6)) -
                            static_cast<unsigned int>(bVar6 != false);
                    goto compare_100044c5;
                }

                if (bVar1 == 0)
                    break;

                bVar1 = pbVar3[1];
                bVar6 = bVar1 < pbVar4[1];

                if (bVar1 != pbVar4[1])
                {
                    iVar2 = (1 - static_cast<unsigned int>(bVar6)) -
                            static_cast<unsigned int>(bVar6 != false);
                    goto compare_100044c5;
                }

                pbVar3 += 2;
                pbVar4 += 2;
            }
            while (bVar1 != 0);

            iVar2 = 0;

        compare_100044c5:
            if (iVar2 == 0)
            {
                context->reserved_4f0 = param_1;
            }
            else
            {
                pbVar4 = reinterpret_cast<std::uint8_t*>(0x10024894);
                pbVar3 = _Str1;

                do
                {
                    bVar1 = *pbVar3;
                    bVar6 = bVar1 < *pbVar4;

                    if (bVar1 != *pbVar4)
                    {
                        iVar2 = (1 - static_cast<unsigned int>(bVar6)) -
                                static_cast<unsigned int>(bVar6 != false);
                        goto compare_10004505;
                    }

                    if (bVar1 == 0)
                        break;

                    bVar1 = pbVar3[1];
                    bVar6 = bVar1 < pbVar4[1];

                    if (bVar1 != pbVar4[1])
                    {
                        iVar2 = (1 - static_cast<unsigned int>(bVar6)) -
                                static_cast<unsigned int>(bVar6 != false);
                        goto compare_10004505;
                    }

                    pbVar3 += 2;
                    pbVar4 += 2;
                }
                while (bVar1 != 0);

                iVar2 = 0;

            compare_10004505:
                if (iVar2 == 0)
                {
                    context->reserved_4f8 = param_1;
                }
                else
                {
                    pbVar4 = reinterpret_cast<std::uint8_t*>(0x1002489c);
                    pbVar3 = _Str1;

                    do
                    {
                        bVar1 = *pbVar3;
                        bVar6 = bVar1 < *pbVar4;

                        if (bVar1 != *pbVar4)
                        {
                            iVar2 = (1 - static_cast<unsigned int>(bVar6)) -
                                    static_cast<unsigned int>(bVar6 != false);
                            goto compare_10004545;
                        }

                        if (bVar1 == 0)
                            break;

                        bVar1 = pbVar3[1];
                        bVar6 = bVar1 < pbVar4[1];

                        if (bVar1 != pbVar4[1])
                        {
                            iVar2 = (1 - static_cast<unsigned int>(bVar6)) -
                                    static_cast<unsigned int>(bVar6 != false);
                            goto compare_10004545;
                        }

                        pbVar3 += 2;
                        pbVar4 += 2;
                    }
                    while (bVar1 != 0);

                    iVar2 = 0;

                compare_10004545:
                    if (iVar2 == 0)
                    {
                        context->reserved_500 = param_1;
                    }
                    else
                    {
                        pbVar4 = reinterpret_cast<std::uint8_t*>(0x100248a4);
                        pbVar3 = _Str1;

                        do
                        {
                            bVar1 = *pbVar3;
                            bVar6 = bVar1 < *pbVar4;

                            if (bVar1 != *pbVar4)
                            {
                                iVar2 =
                                    (1 - static_cast<unsigned int>(bVar6)) -
                                    static_cast<unsigned int>(bVar6 != false);
                                goto compare_10004585;
                            }

                            if (bVar1 == 0)
                                break;

                            bVar1 = pbVar3[1];
                            bVar6 = bVar1 < pbVar4[1];

                            if (bVar1 != pbVar4[1])
                            {
                                iVar2 =
                                    (1 - static_cast<unsigned int>(bVar6)) -
                                    static_cast<unsigned int>(bVar6 != false);
                                goto compare_10004585;
                            }

                            pbVar3 += 2;
                            pbVar4 += 2;
                        }
                        while (bVar1 != 0);

                        iVar2 = 0;

                    compare_10004585:
                        if (iVar2 == 0)
                        {
                            context->reserved_508 = param_1;
                        }
                        else
                        {
                            pbVar4 = reinterpret_cast<std::uint8_t*>(0x100248ac);
                            pbVar3 = _Str1;

                            do
                            {
                                bVar1 = *pbVar3;
                                bVar6 = bVar1 < *pbVar4;

                                if (bVar1 != *pbVar4)
                                {
                                    iVar2 =
                                        (1 - static_cast<unsigned int>(bVar6)) -
                                        static_cast<unsigned int>(bVar6 != false);
                                    goto compare_100045c5;
                                }

                                if (bVar1 == 0)
                                    break;

                                bVar1 = pbVar3[1];
                                bVar6 = bVar1 < pbVar4[1];

                                if (bVar1 != pbVar4[1])
                                {
                                    iVar2 =
                                        (1 - static_cast<unsigned int>(bVar6)) -
                                        static_cast<unsigned int>(bVar6 != false);
                                    goto compare_100045c5;
                                }

                                pbVar3 += 2;
                                pbVar4 += 2;
                            }
                            while (bVar1 != 0);

                            iVar2 = 0;

                        compare_100045c5:
                            if (iVar2 == 0)
                            {
                                context->reserved_510 = param_1;
                            }
                            else
                            {
                                iVar2 = strncmp(
                                    reinterpret_cast<char*>(_Str1),
                                    const_cast<char*>("movspoiler"),
                                    10);

                                if (iVar2 == 0)
                                {
                                    int* piVar5 =
                                        reinterpret_cast<int*>(
                                            context->movspoiler);

                                    iVar2 = 0;

                                    do
                                    {
                                        if (*piVar5 == 0)
                                        {
                                            FUN_10004a00(
                                                reinterpret_cast<undefined4*>(
                                                    &context->movspoiler[iVar2]));
                                            break;
                                        }

                                        iVar2 = iVar2 + 1;
                                        piVar5 = piVar5 + 6;
                                    }
                                    while (iVar2 < 3);
                                }
                                else
                                {
                                    iVar2 = strncmp(
                                        reinterpret_cast<char*>(_Str1),
                                        const_cast<char*>("extra"),
                                        5);

                                    if ((iVar2 == 0) && (_Str1[5] != 0x5f))
                                    {
                                        int* piVar5 =
                                            reinterpret_cast<int*>(
                                                context->extra);

                                        iVar2 = 0;

                                        do
                                        {
                                            if (*piVar5 == 0)
                                            {
                                                context->extra[iVar2].handle =
                                                    param_1;
                                                FUN_10004000();
                                                break;
                                            }

                                            iVar2 = iVar2 + 1;
                                            piVar5 = piVar5 + 2;
                                        }
                                        while (iVar2 < 5);
                                    }
                                    else
                                    {
                                        iVar2 = strncmp(
                                            reinterpret_cast<char*>(_Str1),
                                            const_cast<char*>("movsteer"),
                                            8);

                                        if (iVar2 == 0)
                                        {
                                            context->movsteer = param_1;

                                            if (_Str1[8] == 0x5f)
                                            {
                                                FID_conflict__sscanf(
                                                    reinterpret_cast<char*>(
                                                        _Str1 + 9),
                                                    const_cast<char*>("%f"),
                                                    &context->movsteer_scale);
                                            }
                                            else
                                            {
                                                *reinterpret_cast<undefined4*>(
                                                    &context->movsteer_scale) =
                                                    0x3f800000;
                                            }
                                        }
                                        else
                                        {
                                            iVar2 = strncmp(
                                                reinterpret_cast<char*>(_Str1),
                                                const_cast<char*>("light_em"),
                                                8);

                                            if (iVar2 == 0)
                                            {
                                                reinterpret_cast<FUN_10004ab0_this*>(_Str1)->invoke(param_1);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    register_callback(param_1, FUN_10004430, param_2);
}