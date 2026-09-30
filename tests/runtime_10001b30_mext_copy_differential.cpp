#include <Windows.h>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern "C" int __cdecl FUN_10001b30(int destination, int source);
extern "C" int __cdecl FUN_10001b00(int texture);
extern "C" void __cdecl FUN_10001ad0(int texture);
int DAT_1003aacc = 0x20;

namespace {
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kPluginOffset = 0x20;
constexpr std::uint32_t kOwnedField = kPluginOffset + 0x0c;
constexpr std::uint32_t kDestroyApi = 0x007f3820;
constexpr std::uint32_t kRasterCreateApi = 0x007fb230;
constexpr std::uint32_t kTextureCreateApi = 0x007f37c0;
constexpr char kOriginalPath[] = "C:\\Users\\caner\\OneDrive\\Documents\\ImVehFt\\ImVehFt.asi";

using CopyCallback = int (__cdecl*)(int, int);
using DestroyCallback = int (__cdecl*)(int);
using ConstructorCallback = void (__cdecl*)(int);
struct ApiCall { std::uint32_t api; std::uint32_t a; std::uint32_t b; std::uint32_t c; std::uint32_t d; };
struct Observation {
    int copyResult = 0;
    int destroyResult = 0;
    bool badNestedReentry = false;
    std::vector<ApiCall> calls;
    std::uint8_t source[0x100]{};
    std::uint8_t destination[0x100]{};
    std::uint8_t createdTexture[0x100]{};
    std::uint8_t raster[0x40]{};
};

std::uint8_t* g_originalImage = nullptr;
DestroyCallback g_activeDestroy = nullptr;
ConstructorCallback g_activeConstructor = nullptr;
Observation* g_observation = nullptr;
alignas(16) std::uint8_t g_source[0x100]{};
alignas(16) std::uint8_t g_destination[0x100]{};
alignas(16) std::uint8_t g_ownedTexture[0x100]{};
alignas(16) std::uint8_t g_createdTexture[0x100]{};
alignas(16) std::uint8_t g_raster[0x40]{};
unsigned g_destroyDepth = 0;

void __cdecl RwTextureDestroyStub(int texture);
int __cdecl RwRasterCreateStub(int width, int height, int flags, int type);
int __cdecl RwTextureCreateStub(int raster);

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
        nt->OptionalHeader.ImageBase != kImageBase || nt->OptionalHeader.SizeOfImage < 0x3b000) return false;

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

    // Verified Ghidra encodings: 10001b19 MOV ECX,0x7f3820;
    // 10001b70 MOV EDX,0x7fb230; 10001b78 MOV EAX,0x7f37c0.
    struct Patch { std::uint32_t opcodeRva; std::uint8_t opcode; std::uint32_t operandRva; std::uint32_t target; std::uint32_t replacement; };
    Patch patches[] = {
        {0x1b19, 0xb9, 0x1b1a, kDestroyApi, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&RwTextureDestroyStub))},
        {0x1b70, 0xba, 0x1b71, kRasterCreateApi, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&RwRasterCreateStub))},
        {0x1b78, 0xb8, 0x1b79, kTextureCreateApi, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&RwTextureCreateStub))}
    };
    for (auto const& patch : patches) {
        std::uint32_t target = 0;
        if (image[patch.opcodeRva] != patch.opcode) { VirtualFree(image, 0, MEM_RELEASE); return false; }
        std::memcpy(&target, image + patch.operandRva, sizeof(target));
        if (target != patch.target) { VirtualFree(image, 0, MEM_RELEASE); return false; }
        std::memcpy(image + patch.operandRva, &patch.replacement, sizeof(patch.replacement));
    }
    g_originalImage = image;
    return true;
}

void RwTextureDestroyStub(int texture)
{
    g_observation->calls.push_back({kDestroyApi, static_cast<std::uint32_t>(texture), 0, 0, 0});
    if (++g_destroyDepth > 8) {
        g_observation->badNestedReentry = true;
        --g_destroyDepth;
        return;
    }
    // Model this plugin's registry callback during destruction; other GTA and
    // third-party plugin callbacks are intentionally outside this harness.
    g_activeDestroy(texture);
    --g_destroyDepth;
}

