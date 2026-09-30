#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <array>
#include <cstdint>
#include <cstdio>

namespace {

using Function = std::size_t(__cdecl*)(const wchar_t*);
constexpr std::size_t kFunctionRva = 0x1AD68;
constexpr std::size_t kBufferSize = 2048;
static_assert(sizeof(wchar_t) == 2, "GTA's 32-bit Windows CRT uses 16-bit wchar_t");

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
             const wchar_t* text, std::size_t expected)
{
    const auto old_length = original.function()(text);
    const auto new_length = candidate.function()(text);
    if (old_length != expected || new_length != expected) {
        std::fwprintf(stderr, L"wcslen mismatch: original=%zu candidate=%zu expected=%zu\n",
                      old_length, new_length, expected);
        return false;
    }
    return true;
}

wchar_t* aligned_start(std::array<wchar_t, kBufferSize>& storage, std::size_t alignment)
{
    const auto address = reinterpret_cast<std::uintptr_t>(storage.data());
    const std::size_t padding_bytes = (alignment - (address & 3u)) & 3u;
    return storage.data() + padding_bytes / sizeof(wchar_t);
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

    constexpr std::array<std::size_t, 16> named_lengths{
        0, 1, 2, 3, 4, 7, 8, 15, 16, 31, 32, 63, 64, 255, 256, 1023};
    int named = 0;
    for (const std::size_t alignment : {0u, 2u}) {
        for (const auto length : named_lengths) {
            std::array<wchar_t, kBufferSize> storage{};
            auto* text = aligned_start(storage, alignment);
            for (std::size_t i = 0; i < length; ++i) text[i] = static_cast<wchar_t>(L'A' + i % 26);
            text[length] = L'\0';
            if (!compare(original, candidate, text, length)) return 4;
            ++named;
        }
    }

    constexpr int kRandomCases = 100000;
    std::uint32_t state = 0x1AD6826;
    for (int test = 0; test < kRandomCases; ++test) {
        std::array<wchar_t, kBufferSize> storage{};
        const std::size_t alignment = (next_random(state) & 1u) ? 2u : 0u;
        auto* text = aligned_start(storage, alignment);
        const std::size_t available = kBufferSize - static_cast<std::size_t>(text - storage.data()) - 1;
        const std::size_t length = next_random(state) % (available + 1);
        for (std::size_t i = 0; i < length; ++i) {
            text[i] = static_cast<wchar_t>(1 + next_random(state) % 0xFFFFu);
        }
        text[length] = L'\0';
        if (!compare(original, candidate, text, length)) {
            std::fwprintf(stderr, L"random mismatch at case %d, alignment=%zu, length=%zu\n",
                          test, alignment, length);
            return 5;
        }
    }

    SYSTEM_INFO system_info{};
    GetSystemInfo(&system_info);
    const std::size_t page_size = system_info.dwPageSize;
    auto* pages = static_cast<std::uint8_t*>(VirtualAlloc(nullptr, page_size * 2,
                                                           MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
    if (pages == nullptr) return 6;
    DWORD old_protect = 0;
    if (!VirtualProtect(pages + page_size, page_size, PAGE_NOACCESS, &old_protect)) {
        VirtualFree(pages, 0, MEM_RELEASE);
        return 7;
    }
    int guard_cases = 0;
    for (const std::size_t alignment : {0u, 2u}) {
        for (std::size_t length = 0; length < 64; ++length) {
            auto* terminator = reinterpret_cast<wchar_t*>(pages + page_size - sizeof(wchar_t));
            auto* text = terminator - length;
            while ((reinterpret_cast<std::uintptr_t>(text) & 3u) != alignment) --text;
            for (auto* current = text; current < terminator; ++current) *current = L'B';
            *terminator = L'\0';
            if (!compare(original, candidate, text,
                         static_cast<std::size_t>(terminator - text))) {
                VirtualFree(pages, 0, MEM_RELEASE);
                return 8;
            }
            ++guard_cases;
        }
    }
    VirtualFree(pages, 0, MEM_RELEASE);
    std::wprintf(L"PASS: %d named, %d deterministic randomized, and %d guard-page-boundary wide strings; original vs candidate.\n",
                 named, kRandomCases, guard_cases);
    return 0;
}
