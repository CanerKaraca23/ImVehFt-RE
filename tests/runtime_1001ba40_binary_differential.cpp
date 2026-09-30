#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <limits>

#include <Windows.h>
#include <xmmintrin.h>

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This differential harness requires MSVC x86."
#endif

#ifndef IVF_RANDOM_PATTERN_COUNT
#define IVF_RANDOM_PATTERN_COUNT 4096
#endif

extern "C" volatile std::uint32_t DAT_1003c414 = 0;
extern "C" std::uint64_t __fastcall FUN_1001ba40(
    std::uint32_t,
    std::uint32_t);

namespace {

constexpr std::uintptr_t kOriginalEntry = 0x1001ba40;
constexpr std::uintptr_t kOriginalFlag = 0x1003c414;
constexpr std::size_t kOriginalCodeSize = 0xab;
std::uintptr_t gOriginalEntry = 0;

// Exact .text bytes at ImVehFt.asi VA 0x1001ba40, file offset 0x1ae40.
// Source image SHA-256:
// 409F0DF7AE579841DB05C3EC6AD0A9AFC579194632874962E1BDEE0CCF020D3
// Function ends at 0x1001baeb. The entry-reachable paths are all contained in
// these bytes; the two absolute data operands are redirected to a test page.
constexpr std::array<std::uint8_t, kOriginalCodeSize> kOriginalBytes = {
    0x83,0x3d,0x14,0xc4,0x03,0x10,0x00,0x74,0x2d,0x55,0x8b,0xec,0x83,0xec,0x08,0x83,
    0xe4,0xf8,0xdd,0x1c,0x24,0xf2,0x0f,0x2c,0x04,0x24,0xc9,0xc3,0x83,0x3d,0x14,0xc4,
    0x03,0x10,0x00,0x74,0x11,0x83,0xec,0x04,0xd9,0x3c,0x24,0x58,0x66,0x83,0xe0,0x7f,
    0x66,0x83,0xf8,0x7f,0x74,0xd3,0x55,0x8b,0xec,0x83,0xec,0x20,0x83,0xe4,0xf0,0xd9,
    0xc0,0xd9,0x54,0x24,0x18,0xdf,0x7c,0x24,0x10,0xdf,0x6c,0x24,0x10,0x8b,0x54,0x24,
    0x18,0x8b,0x44,0x24,0x10,0x85,0xc0,0x74,0x3c,0xde,0xe9,0x85,0xd2,0x79,0x1e,0xd9,
    0x1c,0x24,0x8b,0x0c,0x24,0x81,0xf1,0x00,0x00,0x00,0x80,0x81,0xc1,0xff,0xff,0xff,
    0x7f,0x83,0xd0,0x00,0x8b,0x54,0x24,0x14,0x83,0xd2,0x00,0xeb,0x2c,0xd9,0x1c,0x24,
    0x8b,0x0c,0x24,0x81,0xc1,0xff,0xff,0xff,0x7f,0x83,0xd8,0x00,0x8b,0x54,0x24,0x14,
    0x83,0xda,0x00,0xeb,0x14,0x8b,0x54,0x24,0x14,0xf7,0xc2,0xff,0xff,0xff,0x7f,0x75,
    0xb8,0xd9,0x5c,0x24,0x18,0xd9,0x5c,0x24,0x18,0xc9,0xc3
};

struct Result {
    std::uint32_t low;
    std::uint32_t high;
    std::uint16_t status;
    std::uint16_t control;
    std::uint32_t mxcsr;
    std::uint8_t x87Tag;
};

struct Input {
    const char* name;
    std::uint64_t bits;
};

constexpr std::array<Input, 22> kInputs = {{
    {"plus-zero",              0x0000000000000000ull},
    {"minus-zero",             0x8000000000000000ull},
    {"small-positive",         0x3fb999999999999aull},
    {"positive-half",          0x3fe0000000000000ull},
    {"positive-half-below",    0x3fdfffffffffffffull},
    {"positive-half-above",    0x3fe0000000000001ull},
    {"positive-one-half",      0x3ff8000000000000ull},
    {"positive-two-half",      0x4004000000000000ull},
    {"negative-half",          0xbfe0000000000000ull},
    {"negative-one-half",      0xbff8000000000000ull},
    {"negative-two-half",      0xc004000000000000ull},
    {"near-int32-max",         0x41dfffffffc00000ull},
    {"int32-max-rounded",      0x41dfffffffe00000ull},
    {"int32-overflow",         0x41e0000000000000ull},
    {"near-int32-min",         0xc1e0000000000000ull},
    {"negative-overflow",      0xc1e0000000200000ull},
    {"large-finite",           0x43e0000000000000ull},
    {"positive-infinity",      0x7ff0000000000000ull},
    {"negative-infinity",      0xfff0000000000000ull},
    {"quiet-nan",              0x7ff8000000000001ull},
    {"negative-quiet-nan",     0xfff8000000000001ull},
    {"subnormal",              0x0000000000000001ull},
}};

constexpr std::array<std::uint16_t, 4> kControlWords = {
    0x037f, // round-to-nearest
    0x077f, // round-down
    0x0b7f, // round-up
    0x0f7f, // truncate
};

Result CallOriginal(double input, std::uint32_t arg1, std::uint32_t arg2,
                    std::uint16_t controlWord)
{
    std::uint32_t resultLow = 0;
    std::uint32_t resultHigh = 0;
    std::uint16_t resultStatus = 0;
    std::uint16_t resultControl = 0;
    std::uint8_t x87Tag = 0;
    __declspec(align(16)) std::uint8_t fxState[512] = {};
    const std::uintptr_t entry = gOriginalEntry;

    _mm_setcsr(0x1f80);
    __asm {
        fninit
        fldcw controlWord
        fld qword ptr input
        mov ecx, arg1
        mov edx, arg2
        mov eax, entry
        call eax
        mov resultLow, eax
        mov resultHigh, edx
        fnstsw ax
        mov resultStatus, ax
        fnstcw word ptr resultControl
        lea eax, fxState
        fxsave [eax]
        mov al, byte ptr [eax + 4]
        mov x87Tag, al
    }

    return {resultLow, resultHigh, resultStatus, resultControl, _mm_getcsr(), x87Tag};
}

Result CallCandidate(double input, std::uint32_t arg1, std::uint32_t arg2,
                     std::uint16_t controlWord)
{
    std::uint32_t resultLow = 0;
    std::uint32_t resultHigh = 0;
    std::uint16_t resultStatus = 0;
    std::uint16_t resultControl = 0;
    std::uint8_t x87Tag = 0;
    __declspec(align(16)) std::uint8_t fxState[512] = {};

    _mm_setcsr(0x1f80);
    __asm {
        fninit
        fldcw controlWord
        fld qword ptr input
        mov ecx, arg1
        mov edx, arg2
        call FUN_1001ba40
        mov resultLow, eax
        mov resultHigh, edx
        fnstsw ax
        mov resultStatus, ax
        fnstcw word ptr resultControl
        lea eax, fxState
        fxsave [eax]
        mov al, byte ptr [eax + 4]
        mov x87Tag, al
    }

    return {resultLow, resultHigh, resultStatus, resultControl, _mm_getcsr(), x87Tag};
}

bool Same(const Result& left, const Result& right)
{
    return left.low == right.low && left.high == right.high &&
           left.status == right.status && left.control == right.control &&
           left.mxcsr == right.mxcsr && left.x87Tag == right.x87Tag;
}

} // namespace

