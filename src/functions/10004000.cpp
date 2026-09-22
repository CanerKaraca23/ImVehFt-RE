#include <cstddef>
#include <cstdint>

extern "C" int __cdecl strncmp(const char*, const char*, std::size_t);

using GetNameFn = const char* (__cdecl*)(std::uint32_t);

extern "C" void __stdcall FUN_10004000()
{
    std::int32_t* unaff_EDI;

    __asm
    {
        mov unaff_EDI, edi
    }

    const GetNameFn getName =
        reinterpret_cast<GetNameFn>(static_cast<std::uintptr_t>(0x72FB30));

    const std::uint32_t first =
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(*unaff_EDI) + 4u);

    const char* str1 = getName(first);

    std::int32_t cmp = strncmp(str1, "dummy", 5);

    if (cmp == 0)
    {
        const std::uint32_t second =
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<std::int32_t*>(
                        static_cast<std::uintptr_t>(*unaff_EDI) + 4u)) + 4u);

        str1 = getName(second);
    }

    {
        const unsigned char* pbVar3 =
            reinterpret_cast<const unsigned char*>(str1);
        const char* pcVar4 = "door_rf_dummy";
        unsigned char bVar1;
        bool bVar5;

        do
        {
            bVar1 = *pbVar3;
            bVar5 = bVar1 < static_cast<unsigned char>(*pcVar4);

            if (bVar1 != static_cast<unsigned char>(*pcVar4))
                goto door_rf_mismatch;

            if (bVar1 == 0)
                break;

            bVar1 = pbVar3[1];
            bVar5 = bVar1 < static_cast<unsigned char>(pcVar4[1]);

            if (bVar1 != static_cast<unsigned char>(pcVar4[1]))
                goto door_rf_mismatch;

            pbVar3 += 2;
            pcVar4 += 2;
        } while (bVar1 != 0);

        cmp = 0;
        goto door_rf_done;

    door_rf_mismatch:
        cmp = static_cast<std::int32_t>(
            (1u - static_cast<unsigned>(bVar5)) -
            static_cast<unsigned>(bVar5 != false));

    door_rf_done:
        ;
    }

    if (cmp == 0)
    {
        *reinterpret_cast<std::uint16_t*>(unaff_EDI + 1) = 0x0302;
        return;
    }

    {
        const unsigned char* pbVar3 =
            reinterpret_cast<const unsigned char*>(str1);
        const char* pcVar4 = "door_lf_dummy";
        unsigned char bVar1;
        bool bVar5;

        do
        {
            bVar1 = *pbVar3;
            bVar5 = bVar1 < static_cast<unsigned char>(*pcVar4);

            if (bVar1 != static_cast<unsigned char>(*pcVar4))
                goto door_lf_mismatch;

            if (bVar1 == 0)
                break;

            bVar1 = pbVar3[1];
            bVar5 = bVar1 < static_cast<unsigned char>(pcVar4[1]);

            if (bVar1 != static_cast<unsigned char>(pcVar4[1]))
                goto door_lf_mismatch;

            pbVar3 += 2;
            pcVar4 += 2;
        } while (bVar1 != 0);

        cmp = 0;
        goto door_lf_done;

    door_lf_mismatch:
        cmp = static_cast<std::int32_t>(
            (1u - static_cast<unsigned>(bVar5)) -
            static_cast<unsigned>(bVar5 != false));

    door_lf_done:
        ;
    }

    if (cmp == 0)
    {
        *reinterpret_cast<std::uint16_t*>(unaff_EDI + 1) = 0x0202;
        return;
    }

    {
        const unsigned char* pbVar3 =
            reinterpret_cast<const unsigned char*>(str1);
        const char* pcVar4 = "door_rr_dummy";
        unsigned char bVar1;
        bool bVar5;

        do
        {
            bVar1 = *pbVar3;
            bVar5 = bVar1 < static_cast<unsigned char>(*pcVar4);

            if (bVar1 != static_cast<unsigned char>(*pcVar4))
                goto door_rr_mismatch;

            if (bVar1 == 0)
                break;

            bVar1 = pbVar3[1];
            bVar5 = bVar1 < static_cast<unsigned char>(pcVar4[1]);

            if (bVar1 != static_cast<unsigned char>(pcVar4[1]))
                goto door_rr_mismatch;

            pbVar3 += 2;
            pcVar4 += 2;
        } while (bVar1 != 0);

        cmp = 0;
        goto door_rr_done;

    door_rr_mismatch:
        cmp = static_cast<std::int32_t>(
            (1u - static_cast<unsigned>(bVar5)) -
            static_cast<unsigned>(bVar5 != false));

    door_rr_done:
        ;
    }

    if (cmp == 0)
    {
        *reinterpret_cast<std::uint16_t*>(unaff_EDI + 1) = 0x0502;
        return;
    }

    {
        const unsigned char* pbVar3 =
            reinterpret_cast<const unsigned char*>(str1);
        const char* pcVar4 = "door_lr_dummy";
        unsigned char bVar1;
        bool bVar5;

        do
        {
            bVar1 = *pbVar3;
            bVar5 = bVar1 < static_cast<unsigned char>(*pcVar4);

            if (bVar1 != static_cast<unsigned char>(*pcVar4))
                goto door_lr_mismatch;

            if (bVar1 == 0)
                break;

            bVar1 = pbVar3[1];
            bVar5 = bVar1 < static_cast<unsigned char>(pcVar4[1]);

            if (bVar1 != static_cast<unsigned char>(pcVar4[1]))
                goto door_lr_mismatch;

            pbVar3 += 2;
            pcVar4 += 2;
        } while (bVar1 != 0);

        cmp = 0;
        goto door_lr_done;

    door_lr_mismatch:
        cmp = static_cast<std::int32_t>(
            (1u - static_cast<unsigned>(bVar5)) -
            static_cast<unsigned>(bVar5 != false));

    door_lr_done:
        ;
    }

    if (cmp == 0)
    {
        *reinterpret_cast<std::uint16_t*>(unaff_EDI + 1) = 0x0402;
        return;
    }

    {
        const unsigned char* pbVar3 =
            reinterpret_cast<const unsigned char*>(str1);
        const char* pcVar4 = "bonnet_dummy";
        unsigned char bVar1;
        bool bVar5;

        do
        {
            bVar1 = *pbVar3;
            bVar5 = bVar1 < static_cast<unsigned char>(*pcVar4);

            if (bVar1 != static_cast<unsigned char>(*pcVar4))
                goto bonnet_mismatch;

            if (bVar1 == 0)
                break;

            bVar1 = pbVar3[1];
            bVar5 = bVar1 < static_cast<unsigned char>(pcVar4[1]);

            if (bVar1 != static_cast<unsigned char>(pcVar4[1]))
                goto bonnet_mismatch;

            pbVar3 += 2;
            pcVar4 += 2;
        } while (bVar1 != 0);

        cmp = 0;
        goto bonnet_done;

    bonnet_mismatch:
        cmp = static_cast<std::int32_t>(
            (1u - static_cast<unsigned>(bVar5)) -
            static_cast<unsigned>(bVar5 != false));

    bonnet_done:
        ;
    }

    if (cmp == 0)
    {
        *reinterpret_cast<std::uint16_t*>(unaff_EDI + 1) = 3;
        return;
    }

    {
        const unsigned char* pbVar3 =
            reinterpret_cast<const unsigned char*>(str1);
        const char* pcVar4 = "boot_dummy";
        unsigned char bVar1;
        bool bVar5;

        do
        {
            bVar1 = *pbVar3;
            bVar5 = bVar1 < static_cast<unsigned char>(*pcVar4);

            if (bVar1 != static_cast<unsigned char>(*pcVar4))
                goto boot_mismatch;

            if (bVar1 == 0)
                break;

            bVar1 = pbVar3[1];
            bVar5 = bVar1 < static_cast<unsigned char>(pcVar4[1]);

            if (bVar1 != static_cast<unsigned char>(pcVar4[1]))
                goto boot_mismatch;

            pbVar3 += 2;
            pcVar4 += 2;
        } while (bVar1 != 0);

        cmp = 0;
        goto boot_done;

    boot_mismatch:
        cmp = static_cast<std::int32_t>(
            (1u - static_cast<unsigned>(bVar5)) -
            static_cast<unsigned>(bVar5 != false));

    boot_done:
        ;
    }

    if (cmp == 0)
    {
        *reinterpret_cast<std::uint16_t*>(unaff_EDI + 1) = 0x0104;
        return;
    }

    {
        const unsigned char* pbVar3 =
            reinterpret_cast<const unsigned char*>(str1);
        const char* pcVar4 = "bump_front_dummy";
        unsigned char bVar1;
        bool bVar5;

        do
        {
            bVar1 = *pbVar3;
            bVar5 = bVar1 < static_cast<unsigned char>(*pcVar4);

            if (bVar1 != static_cast<unsigned char>(*pcVar4))
                goto bump_front_mismatch;

            if (bVar1 == 0)
                break;

            bVar1 = pbVar3[1];
            bVar5 = bVar1 < static_cast<unsigned char>(pcVar4[1]);

            if (bVar1 != static_cast<unsigned char>(pcVar4[1]))
                goto bump_front_mismatch;

            pbVar3 += 2;
            pcVar4 += 2;
        } while (bVar1 != 0);

        cmp = 0;
        goto bump_front_done;

    bump_front_mismatch:
        cmp = static_cast<std::int32_t>(
            (1u - static_cast<unsigned>(bVar5)) -
            static_cast<unsigned>(bVar5 != false));

    bump_front_done:
        ;
    }

    if (cmp == 0)
    {
        *reinterpret_cast<std::uint16_t*>(unaff_EDI + 1) = 0x0500;
        return;
    }

    {
        const unsigned char* pbVar3 =
            reinterpret_cast<const unsigned char*>(str1);
        const char* pcVar4 = "bump_rear_dummy";
        unsigned char bVar1;
        bool bVar5;

        do
        {
            bVar1 = *pbVar3;
            bVar5 = bVar1 < static_cast<unsigned char>(*pcVar4);

            if (bVar1 != static_cast<unsigned char>(*pcVar4))
                goto bump_rear_mismatch;

            if (bVar1 == 0)
                break;

            bVar1 = pbVar3[1];
            bVar5 = bVar1 < static_cast<unsigned char>(pcVar4[1]);

            if (bVar1 != static_cast<unsigned char>(pcVar4[1]))
                goto bump_rear_mismatch;

            pbVar3 += 2;
            pcVar4 += 2;
        } while (bVar1 != 0);

        cmp = 0;
        goto bump_rear_done;

    bump_rear_mismatch:
        cmp = static_cast<std::int32_t>(
            (1u - static_cast<unsigned>(bVar5)) -
            static_cast<unsigned>(bVar5 != false));

    bump_rear_done:
        ;
    }

    if (cmp == 0)
    {
        *reinterpret_cast<std::uint16_t*>(unaff_EDI + 1) = 0x0600;
        return;
    }

    {
        const unsigned char* pbVar3 =
            reinterpret_cast<const unsigned char*>(str1);
        const char* pcVar4 = "wing_rf_dummy";
        unsigned char bVar1;
        bool bVar5;

        do
        {
            bVar1 = *pbVar3;
            bVar5 = bVar1 < static_cast<unsigned char>(*pcVar4);

            if (bVar1 != static_cast<unsigned char>(*pcVar4))
                goto wing_rf_mismatch;

            if (bVar1 == 0)
                break;

            bVar1 = pbVar3[1];
            bVar5 = bVar1 < static_cast<unsigned char>(pcVar4[1]);

            if (bVar1 != static_cast<unsigned char>(pcVar4[1]))
                goto wing_rf_mismatch;

            pbVar3 += 2;
            pcVar4 += 2;
        } while (bVar1 != 0);

        cmp = 0;
        goto wing_rf_done;

    wing_rf_mismatch:
        cmp = static_cast<std::int32_t>(
            (1u - static_cast<unsigned>(bVar5)) -
            static_cast<unsigned>(bVar5 != false));

    wing_rf_done:
        ;
    }

    if (cmp == 0)
    {
        *reinterpret_cast<std::uint16_t*>(unaff_EDI + 1) = 0x0100;
        return;
    }

    {
        const unsigned char* pbVar3 =
            reinterpret_cast<const unsigned char*>(str1);
        const char* pcVar4 = "wing_lf_dummy";
        unsigned char bVar1;
        bool bVar5;

        do
        {
            bVar1 = *pbVar3;
            bVar5 = bVar1 < static_cast<unsigned char>(*pcVar4);

            if (bVar1 != static_cast<unsigned char>(*pcVar4))
                goto wing_lf_mismatch;

            if (bVar1 == 0)
                break;

            bVar1 = pbVar3[1];
            bVar5 = bVar1 < static_cast<unsigned char>(pcVar4[1]);

            if (bVar1 != static_cast<unsigned char>(pcVar4[1]))
                goto wing_lf_mismatch;

            pbVar3 += 2;
            pcVar4 += 2;
        } while (bVar1 != 0);

        cmp = 0;
        goto wing_lf_done;

    wing_lf_mismatch:
        cmp = static_cast<std::int32_t>(
            (1u - static_cast<unsigned>(bVar5)) -
            static_cast<unsigned>(bVar5 != false));

    wing_lf_done:
        ;
    }

    if (cmp == 0)
    {
        *reinterpret_cast<std::uint16_t*>(unaff_EDI + 1) = 0;
        return;
    }

    *reinterpret_cast<std::uint8_t*>(unaff_EDI + 1) = 6;
}