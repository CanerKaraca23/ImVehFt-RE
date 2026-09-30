#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

extern "C" std::uint32_t __cdecl __setmbcp_nolock(
    std::uint32_t requested_code_page, int context_address);

std::uint32_t DAT_10029490 = 0x12345678U;
std::uint32_t DAT_100298d0[0x3c] = {};
std::uint8_t DAT_100298cc[4] = {};
std::uint8_t DAT_100298e0[0xf0] = {};
int DAT_10039a58 = 1;
extern const std::uint8_t DAT_100294a0[0x300] = {};

static std::uint32_t g_resolved_system_code_page = 0;

extern "C" int __cdecl getSystemCP()
{
    return static_cast<int>(g_resolved_system_code_page);
}

extern "C" void __cdecl setSBUpLow(void*) {}

extern "C" void __fastcall __security_check_cookie(std::uintptr_t) {}

extern "C" void* __cdecl _memset(
    void* destination, int value, std::size_t size)
{
    return std::memset(destination, value, size);
}

static bool run_case(
    std::uint32_t requested_code_page,
    std::uint32_t resolved_system_code_page,
    std::uint32_t expected_lcid)
{
    g_resolved_system_code_page = resolved_system_code_page;
    DAT_100298d0[0] = resolved_system_code_page;

    alignas(4) std::uint8_t context[0x300] = {};
    const std::uint32_t result = __setmbcp_nolock(
        requested_code_page,
        static_cast<int>(reinterpret_cast<std::uintptr_t>(context)));

    const auto* fields = reinterpret_cast<const std::uint32_t*>(context);
    const bool passed = result == 0
        && fields[1] == resolved_system_code_page
        && fields[2] == 1
        && fields[3] == expected_lcid;

    std::printf(
        "resolved-CP locale request=%u: %s (result=%u resolved=%u lcid=0x%X expected=0x%X)\n",
        requested_code_page, passed ? "PASS" : "FAIL", result,
        fields[1], fields[3], expected_lcid);
    return passed;
}

static bool run_sbcs_fallback_case()
{
    g_resolved_system_code_page = 0;
    std::memset(DAT_100298d0, 0, sizeof(DAT_100298d0));

    alignas(4) std::uint8_t context[0x300];
    std::memset(context, 0xCC, sizeof(context));
    const std::uint32_t result = __setmbcp_nolock(
        1252,
        static_cast<int>(reinterpret_cast<std::uintptr_t>(context)));

    const auto* fields = reinterpret_cast<const std::uint32_t*>(context);
    bool copied_single_byte_tables = true;
    for (std::size_t i = 0; i < 0x201; ++i)
        copied_single_byte_tables &= context[0x1C + i] == 0;

    const bool passed = result == 0
        && fields[1] == 0 && fields[2] == 0 && fields[3] == 0
        && fields[4] == 0 && fields[5] == 0 && fields[6] == 0
        && copied_single_byte_tables;
    std::printf(
        "zero-system-CP setSBCS fallback: %s (result=%u)\n",
        passed ? "PASS" : "FAIL", result);
    return passed;
}

int main()
{
    const bool cp_932 = run_case(65001, 0x3A4, 0x411);
    const bool cp_936 = run_case(1252, 0x3A8, 0x804);
    const bool cp_949 = run_case(437, 0x3B5, 0x412);
    const bool cp_950 = run_case(65001, 0x3B6, 0x404);
    const bool sbcs_fallback = run_sbcs_fallback_case();
    return cp_932 && cp_936 && cp_949 && cp_950 && sbcs_fallback ? 0 : 1;
}
