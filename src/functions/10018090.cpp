#include <cstdint>

extern "C" std::int32_t __cdecl __ValidateImageBase(std::uint8_t* pImageBase)
{
    if ((*reinterpret_cast<std::int16_t*>(pImageBase) == 0x5A4D) &&
        (*reinterpret_cast<std::int32_t*>(
             pImageBase +
             *reinterpret_cast<std::int32_t*>(pImageBase + 0x3C)) == 0x4550))
    {
        const std::int32_t nt_offset =
            *reinterpret_cast<std::int32_t*>(pImageBase + 0x3C);
        const std::int16_t optional_header_magic =
            *reinterpret_cast<std::int16_t*>(pImageBase + nt_offset + 0x18);
        return static_cast<std::int32_t>(optional_header_magic == 0x010B);
    }

    return 0;
}