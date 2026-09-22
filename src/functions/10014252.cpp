#include <cstddef>
#include <cstdint>

struct threadmbcinfostruct;

extern "C" void* __cdecl _memset(void* destination, int value, std::size_t size);
extern const std::uint8_t DAT_100294a0[];

void __cdecl setSBCS(threadmbcinfostruct* param_1)
{
    auto* base = reinterpret_cast<std::uint8_t*>(param_1);

    (void)_memset(base + 0x1C, 0, 0x101);

    *reinterpret_cast<std::uint32_t*>(base + 0x04) = 0;
    *reinterpret_cast<std::uint32_t*>(base + 0x08) = 0;
    *reinterpret_cast<std::uint32_t*>(base + 0x0C) = 0;
    *reinterpret_cast<std::uint32_t*>(base + 0x10) = 0;
    *reinterpret_cast<std::uint32_t*>(base + 0x14) = 0;
    *reinterpret_cast<std::uint32_t*>(base + 0x18) = 0;

    std::uint8_t* destination = base + 0x1C;
    int count = 0x101;

    do
    {
        *destination =
            DAT_100294a0[0x1C + (destination - base - 0x1C)];
        destination = destination + 1;
        count = count - 1;
    } while (count != 0);

    destination = base + 0x11D;
    count = 0x100;

    do
    {
        *destination =
            DAT_100294a0[0x11D + (destination - base - 0x11D)];
        destination = destination + 1;
        count = count - 1;
    } while (count != 0);

    return;
}