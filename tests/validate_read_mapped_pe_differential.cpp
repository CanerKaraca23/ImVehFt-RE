#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <array>
#include <cstdint>
#include <cstdio>

namespace {

using Function = int(__cdecl*)(const void*, std::uint32_t);
constexpr std::size_t kFunctionRva = 0x1E073;

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

bool compare(const MappedImage& original, const MappedImage& candidate,
             const void* pointer, std::uint32_t size, int expected)
{
    const int old_result = original.function()(pointer, size);
    const int new_result = candidate.function()(pointer, size);
    if (old_result != expected || new_result != expected) {
        std::fwprintf(stderr, L"ValidateRead mismatch: pointer=%p size=%u original=%d candidate=%d expected=%d\n",
                      pointer, size, old_result, new_result, expected);
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

    std::array<std::uint8_t, 256> data{};
    constexpr std::array<std::uint32_t, 8> sizes{
        0, 1, 2, 3, 4, 0xFFFFu, 0x10000u, 0xFFFFFFFFu};
    for (const auto size : sizes) {
        if (!compare(original, candidate, nullptr, size, 0)) return 4;
        if (!compare(original, candidate, data.data(), size, 1)) return 5;
        if (!compare(original, candidate, data.data() + data.size(), size, 1)) return 6;
    }

    constexpr int kRandomCases = 100000;
    std::uint32_t state = 0x1E073026;
    for (int test = 0; test < kRandomCases; ++test) {
        const auto size = next_random(state);
        const bool is_null = (next_random(state) & 7u) == 0;
        const auto offset = next_random(state) % static_cast<std::uint32_t>(data.size() + 1);
        const void* pointer = is_null ? nullptr : static_cast<const void*>(data.data() + offset);
        if (!compare(original, candidate, pointer, size, is_null ? 0 : 1)) {
            std::fwprintf(stderr, L"random mismatch at case %d\n", test);
            return 7;
        }
    }
    std::wprintf(L"PASS: 24 named and %d deterministic randomized pointer/size pairs; original vs in-place candidate.\n",
                 kRandomCases);
    return 0;
}
