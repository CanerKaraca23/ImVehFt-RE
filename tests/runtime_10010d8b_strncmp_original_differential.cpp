#include <Windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

#pragma comment(linker, "/alternatename:?Candidate_strncmp@@YAHPAD0I@Z=?strncmp@@YAHPAD0I@Z")

int __cdecl Candidate_strncmp(char*, char*, unsigned int);

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kOriginalEntry = 0x10010d8b;

struct Observation
{
    std::int32_t esp_after_call;
    std::int32_t esp_after_caller_cleanup;
    std::int32_t result;
};

volatile std::uint32_t g_esp_before = 0;

extern "C" __declspec(naked) void __cdecl InvokeRaw(
    std::uint32_t, char*, char*, std::uint32_t, Observation*)
{
    __asm {
        push ebp
        mov ebp, esp
        mov dword ptr [g_esp_before], esp
        push dword ptr [ebp + 14h]
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0Ch]
        mov eax, dword ptr [ebp + 8]
        call eax
        mov edx, esp
        sub edx, dword ptr [g_esp_before]
        mov ecx, dword ptr [ebp + 18h]
        mov dword ptr [ecx], edx
        mov dword ptr [ecx + 8], eax
        add esp, 0Ch
        mov edx, esp
        sub edx, dword ptr [g_esp_before]
        mov dword ptr [ecx + 4], edx
        pop ebp
        ret
    }
}

std::uint8_t* MapReference(char const* path)
{
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
        return nullptr;
    DWORD const size = GetFileSize(file, nullptr);
    if (size == INVALID_FILE_SIZE || size < sizeof(IMAGE_DOS_HEADER))
    {
        CloseHandle(file);
        return nullptr;
    }
    std::vector<std::uint8_t> bytes(size);
    DWORD read = 0;
    BOOL const ok = ReadFile(file, bytes.data(), size, &read, nullptr);
    CloseHandle(file);
    if (!ok || read != size)
        return nullptr;

    auto const* dos = reinterpret_cast<IMAGE_DOS_HEADER const*>(bytes.data());
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0 ||
        static_cast<std::size_t>(dos->e_lfanew) + sizeof(IMAGE_NT_HEADERS32) > bytes.size())
        return nullptr;
    auto const* nt = reinterpret_cast<IMAGE_NT_HEADERS32 const*>(
        bytes.data() + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.ImageBase != kImageBase)
        return nullptr;

    auto* image = static_cast<std::uint8_t*>(VirtualAlloc(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(kImageBase)),
        nt->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE));
    if (image != reinterpret_cast<std::uint8_t*>(
                     static_cast<std::uintptr_t>(kImageBase)))
        return nullptr;
    std::memset(image, 0, nt->OptionalHeader.SizeOfImage);
    std::memcpy(image, bytes.data(), nt->OptionalHeader.SizeOfHeaders);

    auto const* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
    {
        if (!section->SizeOfRawData)
            continue;
        if (section->PointerToRawData > bytes.size() ||
            section->SizeOfRawData > bytes.size() - section->PointerToRawData ||
            section->VirtualAddress > nt->OptionalHeader.SizeOfImage ||
            section->SizeOfRawData >
                nt->OptionalHeader.SizeOfImage - section->VirtualAddress)
        {
            VirtualFree(image, 0, MEM_RELEASE);
            return nullptr;
        }
        std::memcpy(image + section->VirtualAddress,
                    bytes.data() + section->PointerToRawData,
                    section->SizeOfRawData);
    }
    return image;
}

bool Compare(std::uint32_t original_address, std::uint32_t candidate_address,
             char* left, char* right, std::uint32_t count,
             std::uint64_t& comparisons)
{
    Observation original{}, candidate{};
    InvokeRaw(original_address, left, right, count, &original);
    InvokeRaw(candidate_address, left, right, count, &candidate);
    ++comparisons;
    return original.result == candidate.result &&
           original.esp_after_call == candidate.esp_after_call &&
           original.esp_after_caller_cleanup == candidate.esp_after_caller_cleanup &&
           original.esp_after_call == -12 &&
           original.esp_after_caller_cleanup == 0;
}

