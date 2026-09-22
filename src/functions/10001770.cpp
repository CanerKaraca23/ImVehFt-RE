#include <cstdint>

extern "C" int __stdcall VirtualProtect(
    void* address,
    std::uint32_t size,
    std::uint32_t new_protect,
    std::uint32_t* old_protect);

extern "C" void __stdcall FUN_10001770()
{
    std::uint32_t local_10;
    std::uint32_t local_c;
    std::uint32_t local_8;

    local_8 = 0xe8;
    VirtualProtect(reinterpret_cast<void*>(0x005b388d), 1, 0x40, &local_10);
    *reinterpret_cast<volatile std::uint8_t*>(0x005b388d) =
        static_cast<std::uint8_t>(local_8);
    VirtualProtect(reinterpret_cast<void*>(0x005b388d), 1, local_10, &local_c);

    VirtualProtect(reinterpret_cast<void*>(0x005b388e), 4, 0x40, &local_10);
    *reinterpret_cast<volatile std::uint32_t*>(0x005b388e) = 0xfa4e00e;
    VirtualProtect(reinterpret_cast<void*>(0x005b388e), 4, local_10, &local_c);

    local_8 = 0xe8;
    VirtualProtect(reinterpret_cast<void*>(0x00731e09), 1, 0x40, &local_10);
    *reinterpret_cast<volatile std::uint8_t*>(0x00731e09) =
        static_cast<std::uint8_t>(local_8);
    VirtualProtect(reinterpret_cast<void*>(0x00731e09), 1, local_10, &local_c);

    VirtualProtect(reinterpret_cast<void*>(0x00731e0a), 4, 0x40, &local_10);
    *reinterpret_cast<volatile std::uint32_t*>(0x00731e0a) = 0xf8cfa92;
    VirtualProtect(reinterpret_cast<void*>(0x00731e0a), 4, local_10, &local_c);
}