#include <Windows.h>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern "C" int __cdecl FUN_10001b00(int texture);
extern "C" void __cdecl FUN_10001ad0(int texture);
int DAT_1003aacc = 0x20;

namespace {
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kEntryRva = 0x1b00;
constexpr std::uint32_t kPluginOffsetGlobalRva = 0x3aacc;
constexpr std::uint32_t kPluginOffset = 0x20;
constexpr std::uint32_t kOwnedTextureField = kPluginOffset + 0x0c;
constexpr std::uint32_t kOriginalDestroyTarget = 0x007f3820;
constexpr char kOriginalPath[] = "C:\\Users\\caner\\OneDrive\\Documents\\ImVehFt\\ImVehFt.asi";

using DestroyCallback = int (__cdecl*)(int);
using ConstructorCallback = void (__cdecl*)(int);
struct Observation {
    int result = 0;
    int nestedResult = 0;
    std::vector<std::uint32_t> destroyCalls;
    std::uint8_t textureBytes[0x100]{};
    std::uint8_t nestedTextureBytes[0x100]{};
};

std::uint8_t* g_originalImage = nullptr;
DestroyCallback g_activeDestroy = nullptr;
Observation* g_observation = nullptr;
alignas(16) std::uint8_t g_texture[0x100]{};
alignas(16) std::uint8_t g_nestedTexture[0x100]{};
bool g_requestReentry = false;
bool g_reentered = false;

void __cdecl RwTextureDestroyStub(int texture);

bool LoadOriginalImage()
{
    HANDLE file = CreateFileA(kOriginalPath, GENERIC_READ, FILE_SHARE_READ,
        nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) return false;

    DWORD fileSize = GetFileSize(file, nullptr);
    if (fileSize == INVALID_FILE_SIZE) { CloseHandle(file); return false; }
    std::vector<std::uint8_t> bytes(fileSize);
    DWORD bytesRead = 0;
    BOOL readOk = ReadFile(file, bytes.data(), fileSize, &bytesRead, nullptr);
    CloseHandle(file);
    if (!readOk || bytesRead != fileSize || fileSize < sizeof(IMAGE_DOS_HEADER)) return false;

    auto const* dos = reinterpret_cast<IMAGE_DOS_HEADER const*>(bytes.data());
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0 ||
        static_cast<std::size_t>(dos->e_lfanew) + sizeof(IMAGE_NT_HEADERS32) > bytes.size()) return false;
    auto const* nt = reinterpret_cast<IMAGE_NT_HEADERS32 const*>(bytes.data() + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE || nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.ImageBase != kImageBase || nt->OptionalHeader.SizeOfImage <= kPluginOffsetGlobalRva ||
        nt->OptionalHeader.SizeOfImage <= kEntryRva + 0x40) return false;

    auto* image = static_cast<std::uint8_t*>(VirtualAlloc(
        reinterpret_cast<void*>(kImageBase), nt->OptionalHeader.SizeOfImage,
        MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE));
    if (image != reinterpret_cast<std::uint8_t*>(kImageBase)) return false;
    std::memset(image, 0, nt->OptionalHeader.SizeOfImage);
    std::memcpy(image, bytes.data(), nt->OptionalHeader.SizeOfHeaders);

    auto const* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section) {
        if (section->SizeOfRawData == 0) continue;
        if (section->PointerToRawData > bytes.size() ||
            section->SizeOfRawData > bytes.size() - section->PointerToRawData ||
            section->VirtualAddress > nt->OptionalHeader.SizeOfImage ||
            section->SizeOfRawData > nt->OptionalHeader.SizeOfImage - section->VirtualAddress) {
            VirtualFree(image, 0, MEM_RELEASE);
            return false;
        }
        std::memcpy(image + section->VirtualAddress,
            bytes.data() + section->PointerToRawData, section->SizeOfRawData);
    }

    // Ghidra: 0x10001b19 is MOV ECX,0x007f3820. Redirect only this external
    // RenderWare call in the mapped test image; leave the destructor body intact.
    if (image[0x1b19] != 0xb9) { VirtualFree(image, 0, MEM_RELEASE); return false; }
    std::uint32_t actualTarget = 0;
    std::memcpy(&actualTarget, image + 0x1b1a, sizeof(actualTarget));
    if (actualTarget != kOriginalDestroyTarget) { VirtualFree(image, 0, MEM_RELEASE); return false; }
    std::uint32_t replacement = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&RwTextureDestroyStub));
    std::memcpy(image + 0x1b1a, &replacement, sizeof(replacement));
    g_originalImage = image;
    return true;
}

void __cdecl RwTextureDestroyStub(int texture)
{
    g_observation->destroyCalls.push_back(static_cast<std::uint32_t>(texture));
    if (g_requestReentry && !g_reentered) {
        g_reentered = true;
        g_observation->nestedResult = g_activeDestroy(
            static_cast<int>(reinterpret_cast<std::uintptr_t>(g_nestedTexture)));
        std::memcpy(g_observation->nestedTextureBytes, g_nestedTexture, sizeof(g_nestedTexture));
    }
}

