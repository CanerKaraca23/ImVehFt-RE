#include <cstdint>

extern void* BasicCallbackManager_0_0_0_0_cbResetDeviceManager_vftable;

extern std::uint32_t _DAT_1003c32c;
extern std::uint32_t _DAT_1003c330;
extern std::uint32_t _DAT_1003c334;
extern std::uint32_t _DAT_1003c338;
extern std::uint32_t _DAT_1003c33c;
extern std::uint32_t _DAT_1003c340;
extern std::uint32_t _DAT_1003c344;
extern std::uint32_t _DAT_1003c348;
extern std::uint32_t _DAT_1003c34c;
extern std::uint32_t _DAT_1003c350;
extern std::uint32_t _DAT_1003c354;
extern std::uint32_t _DAT_1003c358;
extern std::uint32_t _DAT_1003c35c;
extern std::uint32_t _DAT_1003c360;
extern std::uint32_t _DAT_1003c364;
extern std::uint32_t _DAT_1003c368;
extern std::uint32_t DAT_1003c36c;
extern std::uint32_t DAT_1003c370;
extern std::uint32_t DAT_1003c374;
extern std::uint32_t DAT_1003c37c;
extern std::uint32_t DAT_1003c380;
extern std::uint32_t DAT_1003c384;
extern std::uint32_t DAT_1003c328;

std::uint32_t* __stdcall FUN_1000a090()
{
    _DAT_1003c32c = 0;
    _DAT_1003c330 = 0;
    _DAT_1003c334 = 0;
    _DAT_1003c338 = 0;
    _DAT_1003c33c = 0;
    _DAT_1003c340 = 0;
    _DAT_1003c344 = 0;
    _DAT_1003c348 = 0;
    _DAT_1003c34c = 0;
    _DAT_1003c350 = 0;
    _DAT_1003c354 = 0;
    _DAT_1003c358 = 0;
    _DAT_1003c35c = 0;
    _DAT_1003c360 = 0;
    _DAT_1003c364 = 0;
    _DAT_1003c368 = 0;
    DAT_1003c36c = 0;
    DAT_1003c370 = 0;
    DAT_1003c374 = 0;
    DAT_1003c37c = 0;
    DAT_1003c380 = 0;
    DAT_1003c384 = 0;

    *reinterpret_cast<void**>(&DAT_1003c328) =
        BasicCallbackManager_0_0_0_0_cbResetDeviceManager_vftable;

    return &DAT_1003c328;
}