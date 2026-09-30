#include <Windows.h>

#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <float.h>
#include <utility>
#include <vector>

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This differential harness requires MSVC x86."
#endif

extern "C" void __cdecl FUN_10007030(
    int, int, std::uint32_t, char, std::uint32_t, std::uint32_t,
    std::uint32_t, char, char, std::uint8_t);

std::uint32_t DAT_1003bc1c = 0;
std::uint32_t DAT_1003c1f8 = 0;
double _DAT_10024f00 = 0;
double _DAT_10024f08 = 0;
float _DAT_10024f10 = 0;
float _DAT_10024f14 = 0;
float _DAT_10024f28 = 0;
double _DAT_10024f18 = 0;
double _DAT_10024f20 = 0;
double _DAT_10024f30 = 0;
float _DAT_10024ef8 = 0;
double _DAT_10024ef0 = 0;
std::uint32_t _DAT_10024eec = 0;
std::uint32_t _DAT_10024ee8 = 0;
double _DAT_10024ee0 = 0;
float _DAT_10024ed8 = 0;
double _DAT_10024ed0 = 0;
std::uint32_t _DAT_10024ec8 = 0;
double _DAT_10024ec0 = 0;

extern "C" std::uint64_t __fastcall FUN_1001ba40(std::uint32_t state, int intensity)
{
    using Original = std::uint64_t(__fastcall*)(std::uint32_t, int);
    const auto original = reinterpret_cast<Original>(
        static_cast<std::uintptr_t>(0x1001ba40));
    return original(state, intensity);
}

extern "C" long double __stdcall FUN_10008d20()
{
    using Original = long double(__stdcall*)();
    const auto original = reinterpret_cast<Original>(
        static_cast<std::uintptr_t>(0x10008d20));
    return original();
}

extern "C" void __fastcall FUN_100073f0(
    void*, std::uint32_t, void*, float, float, float,
    std::uint32_t, std::uint32_t)
{
}

namespace {

constexpr std::uint32_t kPreferredBase = 0x10000000;
constexpr std::uint32_t kFunctionVa = 0x10007030;
constexpr std::size_t kFunctionSize = 0x3b8; // through RET at 0x100073e7

struct Frame {
    std::uint32_t header[4];
    std::uint32_t modelling[16];
    std::uint32_t ltm[16];
};
static_assert(offsetof(Frame, modelling) == 0x10);
static_assert(offsetof(Frame, ltm) == 0x50);

struct Observation {
    std::uint32_t setupCalls = 0;
    std::uint32_t tickCalls = 0;
    std::uint32_t applyCalls = 0;
    std::uint32_t transformCalls = 0;
    std::uint32_t coronaCalls = 0;
    std::uint32_t setupOutput[5]{};
    std::uint32_t matrixSeenByApply[16]{};
    std::uint32_t matrixProducedByApply[16]{};
    std::uint32_t transformResultToMatrixDelta = 0;
    std::uint32_t transformResultToInputDelta = 0;
    std::uint32_t transformResultBefore = 0;
    std::uint32_t transformInputBefore = 0;
    std::uint32_t transformInputYBefore = 0;
    std::uint32_t transformInputZBefore = 0;
    std::uint32_t transformOutputY = 0;
    std::uint32_t transformedAlphaBits = 0;
    std::uint32_t coronaPosition[4]{};
    std::uint32_t coronaArguments[21]{};
};

struct OperandPatch {
    std::uint32_t from;
    std::uint32_t to;
    unsigned expected;
    unsigned found;
};

Observation g_observation{};
std::uint32_t g_tickCalls = 0;
std::uint32_t g_transformCalls = 0;
float g_paramVector[3] = {0.0f, 4.0f, 3.0f};

void __cdecl StubSetup(void*, const void*, const void*);
extern "C" void __fastcall StubTick(void*, std::uint32_t);
void __cdecl StubApply(void*, const void*);
void* __cdecl StubMatrix(void*, const void*, const void*);
void __cdecl StubTransform(void*, void*, void*);
void __cdecl StubCorona(
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t, const std::uint32_t*,
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
    std::uint32_t, std::uint32_t);
void __cdecl StubEffect();

std::uint8_t* MapPreferredImage(const char* path, std::uint32_t& imageSize)
{
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
        return nullptr;
    const DWORD fileSize = GetFileSize(file, nullptr);
    if (fileSize == INVALID_FILE_SIZE || fileSize < sizeof(IMAGE_DOS_HEADER)) {
        CloseHandle(file);
        return nullptr;
    }
    std::vector<std::uint8_t> bytes(fileSize);
    DWORD read = 0;
    const BOOL readOk = ReadFile(file, bytes.data(), fileSize, &read, nullptr);
    CloseHandle(file);
    if (!readOk || read != fileSize)
        return nullptr;

    const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(bytes.data());
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0)
        return nullptr;
    const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(
        bytes.data() + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.ImageBase != kPreferredBase)
        return nullptr;

