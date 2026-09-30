#include "imvehft_image_aliases.hpp"
#include <cstdint>
#include "gta_sa_address_access.hpp"

extern "C" void __cdecl _free(void*);

#define PTR_DAT_10029eb4 IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10029EB4)
#define PTR_DAT_10029eb8 IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10029EB8)
#define PTR_DAT_10029ebc IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10029EBC)
#define PTR_DAT_10029ec0 IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10029EC0)
#define PTR_DAT_10029ec4 IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10029EC4)
#define PTR_DAT_10029ec8 IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10029EC8)
#define PTR_DAT_10029ecc IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10029ECC)
#define PTR_DAT_10029ee0 IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10029EE0)
#define PTR_DAT_10029ee4 IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10029EE4)
#define PTR_DAT_10029ee8 IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10029EE8)
#define PTR_DAT_10029eec IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10029EEC)
#define PTR_DAT_10029ef0 IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10029EF0)
#define PTR_DAT_10029ef4 IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10029EF4)

extern "C" void __cdecl ___free_lconv_mon(int param_1)
{
    if (param_1 != 0)
    {
        const std::uintptr_t base =
            static_cast<std::uintptr_t>(
                static_cast<std::uint32_t>(param_1));

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x0c))) !=
            PTR_DAT_10029eb4)
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x0c))));

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x10))) !=
            PTR_DAT_10029eb8)
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x10))));

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x14))) !=
            PTR_DAT_10029ebc)
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x14))));

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x18))) !=
            PTR_DAT_10029ec0)
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x18))));

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x1c))) !=
            PTR_DAT_10029ec4)
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x1c))));

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x20))) !=
            PTR_DAT_10029ec8)
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x20))));

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x24))) !=
            PTR_DAT_10029ecc)
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x24))));

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x38))) !=
            PTR_DAT_10029ee0)
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x38))));

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x3c))) !=
            PTR_DAT_10029ee4)
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x3c))));

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x40))) !=
            PTR_DAT_10029ee8)
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x40))));

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x44))) !=
            PTR_DAT_10029eec)
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x44))));

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x48))) !=
            PTR_DAT_10029ef0)
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x48))));

        if (reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x4c))) !=
            PTR_DAT_10029ef4)
            _free(reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    *reinterpret_cast<const std::uint32_t*>(base + 0x4c))));
    }
}