std::uint32_t NextRandom(std::uint32_t& state)
{
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

bool GuardPageCases(std::uint32_t original_address,
                   std::uint32_t candidate_address,
                   std::uint64_t& comparisons)
{
    SYSTEM_INFO system_info{};
    GetSystemInfo(&system_info);
    std::size_t const page_size = system_info.dwPageSize;
    auto* memory = static_cast<char*>(VirtualAlloc(
        nullptr, page_size * 4, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
    if (!memory)
        return false;

    DWORD previous = 0;
    bool const guards_ready =
        VirtualProtect(memory + page_size, page_size, PAGE_NOACCESS, &previous) != FALSE &&
        VirtualProtect(memory + page_size * 3, page_size, PAGE_NOACCESS, &previous) != FALSE;
    if (!guards_ready)
    {
        VirtualFree(memory, 0, MEM_RELEASE);
        return false;
    }

    for (std::uint32_t count = 0; count <= 32; ++count)
    {
        char* const left = memory + page_size - count;
        char* const right = memory + page_size * 3 - count;
        if (count)
        {
            std::memset(left, 0x41, count);
            std::memset(right, 0x41, count);
        }
        if (!Compare(original_address, candidate_address, left, right, count,
                     comparisons))
        {
            VirtualFree(memory, 0, MEM_RELEASE);
            return false;
        }

        if (count)
        {
            left[count - 1] = '\0';
            right[count - 1] = 'B';
            if (!Compare(original_address, candidate_address, left, right,
                         count + 8, comparisons))
            {
                VirtualFree(memory, 0, MEM_RELEASE);
                return false;
            }
        }
    }

    VirtualFree(memory, 0, MEM_RELEASE);
    return true;
}
} // namespace

int main(int argc, char** argv)
{
    static_assert(sizeof(void*) == 4, "Run this harness as PE32/x86.");
    if (argc != 2)
    {
        std::fprintf(stderr, "usage: harness <ImVehFt.asi>\n");
        return 2;
    }

    auto* const reference = MapReference(argv[1]);
    if (!reference)
    {
        std::fprintf(stderr, "Could not map original ImVehFt PE at its preferred base.\n");
        return 3;
    }

    std::uint64_t comparisons = 0;
    auto const candidate_address = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&Candidate_strncmp));
    std::vector<std::array<char, 16>> strings;
    strings.push_back({});
    constexpr std::uint8_t alphabet[] = {0x01, 0x7f, 0x80, 0xff};
    for (unsigned length = 1; length <= 4; ++length)
    {
        std::uint32_t const total = 1u << (length * 2u);
        for (std::uint32_t value = 0; value < total; ++value)
        {
            std::array<char, 16> item{};
            std::uint32_t digits = value;
            for (unsigned index = 0; index < length; ++index)
            {
                item[index] = static_cast<char>(alphabet[digits & 3u]);
                digits >>= 2;
            }
            strings.push_back(item);
        }
    }

    for (auto const& left_storage : strings)
    {
        for (auto const& right_storage : strings)
        {
            for (std::uint32_t count = 0; count <= 8; ++count)
            {
                if (!Compare(kOriginalEntry, candidate_address,
                             const_cast<char*>(left_storage.data()),
                             const_cast<char*>(right_storage.data()), count,
                             comparisons))
                {
                    std::fprintf(stderr,
                                 "Exhaustive mismatch after %llu comparisons (n=%u).\n",
                                 static_cast<unsigned long long>(comparisons), count);
                    VirtualFree(reference, 0, MEM_RELEASE);
                    return 4;
                }
            }
        }
    }

    std::uint32_t random = 0x6d2b79f5u;
    std::array<char, 40> left{};
    std::array<char, 40> right{};
    constexpr std::uint32_t kRandomCases = 100000;
    for (std::uint32_t test = 0; test < kRandomCases; ++test)
    {
        for (std::size_t index = 0; index < left.size(); ++index)
        {
            left[index] = static_cast<char>(NextRandom(random) & 0xffu);
            right[index] = static_cast<char>(NextRandom(random) & 0xffu);
        }
        left[NextRandom(random) % left.size()] = '\0';
        right[NextRandom(random) % right.size()] = '\0';
        std::uint32_t const offset_left = NextRandom(random) & 3u;
        std::uint32_t const offset_right = NextRandom(random) & 3u;
        std::uint32_t const count = NextRandom(random) % 36u;
        if (!Compare(kOriginalEntry, candidate_address,
                     left.data() + offset_left, right.data() + offset_right,
                     count, comparisons))
        {
            std::fprintf(stderr,
                         "Random mismatch at case %u (n=%u, offsets=%u/%u).\n",
                         test, count, offset_left, offset_right);
            VirtualFree(reference, 0, MEM_RELEASE);
            return 5;
        }
    }

    if (!GuardPageCases(kOriginalEntry, candidate_address, comparisons))
    {
        std::fprintf(stderr,
                     "Guard-page bound/early-NUL case failed after %llu comparisons.\n",
                     static_cast<unsigned long long>(comparisons));
        VirtualFree(reference, 0, MEM_RELEASE);
        return 6;
    }

    VirtualFree(reference, 0, MEM_RELEASE);
    std::printf("PASS: %llu original/candidate comparisons; exhaustive short binary strings, %u deterministic random cases, and guard-page bounds; result and cdecl stack matched.\n",
                static_cast<unsigned long long>(comparisons), kRandomCases);
    std::puts("LIMIT: only bounded valid buffers were used; no whole-image or GTA runtime behavior was exercised.");
    return 0;
}
