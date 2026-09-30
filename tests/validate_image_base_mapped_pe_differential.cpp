#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

namespace {

using ValidateImageBase = int(__cdecl*)(std::uint8_t*);
constexpr std::size_t kFunctionRva = 0x18090;
constexpr std::size_t kBufferSize = 512;
constexpr std::uint32_t kPeSignature = 0x00004550;
constexpr std::uint16_t kDosSignature = 0x5A4D;
constexpr std::uint16_t kPe32Magic = 0x010B;

struct MappedImage {
    HANDLE file = INVALID_HANDLE_VALUE;
    HANDLE mapping = nullptr;
    std::uint8_t* base = nullptr;

    explicit MappedImage(const wchar_t* path)
    {
        file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE,
                           nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file == INVALID_HANDLE_VALUE) {
            std::fwprintf(stderr, L"CreateFileW failed (%lu): %ls\n", GetLastError(), path);
            return;
        }
        mapping = CreateFileMappingW(file, nullptr, PAGE_READONLY | SEC_IMAGE, 0, 0, nullptr);
        if (mapping == nullptr) {
            std::fwprintf(stderr, L"CreateFileMappingW(SEC_IMAGE) failed (%lu): %ls\n",
                          GetLastError(), path);
            return;
        }
        base = static_cast<std::uint8_t*>(MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, 0));
        if (base == nullptr) {
            std::fwprintf(stderr, L"MapViewOfFile failed (%lu): %ls\n", GetLastError(), path);
        }
    }

    MappedImage(const MappedImage&) = delete;
    MappedImage& operator=(const MappedImage&) = delete;

    ~MappedImage()
    {
        if (base != nullptr) UnmapViewOfFile(base);
        if (mapping != nullptr) CloseHandle(mapping);
        if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
    }

    ValidateImageBase function() const
    {
        return reinterpret_cast<ValidateImageBase>(base + kFunctionRva);
    }
};

template <typename T>
void store(std::array<std::uint8_t, kBufferSize>& bytes, std::size_t offset, T value)
{
    std::memcpy(bytes.data() + offset, &value, sizeof(value));
}

std::array<std::uint8_t, kBufferSize> make_image(std::uint32_t nt_offset,
                                                 std::uint16_t dos,
                                                 std::uint32_t signature,
                                                 std::uint16_t magic)
{
    std::array<std::uint8_t, kBufferSize> bytes{};
    store(bytes, 0, dos);
    store(bytes, 0x3C, nt_offset);
    store(bytes, nt_offset, signature);
    store(bytes, nt_offset + 0x18, magic);
    return bytes;
}

std::uint32_t next_random(std::uint32_t& state)
{
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
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
    if (original.base == nullptr || candidate.base == nullptr) return 3;

    const auto original_function = original.function();
    const auto candidate_function = candidate.function();
    const auto check = [&](const wchar_t* label, const std::array<std::uint8_t, kBufferSize>& bytes,
                           int expected) {
        auto mutable_bytes = bytes;
        const int old_result = original_function(mutable_bytes.data());
        mutable_bytes = bytes;
        const int new_result = candidate_function(mutable_bytes.data());
        if (old_result != expected || new_result != expected) {
            std::fwprintf(stderr, L"%ls: original=%d candidate=%d expected=%d\n",
                          label, old_result, new_result, expected);
            return false;
        }
        return true;
    };

    int named_cases = 0;
    const auto run_named = [&](const wchar_t* label,
                               const std::array<std::uint8_t, kBufferSize>& bytes, int expected) {
        if (!check(label, bytes, expected)) return false;
        ++named_cases;
        return true;
    };
    if (!run_named(L"valid PE32 at 0x40", make_image(0x40, kDosSignature, kPeSignature, kPe32Magic), 1) ||
        !run_named(L"invalid DOS signature", make_image(0x40, 0, kPeSignature, kPe32Magic), 0) ||
        !run_named(L"invalid PE signature", make_image(0x40, kDosSignature, 0, kPe32Magic), 0) ||
        !run_named(L"PE32+ magic rejected", make_image(0x40, kDosSignature, kPeSignature, 0x020B), 0) ||
        !run_named(L"valid PE32 at alternate safe offset", make_image(0x1E0, kDosSignature, kPeSignature, kPe32Magic), 1)) {
        return 4;
    }

    constexpr int kRandomCases = 100000;
    std::uint32_t state = 0xA17E2026;
    for (int test = 0; test < kRandomCases; ++test) {
        std::array<std::uint8_t, kBufferSize> bytes{};
        for (auto& byte : bytes) byte = static_cast<std::uint8_t>(next_random(state));
        const auto nt_offset = static_cast<std::uint32_t>(0x40 + next_random(state) % 0x180);
        store(bytes, 0x3C, nt_offset);
        switch (test % 4) {
        case 0: store(bytes, 0, kDosSignature); break;
        case 1: store(bytes, nt_offset, kPeSignature); break;
        case 2: store(bytes, nt_offset + 0x18, kPe32Magic); break;
        default:
            store(bytes, 0, kDosSignature);
            store(bytes, nt_offset, kPeSignature);
            store(bytes, nt_offset + 0x18, kPe32Magic);
            break;
        }
        auto original_bytes = bytes;
        const int old_result = original_function(original_bytes.data());
        auto candidate_bytes = bytes;
        const int new_result = candidate_function(candidate_bytes.data());
        if (old_result != new_result) {
            std::fwprintf(stderr, L"random case %d mismatch: original=%d candidate=%d\n",
                          test, old_result, new_result);
            return 5;
        }
    }

    std::wprintf(L"PASS: %d named cases and %d deterministic bounded random cases; original ASI vs in-place candidate PE mapping.\n",
                 named_cases, kRandomCases);
    return 0;
}
