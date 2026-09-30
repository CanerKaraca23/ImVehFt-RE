#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace {

using Function = std::size_t(__cdecl*)(const char*);
constexpr std::size_t kFunctionRva = 0x11650;
constexpr std::size_t kBufferSize = 4096;

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
             const char* text, std::size_t expected, const wchar_t* label)
{
    const auto old_length = original.function()(text);
    const auto new_length = candidate.function()(text);
    if (old_length != expected || new_length != expected) {
        std::fwprintf(stderr, L"%ls: original=%zu candidate=%zu expected=%zu\n",
                      label, old_length, new_length, expected);
        return false;
    }
    return true;
}

char* aligned_start(std::array<char, kBufferSize>& storage, std::size_t alignment)
{
    const auto address = reinterpret_cast<std::uintptr_t>(storage.data());
    const std::size_t padding = (alignment - (address & 3u)) & 3u;
    return storage.data() + padding;
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

    constexpr std::array<std::size_t, 17> named_lengths{
        0, 1, 2, 3, 4, 5, 7, 15, 16, 31, 32, 63, 64, 255, 256, 1023, 4091};
    int named = 0;
    for (std::size_t alignment = 0; alignment < 4; ++alignment) {
        for (const auto length : named_lengths) {
            std::array<char, kBufferSize> storage{};
            auto* text = aligned_start(storage, alignment);
            std::memset(text, 0x7F, kBufferSize - static_cast<std::size_t>(text - storage.data()));
            text[length] = '\0';
            if (!compare(original, candidate, text, length, L"named/alignment")) return 4;
            ++named;
        }
    }

    constexpr int kRandomCases = 100000;
    std::uint32_t state = 0x1165026;
    for (int test = 0; test < kRandomCases; ++test) {
        std::array<char, kBufferSize> storage{};
        const std::size_t alignment = next_random(state) & 3u;
        auto* text = aligned_start(storage, alignment);
        const std::size_t available = kBufferSize - static_cast<std::size_t>(text - storage.data()) - 1;
        const std::size_t length = next_random(state) % (available + 1);
        for (std::size_t i = 0; i < length; ++i) {
            auto byte = static_cast<char>(next_random(state) & 0xFFu);
            if (byte == '\0') byte = '\x7F';
            text[i] = byte;
        }
        text[length] = '\0';
        if (!compare(original, candidate, text, length, L"random")) {
            std::fwprintf(stderr, L"random mismatch at case %d, alignment=%zu, length=%zu\n",
                          test, alignment, length);
            return 5;
        }
    }

    SYSTEM_INFO system_info{};
    GetSystemInfo(&system_info);
    const std::size_t page_size = system_info.dwPageSize;
    auto* pages = static_cast<char*>(VirtualAlloc(nullptr, page_size * 2,
                                                   MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
    if (pages == nullptr) return 6;
    DWORD old_protect = 0;
    if (!VirtualProtect(pages + page_size, page_size, PAGE_NOACCESS, &old_protect)) {
        VirtualFree(pages, 0, MEM_RELEASE);
        return 7;
    }
    int guard_cases = 0;
    for (std::size_t alignment = 0; alignment < 4; ++alignment) {
        for (std::size_t length = 0; length < 64; ++length) {
            char* terminator = pages + page_size - 1;
            char* text = terminator - length;
            while ((reinterpret_cast<std::uintptr_t>(text) & 3u) != alignment) --text;
            std::memset(text, 0x41, static_cast<std::size_t>(terminator - text));
            *terminator = '\0';
            if (!compare(original, candidate, text,
                         static_cast<std::size_t>(terminator - text), L"guard-page")) {
                VirtualFree(pages, 0, MEM_RELEASE);
                return 8;
            }
            ++guard_cases;
        }
    }
    VirtualFree(pages, 0, MEM_RELEASE);
    std::wprintf(L"PASS: %d named, %d deterministic randomized, and %d guard-page-boundary strings; original vs in-place candidate.\n",
                 named, kRandomCases, guard_cases);
    return 0;
}