int RwRasterCreateStub(int width, int height, int flags, int type)
{
    g_observation->calls.push_back({kRasterCreateApi,
        static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height),
        static_cast<std::uint32_t>(flags), static_cast<std::uint32_t>(type)});
    return static_cast<int>(reinterpret_cast<std::uintptr_t>(g_raster));
}

int RwTextureCreateStub(int raster)
{
    g_observation->calls.push_back({kTextureCreateApi,
        static_cast<std::uint32_t>(raster), 0, 0, 0});
    std::memset(g_createdTexture, 0x5a, sizeof(g_createdTexture));
    g_activeConstructor(static_cast<int>(reinterpret_cast<std::uintptr_t>(g_createdTexture)));
    return static_cast<int>(reinterpret_cast<std::uintptr_t>(g_createdTexture));
}

std::uint32_t PatchCandidateImmediate(void* entry, std::uint32_t target, std::uint32_t replacement)
{
    auto* code = static_cast<std::uint8_t*>(entry);
    std::uint32_t matches = 0;
    std::uint32_t* immediate = nullptr;
    for (std::size_t i = 0; i + sizeof(target) <= 0x200; ++i) {
        std::uint32_t value = 0;
        std::memcpy(&value, code + i, sizeof(value));
        if (value == target) { ++matches; immediate = reinterpret_cast<std::uint32_t*>(code + i); }
    }
    if (matches != 1 || immediate == nullptr) return matches;
    DWORD oldProtection = 0;
    if (!VirtualProtect(immediate, sizeof(*immediate), PAGE_EXECUTE_READWRITE, &oldProtection)) return 0;
    *immediate = replacement;
    FlushInstructionCache(GetCurrentProcess(), immediate, sizeof(*immediate));
    DWORD ignored = 0;
    VirtualProtect(immediate, sizeof(*immediate), oldProtection, &ignored);
    return 1;
}

void ResetFixture(bool sourceOwnsTexture)
{
    std::memset(g_source, 0xa5, sizeof(g_source));
    std::memset(g_destination, 0x3c, sizeof(g_destination));
    std::memset(g_ownedTexture, 0x4d, sizeof(g_ownedTexture));
    std::memset(g_raster, 0x6e, sizeof(g_raster));
    std::uint32_t rasterPointer = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(g_raster));
    std::memcpy(g_ownedTexture, &rasterPointer, sizeof(rasterPointer));
    std::uint32_t width = 640, height = 480;
    std::memcpy(g_raster + 0x0c, &width, sizeof(width));
    std::memcpy(g_raster + 0x10, &height, sizeof(height));

    std::uint32_t noOwnedTexture = 0;
    std::uint32_t ownedPointer = sourceOwnsTexture
        ? static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(g_ownedTexture))
        : 0;
    std::memcpy(g_source + kPluginOffset + 0x0c, &ownedPointer, sizeof(ownedPointer));
    std::memcpy(g_destination + kPluginOffset + 0x0c, &noOwnedTexture, sizeof(noOwnedTexture));
}

Observation RunCase(CopyCallback copy, DestroyCallback destroy, ConstructorCallback constructor,
    bool sourceOwnsTexture)
{
    ResetFixture(sourceOwnsTexture);
    Observation observation{};
    g_observation = &observation;
    g_activeDestroy = destroy;
    g_activeConstructor = constructor;
    g_destroyDepth = 0;

    int destination = static_cast<int>(reinterpret_cast<std::uintptr_t>(g_destination));
    int source = static_cast<int>(reinterpret_cast<std::uintptr_t>(g_source));
    constructor(destination);
    observation.copyResult = copy(destination, source);
    observation.destroyResult = destroy(destination);
    std::memcpy(observation.source, g_source, sizeof(g_source));
    std::memcpy(observation.destination, g_destination, sizeof(g_destination));
    std::memcpy(observation.createdTexture, g_createdTexture, sizeof(g_createdTexture));
    std::memcpy(observation.raster, g_raster, sizeof(g_raster));
    return observation;
}

