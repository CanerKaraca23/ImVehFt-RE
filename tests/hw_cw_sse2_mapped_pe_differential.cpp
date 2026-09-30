#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cstdint>
#include <cstdio>
#include <cwchar>

namespace {

using Function = std::uint32_t(__fastcall*)(std::uint32_t, std::uint32_t);
constexpr std::size_t kFunctionRva = 0x1FB89;
constexpr std::uint32_t kFlagBits[6]{1u << 0, 1u << 1, 1u << 2, 1u << 3, 1u << 4, 1u << 19};

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

std::uint32_t expected_result(std::uint32_t flags)
{
    std::uint32_t result = 0;
    if ((flags & (1u << 4)) != 0) result |= 0x80u;
    if ((flags & (1u << 3)) != 0) result |= 0x200u;
    if ((flags & (1u << 2)) != 0) result |= 0x400u;
    if ((flags & (1u << 1)) != 0) result |= 0x800u;
    if ((flags & (1u << 0)) != 0) result |= 0x1000u;
    if ((flags & (1u << 19)) != 0) result |= 0x100u;
    switch ((flags >> 8) & 3u) {
    case 1: result |= 0x2000u; break;
    case 2: result |= 0x4000u; break;
    case 3: result |= 0x6000u; break;
    default: break;
    }
    switch ((flags >> 24) & 3u) {
    case 1: result |= 0x8040u; break;
    case 2: result |= 0x0040u; break;
    case 3: result |= 0x8000u; break;
    default: break;
    }
    return result;
}

std::uint32_t next_random(std::uint32_t& state)
{
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

bool check(const MappedImage& original, const MappedImage& candidate,
           std::uint32_t ignored, std::uint32_t flags, const wchar_t* label)
{
    const auto expected = expected_result(flags);
    const auto old_result = original.function()(ignored, flags);
    const auto new_result = candidate.function()(ignored, flags);
    if (old_result != expected || new_result != expected) {
        std::fwprintf(stderr, L"%ls: ecx=0x%08X edx=0x%08X old=0x%08X new=0x%08X expected=0x%08X\n",
                      label, ignored, flags, old_result, new_result, expected);
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

    std::uint32_t combinations = 0;
    for (std::uint32_t bitset = 0; bitset < 64; ++bitset) {
        for (std::uint32_t mode1 = 0; mode1 < 4; ++mode1) {
            for (std::uint32_t mode2 = 0; mode2 < 4; ++mode2) {
                std::uint32_t flags = (mode1 << 8) | (mode2 << 24);
                for (std::uint32_t bit = 0; bit < 6; ++bit) {
                    if ((bitset & (1u << bit)) != 0) flags |= kFlagBits[bit];
                }
                const auto ignored = 0xA5A50000u ^ combinations;
                if (!check(original, candidate, ignored, flags, L"field-combination")) return 4;
                ++combinations;
            }
        }
    }

    constexpr int kRandomCases = 100000;
    std::uint32_t state = 0x1FB8926;
    for (int test = 0; test < kRandomCases; ++test) {
        const auto ignored = next_random(state);
        const auto flags = next_random(state);
        if (!check(original, candidate, ignored, flags, L"random")) {
            std::fwprintf(stderr, L"random mismatch at case %d\n", test);
            return 5;
        }
    }
    std::wprintf(L"PASS: all %u combinations of documented control fields and %d deterministic randomized ECX/EDX pairs; original vs candidate.\n",
                 combinations, kRandomCases);
    return 0;
}
