#include <cstdint>

#pragma pack(push, 1)
struct FUN_10001350_Node
{
    std::uint32_t next;        // +0x00
    std::uint8_t  unknown04[4];
    std::uint16_t index;       // +0x08
    std::uint8_t  padding0A;  // +0x0A
    std::uint8_t  flag;        // +0x0B
    std::uint8_t  unknown0C[4];
    std::uint32_t source;      // +0x10
};
#pragma pack(pop)

extern "C" std::uint32_t DAT_1003c25c;
extern "C" std::uint32_t DAT_00A9B0C8[];

extern "C" void __stdcall FUN_10001350()
{
    auto* sentinel =
        reinterpret_cast<FUN_10001350_Node*>(&DAT_1003c25c);

    auto* node =
        reinterpret_cast<FUN_10001350_Node*>(
            static_cast<std::uintptr_t>(sentinel->next));

    if (node != sentinel)
    {
        do
        {
            const std::uint16_t index = node->index;

            auto* object =
                reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(DAT_00A9B0C8[index]));

            const std::uint8_t flag = node->flag;
            object[0x2D0] = flag;

            if (flag != 0)
            {
                int offset = 0;
                auto* destination = object + 0x2B8;
                const auto* source =
                    reinterpret_cast<const std::uint8_t*>(
                        static_cast<std::uintptr_t>(node->source));

                do
                {
                    destination[-8]  = source[offset];
                    destination[0]   = source[offset + 2];
                    destination[8]   = source[offset + 4];
                    destination[16]  = source[offset + 6];

                    ++destination;
                    offset += 8;
                }
                while ((destination - (object + 0x2B8)) <
                       static_cast<std::uint8_t>(object[0x2D0]));
            }

            node =
                reinterpret_cast<FUN_10001350_Node*>(
                    static_cast<std::uintptr_t>(node->next));
        }
        while (node != sentinel);
    }
}