int main()
{
    static_assert(sizeof(void*) == 4, "Run as a 32-bit executable.");
    static_assert(kOriginalBytes.size() == kOriginalCodeSize);

    auto* const codePage = static_cast<std::uint8_t*>(VirtualAlloc(
        nullptr, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
    if (codePage == nullptr) {
        std::fprintf(stderr, "Could not reserve test code page (error %lu).\n",
                     GetLastError());
        return 2;
    }

    auto* const flagPage = static_cast<std::uint8_t*>(VirtualAlloc(
        nullptr, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
    if (flagPage == nullptr) {
        std::fprintf(stderr, "Could not reserve test data page (error %lu).\n",
                     GetLastError());
        VirtualFree(codePage, 0, MEM_RELEASE);
        return 2;
    }

    constexpr std::size_t originalEntryOffset = kOriginalEntry - 0x1001b000;
    auto* const relocatedOriginalEntry = codePage + originalEntryOffset;
    std::memcpy(relocatedOriginalEntry, kOriginalBytes.data(), kOriginalBytes.size());
    const auto relocatedFlag = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(flagPage + (kOriginalFlag & 0xfff)));
    std::size_t absoluteGlobalFixups = 0;
    for (std::size_t offset = 0; offset + sizeof(std::uint32_t) <= kOriginalBytes.size(); ++offset) {
        std::uint32_t operand = 0;
        std::memcpy(&operand, relocatedOriginalEntry + offset, sizeof(operand));
        if (operand == kOriginalFlag) {
            std::memcpy(relocatedOriginalEntry + offset, &relocatedFlag, sizeof(relocatedFlag));
            ++absoluteGlobalFixups;
        }
    }
    if (absoluteGlobalFixups != 2) {
        std::fprintf(stderr, "Expected exactly 2 original-flag operands; patched %zu.\n",
                     absoluteGlobalFixups);
        VirtualFree(flagPage, 0, MEM_RELEASE);
        VirtualFree(codePage, 0, MEM_RELEASE);
        return 2;
    }

    DWORD oldProtection = 0;
    if (!VirtualProtect(codePage, 0x1000, PAGE_EXECUTE_READ, &oldProtection)) {
        std::fprintf(stderr, "Could not protect original code page (error %lu).\n",
                     GetLastError());
        VirtualFree(flagPage, 0, MEM_RELEASE);
        VirtualFree(codePage, 0, MEM_RELEASE);
        return 2;
    }
    FlushInstructionCache(GetCurrentProcess(), codePage, 0x1000);

    auto* const originalFlag = reinterpret_cast<volatile std::uint32_t*>(
        flagPage + (kOriginalFlag & 0xfff));
    const auto originalEntry = reinterpret_cast<std::uintptr_t>(relocatedOriginalEntry);
    gOriginalEntry = originalEntry;
    constexpr std::uint32_t arg1 = 0x13579bdf;
    constexpr std::uint32_t arg2 = 0xa5c36987;
    std::size_t comparisons = 0;
    std::size_t mismatches = 0;
    constexpr std::size_t randomPatternCount = IVF_RANDOM_PATTERN_COUNT;

    const auto compareOne = [&](const char* name, std::uint64_t bits,
                                std::uint32_t mode, std::uint16_t controlWord) {
        double input = 0.0;
        std::memcpy(&input, &bits, sizeof(input));
        const auto expected = CallOriginal(input, arg1, arg2, controlWord);
        const auto actual = CallCandidate(input, arg1, arg2, controlWord);
        ++comparisons;
        if (!Same(expected, actual)) {
            if (mismatches < 32) {
                std::printf(
                    "MISMATCH mode=%08x cw=%04x input=%s bits=%016llx orig=%08x:%08x sw=%04x cw=%04x mx=%08x tag=%02x cand=%08x:%08x sw=%04x cw=%04x mx=%08x tag=%02x\n",
                    mode, controlWord, name,
                    static_cast<unsigned long long>(bits),
                    expected.high, expected.low, expected.status,
                    expected.control, expected.mxcsr, expected.x87Tag,
                    actual.high, actual.low, actual.status,
                    actual.control, actual.mxcsr, actual.x87Tag);
            }
            ++mismatches;
        }
    };

    for (const auto mode : {0u, 1u, 0x12345678u}) {
        *originalFlag = mode;
        DAT_1003c414 = mode;
        for (const auto controlWord : kControlWords) {
            for (const auto& test : kInputs) {
                compareOne(test.name, test.bits, mode, controlWord);
            }

            std::uint64_t randomState = 0x9e3779b97f4a7c15ull;
            for (std::size_t index = 0; index < randomPatternCount; ++index) {
                randomState ^= randomState >> 12;
                randomState ^= randomState << 25;
                randomState ^= randomState >> 27;
                const auto bits = randomState * 0x2545f4914f6cdd1dull;
                compareOne("xorshift64*", bits, mode, controlWord);
            }
        }
    }

    std::printf(
        "FUN_1001ba40 original-binary differential: %zu/%zu matched; %zu mismatches (%zu directed inputs + %zu deterministic random bit patterns per mode/control-word pair).\n",
        comparisons - mismatches, comparisons, mismatches, kInputs.size(),
        randomPatternCount);
    VirtualFree(flagPage, 0, MEM_RELEASE);
    VirtualFree(codePage, 0, MEM_RELEASE);
    return mismatches == 0 ? 0 : 1;
}
