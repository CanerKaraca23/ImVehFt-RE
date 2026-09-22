#include <cstddef>
#include <cstdint>

extern "C" void* __fastcall FUN_10016f49(std::uint32_t param_1)
{
    std::uint8_t* source;
    std::uint8_t* destination;
    __asm mov source, esi
    __asm mov destination, edi

    std::uint8_t* original_destination = destination;

    if ((reinterpret_cast<std::uintptr_t>(source) & 0x0Fu) != 0u) {
        const std::uint32_t alignment_bytes =
            0x10u - static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(source) & 0x0Fu);

        param_1 -= alignment_bytes;

        for (std::uint32_t count = alignment_bytes & 3u;
             count != 0u;
             --count) {
            *destination = *source;
            ++source;
            ++destination;
        }

        for (std::uint32_t count = alignment_bytes >> 2u;
             count != 0u;
             --count) {
            *reinterpret_cast<std::uint32_t*>(destination) =
                *reinterpret_cast<const std::uint32_t*>(source);
            source += 4;
            destination += 4;
        }
    }

    for (std::uint32_t count = param_1 >> 7u;
         count != 0u;
         --count) {
        const std::uint32_t value_01 =
            reinterpret_cast<const std::uint32_t*>(source)[1];
        const std::uint32_t value_02 =
            reinterpret_cast<const std::uint32_t*>(source)[2];
        const std::uint32_t value_03 =
            reinterpret_cast<const std::uint32_t*>(source)[3];
        const std::uint32_t value_04 =
            reinterpret_cast<const std::uint32_t*>(source)[4];
        const std::uint32_t value_05 =
            reinterpret_cast<const std::uint32_t*>(source)[5];
        const std::uint32_t value_06 =
            reinterpret_cast<const std::uint32_t*>(source)[6];
        const std::uint32_t value_07 =
            reinterpret_cast<const std::uint32_t*>(source)[7];
        const std::uint32_t value_08 =
            reinterpret_cast<const std::uint32_t*>(source)[8];
        const std::uint32_t value_09 =
            reinterpret_cast<const std::uint32_t*>(source)[9];
        const std::uint32_t value_10 =
            reinterpret_cast<const std::uint32_t*>(source)[10];
        const std::uint32_t value_11 =
            reinterpret_cast<const std::uint32_t*>(source)[11];
        const std::uint32_t value_12 =
            reinterpret_cast<const std::uint32_t*>(source)[12];
        const std::uint32_t value_13 =
            reinterpret_cast<const std::uint32_t*>(source)[13];
        const std::uint32_t value_14 =
            reinterpret_cast<const std::uint32_t*>(source)[14];
        const std::uint32_t value_15 =
            reinterpret_cast<const std::uint32_t*>(source)[15];

        reinterpret_cast<std::uint32_t*>(destination)[0] =
            reinterpret_cast<const std::uint32_t*>(source)[0];
        reinterpret_cast<std::uint32_t*>(destination)[1] = value_01;
        reinterpret_cast<std::uint32_t*>(destination)[2] = value_02;
        reinterpret_cast<std::uint32_t*>(destination)[3] = value_03;
        reinterpret_cast<std::uint32_t*>(destination)[4] = value_04;
        reinterpret_cast<std::uint32_t*>(destination)[5] = value_05;
        reinterpret_cast<std::uint32_t*>(destination)[6] = value_06;
        reinterpret_cast<std::uint32_t*>(destination)[7] = value_07;
        reinterpret_cast<std::uint32_t*>(destination)[8] = value_08;
        reinterpret_cast<std::uint32_t*>(destination)[9] = value_09;
        reinterpret_cast<std::uint32_t*>(destination)[10] = value_10;
        reinterpret_cast<std::uint32_t*>(destination)[11] = value_11;
        reinterpret_cast<std::uint32_t*>(destination)[12] = value_12;
        reinterpret_cast<std::uint32_t*>(destination)[13] = value_13;
        reinterpret_cast<std::uint32_t*>(destination)[14] = value_14;
        reinterpret_cast<std::uint32_t*>(destination)[15] = value_15;

        const std::uint32_t value_17 =
            reinterpret_cast<const std::uint32_t*>(source)[17];
        const std::uint32_t value_18 =
            reinterpret_cast<const std::uint32_t*>(source)[18];
        const std::uint32_t value_19 =
            reinterpret_cast<const std::uint32_t*>(source)[19];
        const std::uint32_t value_20 =
            reinterpret_cast<const std::uint32_t*>(source)[20];
        const std::uint32_t value_21 =
            reinterpret_cast<const std::uint32_t*>(source)[21];
        const std::uint32_t value_22 =
            reinterpret_cast<const std::uint32_t*>(source)[22];
        const std::uint32_t value_23 =
            reinterpret_cast<const std::uint32_t*>(source)[23];
        const std::uint32_t value_24 =
            reinterpret_cast<const std::uint32_t*>(source)[24];
        const std::uint32_t value_25 =
            reinterpret_cast<const std::uint32_t*>(source)[25];
        const std::uint32_t value_26 =
            reinterpret_cast<const std::uint32_t*>(source)[26];
        const std::uint32_t value_27 =
            reinterpret_cast<const std::uint32_t*>(source)[27];
        const std::uint32_t value_28 =
            reinterpret_cast<const std::uint32_t*>(source)[28];
        const std::uint32_t value_29 =
            reinterpret_cast<const std::uint32_t*>(source)[29];
        const std::uint32_t value_30 =
            reinterpret_cast<const std::uint32_t*>(source)[30];
        const std::uint32_t value_31 =
            reinterpret_cast<const std::uint32_t*>(source)[31];

        reinterpret_cast<std::uint32_t*>(destination)[16] =
            reinterpret_cast<const std::uint32_t*>(source)[16];
        reinterpret_cast<std::uint32_t*>(destination)[17] = value_17;
        reinterpret_cast<std::uint32_t*>(destination)[18] = value_18;
        reinterpret_cast<std::uint32_t*>(destination)[19] = value_19;
        reinterpret_cast<std::uint32_t*>(destination)[20] = value_20;
        reinterpret_cast<std::uint32_t*>(destination)[21] = value_21;
        reinterpret_cast<std::uint32_t*>(destination)[22] = value_22;
        reinterpret_cast<std::uint32_t*>(destination)[23] = value_23;
        reinterpret_cast<std::uint32_t*>(destination)[24] = value_24;
        reinterpret_cast<std::uint32_t*>(destination)[25] = value_25;
        reinterpret_cast<std::uint32_t*>(destination)[26] = value_26;
        reinterpret_cast<std::uint32_t*>(destination)[27] = value_27;
        reinterpret_cast<std::uint32_t*>(destination)[28] = value_28;
        reinterpret_cast<std::uint32_t*>(destination)[29] = value_29;
        reinterpret_cast<std::uint32_t*>(destination)[30] = value_30;
        reinterpret_cast<std::uint32_t*>(destination)[31] = value_31;

        source += 0x80;
        destination += 0x80;
    }

    if ((param_1 & 0x7Fu) != 0u) {
        for (std::uint32_t count = (param_1 & 0x7Fu) >> 4u;
             count != 0u;
             --count) {
            const std::uint32_t value_01 =
                reinterpret_cast<const std::uint32_t*>(source)[1];
            const std::uint32_t value_02 =
                reinterpret_cast<const std::uint32_t*>(source)[2];
            const std::uint32_t value_03 =
                reinterpret_cast<const std::uint32_t*>(source)[3];

            reinterpret_cast<std::uint32_t*>(destination)[0] =
                reinterpret_cast<const std::uint32_t*>(source)[0];
            reinterpret_cast<std::uint32_t*>(destination)[1] = value_01;
            reinterpret_cast<std::uint32_t*>(destination)[2] = value_02;
            reinterpret_cast<std::uint32_t*>(destination)[3] = value_03;

            source += 0x10;
            destination += 0x10;
        }

        if ((param_1 & 0x0Fu) != 0u) {
            for (std::uint32_t count = (param_1 & 0x0Fu) >> 2u;
                 count != 0u;
                 --count) {
                *reinterpret_cast<std::uint32_t*>(destination) =
                    *reinterpret_cast<const std::uint32_t*>(source);
                source += 4;
                destination += 4;
            }

            for (std::uint32_t count = param_1 & 3u;
                 count != 0u;
                 --count) {
                *destination = *source;
                ++source;
                ++destination;
            }
        }
    }

    return original_destination;
}