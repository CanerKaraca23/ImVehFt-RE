#include <cstdint>

#pragma pack(push, 1)
struct FUN_1000a4f0_Node
{
    std::int32_t self;   // +0x00
    std::int32_t next;   // +0x04
    std::uint32_t value; // +0x08
};
#pragma pack(pop)

static_assert(sizeof(FUN_1000a4f0_Node) == 0x0C);

extern "C" std::int32_t __stdcall FUN_10009360(void);

extern "C" std::uint32_t __stdcall FUN_1000a4f0(void)
{
    const std::int32_t iVar2 = FUN_10009360();
    auto* const root = reinterpret_cast<FUN_1000a4f0_Node*>(
        static_cast<std::uintptr_t>(iVar2));

    if (root->next == 0)
    {
        root->next = iVar2;
        root->self = iVar2;
    }

    std::int32_t iVar6 = root->next;

    do
    {
        if (root->next == 0)
        {
            root->next = iVar2;
            root->self = iVar2;
        }

        if (iVar6 == iVar2)
        {
            return 0;
        }

        auto* const node = reinterpret_cast<FUN_1000a4f0_Node*>(
            static_cast<std::uintptr_t>(iVar6));

        std::uint8_t* pbVar3 = reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(node->value));
        const char* pcVar5 = "SA::Render";

        std::int32_t iVar4;
        std::uint8_t bVar1;
        bool bVar7;

        do
        {
            bVar1 = *pbVar3;
            bVar7 = bVar1 < static_cast<std::uint8_t>(*pcVar5);

            if (bVar1 != static_cast<std::uint8_t>(*pcVar5))
            {
                iVar4 =
                    (1 - static_cast<std::uint32_t>(bVar7)) -
                    static_cast<std::uint32_t>(bVar7 != 0);
                goto LAB_1000a545;
            }

            if (bVar1 == 0)
            {
                break;
            }

            bVar1 = pbVar3[1];
            bVar7 = bVar1 < static_cast<std::uint8_t>(pcVar5[1]);

            if (bVar1 != static_cast<std::uint8_t>(pcVar5[1]))
            {
                iVar4 =
                    (1 - static_cast<std::uint32_t>(bVar7)) -
                    static_cast<std::uint32_t>(bVar7 != 0);
                goto LAB_1000a545;
            }

            pbVar3 = pbVar3 + 2;
            pcVar5 = pcVar5 + 2;
        }
        while (bVar1 != 0);

        iVar4 = 0;

    LAB_1000a545:
        if (iVar4 == 0)
        {
            return node->value;
        }

        iVar6 = node->next;
    }
    while (true);
}