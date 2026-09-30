#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <array>
#include <cstdint>
#include <cstdio>

namespace {

using Function = std::uint32_t(__cdecl*)(std::uint32_t, std::uint32_t);
constexpr std::size_t kFunctionRva = 0x1CA18;
constexpr std::uint32_t kExponentMask = 0x7FF00000u;

struct MappedImage {
    HANDLE file = INVALID_HANDLE_VALUE;
    HANDLE mapping = nullptr;
    std::uint8_t* base = nullptr;
    explicit MappedImage(const wchar_t* path)
    {
        file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE,
                           nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file == INVALID_HANDLE_VALUE) return;
        mapping = CreateFileMappingW(file, nullptr, PAGE_READONLY | SEC_IMAGE, 0, 0, nullptr);
        if (mapping == nullptr) return;
        base = static_cast<std::uint8_t*>(MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, 0));
    }
    MappedImage(const MappedImage&) = delete;
    MappedImage& operator=(const MappedImage&) = delete;
    ~MappedImage()
    {
        if (base != nullptr) UnmapViewOfFile(base);
        if (mapping != nullptr) CloseHandle(mapping);
        if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
    }
    Function function() const { return reinterpret_cast<Function>(base + kFunctionRva); }
};

std::uint32_t next_random(std::uint32_t& state)
{
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

bool check(const MappedImage& original, const MappedImage& candidate,
           std::uint32_t ignored, std::uint32_t bits)
{
    const std::uint32_t expected = (bits & kExponentMask) == kExponentMask
        ? bits : bits & kExponentMask;
    const auto old_result = original.function()(ignored, bits);
    const auto new_result = candidate.function()(ignored, bits);
    if (old_result != expected || new_result != expected) {
        std::fwprintf(stderr, L"bitmask mismatch: ignored=0x%08X bits=0x%08X old=0x%08X new=0x%08X expected=0x%08X\n",
                      ignored, bits, old_result, new_result, expected);
        return false;
    }
    return true;
}

} // namespace

int wmain(int argc, wchar_t** argv)
{
    if (argc != 3) {
        std::fwprintf(stderr, L"usage: %ls <original.asi> <single-function-probe.bin>\n", argv[0]);
        return 2;
    }
    MappedImage original(argv[1]);
    MappedImage candidate(argv[2]);
    if (original.base == nullptr || candidate.base == nullptr) {
        std::fwprintf(stderr, L"failed to SEC_IMAGE-map one of the input PE files\n");
        return 3;
    }

    constexpr std::array<std::uint32_t, 12> named_bits{
        0, 1, 0x7FEFFFFFu, 0x7FF00000u, 0x7FF00001u, 0x7FFFFFFFu,
        0xFFF00000u, 0xFFF80000u, 0x3F800000u, 0xBF800000u, 0x00800000u, 0xFFFFFFFFu};
    for (std::size_t i = 0; i < named_bits.size(); ++i) {
        if (!check(original, candidate, static_cast<std::uint32_t>(i), named_bits[i])) return 4;
    }

    constexpr int kRandomCases = 100000;
    std::uint32_t state = 0x1CA1826;
    for (int test = 0; test < kRandomCases; ++test) {
        const auto ignored = next_random(state);
        const auto bits = next_random(state);
        if (!check(original, candidate, ignored, bits)) {
            std::fwprintf(stderr, L"random mismatch at case %d\n", test);
            return 5;
        }
    }
    std::wprintf(L"PASS: %zu named bit patterns and %d deterministic randomized pairs; original vs candidate.\n",
                 named_bits.size(), kRandomCases);
    return 0;
}