    imageSize = nt->OptionalHeader.SizeOfImage;
    auto* image = static_cast<std::uint8_t*>(VirtualAlloc(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(kPreferredBase)),
        imageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE));
    if (image != reinterpret_cast<std::uint8_t*>(
                     static_cast<std::uintptr_t>(kPreferredBase)))
        return nullptr;
    std::memset(image, 0, imageSize);
    std::memcpy(image, bytes.data(), nt->OptionalHeader.SizeOfHeaders);
    const auto* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section) {
        if (section->SizeOfRawData == 0)
            continue;
        if (section->PointerToRawData > bytes.size() ||
            section->SizeOfRawData > bytes.size() - section->PointerToRawData ||
            section->VirtualAddress > imageSize ||
            section->SizeOfRawData > imageSize - section->VirtualAddress) {
            VirtualFree(image, 0, MEM_RELEASE);
            return nullptr;
        }
        std::memcpy(image + section->VirtualAddress,
                    bytes.data() + section->PointerToRawData,
                    section->SizeOfRawData);
    }
    return image;
}

template <typename T>
T ReadImageValue(const std::uint8_t* image, std::uint32_t va)
{
    T value{};
    std::memcpy(&value, image + (va - kPreferredBase), sizeof(value));
    return value;
}

template <typename T>
void CopyImageValue(const std::uint8_t* image, std::uint32_t va, T& target)
{
    target = ReadImageValue<T>(image, va);
}

void SetCandidateGlobals(const std::uint8_t* image)
{
    CopyImageValue(image, 0x1003bc1c, DAT_1003bc1c);
    CopyImageValue(image, 0x1003c1f8, DAT_1003c1f8);
    CopyImageValue(image, 0x10024f00, _DAT_10024f00);
    CopyImageValue(image, 0x10024f08, _DAT_10024f08);
    CopyImageValue(image, 0x10024f10, _DAT_10024f10);
    CopyImageValue(image, 0x10024f14, _DAT_10024f14);
    CopyImageValue(image, 0x10024f28, _DAT_10024f28);
    CopyImageValue(image, 0x10024f18, _DAT_10024f18);
    CopyImageValue(image, 0x10024f20, _DAT_10024f20);
    CopyImageValue(image, 0x10024f30, _DAT_10024f30);
    CopyImageValue(image, 0x10024ef8, _DAT_10024ef8);
    CopyImageValue(image, 0x10024ef0, _DAT_10024ef0);
    CopyImageValue(image, 0x10024eec, _DAT_10024eec);
    CopyImageValue(image, 0x10024ee8, _DAT_10024ee8);
    CopyImageValue(image, 0x10024ee0, _DAT_10024ee0);
    CopyImageValue(image, 0x10024ed8, _DAT_10024ed8);
    CopyImageValue(image, 0x10024ed0, _DAT_10024ed0);
    CopyImageValue(image, 0x10024ec8, _DAT_10024ec8);
    CopyImageValue(image, 0x10024ec0, _DAT_10024ec0);
}

bool ReplaceOperands(std::uint8_t* code, std::size_t size,
                     OperandPatch* patches, std::size_t count)
{
    for (std::size_t offset = 0; offset + 4 <= size; ++offset) {
        std::uint32_t operand = 0;
        std::memcpy(&operand, code + offset, sizeof(operand));
        for (std::size_t i = 0; i < count; ++i) {
            if (operand == patches[i].from) {
                std::memcpy(code + offset, &patches[i].to,
                            sizeof(patches[i].to));
                ++patches[i].found;
                break;
            }
        }
    }
    for (std::size_t i = 0; i < count; ++i) {
        if (patches[i].found != patches[i].expected) {
            std::fprintf(stderr,
                         "operand %08lx: found %u, expected %u\n",
                         static_cast<unsigned long>(patches[i].from),
                         patches[i].found, patches[i].expected);
            return false;
        }
    }
    FlushInstructionCache(GetCurrentProcess(), code, size);
    return true;
}

