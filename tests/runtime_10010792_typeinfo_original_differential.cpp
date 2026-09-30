#include <Windows.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

struct TypeInfoStorage
{
    bool __thiscall equals(const TypeInfoStorage* other) const;
    void** vtable;
};

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kOriginalEntry = 0x10010792;
constexpr std::size_t kNameOffset = 9;
constexpr std::size_t kNameCapacity = 256;

struct Observation
{
    std::int32_t esp_after_call;
    std::int32_t result;
};

volatile std::uint32_t g_esp_before = 0;

extern "C" __declspec(naked) void __cdecl InvokeRaw(
    std::uint32_t, void*, void*, Observation*)
{
    __asm {
        push ebp
        mov ebp, esp
        mov dword ptr [g_esp_before], esp
        push dword ptr [ebp + 10h]
        mov ecx, dword ptr [ebp + 0Ch]
        mov eax, dword ptr [ebp + 8]
        call eax
        mov edx, esp
        sub edx, dword ptr [g_esp_before]
        mov ecx, dword ptr [ebp + 14h]
        mov dword ptr [ecx], edx
        mov dword ptr [ecx + 4], eax
        pop ebp
        ret
    }
}

std::uint8_t* MapReference(char const* path)
{
    HANDLE const file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ,
                                    nullptr, OPEN_EXISTING,
                                    FILE_ATTRIBUTE_NORMAL, nullptr);
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

    auto const* const dos = reinterpret_cast<IMAGE_DOS_HEADER const*>(bytes.data());
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0 ||
        static_cast<std::size_t>(dos->e_lfanew) + sizeof(IMAGE_NT_HEADERS32) >
            bytes.size())
        return nullptr;
    auto const* const nt = reinterpret_cast<IMAGE_NT_HEADERS32 const*>(
        bytes.data() + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.ImageBase != kImageBase)
        return nullptr;

    auto* const image = static_cast<std::uint8_t*>(VirtualAlloc(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(kImageBase)),
        nt->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE));
    if (image != reinterpret_cast<std::uint8_t const*>(
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

std::uint32_t CandidateAddress()
{
    using Member = bool (TypeInfoStorage::*)(TypeInfoStorage const*) const;
    Member const member = &TypeInfoStorage::equals;
    static_assert(sizeof(member) == sizeof(std::uint32_t));
    std::uint32_t address = 0;
    std::memcpy(&address, &member, sizeof(address));
    return address;
}

std::array<std::uint8_t, kNameOffset + kNameCapacity> MakeType(
    std::string const& name)
{
    std::array<std::uint8_t, kNameOffset + kNameCapacity> type{};
    std::memcpy(type.data() + kNameOffset, name.c_str(), name.size() + 1);
    return type;
}

bool Compare(std::uint32_t original, std::uint32_t candidate,
             std::string const& left_name, std::string const& right_name,
             std::uint64_t& cases)
{
    auto left = MakeType(left_name);
    auto right = MakeType(right_name);
    Observation original_result{};
    Observation candidate_result{};
    InvokeRaw(original, left.data(), right.data(), &original_result);
    InvokeRaw(candidate, left.data(), right.data(), &candidate_result);
    ++cases;
    bool const matches = static_cast<std::uint8_t>(original_result.result) ==
           static_cast<std::uint8_t>(candidate_result.result) &&
           original_result.esp_after_call == candidate_result.esp_after_call &&
           original_result.esp_after_call == 0 &&
           (static_cast<std::uint8_t>(original_result.result) != 0) ==
               (left_name == right_name);
    if (!matches)
        std::fprintf(stderr,
                     "compare mismatch left='%s' right='%s' original=%ld/%ld candidate=%ld/%ld expected_equal=%d target=0x%08lx\n",
                     left_name.c_str(), right_name.c_str(),
                     original_result.result, original_result.esp_after_call,
                     candidate_result.result, candidate_result.esp_after_call,
                     left_name == right_name, candidate);
    return matches;
}

std::uint32_t Next(std::uint32_t& state)
{
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

std::string RandomName(std::uint32_t& state, std::size_t length)
{
    std::string result(length, '\0');
    for (char& ch : result)
        ch = static_cast<char>(0x20 + Next(state) % 0x5f);
    return result;
}
} // namespace

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::fprintf(stderr, "usage: harness <ImVehFt.asi>\n");
        return 2;
    }
    auto* const image = MapReference(argv[1]);
    if (!image)
    {
        std::fprintf(stderr, "Could not map the reference ASI at its preferred base.\n");
        return 3;
    }

    std::uint64_t cases = 0;
    std::array<std::pair<std::string, std::string>, 8> const directed = {{
        {"", ""}, {"exception", "exception"}, {"exception", "Exception"},
        {"type_info", "type_info"}, {"a", "ab"}, {"ab", "a"},
        {"same-prefix-left", "same-prefix-right"},
        {"012345678901234567890123456789", "012345678901234567890123456789"}}};
    for (auto const& [left, right] : directed)
    {
        if (!Compare(kOriginalEntry, CandidateAddress(), left, right, cases))
        {
            std::fprintf(stderr, "directed type_info equality mismatch\n");
            VirtualFree(image, 0, MEM_RELEASE);
            return 4;
        }
    }

    std::uint32_t state = 0x9e3779b9u;
    constexpr std::uint32_t kRandomCases = 100000;
    for (std::uint32_t test = 0; test < kRandomCases; ++test)
    {
        std::size_t const left_length = Next(state) % 96;
        std::size_t const right_length = Next(state) % 96;
        std::string left = RandomName(state, left_length);
        std::string right = test % 3 == 0 && left_length == right_length ?
            left : RandomName(state, right_length);
        if (!Compare(kOriginalEntry, CandidateAddress(), left, right, cases))
        {
            std::fprintf(stderr, "type_info mismatch at random case %u\n", test);
            VirtualFree(image, 0, MEM_RELEASE);
            return 5;
        }
    }

    VirtualFree(image, 0, MEM_RELEASE);
    std::printf("PASS: %llu original/candidate type_info comparisons; directed names, %u deterministic randomized cases, result and thiscall RET 4 cleanup matched.\n",
                static_cast<unsigned long long>(cases), kRandomCases);
    std::printf("LIMIT: synthetic type-name buffers and the recovered candidate _strcmp were used; C++ EH integration and GTA startup were not exercised.\n");
    return 0;
}
