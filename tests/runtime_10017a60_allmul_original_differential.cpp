#include <Windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern "C" long long __stdcall __allmul(
    std::uint32_t, std::int32_t, std::uint32_t, std::int32_t);

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kOriginalEntry = 0x10017a60;
constexpr std::uint32_t kExpectedEbx = 0xb16b00b5;
constexpr std::uint32_t kExpectedEsi = 0x51e51e51;
constexpr std::uint32_t kExpectedEdi = 0xd1ed1eed;

struct Invocation
{
    std::int32_t esp_delta;
    std::uint32_t eax;
    std::uint32_t edx;
    std::uint32_t ebx;
    std::uint32_t esi;
    std::uint32_t edi;
};

volatile std::uint32_t g_esp_before = 0;

extern "C" __declspec(naked) void __cdecl InvokeRaw(
    std::uint32_t, std::uint32_t, std::int32_t, std::uint32_t, std::int32_t,
    Invocation*)
{
    __asm {
        push ebp
        mov ebp, esp
        push edi
        push esi
        push ebx
        mov ebx, 0B16B00B5h
        mov esi, 051E51E51h
        mov edi, 0D1ED1EEDh
        mov dword ptr [g_esp_before], esp
        push dword ptr [ebp + 18h]
        push dword ptr [ebp + 14h]
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0Ch]
        mov eax, dword ptr [ebp + 8]
        call eax
        mov ecx, dword ptr [ebp + 1Ch]
        mov dword ptr [ecx + 4], eax
        mov dword ptr [ecx + 8], edx
        mov eax, esp
        sub eax, dword ptr [g_esp_before]
        mov dword ptr [ecx], eax
        mov dword ptr [ecx + 0Ch], ebx
        mov dword ptr [ecx + 10h], esi
        mov dword ptr [ecx + 14h], edi
        pop ebx
        pop esi
        pop edi
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

std::uint32_t NextRandom(std::uint32_t& state)
{
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

std::array<std::uint32_t, 2> ExpectedProduct(std::uint32_t a_low,
                                             std::uint32_t a_high,
                                             std::uint32_t b_low,
                                             std::uint32_t b_high)
{
    std::uint64_t const low_product =
        static_cast<std::uint64_t>(a_low) * b_low;
    std::uint32_t const high =
        static_cast<std::uint32_t>(low_product >> 32) +
        static_cast<std::uint32_t>(a_low * b_high) +
        static_cast<std::uint32_t>(a_high * b_low);
    return {static_cast<std::uint32_t>(low_product), high};
}

bool CheckOne(std::uint32_t candidate_address, std::uint32_t a_low,
              std::uint32_t a_high, std::uint32_t b_low,
              std::uint32_t b_high, std::uint64_t& count)
{
    Invocation original{}, candidate{};
    InvokeRaw(kOriginalEntry, a_low, static_cast<std::int32_t>(a_high), b_low,
              static_cast<std::int32_t>(b_high), &original);
    InvokeRaw(candidate_address, a_low, static_cast<std::int32_t>(a_high),
              b_low, static_cast<std::int32_t>(b_high), &candidate);
    ++count;

    auto const expected = ExpectedProduct(a_low, a_high, b_low, b_high);
    auto const valid = [&](Invocation const& value) {
        return value.eax == expected[0] && value.edx == expected[1] &&
               value.esp_delta == 0 && value.ebx == kExpectedEbx &&
               value.esi == kExpectedEsi && value.edi == kExpectedEdi;
    };
    return valid(original) && valid(candidate) &&
           original.eax == candidate.eax && original.edx == candidate.edx &&
           original.esp_delta == candidate.esp_delta &&
           original.ebx == candidate.ebx && original.esi == candidate.esi &&
           original.edi == candidate.edi;
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

    auto const candidate_address = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&__allmul));
    std::uint64_t comparisons = 0;
    constexpr std::array<std::uint32_t, 6> edges = {
        0u, 1u, 0x7fffffffu, 0x80000000u, 0xfffffffeu, 0xffffffffu};
    for (std::uint32_t a_low : edges)
        for (std::uint32_t a_high : edges)
            for (std::uint32_t b_low : edges)
                for (std::uint32_t b_high : edges)
                    if (!CheckOne(candidate_address, a_low, a_high, b_low,
                                  b_high, comparisons))
                    {
                        std::fprintf(stderr,
                                     "Directed multiply mismatch after %llu cases.\n",
                                     static_cast<unsigned long long>(comparisons));
                        VirtualFree(reference, 0, MEM_RELEASE);
                        return 4;
                    }

    std::uint32_t random = 0x9e3779b9u;
    constexpr std::uint32_t kRandomCases = 1000000;
    for (std::uint32_t test = 0; test < kRandomCases; ++test)
    {
        std::uint32_t const a_low = NextRandom(random);
        std::uint32_t const a_high = NextRandom(random);
        std::uint32_t const b_low = NextRandom(random);
        std::uint32_t const b_high = NextRandom(random);
        if (!CheckOne(candidate_address, a_low, a_high, b_low, b_high,
                      comparisons))
        {
            std::fprintf(stderr,
                         "Random multiply mismatch at case %u (operands %08x:%08x * %08x:%08x).\n",
                         test, a_high, a_low, b_high, b_low);
            VirtualFree(reference, 0, MEM_RELEASE);
            return 5;
        }
    }

    VirtualFree(reference, 0, MEM_RELEASE);
    std::printf("PASS: %llu original/candidate/independent-oracle cases; %llu edge combinations plus %u deterministic random operands; EDX:EAX, stdcall cleanup, and callee-saved registers matched.\n",
                static_cast<unsigned long long>(comparisons),
                static_cast<unsigned long long>(edges.size() * edges.size() *
                                                edges.size() * edges.size()),
                kRandomCases);
    std::puts("LIMIT: controlled function-level tests only; no full CRT, startup, or GTA behavior.");
    return 0;
}