bool PatchOriginal(const std::uint8_t* image)
{
    auto* code = const_cast<std::uint8_t*>(image + (kFunctionVa-kPreferredBase));
    OperandPatch patches[] = {
        {0x007f18b0, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubMatrix)), 1, 0},
        {0x0040fe60, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubSetup)), 1, 0},
        {0x0059c910, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubTick)), 1, 0},
        {0x007f2070, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubApply)), 1, 0},
        {0x0059c790, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubTransform)), 1, 0},
        {0x006fc580, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubCorona)), 2, 0},
        {0x0054eef0, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubEffect)), 1, 0},
    };
    return ReplaceOperands(code, kFunctionSize, patches,
                           sizeof(patches) / sizeof(patches[0]));
}

bool FindCandidateImpl(const char* mapPath, std::uint32_t& address,
                       std::size_t& size)
{
    FILE* map = nullptr;
    if (fopen_s(&map, mapPath, "r") != 0 || map == nullptr)
        return false;
    char line[2048]{};
    bool inPublics = false;
    unsigned segmentOfFunction = 0;
    unsigned offsetOfFunction = 0;
    unsigned addressOfFunction = 0;
    unsigned nextOffset = 0xffffffffu;
    std::vector<std::pair<unsigned, unsigned>> symbols;
    while (std::fgets(line, sizeof(line), map) != nullptr) {
        if (std::strstr(line, "Publics by Value") != nullptr) {
            inPublics = true;
            continue;
        }
        if (!inPublics)
            continue;
        unsigned segment = 0, offset = 0, absolute = 0;
        char symbol[512]{};
        if (sscanf_s(line, "%x:%x %511s %x", &segment, &offset, symbol,
                     static_cast<unsigned>(sizeof(symbol)), &absolute) != 4)
            continue;
        symbols.emplace_back(segment, offset);
        if (std::strstr(symbol, "FUN_10007030_impl") != nullptr) {
            segmentOfFunction = segment;
            offsetOfFunction = offset;
            addressOfFunction = absolute;
        }
    }
    std::fclose(map);
    for (const auto& symbol : symbols) {
        if (symbol.first == segmentOfFunction &&
            symbol.second > offsetOfFunction && symbol.second < nextOffset)
            nextOffset = symbol.second;
    }
    if (segmentOfFunction == 0 || addressOfFunction == 0 ||
        nextOffset == 0xffffffffu || nextOffset <= offsetOfFunction) {
        std::fprintf(stderr,
                     "candidate impl map span invalid: seg=%x start=%x next=%x VA=%08x\n",
                     segmentOfFunction, offsetOfFunction, nextOffset,
                     addressOfFunction);
        return false;
    }
    address = addressOfFunction;
    size = nextOffset - offsetOfFunction;
    return size != 0;
}

bool PatchCandidate(const char* mapPath)
{
    std::uint32_t address = 0;
    std::size_t size = 0;
    if (!FindCandidateImpl(mapPath, address, size)) {
        std::fprintf(stderr, "Could not find FUN_10007030_impl in linker map.\n");
        return false;
    }
    const auto imageBase = reinterpret_cast<std::uintptr_t>(GetModuleHandleW(nullptr));
    if (address < 0x00400000)
        return false;
    auto* code = reinterpret_cast<std::uint8_t*>(imageBase + address - 0x00400000);
    OperandPatch patches[] = {
        {0x007f18b0, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubMatrix)), 1, 0},
        {0x0040fe60, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubSetup)), 1, 0},
        {0x0059c910, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubTick)), 1, 0},
        {0x007f2070, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubApply)), 1, 0},
        {0x0059c790, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubTransform)), 1, 0},
        {0x006fc580, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubCorona)), 2, 0},
        {0x0054eef0, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&StubEffect)), 1, 0},
    };
    DWORD oldProtection = 0;
    if (!VirtualProtect(code, size, PAGE_EXECUTE_READWRITE, &oldProtection)) {
        std::fprintf(stderr,
                     "VirtualProtect candidate impl failed: map VA=%08lx host=%p size=%zx error=%lu\n",
                     static_cast<unsigned long>(address), code, size,
                     GetLastError());
        return false;
    }
    const bool ok = ReplaceOperands(code, size, patches,
                                    sizeof(patches) / sizeof(patches[0]));
    DWORD ignored = 0;
    return VirtualProtect(code, size, oldProtection, &ignored) && ok;
}