std::uint32_t FindAndPatchCandidateCall()
{
    auto* code = reinterpret_cast<std::uint8_t*>(&FUN_10001b00);
    std::uint32_t matches = 0;
    std::uint32_t* immediate = nullptr;
    for (std::size_t i = 0; i + sizeof(std::uint32_t) <= 0x80; ++i) {
        std::uint32_t value = 0;
        std::memcpy(&value, code + i, sizeof(value));
        if (value == kOriginalDestroyTarget) {
            ++matches;
            immediate = reinterpret_cast<std::uint32_t*>(code + i);
        }
    }
    if (matches != 1 || immediate == nullptr) return matches;
    DWORD oldProtection = 0;
    if (!VirtualProtect(immediate, sizeof(*immediate), PAGE_EXECUTE_READWRITE, &oldProtection)) return 0;
    *immediate = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&RwTextureDestroyStub));
    FlushInstructionCache(GetCurrentProcess(), immediate, sizeof(*immediate));
    DWORD ignored = 0;
    VirtualProtect(immediate, sizeof(*immediate), oldProtection, &ignored);
    return 1;
}

Observation RunCase(DestroyCallback function, ConstructorCallback constructor,
    std::uint32_t ownedTexture, bool reentry)
{
    Observation observation{};
    std::memset(g_texture, 0xa5, sizeof(g_texture));
    std::memset(g_nestedTexture, 0x5a, sizeof(g_nestedTexture));
    std::memcpy(g_texture + kOwnedTextureField, &ownedTexture, sizeof(ownedTexture));
    constructor(static_cast<int>(reinterpret_cast<std::uintptr_t>(g_nestedTexture)));
    observation.destroyCalls.clear();
    g_observation = &observation;
    g_activeDestroy = function;
    g_requestReentry = reentry;
    g_reentered = false;
    observation.result = function(static_cast<int>(reinterpret_cast<std::uintptr_t>(g_texture)));
    std::memcpy(observation.textureBytes, g_texture, sizeof(g_texture));
    return observation;
}

bool Equal(Observation const& left, Observation const& right)
{
    return left.result == right.result && left.nestedResult == right.nestedResult &&
        left.destroyCalls == right.destroyCalls &&
        std::memcmp(left.textureBytes, right.textureBytes, sizeof(left.textureBytes)) == 0 &&
        std::memcmp(left.nestedTextureBytes, right.nestedTextureBytes, sizeof(left.nestedTextureBytes)) == 0;
}

bool RunPair(char const* name, std::uint32_t ownedTexture, bool reentry)
{
    auto original = reinterpret_cast<DestroyCallback>(g_originalImage + kEntryRva);
    auto candidate = &FUN_10001b00;
    auto originalConstructor = reinterpret_cast<ConstructorCallback>(g_originalImage + 0x1ad0);
    auto candidateConstructor = &FUN_10001ad0;
    Observation expected = RunCase(original, originalConstructor, ownedTexture, reentry);
    Observation actual = RunCase(candidate, candidateConstructor, ownedTexture, reentry);
    if (!Equal(expected, actual)) {
        std::printf("FAIL %s originalResult=%08x candidateResult=%08x originalCalls=%zu candidateCalls=%zu\n",
            name, expected.result, actual.result, expected.destroyCalls.size(), actual.destroyCalls.size());
        return false;
    }
    if ((ownedTexture == 0 && !actual.destroyCalls.empty()) ||
        (ownedTexture != 0 && (actual.destroyCalls.size() != 1 || actual.destroyCalls[0] != ownedTexture))) {
        std::printf("FAIL %s unexpected RenderWare destroy call count/target\n", name);
        return false;
    }
    if (reentry && actual.nestedResult != static_cast<int>(reinterpret_cast<std::uintptr_t>(g_nestedTexture))) {
        std::printf("FAIL %s nested callback did not return the nested texture pointer\n", name);
        return false;
    }
    if (reentry) {
        std::uint32_t fields[4]{};
        std::memcpy(fields, actual.nestedTextureBytes + kPluginOffset, sizeof(fields));
        if (fields[0] != 1 || fields[1] != 0 || fields[2] != 0 || fields[3] != 0) {
            std::printf("FAIL %s candidate constructor did not initialize the nested MEXT record\n", name);
            return false;
        }
    }
    std::printf("PASS %s destroyCalls=%zu reentry=%u\n", name,
        actual.destroyCalls.size(), reentry ? 1u : 0u);
    return true;
}
}

int main()
{
    if (!LoadOriginalImage()) {
        std::puts("FAIL could not map and verify original ImVehFt image at its preferred base");
        return 2;
    }
    if (FindAndPatchCandidateCall() != 1) {
        std::puts("FAIL expected exactly one candidate 0x7f3820 call immediate in FUN_10001b00");
        return 3;
    }
    std::uint32_t pluginOffset = kPluginOffset;
    std::memcpy(g_originalImage + kPluginOffsetGlobalRva, &pluginOffset, sizeof(pluginOffset));
    DAT_1003aacc = static_cast<int>(kPluginOffset);

    bool ok = true;
    ok &= RunPair("null-owner-record", 0, false);
    ok &= RunPair("owned-texture", 0x11112222, false);
    ok &= RunPair("callback-reentry-with-empty-child-owner", 0x33334444, true);
    if (!ok) return 1;
    std::puts("PASS all original-vs-candidate MEXT destructor comparisons");
    return 0;
}
