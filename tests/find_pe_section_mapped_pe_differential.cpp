#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <initializer_list>

namespace {

using Function = PIMAGE_SECTION_HEADER(__cdecl*)(PBYTE, DWORD_PTR);
constexpr std::size_t kFunctionRva = 0x180D0;
constexpr std::size_t kImageSize = 4096;
constexpr std::uint16_t kDosSignature = 0x5A4D;
constexpr std::uint32_t kPeSignature = 0x00004550;

struct SectionSpec {
    std::uint32_t virtual_size;
    std::uint32_t virtual_address;
};

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

std::size_t make_image(std::array<std::uint8_t, kImageSize>& image,
                       std::size_t nt_offset, std::uint16_t optional_size,
                       const SectionSpec* specs, std::size_t section_count)
{
    image.fill(0);
    std::memcpy(image.data(), &kDosSignature, sizeof(kDosSignature));
    std::memcpy(image.data() + 0x3C, &nt_offset, sizeof(std::uint32_t));
    std::memcpy(image.data() + nt_offset, &kPeSignature, sizeof(kPeSignature));
    const auto count = static_cast<std::uint16_t>(section_count);
    std::memcpy(image.data() + nt_offset + 6, &count, sizeof(count));
    std::memcpy(image.data() + nt_offset + 20, &optional_size, sizeof(optional_size));
    const std::size_t section_table = nt_offset + 24u + optional_size;
    for (std::size_t index = 0; index < section_count; ++index) {
        const auto offset = section_table + index * sizeof(IMAGE_SECTION_HEADER);
        std::memcpy(image.data() + offset + 8, &specs[index].virtual_size, sizeof(std::uint32_t));
        std::memcpy(image.data() + offset + 12, &specs[index].virtual_address, sizeof(std::uint32_t));
    }
    return section_table;
}

bool check(const MappedImage& original, const MappedImage& candidate,
           std::array<std::uint8_t, kImageSize>& image,
           std::size_t section_table, std::size_t section_count,
           std::uint32_t rva, const wchar_t* label)
{
    std::size_t expected_offset = SIZE_MAX;
    for (std::size_t index = 0; index < section_count; ++index) {
        std::uint32_t virtual_size = 0;
        std::uint32_t virtual_address = 0;
        const auto offset = section_table + index * sizeof(IMAGE_SECTION_HEADER);
        std::memcpy(&virtual_size, image.data() + offset + 8, sizeof(virtual_size));
        std::memcpy(&virtual_address, image.data() + offset + 12, sizeof(virtual_address));
        if (virtual_address <= rva && rva < virtual_address + virtual_size) {
            expected_offset = offset;
            break;
        }
    }
    const auto* old_result = original.function()(image.data(), rva);
    const auto* new_result = candidate.function()(image.data(), rva);
    const auto old_offset = old_result == nullptr ? SIZE_MAX :
        static_cast<std::size_t>(reinterpret_cast<const std::uint8_t*>(old_result) - image.data());
    const auto new_offset = new_result == nullptr ? SIZE_MAX :
        static_cast<std::size_t>(reinterpret_cast<const std::uint8_t*>(new_result) - image.data());
    if (old_offset != expected_offset || new_offset != expected_offset) {
        std::fwprintf(stderr, L"%ls: rva=0x%08X expected=%zu original=%zu candidate=%zu\n",
                      label, rva, expected_offset, old_offset, new_offset);
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

    constexpr std::array<SectionSpec, 4> named_sections{{
        {0x100, 0x1000}, {0x80, 0x2000}, {0x20, 0x2080}, {0x1000, 0x5000}}};
    constexpr std::array<std::uint32_t, 14> named_rvas{
        0, 0x0FFF, 0x1000, 0x1001, 0x10FF, 0x1100, 0x2000, 0x207F,
        0x2080, 0x209F, 0x20A0, 0x5000, 0x5FFF, 0x6000};
    int named = 0;
    for (const auto nt_offset : {0x40u, 0x100u, 0x300u}) {
        for (const auto optional_size : {0x80u, 0xE0u, 0xF0u}) {
            std::array<std::uint8_t, kImageSize> image{};
            const auto table = make_image(image, nt_offset, static_cast<std::uint16_t>(optional_size),
                                          named_sections.data(), named_sections.size());
            for (const auto rva : named_rvas) {
                if (!check(original, candidate, image, table, named_sections.size(), rva, L"named")) return 4;
                ++named;
            }
        }
    }

    constexpr int kRandomCases = 100000;
    std::uint32_t state = 0x180D026;
    constexpr std::array<std::uint16_t, 4> optional_sizes{0x80, 0xE0, 0xF0, 0x120};
    for (int test = 0; test < kRandomCases; ++test) {
        std::array<std::uint8_t, kImageSize> image{};
        const auto nt_offset = static_cast<std::size_t>(0x40 + 4 * (next_random(state) % 64));
        const auto optional_size = optional_sizes[next_random(state) % optional_sizes.size()];
        const std::size_t count = next_random(state) % 9;
        std::array<SectionSpec, 8> sections{};
        for (std::size_t index = 0; index < count; ++index) {
            sections[index].virtual_address = next_random(state) % 0x10000;
            sections[index].virtual_size = next_random(state) % 0x4000;
        }
        const auto table = make_image(image, nt_offset, optional_size, sections.data(), count);
        const auto rva = next_random(state) % 0x14000;
        if (!check(original, candidate, image, table, count, rva, L"random")) {
            std::fwprintf(stderr, L"random mismatch at case %d\n", test);
            return 5;
        }
    }
    std::wprintf(L"PASS: %d named and %d deterministic randomized synthetic-PE section lookups; original vs candidate.\n",
                 named, kRandomCases);
    return 0;
}