void CallWithEntry(std::uintptr_t entry, const std::uint32_t* words,
                   std::uint32_t incomingEax)
{
    __asm {
        push esi
        mov esi, words
        push dword ptr [esi + 36]
        push dword ptr [esi + 32]
        push dword ptr [esi + 28]
        push dword ptr [esi + 24]
        push dword ptr [esi + 20]
        push dword ptr [esi + 16]
        push dword ptr [esi + 12]
        push dword ptr [esi + 8]
        push dword ptr [esi + 4]
        push dword ptr [esi]
        mov eax, incomingEax
        mov edx, entry
        call edx
        add esp, 28h
        pop esi
    }
}

bool CallSafely(std::uintptr_t entry, const std::uint32_t* words,
                std::uint32_t incomingEax)
{
    __try {
        CallWithEntry(entry, words, incomingEax);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

void ResetObservation()
{
    g_observation = {};
    g_tickCalls = 0;
    g_transformCalls = 0;
}

void __cdecl StubSetup(void* result, const void* from, const void* what)
{
    ++g_observation.setupCalls;
    const auto* lhs = static_cast<const float*>(from);
    const auto* rhs = static_cast<const float*>(what);
    auto* out = static_cast<float*>(result);
    for (std::size_t i = 0; i < 3; ++i)
        out[i] = lhs[i] - rhs[i];
    std::memcpy(g_observation.setupOutput, result, 3 * sizeof(float));
}

extern "C" void __fastcall StubTick(void* local18, std::uint32_t)
{
    ++g_tickCalls;
    auto* vector = static_cast<float*>(local18);
    const float length = std::sqrt(vector[0] * vector[0] +
                                   vector[1] * vector[1] +
                                   vector[2] * vector[2]);
    if (length != 0.0f) {
        vector[0] /= length;
        vector[1] /= length;
        vector[2] /= length;
    }
}

void __cdecl StubApply(void* destination, const void* source)
{
    ++g_observation.applyCalls;
    std::memcpy(g_observation.matrixSeenByApply, source, 64);
    // The test input is an identity RwMatrix, whose inverse is itself.
    std::memcpy(destination, source, 64);
    std::memcpy(g_observation.matrixProducedByApply, destination, 64);
}

void* __cdecl StubMatrix(void* destination, const void*, const void*)
{
    std::memset(destination, 0x5a, 64);
    return destination;
}

void __cdecl StubTransform(void* result, void* matrix, void* input)
{
    ++g_transformCalls;
    const auto resultAddress = reinterpret_cast<std::uintptr_t>(result);
    const auto matrixAddress = reinterpret_cast<std::uintptr_t>(matrix);
    const auto inputAddress = reinterpret_cast<std::uintptr_t>(input);
    g_observation.transformResultToMatrixDelta =
        static_cast<std::uint32_t>(resultAddress - matrixAddress);
    g_observation.transformResultToInputDelta =
        static_cast<std::uint32_t>(resultAddress - inputAddress);
    std::memcpy(&g_observation.transformResultBefore, result,
                sizeof(g_observation.transformResultBefore));
    std::memcpy(&g_observation.transformInputBefore, input,
                sizeof(g_observation.transformInputBefore));
    std::memcpy(&g_observation.transformInputYBefore,
                static_cast<const float*>(input) + 1,
                sizeof(g_observation.transformInputYBefore));
    std::memcpy(&g_observation.transformInputZBefore,
                static_cast<const float*>(input) + 2,
                sizeof(g_observation.transformInputZBefore));
    const auto* basis = static_cast<const float*>(matrix);
    const auto* vector = static_cast<const float*>(input);
    float transformed[3] = {
        basis[0] * vector[0] + basis[4] * vector[1] + basis[8] * vector[2],
        basis[1] * vector[0] + basis[5] * vector[1] + basis[9] * vector[2],
        basis[2] * vector[0] + basis[6] * vector[1] + basis[10] * vector[2]};
    std::memcpy(result, transformed, sizeof(transformed));
    std::memcpy(&g_observation.transformedAlphaBits, &transformed[1],
                sizeof(transformed[1]));
    std::memcpy(&g_observation.transformOutputY, &transformed[1],
                sizeof(transformed[1]));
}

void __cdecl StubCorona(
    std::uint32_t a0, std::uint32_t a1, std::uint32_t a2,
    std::uint32_t a3, std::uint32_t a4, std::uint32_t a5,
    const std::uint32_t* position,
    std::uint32_t a7, std::uint32_t a8, std::uint32_t a9,
    std::uint32_t a10, std::uint32_t a11, std::uint32_t a12,
    std::uint32_t a13, std::uint32_t a14, std::uint32_t a15,
    std::uint32_t a16, std::uint32_t a17, std::uint32_t a18,
    std::uint32_t a19, std::uint32_t a20)
{
    ++g_observation.coronaCalls;
    const std::uint32_t words[21] = {
        a0,a1,a2,a3,a4,a5,
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(position)),
        a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20};
    std::memcpy(g_observation.coronaArguments, words, sizeof(words));
    std::memcpy(g_observation.coronaPosition, position, 16);
}

void __cdecl StubEffect()
{
}

bool EqualObservations(const Observation& a, const Observation& b)
{
    if (a.setupCalls != b.setupCalls || a.tickCalls != b.tickCalls ||
        a.applyCalls != b.applyCalls || a.transformCalls != b.transformCalls ||
        a.coronaCalls != b.coronaCalls ||
        a.transformResultToMatrixDelta != b.transformResultToMatrixDelta ||
        a.transformResultToInputDelta != b.transformResultToInputDelta ||
        a.transformResultBefore != b.transformResultBefore ||
        a.transformInputBefore != b.transformInputBefore ||
        a.transformInputYBefore != b.transformInputYBefore ||
        a.transformInputZBefore != b.transformInputZBefore ||
        a.transformOutputY != b.transformOutputY ||
        a.transformedAlphaBits != b.transformedAlphaBits ||
        std::memcmp(a.setupOutput, b.setupOutput, sizeof(a.setupOutput)) != 0 ||
        std::memcmp(a.matrixSeenByApply, b.matrixSeenByApply,
                    sizeof(a.matrixSeenByApply)) != 0 ||
        std::memcmp(a.matrixProducedByApply, b.matrixProducedByApply,
                    sizeof(a.matrixProducedByApply)) != 0 ||
        std::memcmp(a.coronaPosition, b.coronaPosition,
                    sizeof(a.coronaPosition)) != 0)
        return false;
    for (std::size_t i = 0; i < 21; ++i) {
        if (i != 6 && a.coronaArguments[i] != b.coronaArguments[i])
            return false;
    }
    return true;
}

void SnapshotCounts()
{
    g_observation.tickCalls = g_tickCalls;
    g_observation.transformCalls = g_transformCalls;
}

} // namespace

