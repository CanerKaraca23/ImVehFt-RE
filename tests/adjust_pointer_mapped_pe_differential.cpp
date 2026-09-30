#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <array>
#include <cstdint>
#include <cstdio>

namespace {

using Function = int(__cdecl*)(int, std::int32_t*);
constexpr std::size_t kFunctionRva = 0x1CF82;
constexpr std::size_t kVbtableIndex = 128;

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
           const std::array<std::int32_t, 256>& object,
           std::array<std::int32_t, 3>& pmd, const wchar_t* label)
{
    const auto base = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(object.data()));
    std::uint32_t expected = base + static_cast<std::uint32_t>(pmd[0]);
    if (pmd[1] >= 0) {
        const auto vbtable_bits = static_cast<std::uint32_t>(object[static_cast<std::size_t>(pmd[1]) / 4]);
        const auto* vbtable = reinterpret_cast<const std::int32_t*>(static_cast<std::uintptr_t>(vbtable_bits));
        const auto virtual_adjustment = static_cast<std::uint32_t>(vbtable[pmd[2] / 4]);
        expected += virtual_adjustment + static_cast<std::uint32_t>(pmd[1]);
    }
    const int old_result = original.function()(static_cast<int>(base), pmd.data());
    const int new_result = candidate.function()(static_cast<int>(base), pmd.data());
    if (static_cast<std::uint32_t>(old_result) != expected ||
        static_cast<std::uint32_t>(new_result) != expected) {
        std::fwprintf(stderr, L"%ls: pmd={%d,%d,%d} expected=0x%08X old=0x%08X new=0x%08X\n",
                      label, pmd[0], pmd[1], pmd[2], expected,
                      static_cast<std::uint32_t>(old_result), static_cast<std::uint32_t>(new_result));
        return false;
    }
    return true;
}

void install_vbtable(std::array<std::int32_t, 256>& object,
                     std::int32_t pdisp, std::int32_t vdisp,
                     std::int32_t virtual_adjustment)
{
    const auto vbtable_address = reinterpret_cast<std::uintptr_t>(object.data() + kVbtableIndex);
    object[static_cast<std::size_t>(pdisp) / 4] = static_cast<std::int32_t>(vbtable_address);
    object[kVbtableIndex + static_cast<std::size_t>(vdisp) / 4] = virtual_adjustment;
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

    constexpr std::array<std::array<std::int32_t, 3>, 8> named_pmds{{
        {{0, -1, 0}}, {{16, -4, 8}}, {{-16, -32, 12}}, {{0, 0, 0}},
        {{8, 4, 4}}, {{-64, 16, 12}}, {{127, 28, 20}}, {{-128, 8, 32}}}};
    int named = 0;
    for (auto pmd : named_pmds) {
        std::array<std::int32_t, 256> object{};
        if (pmd[1] >= 0) install_vbtable(object, pmd[1], pmd[2], static_cast<std::int32_t>(named * 13) - 40);
        if (!check(original, candidate, object, pmd, L"named")) return 4;
        ++named;
    }

    constexpr int kRandomCases = 100000;
    std::uint32_t state = 0x1CF8226;
    for (int test = 0; test < kRandomCases; ++test) {
        std::array<std::int32_t, 256> object{};
        std::array<std::int32_t, 3> pmd{};
        pmd[0] = static_cast<std::int32_t>(next_random(state));
        if ((next_random(state) & 3u) == 0) {
            pmd[1] = -static_cast<std::int32_t>(1 + next_random(state) % 0x1000);
            pmd[2] = 0;
        } else {
            pmd[1] = static_cast<std::int32_t>((next_random(state) % 8) * 4);
            pmd[2] = static_cast<std::int32_t>((next_random(state) % 16) * 4);
            const auto adjustment = static_cast<std::int32_t>(next_random(state));
            install_vbtable(object, pmd[1], pmd[2], adjustment);
        }
        if (!check(original, candidate, object, pmd, L"random")) {
            std::fwprintf(stderr, L"random mismatch at case %d\n", test);
            return 5;
        }
    }
    std::wprintf(L"PASS: %d named non-virtual/virtual PMD layouts and %d deterministic randomized cases; original vs candidate.\n",
                 named, kRandomCases);
    return 0;
}
