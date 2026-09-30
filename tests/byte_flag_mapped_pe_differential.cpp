#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace {

using Function = void(__cdecl*)(std::uint8_t*, int);
constexpr std::size_t kFunctionRva = 0x3FE0;
constexpr std::size_t kBufferSize = 16;

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
           const std::array<std::uint8_t, kBufferSize>& initial, int value)
{
    auto old_bytes = initial;
    auto new_bytes = initial;
    original.function()(old_bytes.data(), value);
    candidate.function()(new_bytes.data(), value);
    return old_bytes == new_bytes;
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

    constexpr std::array<int, 8> named_values{0, 1, -1, 2, -2, 0x7fffffff,
                                               static_cast<int>(0x80000000u), 0x100};
    int named = 0;
    for (int value : named_values) {
        std::array<std::uint8_t, kBufferSize> data{};
        for (std::size_t i = 0; i < data.size(); ++i) data[i] = static_cast<std::uint8_t>(i * 17 + 3);
        if (!check(original, candidate, data, value)) {
            std::fwprintf(stderr, L"named differential mismatch at value %d\n", value);
            return 4;
        }
        ++named;
    }

    constexpr int kRandomCases = 100000;
    std::uint32_t state = 0x3FE02026;
    for (int test = 0; test < kRandomCases; ++test) {
        std::array<std::uint8_t, kBufferSize> data{};
        for (auto& byte : data) byte = static_cast<std::uint8_t>(next_random(state));
        const auto raw = next_random(state);
        const int value = static_cast<int>(raw);
        if (!check(original, candidate, data, value)) {
            std::fwprintf(stderr, L"random differential mismatch at case %d, value 0x%08X\n",
                          test, static_cast<unsigned int>(raw));
            return 5;
        }
    }
    std::wprintf(L"PASS: %d named inputs and %d deterministic randomized inputs; mapped original vs patched candidate.\n",
                 named, kRandomCases);
    return 0;
}
