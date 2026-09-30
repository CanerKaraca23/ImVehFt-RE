#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <array>
#include <cstdint>
#include <cstdio>

namespace {

using Function = void(__cdecl*)(void*, void*, std::uint32_t);
using Callback = void(__fastcall*)(std::uintptr_t);
constexpr std::size_t kFunctionRva = 0x99E0;

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

volatile std::uintptr_t g_received = 0;
volatile std::uint32_t g_calls = 0;

void __fastcall capture_receiver(std::uintptr_t receiver)
{
    g_received = receiver;
    ++g_calls;
}

std::uint32_t next_random(std::uint32_t& state)
{
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

bool check(const MappedImage& image, std::uintptr_t receiver, std::uint32_t ignored)
{
    const Callback callback = &capture_receiver;
    std::array<std::uintptr_t, 1> holder{receiver};
    g_received = 0;
    g_calls = 0;
    image.function()(reinterpret_cast<void*>(callback), holder.data(), ignored);
    return g_received == receiver && g_calls == 1;
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
    constexpr std::array<std::uintptr_t, 8> named_receivers{
        0, 1, 0xFFFFFFFFu, 0x80000000u, 0x100099E0u, 0x7FFFFFFFu, 0x12345678u, 0xA5A5A5A5u};
    constexpr std::array<std::uint32_t, 8> named_ignored{
        0, 1, 0xFFFFFFFFu, 0x80000000u, 0x100099E0u, 0x7FFFFFFFu, 0x12345678u, 0xA5A5A5A5u};
    for (std::size_t i = 0; i < named_receivers.size(); ++i) {
        if (!check(original, named_receivers[i], named_ignored[i]) ||
            !check(candidate, named_receivers[i], named_ignored[i])) {
            std::fwprintf(stderr, L"named callback/ECX contract failed at case %zu\n", i);
            return 4;
        }
    }

    constexpr int kRandomCases = 100000;
    std::uint32_t state = 0x99E02026;
    for (int test = 0; test < kRandomCases; ++test) {
        const auto receiver = static_cast<std::uintptr_t>(next_random(state));
        const auto ignored = next_random(state);
        if (!check(original, receiver, ignored) || !check(candidate, receiver, ignored)) {
            std::fwprintf(stderr, L"random callback/ECX contract failed at case %d\n", test);
            return 5;
        }
    }
    std::wprintf(L"PASS: 8 named and %d deterministic randomized calls; original and candidate each passed receiver in ECX exactly once.\n",
                 kRandomCases);
    return 0;
}
