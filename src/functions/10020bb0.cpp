#include "imvehft_image_aliases.hpp"
#include <cstdint>
#include "gta_sa_address_access.hpp"

#define DAT_10037670 IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10037670)
#define DAT_10037674 IMVEHFT_GLOBAL_AT(std::uint32_t, IVF_IMAGE_ADDRESS_10037674)
#define DAT_10037678 IMVEHFT_GLOBAL_AT(std::uint32_t, IVF_IMAGE_ADDRESS_10037678)
#define DAT_10037660 IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10037660)
#define _DAT_10037664 IMVEHFT_GLOBAL_AT(std::uint32_t, IVF_IMAGE_ADDRESS_10037664)
#define _DAT_10037668 IMVEHFT_GLOBAL_AT(std::uint32_t, IVF_IMAGE_ADDRESS_10037668)

extern "C" void __cdecl FUN_10010756(void* param_1);

extern "C" void __stdcall FUN_10020bb0(void)
{
    IMVEHFT_GLOBAL_AT(void*, IVF_IMAGE_ADDRESS_10037648) =
        reinterpret_cast<void*>(IVF_IMAGE_ADDRESS_10024CE0);

    if (DAT_10037670 != nullptr) {
        FUN_10010756(DAT_10037670);
    }

    DAT_10037670 = nullptr;
    DAT_10037674 = 0;
    DAT_10037678 = 0;

    if (DAT_10037660 != nullptr) {
        FUN_10010756(DAT_10037660);
    }

    DAT_10037660 = nullptr;
    _DAT_10037664 = 0;
    _DAT_10037668 = 0;
}