bool Equal(Observation const& a, Observation const& b)
{
    return a.copyResult == b.copyResult && a.destroyResult == b.destroyResult &&
        a.badNestedReentry == b.badNestedReentry && a.calls.size() == b.calls.size() &&
        (a.calls.empty() || std::memcmp(a.calls.data(), b.calls.data(), a.calls.size() * sizeof(ApiCall)) == 0) &&
        std::memcmp(a.source, b.source, sizeof(a.source)) == 0 &&
        std::memcmp(a.destination, b.destination, sizeof(a.destination)) == 0 &&
        std::memcmp(a.createdTexture, b.createdTexture, sizeof(a.createdTexture)) == 0 &&
        std::memcmp(a.raster, b.raster, sizeof(a.raster)) == 0;
}

bool RunPair(char const* label, bool sourceOwnsTexture)
{
    auto originalCopy = reinterpret_cast<CopyCallback>(g_originalImage + 0x1b30);
    auto originalDestroy = reinterpret_cast<DestroyCallback>(g_originalImage + 0x1b00);
    auto originalConstructor = reinterpret_cast<ConstructorCallback>(g_originalImage + 0x1ad0);
    Observation expected = RunCase(originalCopy, originalDestroy, originalConstructor, sourceOwnsTexture);
    Observation actual = RunCase(&FUN_10001b30, &FUN_10001b00, &FUN_10001ad0, sourceOwnsTexture);
    if (!Equal(expected, actual)) {
        std::printf("FAIL %s origCopy=%08x candCopy=%08x origDestroy=%08x candDestroy=%08x calls=%zu/%zu\n",
            label, expected.copyResult, actual.copyResult, expected.destroyResult,
            actual.destroyResult, expected.calls.size(), actual.calls.size());
        return false;
    }
    if (actual.badNestedReentry) {
        std::printf("FAIL %s excessive MEXT destroy re-entry\n", label);
        return false;
    }
    if (sourceOwnsTexture) {
        if (actual.calls.size() != 3 || actual.calls[0].api != kRasterCreateApi ||
            actual.calls[0].a != 640 || actual.calls[0].b != 480 ||
            actual.calls[0].c != 0 || actual.calls[0].d != 5 ||
            actual.calls[1].api != kTextureCreateApi || actual.calls[2].api != kDestroyApi ||
            actual.calls[2].a != static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(g_createdTexture))) {
            std::printf("FAIL %s unexpected create/destroy sequence\n", label);
            return false;
        }
    } else if (!actual.calls.empty()) {
        std::printf("FAIL %s unexpected API call for source with no owned texture\n", label);
        return false;
    }
    std::printf("PASS %s sourceOwned=%u calls=%zu\n", label, sourceOwnsTexture ? 1u : 0u, actual.calls.size());
    return true;
}
}

int main()
{
    if (!LoadOriginalImage()) {
        std::puts("FAIL could not map/verify original ASI call sites at preferred base");
        return 2;
    }
    auto replacementDestroy = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&RwTextureDestroyStub));
    auto replacementRaster = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&RwRasterCreateStub));
    auto replacementTexture = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&RwTextureCreateStub));
    std::uint32_t pluginOffset = kPluginOffset;
    std::memcpy(g_originalImage + 0x3aacc, &pluginOffset, sizeof(pluginOffset));
    DAT_1003aacc = static_cast<int>(kPluginOffset);

    if (PatchCandidateImmediate(reinterpret_cast<void*>(&FUN_10001b30), kRasterCreateApi, replacementRaster) != 1 ||
        PatchCandidateImmediate(reinterpret_cast<void*>(&FUN_10001b30), kTextureCreateApi, replacementTexture) != 1 ||
        PatchCandidateImmediate(reinterpret_cast<void*>(&FUN_10001b00), kDestroyApi, replacementDestroy) != 1) {
        std::puts("FAIL candidate API immediate inventory did not match exact expected operands");
        return 3;
    }

    bool ok = true;
    ok &= RunPair("copy-with-null-owned-slot", false);
    ok &= RunPair("copy-create-destroy-owned-texture", true);
    if (!ok) return 1;
    std::puts("PASS all MEXT copy/create/destroy original-vs-candidate comparisons");
    return 0;
}
