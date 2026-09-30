#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cstdint>
#include <cstdio>
#include <cwchar>
#include <cstring>

namespace {

using Function = int(__stdcall*)();
constexpr std::size_t kFunctionRva = 0x2044E;
const float kDenormal = [] {
    std::uint32_t bits = 1;
    float value = 0;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}();
const double kOne = 1.0;
const double kZero = 0.0;
const double kPi = 3.14159265358979323846;

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

void prepare_state(unsigned selector)
{
    __asm { fninit }
    switch (selector % 10u) {
    case 0: break;
    case 1:
        __asm { fld qword ptr [kOne] }
        __asm { ftst }
        break;
    case 2:
        __asm { fld qword ptr [kZero] }
        __asm { ftst }
        break;
    case 3:
        __asm { fld qword ptr [kOne] }
        __asm { fchs }
        __asm { ftst }
        break;
    case 4:
        __asm { fld qword ptr [kZero] }
        __asm { fld qword ptr [kZero] }
        __asm { fdivp st(1), st(0) }
        break;
    case 5:
        __asm { fld qword ptr [kOne] }
        __asm { fld qword ptr [kZero] }
        __asm { fdivp st(1), st(0) }
        break;
    case 6: __asm { fld dword ptr [kDenormal] } break;
    case 7:
        __asm { fld qword ptr [kOne] }
        __asm { fld qword ptr [kPi] }
        __asm { fyl2x }
        break;
    case 8:
        __asm { fld qword ptr [kOne] }
        __asm { fld qword ptr [kOne] }
        __asm { faddp st(1), st(0) }
        __asm { ftst }
        break;
    default:
        __asm {
            fld qword ptr [kOne]
            fld qword ptr [kOne]
            fld qword ptr [kOne]
            fld qword ptr [kOne]
            fld qword ptr [kOne]
            fld qword ptr [kOne]
            fld qword ptr [kOne]
            fld qword ptr [kOne]
            fld qword ptr [kOne]
        }
        break;
    }
}

std::uint16_t read_status()
{
    std::uint16_t status = 0;
    __asm {
        fnstsw ax
        mov status, ax
    }
    return status;
}

bool check(const MappedImage& original, const MappedImage& candidate,
           unsigned selector, const wchar_t* label)
{
    prepare_state(selector);
    const int expected = static_cast<std::int16_t>(read_status());
    const int old_result = original.function()();
    const int new_result = candidate.function()();
    if (old_result != expected || new_result != expected) {
        std::fwprintf(stderr, L"%ls selector=%u expected=0x%04X old=0x%04X new=0x%04X\n",
                      label, selector, static_cast<unsigned short>(expected),
                      static_cast<unsigned short>(old_result), static_cast<unsigned short>(new_result));
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
    for (unsigned selector = 0; selector < 10; ++selector) {
        if (!check(original, candidate, selector, L"named x87 state")) return 4;
    }
    constexpr int kRandomCases = 100000;
    std::uint32_t state = 0x2044E026;
    for (int test = 0; test < kRandomCases; ++test) {
        if (!check(original, candidate, next_random(state), L"randomized x87 state")) {
            std::fwprintf(stderr, L"random mismatch at case %d\n", test);
            return 5;
        }
    }
    std::wprintf(L"PASS: 10 named x87 states and %d deterministic randomized x87-state selections; original vs candidate.\n",
                 kRandomCases);
    return 0;
}