int main(int argc, char** argv)
{
    static_assert(sizeof(void*) == 4, "Run as PE32 x86.");
    if (argc != 3) {
        std::fprintf(stderr, "usage: harness <reference-ImVehFt.asi> <linker-map>\n");
        return 2;
    }
    std::uint32_t imageSize = 0;
    auto* originalImage = MapPreferredImage(argv[1], imageSize);
    if (originalImage == nullptr || imageSize <= kFunctionVa-kPreferredBase+kFunctionSize) {
        std::fprintf(stderr, "Could not map the reference ASI at 0x10000000.\n");
        return 2;
    }
    SetCandidateGlobals(originalImage);
    const bool originalPatched = PatchOriginal(originalImage);
    const bool candidatePatched = originalPatched && PatchCandidate(argv[2]);
    if (!originalPatched || !candidatePatched) {
        std::fprintf(stderr, "patch results: original=%u candidate=%u\n",
                     originalPatched ? 1u : 0u,
                     candidatePatched ? 1u : 0u);
        std::fprintf(stderr, "Failed to redirect original/candidate API calls.\n");
        return 2;
    }

    Frame frame{};
    const std::uint32_t identity[16] = {
        0x3f800000,0,0,0, 0,0x3f800000,0,0,
        0,0,0x3f800000,0, 0,0,0,0};
    std::memcpy(frame.modelling, identity, sizeof(identity));
    std::memcpy(frame.ltm, identity, sizeof(identity));
    const std::uint32_t vectorAddress = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(g_paramVector));
    const auto frameAddress = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&frame));
    const auto runCase = [&](const char* label, std::uint32_t incomingEax,
                             std::uint32_t mode, float vx, float vy, float vz,
                             bool expectCorona) {
        std::array<std::uint32_t, 10> stackWords = {
            frameAddress, 0x12345678, vectorAddress, 0x12,
            0xa5, 0xb6, 0xc7, 0, 0, mode};
        g_paramVector[0] = vx;
        g_paramVector[1] = vy;
        g_paramVector[2] = vz;

        ResetObservation();
        _fpreset();
        if (!CallSafely(kFunctionVa, stackWords.data(), incomingEax)) {
            std::fprintf(stderr, "%s: original raised an exception.\n", label);
            return false;
        }
        SnapshotCounts();
        const Observation original = g_observation;

        ResetObservation();
        _fpreset();
        if (!CallSafely(reinterpret_cast<std::uintptr_t>(&FUN_10007030),
                        stackWords.data(), incomingEax)) {
            std::fprintf(stderr, "%s: candidate raised an exception.\n", label);
            return false;
        }
        SnapshotCounts();
        const Observation candidate = g_observation;

        bool matrixTailAlias = true;
        for (std::size_t i = 0; i < 12; ++i) {
            matrixTailAlias &= original.matrixSeenByApply[i] == frame.ltm[i];
            matrixTailAlias &= candidate.matrixSeenByApply[i] == frame.ltm[i];
        }
        for (std::size_t i = 0; i < 4; ++i) {
            matrixTailAlias &= original.matrixSeenByApply[12 + i] ==
                               frame.ltm[12 + i];
            matrixTailAlias &= candidate.matrixSeenByApply[12 + i] ==
                               frame.ltm[12 + i];
        }
        const bool transformAbi =
            original.transformResultToMatrixDelta == 0xd8 &&
            candidate.transformResultToMatrixDelta == 0xd8 &&
            original.transformResultToInputDelta == 0 &&
            candidate.transformResultToInputDelta == 0;
        bool coronaMatrixAlias = original.coronaCalls == (expectCorona ? 1u : 0u) &&
                                 candidate.coronaCalls == (expectCorona ? 1u : 0u);
        if (expectCorona) {
            for (std::size_t i = 0; i < 4; ++i) {
                coronaMatrixAlias &= original.coronaPosition[i] ==
                                     frame.modelling[12 + i];
                coronaMatrixAlias &= candidate.coronaPosition[i] ==
                                     frame.modelling[12 + i];
            }
        }

        const bool equal = EqualObservations(original, candidate);
        const bool passed = equal && matrixTailAlias && coronaMatrixAlias &&
                            transformAbi;
        std::printf("%s: %s; mode=%u tick=%08lx corona=%u/%u alpha=%02lx/%02lx; "
                    "transform-abi=%s matrix-alias=%s corona-path=%s\n",
                    label, passed ? "MATCH" : "MISMATCH", mode,
                    static_cast<unsigned long>(g_observation.transformedAlphaBits),
                    original.coronaCalls, candidate.coronaCalls,
                    static_cast<unsigned long>(original.coronaArguments[5]),
                    static_cast<unsigned long>(candidate.coronaArguments[5]),
                    transformAbi ? "PASS" : "FAIL",
                    matrixTailAlias ? "PASS" : "FAIL",
                    coronaMatrixAlias ? "PASS" : "FAIL");
        if (!passed) {
            std::fprintf(stderr,
                "observation details: calls setup/tick/apply/transform/corona "
                "%u/%u/%u/%u/%u vs %u/%u/%u/%u/%u; "
                "input xyz %08lx/%08lx/%08lx vs %08lx/%08lx/%08lx; "
                "output y %08lx/%08lx; alpha %08lx/%08lx\n",
                original.setupCalls, original.tickCalls, original.applyCalls,
                original.transformCalls, original.coronaCalls,
                candidate.setupCalls, candidate.tickCalls, candidate.applyCalls,
                candidate.transformCalls, candidate.coronaCalls,
                static_cast<unsigned long>(original.transformInputBefore),
                static_cast<unsigned long>(original.transformInputYBefore),
                static_cast<unsigned long>(original.transformInputZBefore),
                static_cast<unsigned long>(candidate.transformInputBefore),
                static_cast<unsigned long>(candidate.transformInputYBefore),
                static_cast<unsigned long>(candidate.transformInputZBefore),
                static_cast<unsigned long>(original.transformOutputY),
                static_cast<unsigned long>(candidate.transformOutputY),
                static_cast<unsigned long>(original.transformedAlphaBits),
                static_cast<unsigned long>(candidate.transformedAlphaBits));
            for (std::size_t i = 0; i < 5; ++i)
                if (original.setupOutput[i] != candidate.setupOutput[i])
                    std::fprintf(stderr, "helper result[%zu]: %08lx/%08lx\n", i,
                        static_cast<unsigned long>(original.setupOutput[i]),
                        static_cast<unsigned long>(candidate.setupOutput[i]));
            std::fprintf(stderr,
                "counts setup/tick/apply/transform/corona original="
                "%u/%u/%u/%u/%u candidate=%u/%u/%u/%u/%u\n",
                original.setupCalls, original.tickCalls, original.applyCalls,
                original.transformCalls, original.coronaCalls,
                candidate.setupCalls, candidate.tickCalls,
                candidate.applyCalls, candidate.transformCalls,
                candidate.coronaCalls);
            std::fprintf(stderr,
                "transform delta result-matrix/input original=%08lx/%08lx "
                "candidate=%08lx/%08lx; first words=%08lx/%08lx\n",
                static_cast<unsigned long>(original.transformResultToMatrixDelta),
                static_cast<unsigned long>(original.transformResultToInputDelta),
                static_cast<unsigned long>(candidate.transformResultToMatrixDelta),
                static_cast<unsigned long>(candidate.transformResultToInputDelta),
                static_cast<unsigned long>(original.transformResultBefore),
                static_cast<unsigned long>(candidate.transformResultBefore));
            std::fprintf(stderr, "apply matrix tail original/candidate:\n");
            for (std::size_t i = 0; i < 16; ++i)
                std::fprintf(stderr, "%02zu %08lx %08lx\n", i,
                    static_cast<unsigned long>(original.matrixSeenByApply[i]),
                    static_cast<unsigned long>(candidate.matrixSeenByApply[i]));
            std::fprintf(stderr, "applied matrix basis-y original/candidate:");
            for (std::size_t i : {1u, 5u, 9u})
                std::fprintf(stderr, " %08lx/%08lx",
                    static_cast<unsigned long>(original.matrixProducedByApply[i]),
                    static_cast<unsigned long>(candidate.matrixProducedByApply[i]));
            std::fprintf(stderr, "\n");
            std::fprintf(stderr, "corona args original/candidate:\n");
            for (std::size_t i = 0; i < 21; ++i)
                if (i != 6 && original.coronaArguments[i] !=
                              candidate.coronaArguments[i])
                    std::fprintf(stderr, "%02zu %08lx %08lx\n", i,
                        static_cast<unsigned long>(original.coronaArguments[i]),
                        static_cast<unsigned long>(candidate.coronaArguments[i]));
        }
        return passed;
    };

    const bool direct = runCase("direct-corona", 0x1234567f, 2,
                                0.0f, 4.0f, 3.0f, true);
    const bool alphaAboveThreshold = runCase("alpha-above-threshold",
                                             0x1234567f, 0,
                                             0.0f, 4.0f, 3.0f, true);
    const bool alphaBelowThreshold = runCase("alpha-below-threshold",
                                             0x1234567f, 0,
                                             1.0f, 0.25f, 0.0f, true);
    const bool alphaSuppressed = runCase("alpha-suppressed-mode",
                                         0x12345623, 1,
                                         0.0f, 4.0f, 3.0f, false);
    return direct && alphaAboveThreshold && alphaBelowThreshold &&
           alphaSuppressed ? 0 : 1;
}
