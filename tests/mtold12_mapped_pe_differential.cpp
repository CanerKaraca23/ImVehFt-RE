#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cwchar>
#include <cstring>

namespace {

using Function = void(__cdecl*)(char*, int, std::uint32_t*);
constexpr std::size_t kFunctionRva = 0x20564;
constexpr std::size_t kMaxDigits = 25;
constexpr std::size_t kOutputSize = 12;

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
             const std::array<std::uint8_t, kMaxDigits>& digits, int length,
             const wchar_t* label)
{
    std::array<char, kMaxDigits> old_input{};
    std::array<char, kMaxDigits> new_input{};
    for (int index = 0; index < length; ++index) {
        old_input[static_cast<std::size_t>(index)] = static_cast<char>(digits[static_cast<std::size_t>(index)]);
        new_input[static_cast<std::size_t>(index)] = static_cast<char>(digits[static_cast<std::size_t>(index)]);
    }
    std::array<std::uint32_t, 3> old_output{0xCCCCCCCCu, 0xCCCCCCCCu, 0xCCCCCCCCu};
    std::array<std::uint32_t, 3> new_output{0xCCCCCCCCu, 0xCCCCCCCCu, 0xCCCCCCCCu};
    original.function()(old_input.data(), length, old_output.data());
    candidate.function()(new_input.data(), length, new_output.data());
    if (std::memcmp(old_output.data(), new_output.data(), kOutputSize) != 0 ||
        old_input != new_input) {
        std::fwprintf(stderr, L"%ls mismatch: length=%d original={%08X,%08X,%08X} candidate={%08X,%08X,%08X}\n",
                      label, length, old_output[0], old_output[1], old_output[2],
                      new_output[0], new_output[1], new_output[2]);
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

    constexpr std::array<std::array<std::uint8_t, 6>, 8> named_digits{{
        {{1, 0, 0, 0, 0, 0}}, {{9, 0, 0, 0, 0, 0}}, {{1, 0, 0, 0, 0, 2}},
        {{1, 2, 3, 4, 5, 6}}, {{9, 9, 9, 9, 9, 9}}, {{1, 0, 0, 0, 0, 9}},
        {{4, 0, 2, 0, 8, 1}}, {{7, 0, 0, 0, 0, 3}}}};
    constexpr std::array<int, 8> named_lengths{1, 1, 2, 6, 6, 6, 6, 6};
    for (std::size_t index = 0; index < named_digits.size(); ++index) {
        std::array<std::uint8_t, kMaxDigits> digits{};
        std::memcpy(digits.data(), named_digits[index].data(), named_lengths[index]);
        if (!compare(original, candidate, digits, named_lengths[index], L"named")) return 4;
    }

    constexpr int kRandomCases = 100000;
    std::uint32_t state = 0x20564026;
    for (int test = 0; test < kRandomCases; ++test) {
        std::array<std::uint8_t, kMaxDigits> digits{};
        const int length = 1 + static_cast<int>(next_random(state) % kMaxDigits);
        digits[0] = static_cast<std::uint8_t>(1 + next_random(state) % 9);
        for (int index = 1; index + 1 < length; ++index) {
            digits[static_cast<std::size_t>(index)] = static_cast<std::uint8_t>(next_random(state) % 10);
        }
        if (length > 1) digits[static_cast<std::size_t>(length - 1)] =
            static_cast<std::uint8_t>(1 + next_random(state) % 9);
        if (!compare(original, candidate, digits, length, L"random normalized digit sequence")) {
            std::fwprintf(stderr, L"random mismatch at case %d\n", test);
            return 5;
        }
    }
    std::wprintf(L"PASS: %zu named and %d deterministic randomized normalized digit sequences (1-25 digits); original vs candidate output bytes.\n",
                 named_digits.size(), kRandomCases);
    return 0;
}
