#define NOMINMAX
#include <Windows.h>
#include <xmmintrin.h>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <limits>
#include <vector>

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This differential harness requires MSVC x86."
#endif

extern "C" volatile std::uint32_t DAT_1003c414 = 0;
extern "C" void __cdecl FUN_10006be0();
extern "C" std::uint64_t __fastcall FUN_1001ba40(std::uint32_t, std::uint32_t);
extern "C" long double __stdcall FUN_10008d20();
extern "C" void __fastcall FUN_100073f0(
    void*, std::uint32_t, void*, float, float, float, std::uint32_t, float);
extern "C" void __cdecl CallWithEntry(
    std::uintptr_t, const std::uint32_t*, std::uint32_t);
extern "C" void __cdecl StubSetup(void*, std::uint32_t, void*);
extern "C" void __cdecl StubTick();
extern "C" void __cdecl StubApply(void*, const void*);
extern "C" void __cdecl StubEffect(void*, int, void*, void*);
extern "C" void* __cdecl StubMatrix(void*, const void*, const void*);
extern "C" void __cdecl StubTransform();
extern "C" void __cdecl StubCorona();
extern "C" std::uint32_t g_corona_words[21];
extern "C" volatile std::uint32_t g_corona_call_count;

std::uint32_t DAT_10024ec8 = 0;
double DAT_10024ec0 = 0;
float DAT_1003c1f8 = 0;
float DAT_1003bc1c = 0;
float _DAT_10024ed8 = 0;
double _DAT_10024e88 = 0;
double _DAT_10024ed0 = 0;
std::uint32_t _DAT_10024eec = 0;
double _DAT_10024ee0 = 0;
float _DAT_10024ef8 = 0;
float _DAT_10024f28 = 0;
double _DAT_10024f30 = 0;
float _DAT_10024f38 = 0;
float _DAT_10024f10 = 0;

extern "C" volatile std::uint32_t g_test_intensity_bits = 0;
extern "C" volatile std::uint32_t g_test_transform_edx = 0;
extern "C" volatile std::uint32_t g_test_transform_calls = 0;
extern "C" std::uint32_t g_corona_words[21] = {};
extern "C" volatile std::uint32_t g_corona_call_count = 0;
extern "C" volatile std::uint32_t g_captured_alpha_input = 0;
extern "C" volatile std::uint32_t g_alpha_helper_call_count = 0;
extern "C" volatile std::uint32_t g_captured_param8 = 0;
extern "C" volatile std::uint32_t g_captured_param7 = 0;
extern "C" volatile std::uint32_t g_captured_edx = 0;
extern "C" volatile float g_test_scene_value = 0.0f;
extern "C" volatile std::uint32_t g_effect_call_count = 0;
extern "C" volatile std::uint32_t g_raw_local18_seed = 0x3f000000u;
extern "C" volatile std::uint32_t g_render_call_count = 0;
extern "C" std::uint32_t g_render_words[8] = {};
extern "C" volatile std::uint16_t g_x87_setup_status = 0;
extern "C" volatile std::uint16_t g_x87_transform_status = 0;
extern "C" volatile std::uint16_t g_x87_corona_status = 0;

namespace {

constexpr std::uint32_t kPreferredBase = 0x10000000;
constexpr std::uint32_t kFunctionVa = 0x10006be0;
constexpr std::size_t kFunctionSize = 0x442; // through RET at 0x10007021
constexpr std::uint32_t kAlphaHelperVa = 0x1001ba40;
constexpr std::size_t kAlphaHelperSize = 0xab;

struct Frame {
    std::uint8_t header[4];
    std::uint32_t parent;
    std::uint8_t dirtyLink[8];
    float modelling[16];
    float ltm[16];
};
static_assert(offsetof(Frame, modelling) == 0x10);
static_assert(offsetof(Frame, ltm) == 0x50);

struct CoronaRecord {
    std::uint32_t word[21]{};
    std::uint32_t callCount = 0;
};

struct RenderRecord {
    std::uint32_t words[8]{};
    std::uint32_t callCount = 0;
};

struct FpRecord {
    std::uint16_t status;
    std::uint16_t control;
    std::uint32_t mxcsr;
    std::uint8_t x87Tag;
};

struct Observation {
    CoronaRecord corona;
    FpRecord fp;
    std::uint32_t setupCalls;
    std::uint32_t transformCalls;
    std::uint32_t alphaInputBits;
    std::uint32_t alphaHelperCalls;
    std::uint32_t helperParam8;
    std::uint32_t helperParam7;
    std::uint32_t helperEdx;
    std::uint32_t effectCalls;
    RenderRecord render;
    std::uint16_t x87SetupStatus;
    std::uint16_t x87TransformStatus;
    std::uint16_t x87CoronaStatus;
};

struct Patch {
    std::uint32_t from;
    std::uint32_t to;
    unsigned expected;
    unsigned found;
};

std::uint32_t g_setupCalls = 0;
std::uint32_t g_transformBits = 0;
std::array<std::uint32_t, 16> g_matrixResult{};
static_assert(sizeof(g_matrixResult) == 64);
std::uint8_t* g_originalAlphaHook = nullptr;
std::uint8_t* g_candidateAlphaHook = nullptr;

std::uint32_t FloatBits(float value)
{
    std::uint32_t bits = 0;
    std::memcpy(&bits, &value, sizeof(bits));
    return bits;
}

float ReadFloat(const std::uint8_t* image, std::uint32_t va)
{
    float value = 0;
    std::memcpy(&value, image + (va - kPreferredBase), sizeof(value));
    return value;
}

template <typename T>
T ReadImageValue(const std::uint8_t* image, std::uint32_t va)
{
    T value{};
    std::memcpy(&value, image + (va - kPreferredBase), sizeof(value));
    return value;
}

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

bool ReplaceOperands(std::uint8_t* code, std::size_t codeSize,
                     Patch* patches, std::size_t patchCount)
{
    for (std::size_t offset = 0; offset + sizeof(std::uint32_t) <= codeSize;
         ++offset) {
        std::uint32_t operand = 0;
        std::memcpy(&operand, code + offset, sizeof(operand));
        for (std::size_t i = 0; i < patchCount; ++i) {
            if (operand == patches[i].from) {
                std::memcpy(code + offset, &patches[i].to, sizeof(patches[i].to));
                ++patches[i].found;
                break;
            }
        }
    }
    for (std::size_t i = 0; i < patchCount; ++i) {
        if (patches[i].found != patches[i].expected) {
            std::fprintf(stderr,
                         "operand %08lx: found %u, expected %u\n",
                         static_cast<unsigned long>(patches[i].from),
                         patches[i].found, patches[i].expected);
            return false;
        }
    }
    FlushInstructionCache(GetCurrentProcess(), code, codeSize);
    return true;
}

bool PatchOriginalRenderCall(std::uint8_t* code)
{
    constexpr std::size_t callOffset = 0x428;
    if (callOffset + 5 > kFunctionSize || code[callOffset] != 0xe8)
        return false;
    std::int32_t oldRelative = 0;
    std::memcpy(&oldRelative, code + callOffset + 1, sizeof(oldRelative));
    const auto oldDestination = static_cast<std::uint32_t>(
        kFunctionVa + callOffset + 5 + oldRelative);
    if (oldDestination != 0x100073f0)
        return false;
    const auto replacement = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_100073f0));
    const auto newRelative = static_cast<std::int32_t>(
        replacement - static_cast<std::uint32_t>(
            kFunctionVa + callOffset + 5));
    std::memcpy(code + callOffset + 1, &newRelative, sizeof(newRelative));
    return true;
}

bool PatchOriginalClockCall(std::uint8_t* code)
{
    constexpr std::size_t callOffset = 0x3ef;
    if (callOffset + 5 > kFunctionSize || code[callOffset] != 0xe8)
        return false;
    std::int32_t oldRelative = 0;
    std::memcpy(&oldRelative, code + callOffset + 1, sizeof(oldRelative));
    const auto oldDestination = static_cast<std::uint32_t>(
        kFunctionVa + callOffset + 5 + oldRelative);
    if (oldDestination != 0x10008d20)
        return false;
    const auto replacement = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&FUN_10008d20));
    const auto newRelative = static_cast<std::int32_t>(
        replacement - static_cast<std::uint32_t>(
            kFunctionVa + callOffset + 5));
    std::memcpy(code + callOffset + 1, &newRelative, sizeof(newRelative));
    return true;
}

std::uint8_t* CreateAlphaCaptureHook(std::uint32_t destination)
{
    auto* hook = static_cast<std::uint8_t*>(VirtualAlloc(
        nullptr, 0x1000, MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE));
    if (hook == nullptr)
        return nullptr;
    const std::uint8_t instructions[] = {
        0x9c,                               // PUSHFD
        0x50,                               // PUSH EAX
        0xd9, 0xc0,                         // FLD ST(0): duplicate input
        0xd9, 0x1d, 0, 0, 0, 0,           // FSTP dword ptr [capture]
        0x8b, 0x45, 0x24,                   // MOV EAX,[EBP+24] (param_8)
        0xa3, 0, 0, 0, 0,                   // MOV [param8 capture],EAX
        0x8b, 0x45, 0x20,                   // MOV EAX,[EBP+20] (param_7)
        0xa3, 0, 0, 0, 0,                   // MOV [param7 capture],EAX
        0x89, 0x15, 0, 0, 0, 0,           // MOV [EDX capture],EDX
        0xff, 0x05, 0, 0, 0, 0,           // INC dword ptr [call count]
        0x58,                               // POP EAX
        0x9d,                               // POPFD
        0xe9, 0, 0, 0, 0                  // JMP destination helper
    };
    std::memcpy(hook, instructions, sizeof(instructions));
    const auto capture = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&g_captured_alpha_input));
    const auto counter = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&g_alpha_helper_call_count));
    const auto param8 = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&g_captured_param8));
    const auto param7 = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&g_captured_param7));
    const auto edx = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&g_captured_edx));
    std::memcpy(hook + 6, &capture, sizeof(capture));
    std::memcpy(hook + 14, &param8, sizeof(param8));
    std::memcpy(hook + 22, &param7, sizeof(param7));
    std::memcpy(hook + 28, &edx, sizeof(edx));
    std::memcpy(hook + 34, &counter, sizeof(counter));
    const auto next = reinterpret_cast<std::uintptr_t>(hook + sizeof(instructions));
    const auto relative = static_cast<std::int32_t>(
        destination - static_cast<std::uint32_t>(next));
    std::memcpy(hook + 41, &relative, sizeof(relative));
    FlushInstructionCache(GetCurrentProcess(), hook, sizeof(instructions));
    return hook;
}

bool PatchOriginalAlphaCalls(std::uint8_t* code, std::uint8_t* hook)
{
    constexpr std::size_t operandOffsets[] = {0x174, 0x2a7};
    for (const auto operandOffset : operandOffsets) {
        if (operandOffset < 1 || operandOffset + 4 > kFunctionSize ||
            code[operandOffset - 1] != 0xe8)
            return false;
        std::int32_t oldRelative = 0;
        std::memcpy(&oldRelative, code + operandOffset, sizeof(oldRelative));
        const auto oldDestination = static_cast<std::uint32_t>(
            kFunctionVa + operandOffset + 4 + oldRelative);
        if (oldDestination != kAlphaHelperVa)
            return false;
        const auto next = static_cast<std::uint32_t>(
            kFunctionVa + operandOffset + 4);
        const auto destination = static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(hook));
        const auto newRelative = static_cast<std::int32_t>(destination - next);
        std::memcpy(code + operandOffset, &newRelative, sizeof(newRelative));
    }
    FlushInstructionCache(GetCurrentProcess(), code, kFunctionSize);
    return true;
}

bool FindCandidateImplementationRange(const char* mapPath,
                                      std::uint32_t& address,
                                      std::size_t& size)
{
    FILE* map = nullptr;
    if (fopen_s(&map, mapPath, "r") != 0 || map == nullptr)
        return false;
    char line[2048]{};
    bool inPublics = false;
    unsigned functionSegment = 0;
    unsigned functionOffset = 0;
    unsigned functionAddress = 0;
    unsigned nextOffset = std::numeric_limits<unsigned>::max();
    while (std::fgets(line, sizeof(line), map) != nullptr) {
        if (std::strstr(line, "Publics by Value") != nullptr) {
            inPublics = true;
            continue;
        }
        if (!inPublics)
            continue;
        unsigned segment = 0;
        unsigned offset = 0;
        unsigned absoluteAddress = 0;
        char symbol[512]{};
        if (sscanf_s(line, "%x:%x %511s %x", &segment, &offset,
                     symbol, static_cast<unsigned>(sizeof(symbol)),
                     &absoluteAddress) != 4)
            continue;
        if (std::strcmp(symbol, "_FUN_10006be0_impl") == 0) {
            functionSegment = segment;
            functionOffset = offset;
            functionAddress = absoluteAddress;
        }
        else if (functionSegment != 0 && segment == functionSegment &&
                 offset > functionOffset && offset < nextOffset) {
            nextOffset = offset;
        }
    }
    std::fclose(map);
    if (functionSegment == 0 || functionAddress == 0 ||
        nextOffset == std::numeric_limits<unsigned>::max())
        return false;
    address = functionAddress;
    size = nextOffset - functionOffset;
    return size != 0;
}

bool PatchCandidateAlphaCalls(const char* mapPath, std::uint8_t* hook)
{
    std::uint32_t functionAddress = 0;
    std::size_t functionSize = 0;
    if (!FindCandidateImplementationRange(mapPath, functionAddress,
                                          functionSize))
        return false;
    const auto loadedImageBase = reinterpret_cast<std::uintptr_t>(
        GetModuleHandleW(nullptr));
    auto* code = reinterpret_cast<std::uint8_t*>(
        loadedImageBase + (functionAddress - 0x00400000));
    const auto functionStart = reinterpret_cast<std::uintptr_t>(code);
    const auto originalHelper = reinterpret_cast<std::uintptr_t>(&FUN_1001ba40);
    const auto hookAddress = reinterpret_cast<std::uintptr_t>(hook);
    unsigned found = 0;
    DWORD oldProtection = 0;
    if (!VirtualProtect(code, functionSize, PAGE_EXECUTE_READWRITE,
                        &oldProtection))
        return false;
    for (std::size_t offset = 0; offset + 5 <= functionSize; ++offset) {
        if (code[offset] != 0xe8)
            continue;
        std::int32_t relative = 0;
        std::memcpy(&relative, code + offset + 1, sizeof(relative));
        const auto destination = static_cast<std::uintptr_t>(
            static_cast<std::intptr_t>(functionStart + offset + 5) + relative);
        if (destination != originalHelper)
            continue;
        const auto newRelative = static_cast<std::int32_t>(
            hookAddress - (functionStart + offset + 5));
        std::memcpy(code + offset + 1, &newRelative, sizeof(newRelative));
        ++found;
    }
    DWORD ignored = 0;
    const bool restored = VirtualProtect(code, functionSize, oldProtection,
                                         &ignored) != 0;
    FlushInstructionCache(GetCurrentProcess(), code, functionSize);
    if (found != 3 || !restored) {
        std::fprintf(stderr,
                     "candidate alpha-helper call sites: found %u, expected 3; protection restore=%u\n",
                     found, restored ? 1u : 0u);
        return false;
    }
    return true;
}

bool PatchCandidateCalls(const char* mapPath)
{
    std::uint32_t functionAddress = 0;
    std::size_t functionSize = 0;
    if (!FindCandidateImplementationRange(mapPath, functionAddress,
                                          functionSize)) {
        std::fprintf(stderr, "Could not find candidate implementation in map %s.\n",
                     mapPath);
        return false;
    }
    if (functionSize < sizeof(std::uint32_t)) {
        std::fprintf(stderr, "Invalid candidate implementation span: %zu bytes.\n",
                     functionSize);
        return false;
    }
    const auto loadedImageBase = reinterpret_cast<std::uintptr_t>(
        GetModuleHandleW(nullptr));
    if (functionAddress < 0x00400000) {
        std::fprintf(stderr, "Invalid preferred candidate function VA %08lx.\n",
                     static_cast<unsigned long>(functionAddress));
        return false;
    }
    auto* code = reinterpret_cast<std::uint8_t*>(
        loadedImageBase + (functionAddress - 0x00400000));

    Patch patches[] = {
        {0x007f18b0, reinterpret_cast<std::uint32_t>(&StubMatrix), 1, 0},
        {0x0040fe60, reinterpret_cast<std::uint32_t>(&StubSetup), 1, 0},
        {0x0059c910, reinterpret_cast<std::uint32_t>(&StubTick), 1, 0},
        {0x007f2070, reinterpret_cast<std::uint32_t>(&StubApply), 1, 0},
        {0x0059c790, reinterpret_cast<std::uint32_t>(&StubTransform), 1, 0},
        {0x006fc580, reinterpret_cast<std::uint32_t>(&StubCorona), 1, 0},
        {0x0054eef0, reinterpret_cast<std::uint32_t>(&StubEffect), 1, 0},
        {0x00c812a8, reinterpret_cast<std::uint32_t>(&g_test_scene_value), 2, 0},
    };
    DWORD oldProtection = 0;
    if (!VirtualProtect(code, functionSize, PAGE_EXECUTE_READWRITE,
                        &oldProtection))
        return false;
    const bool patched = ReplaceOperands(code, functionSize, patches,
                                         sizeof(patches) / sizeof(patches[0]));
    DWORD ignored = 0;
    if (!VirtualProtect(code, functionSize, oldProtection, &ignored))
        return false;
    return patched;
}

void SetCandidateGlobals(const std::uint8_t* original)
{
    DAT_10024ec8 = ReadImageValue<std::uint32_t>(original, 0x10024ec8);
    DAT_10024ec0 = ReadImageValue<double>(original, 0x10024ec0);
    DAT_1003c1f8 = ReadFloat(original, 0x1003c1f8);
    DAT_1003bc1c = ReadFloat(original, 0x1003bc1c);
    _DAT_10024ed8 = ReadFloat(original, 0x10024ed8);
    _DAT_10024e88 = ReadImageValue<double>(original, 0x10024e88);
    _DAT_10024ed0 = ReadImageValue<double>(original, 0x10024ed0);
    _DAT_10024eec = ReadImageValue<std::uint32_t>(original, 0x10024eec);
    _DAT_10024ee0 = ReadImageValue<double>(original, 0x10024ee0);
    _DAT_10024ef8 = ReadFloat(original, 0x10024ef8);
    _DAT_10024f28 = ReadFloat(original, 0x10024f28);
    _DAT_10024f30 = ReadImageValue<double>(original, 0x10024f30);
    _DAT_10024f38 = ReadFloat(original, 0x10024f38);
    _DAT_10024f10 = ReadFloat(original, 0x10024f10);
}

void ResetObservation()
{
    std::memset(g_corona_words, 0, sizeof(g_corona_words));
    g_corona_call_count = 0;
    g_setupCalls = 0;
    g_test_transform_calls = 0;
    g_captured_alpha_input = 0;
    g_alpha_helper_call_count = 0;
    g_captured_param8 = 0;
    g_captured_param7 = 0;
    g_captured_edx = 0;
    g_effect_call_count = 0;
    g_render_call_count = 0;
    std::memset(g_render_words, 0, sizeof(g_render_words));
    g_x87_setup_status = 0;
    g_x87_transform_status = 0;
    g_x87_corona_status = 0;
}

FpRecord CaptureFp()
{
    FpRecord fp{};
    __declspec(align(16)) std::uint8_t state[512]{};
    std::uint16_t controlWord = 0;
    __asm {
        fnstsw ax
        mov fp.status, ax
        fnstcw controlWord
        lea eax, state
        fxsave [eax]
        mov al, byte ptr [eax + 4]
        mov fp.x87Tag, al
    }
    fp.control = controlWord;
    fp.mxcsr = _mm_getcsr();
    return fp;
}

std::uint64_t CallAlphaHelper(std::uintptr_t entry, float input,
                              std::uint32_t secondArgument,
                              std::uint16_t controlWord)
{
    std::uint32_t resultLow = 0;
    std::uint32_t resultHigh = 0;
    __asm {
        fninit
        fldcw controlWord
        fld input
        mov ecx, 0
        mov edx, secondArgument
        mov eax, entry
        call eax
        mov dword ptr resultLow, eax
        mov dword ptr resultHigh, edx
    }
    return (static_cast<std::uint64_t>(resultHigh) << 32) | resultLow;
}

int LogHarnessException(EXCEPTION_POINTERS* exception)
{
    std::fprintf(stderr, "harness exception code=%08lx eip=%08lx address=%p\\n",
        static_cast<unsigned long>(exception->ExceptionRecord->ExceptionCode),
        static_cast<unsigned long>(exception->ContextRecord->Eip),
        exception->ExceptionRecord->ExceptionAddress);
    std::fflush(stderr);
    return EXCEPTION_EXECUTE_HANDLER;
}

bool SafeCallWithEntry(std::uintptr_t entry, const std::uint32_t* stackWords,
                       std::uint32_t incomingEax)
{
    __try {
        CallWithEntry(entry, stackWords, incomingEax);
        return true;
    }
    __except (LogHarnessException(GetExceptionInformation())) {
        return false;
    }
}

Observation InvokeAndObserve(std::uintptr_t entry,
                            const std::uint32_t* stackWords,
                            std::uint32_t incomingEax,
                            std::uint16_t controlWord)
{
    ResetObservation();
    _mm_setcsr(0x1f80);
    __asm {
        fninit
        fldcw controlWord
    }
    if (!SafeCallWithEntry(entry, stackWords, incomingEax))
        return {};
    CoronaRecord corona{};
    std::memcpy(corona.word, g_corona_words, sizeof(corona.word));
    corona.callCount = g_corona_call_count;
    RenderRecord render{};
    std::memcpy(render.words, g_render_words, sizeof(render.words));
    render.callCount = g_render_call_count;
    return {corona, CaptureFp(), g_setupCalls, g_test_transform_calls,
            g_captured_alpha_input, g_alpha_helper_call_count,
            g_captured_param8, g_captured_param7, g_captured_edx,
            g_effect_call_count, render, g_x87_setup_status,
            g_x87_transform_status, g_x87_corona_status};
}

bool SameObservation(const Observation& original,
                     const Observation& candidate)
{
    if (original.corona.callCount != candidate.corona.callCount ||
        original.setupCalls != candidate.setupCalls ||
        original.transformCalls != candidate.transformCalls ||
        original.alphaInputBits != candidate.alphaInputBits ||
        original.alphaHelperCalls != candidate.alphaHelperCalls ||
        original.helperParam7 != candidate.helperParam7 ||
        original.helperEdx != candidate.helperEdx ||
        original.effectCalls != candidate.effectCalls ||
        original.render.callCount != candidate.render.callCount ||
        std::memcmp(original.render.words, candidate.render.words,
                    sizeof(original.render.words)) != 0 ||
        std::memcmp(&original.fp, &candidate.fp, sizeof(FpRecord)) != 0)
        return false;
    for (std::size_t i = 0; i < 21; ++i) {
        if (i == 6) // the per-invocation local corona-position pointer
            continue;
        if (original.corona.word[i] != candidate.corona.word[i])
            return false;
    }
    return true;
}

bool SameObservationExceptX87ConditionCodes(const Observation& original,
                                            const Observation& candidate)
{
    // C0/C1/C2/C3 are volatile x87 condition codes, not function results.
    // Keep exception flags, TOP/tag, control word and MXCSR exact.
    constexpr std::uint16_t kX87ConditionCodeMask = 0x4700;
    auto normalizedOriginal = original;
    auto normalizedCandidate = candidate;
    normalizedOriginal.fp.status &=
        static_cast<std::uint16_t>(~kX87ConditionCodeMask);
    normalizedCandidate.fp.status &=
        static_cast<std::uint16_t>(~kX87ConditionCodeMask);
    return SameObservation(normalizedOriginal, normalizedCandidate);
}

} // namespace

extern "C" void __cdecl StubSetup(void* result, std::uint32_t, void*)
{
    __asm {
        push eax
        fnstsw ax
        mov g_x87_setup_status, ax
        pop eax
    }
    ++g_setupCalls;
    const std::uint32_t intensityBits = g_test_intensity_bits;
    std::memcpy(static_cast<std::uint8_t*>(result) + 4,
                &intensityBits,
                sizeof(std::uint32_t));
}

extern "C" void __cdecl StubTick() {}

extern "C" void __cdecl StubApply(void*, const void*) {}

extern "C" void __cdecl StubEffect(
    void* local18, int, void*, void* local28)
{
    ++g_effect_call_count;
    constexpr std::uint32_t marker = 0x3f123456u;
    constexpr std::uint32_t effectResult[3] = {
        0x13579bdfu, 0x2468ace0u, 0x5a5aa5a5u};
    std::memcpy(local18, &marker, sizeof(marker));
    std::memcpy(local28, effectResult, sizeof(effectResult));
}

extern "C" void* __cdecl StubMatrix(void* result, const void*, const void*)
{
    std::memcpy(result, g_matrixResult.data(), sizeof(g_matrixResult));
    return result;
}

extern "C" __declspec(naked) void __cdecl StubTransform(void)
{
    __asm {
        push eax
        fnstsw ax
        mov dword ptr [g_x87_transform_status], eax
        pop eax
        inc dword ptr [g_test_transform_calls]
        mov eax, dword ptr [esp + 4]
        mov ecx, dword ptr [g_test_intensity_bits]
        mov dword ptr [eax + 4], ecx
        mov edx, dword ptr [g_test_transform_edx]
        ret
    }
}

extern "C" __declspec(naked) void __cdecl StubCorona()
{
    __asm {
        push eax
        fnstsw ax
        mov dword ptr [g_x87_corona_status], eax
        pop eax
        push ebx
        push esi
        push edi
        pushfd
        cld
        lea esi, [esp + 14h]
        lea edi, g_corona_words
        mov ecx, 15h
        rep movsd
        popfd
        inc dword ptr [g_corona_call_count]
        pop edi
        pop esi
        pop ebx
        ret
    }
}

extern "C" long double __stdcall FUN_10008d20()
{
    return 0.5L;
}

extern "C" __declspec(naked) void __fastcall FUN_100073f0(
    void*, std::uint32_t, void*, float, float, float, std::uint32_t, float)
{
    __asm {
        mov dword ptr [g_render_words], ecx
        mov dword ptr [g_render_words + 4], edx
        mov eax, dword ptr [esp + 4]
        mov ecx, dword ptr [eax]
        mov dword ptr [g_render_words + 8], ecx
        mov eax, dword ptr [esp + 8]
        mov dword ptr [g_render_words + 12], eax
        mov eax, dword ptr [esp + 0ch]
        mov dword ptr [g_render_words + 16], eax
        mov eax, dword ptr [esp + 10h]
        mov dword ptr [g_render_words + 20], eax
        mov eax, dword ptr [esp + 14h]
        mov dword ptr [g_render_words + 24], eax
        mov eax, dword ptr [esp + 18h]
        mov dword ptr [g_render_words + 28], eax
        inc dword ptr [g_render_call_count]
        ret
    }
}

extern "C" __declspec(naked) void __cdecl CallWithEntry(
    std::uintptr_t, const std::uint32_t*, std::uint32_t)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi
        mov esi, dword ptr [ebp + 0ch]
        push dword ptr [esi + 2ch]
        push dword ptr [esi + 28h]
        push dword ptr [esi + 24h]
        push dword ptr [esi + 20h]
        push dword ptr [esi + 1ch]
        push dword ptr [esi + 18h]
        push dword ptr [esi + 14h]
        push dword ptr [esi + 10h]
        push dword ptr [esi + 0ch]
        push dword ptr [esi + 08h]
        push dword ptr [esi + 04h]
        push dword ptr [esi]
        mov eax, dword ptr [ebp + 10h]
        // Both target and candidate deliberately read their untouched
        // [EBP-0x18] local in mode 3. Seed the caller's future frame slot so
        // each independently invoked implementation sees the same value.
        push ecx
        mov ecx, dword ptr [g_raw_local18_seed]
        mov dword ptr [esp - 1ch], ecx
        pop ecx
        call dword ptr [ebp + 08h]
        add esp, 30h
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret
    }
}

int main(int argc, char** argv)
{
    static_assert(sizeof(void*) == 4, "Run this harness as a PE32 process.");
    if (argc != 3) {
        std::fprintf(stderr,
                     "usage: harness <reference-ImVehFt.asi> <linker-map>\n");
        return 2;
    }

    std::uint32_t originalImageSize = 0;
    auto* originalImage = MapPreferredImage(argv[1], originalImageSize);
    if (originalImage == nullptr) {
        std::fprintf(stderr,
                     "Could not map reference ASI at preferred base 0x10000000 (error %lu).\n",
                     GetLastError());
        return 2;
    }
    if (originalImageSize < 0x3c500) {
        std::fprintf(stderr, "Reference image is unexpectedly small.\n");
        return 2;
    }

    const auto stub = [](auto function) {
        return static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(function));
    };
    const bool traceAlpha = argc > 3 &&
        std::strcmp(argv[3], "--trace-alpha") == 0;
    if (traceAlpha) {
        g_originalAlphaHook = CreateAlphaCaptureHook(kAlphaHelperVa);
        g_candidateAlphaHook = CreateAlphaCaptureHook(stub(&FUN_1001ba40));
        if (g_originalAlphaHook == nullptr || g_candidateAlphaHook == nullptr) {
            std::fprintf(stderr, "Could not allocate executable alpha-capture hooks.\n");
            return 2;
        }
    }
    Patch originalPatches[] = {
        {0x007f18b0, stub(&StubMatrix), 1, 0},
        {0x0040fe60, stub(&StubSetup), 1, 0},
        {0x0059c910, stub(&StubTick), 1, 0},
        {0x007f2070, stub(&StubApply), 1, 0},
        {0x0059c790, stub(&StubTransform), 1, 0},
        {0x006fc580, stub(&StubCorona), 2, 0},
        {0x0054eef0, stub(&StubEffect), 1, 0},
        {0x00c812a8, stub(&g_test_scene_value), 2, 0},
    };
    DWORD oldProtection = 0;
    auto* originalCode = originalImage + (kFunctionVa - kPreferredBase);
    if (!VirtualProtect(originalCode, kFunctionSize, PAGE_EXECUTE_READWRITE,
                        &oldProtection) ||
        !PatchOriginalRenderCall(originalCode) ||
        !PatchOriginalClockCall(originalCode) ||
        (traceAlpha && !PatchOriginalAlphaCalls(originalCode, g_originalAlphaHook)) ||
        !ReplaceOperands(originalCode, kFunctionSize, originalPatches,
                         sizeof(originalPatches) / sizeof(originalPatches[0]))) {
        std::fprintf(stderr, "Reference-function API redirection failed.\n");
        return 2;
    }
    if (!PatchCandidateCalls(argv[2])) {
        std::fprintf(stderr, "Candidate-function API redirection failed.\n");
        return 2;
    }
    if (traceAlpha && !PatchCandidateAlphaCalls(argv[2], g_candidateAlphaHook)) {
        std::fprintf(stderr, "Candidate alpha-helper redirection failed.\n");
        return 2;
    }

    SetCandidateGlobals(originalImage);
    std::printf(
        "Original constants: alpha_upper=%08lx alpha_lower=%08lx alpha_scale=%016llx corona_size=%08lx\n",
        static_cast<unsigned long>(FloatBits(_DAT_10024f28)),
        static_cast<unsigned long>(FloatBits(_DAT_10024f38)),
        static_cast<unsigned long long>(
            *reinterpret_cast<const std::uint64_t*>(&_DAT_10024f30)),
        static_cast<unsigned long>(FloatBits(_DAT_10024f10)));
    constexpr std::uint32_t helperModes[] = {0, 1, 0x12345678};
    for (const auto mode : helperModes) {
        *reinterpret_cast<volatile std::uint32_t*>(
            originalImage + (0x1003c414 - kPreferredBase)) = mode;
        DAT_1003c414 = mode;
        const auto oldResult = CallAlphaHelper(
            0x1001ba40, 63.5f, 127, 0x037f);
        const auto newResult = CallAlphaHelper(
            reinterpret_cast<std::uintptr_t>(&FUN_1001ba40),
            63.5f, 127, 0x037f);
        std::printf("Alpha helper input=63.5 edx=127 mode=%08lx: %016llx / %016llx\n",
                    static_cast<unsigned long>(mode),
                    static_cast<unsigned long long>(oldResult),
                    static_cast<unsigned long long>(newResult));
    }
    std::array<std::uint32_t, 12> args{};
    Frame frame{};
    for (std::size_t i = 0; i < 16; ++i) {
        frame.modelling[i] = static_cast<float>(i + 1) / 4.0f;
        frame.ltm[i] = static_cast<float>(i + 17) / 8.0f;
    }
    args[0] = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&frame));
    args[1] = 0x89abcdef;
    args[2] = static_cast<std::uint32_t>(-7);
    args[3] = 0x35;
    args[4] = 0xa3;
    args[5] = 0x76543210;
    args[6] = 0;
    args[7] = FloatBits(3.75f);
    args[8] = 0; // modelling matrix copied directly
    args[9] = FloatBits(0.0f); // exit before the later world/effect path
    args[10] = 0;
    args[11] = FloatBits(0.625f);

    constexpr std::uint32_t incomingEax = 0x12345678;
    constexpr std::uint16_t controlWords[] = {0x037f, 0x077f, 0x0b7f, 0x0f7f};
    constexpr std::uint32_t globalModes[] = {0, 1, 0x12345678};
    constexpr std::uint32_t alphaBytes[] = {0, 1, 127, 255};
    constexpr std::uint32_t coronaModes[] = {0, 1, 2, 3, 4};
    const float intensityValues[] = {
        -std::numeric_limits<float>::infinity(), -1.0f, -0.5f,
        -0.49999997f, -0.25f, -0.0f, 0.0f, 0.25f,
        0.49999997f, 0.5f, 0.50000006f, 1.0f, 2.0f,
        std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::quiet_NaN()};

    std::size_t comparisons = 0;
    std::size_t mismatches = 0;
    for (const auto mode : globalModes) {
        *reinterpret_cast<volatile std::uint32_t*>(
            originalImage + (0x1003c414 - kPreferredBase)) = mode;
        DAT_1003c414 = mode;
        for (const auto coronaMode : coronaModes) {
            args[10] = coronaMode;
            const std::size_t intensityCount = coronaMode == 2 ? 1 :
                sizeof(intensityValues) / sizeof(intensityValues[0]);
            for (std::size_t intensityIndex = 0;
                 intensityIndex < intensityCount; ++intensityIndex) {
                g_test_intensity_bits = FloatBits(intensityValues[intensityIndex]);
                for (const auto alpha : alphaBytes) {
                    args[6] = alpha;
                    for (const auto controlWord : controlWords) {
                        const auto original = InvokeAndObserve(
                            kFunctionVa, args.data(), incomingEax, controlWord);
                        const auto candidate = InvokeAndObserve(
                            reinterpret_cast<std::uintptr_t>(&FUN_10006be0),
                            args.data(), incomingEax, controlWord);
                        ++comparisons;
                        if (!SameObservation(original, candidate)) {
                            if (mismatches < 24) {
                                std::printf(
                                    "MISMATCH global=%08lx mode=%lu intensity=%08lx alpha=%lu cw=%04x origCalls=%lu candCalls=%lu helper=%08lx/%lu p8=%08lx p7=%08lx edx=%08lx != %08lx/%lu p8=%08lx p7=%08lx edx=%08lx\n",
                                    static_cast<unsigned long>(mode),
                                    static_cast<unsigned long>(coronaMode),
                                    static_cast<unsigned long>(g_test_intensity_bits),
                                    static_cast<unsigned long>(alpha), controlWord,
                                    static_cast<unsigned long>(original.corona.callCount),
                                    static_cast<unsigned long>(candidate.corona.callCount),
                                    static_cast<unsigned long>(original.alphaInputBits),
                                    static_cast<unsigned long>(original.alphaHelperCalls),
                                    static_cast<unsigned long>(original.helperParam8),
                                    static_cast<unsigned long>(original.helperParam7),
                                    static_cast<unsigned long>(original.helperEdx),
                                    static_cast<unsigned long>(candidate.alphaInputBits),
                                    static_cast<unsigned long>(candidate.alphaHelperCalls),
                                    static_cast<unsigned long>(candidate.helperParam8),
                                    static_cast<unsigned long>(candidate.helperParam7),
                                    static_cast<unsigned long>(candidate.helperEdx));
                                for (std::size_t i = 0; i < 21; ++i) {
                                    if (i != 6 && original.corona.word[i] !=
                                                     candidate.corona.word[i])
                                        std::printf(" arg%02u: %08lx != %08lx\n",
                                            static_cast<unsigned>(i + 1),
                                            static_cast<unsigned long>(original.corona.word[i]),
                                            static_cast<unsigned long>(candidate.corona.word[i]));
                                }
                                if (std::memcmp(&original.fp, &candidate.fp,
                                                sizeof(FpRecord)) != 0)
                                    std::printf(
                                        " fp: sw/cw/mx/tag %04x/%04x/%08lx/%02x != %04x/%04x/%08lx/%02x; setup/transform %lu/%lu != %lu/%lu\n",
                                        original.fp.status, original.fp.control,
                                        static_cast<unsigned long>(original.fp.mxcsr),
                                        original.fp.x87Tag, candidate.fp.status,
                                        candidate.fp.control,
                                        static_cast<unsigned long>(candidate.fp.mxcsr),
                                        candidate.fp.x87Tag,
                                        static_cast<unsigned long>(original.setupCalls),
                                        static_cast<unsigned long>(original.transformCalls),
                                        static_cast<unsigned long>(candidate.setupCalls),
                                        static_cast<unsigned long>(candidate.transformCalls));
                            }
                            ++mismatches;
                        }
                    }
                }
            }
        }
    }

    std::uint32_t randomState = 0x6d2b79f5u;
    const auto nextRandom = [&randomState]() {
        randomState ^= randomState << 13;
        randomState ^= randomState >> 17;
        randomState ^= randomState << 5;
        return randomState;
    };
    constexpr std::size_t randomCases = 4096;
    for (std::size_t index = 0; index < randomCases; ++index) {
        const auto mode = globalModes[nextRandom() % 3];
        const auto coronaMode = coronaModes[nextRandom() % 5];
        *reinterpret_cast<volatile std::uint32_t*>(
            originalImage + (0x1003c414 - kPreferredBase)) = mode;
        DAT_1003c414 = mode;

        for (std::size_t i = 0; i < 16; ++i) {
            const auto modelling = static_cast<std::int32_t>(nextRandom() % 20001) - 10000;
            const auto ltm = static_cast<std::int32_t>(nextRandom() % 20001) - 10000;
            frame.modelling[i] = static_cast<float>(modelling) / 257.0f;
            frame.ltm[i] = static_cast<float>(ltm) / 193.0f;
        }
        for (std::size_t i = 0; i < g_matrixResult.size(); ++i) {
            const auto matrixWord = static_cast<std::int32_t>(nextRandom() % 20001) - 10000;
            g_matrixResult[i] = FloatBits(static_cast<float>(matrixWord) / 311.0f);
        }

        const auto intensity = static_cast<std::int32_t>(nextRandom() % 20001) - 10000;
        g_test_intensity_bits = FloatBits(static_cast<float>(intensity) / 4096.0f);
        g_test_transform_edx = nextRandom();
        args[1] = nextRandom();
        args[2] = static_cast<std::uint32_t>(static_cast<std::int8_t>(nextRandom()));
        args[3] = nextRandom() & 0xffu;
        args[4] = nextRandom() & 0xffu;
        args[5] = nextRandom();
        args[6] = nextRandom() & 0xffu;
        const float radius = static_cast<float>(1 + nextRandom() % 65535) / 4096.0f;
        args[7] = FloatBits(radius);
        args[8] = (nextRandom() & 1u) ? 1u : 0u;
        args[9] = FloatBits(0.0f); // retain the separately tested early-return path
        args[10] = coronaMode;
        const auto tailRadius = static_cast<float>(nextRandom() % 4097) / 512.0f;
        args[11] = FloatBits(tailRadius);

        const auto controlWord = controlWords[nextRandom() % 4];
        const auto original = InvokeAndObserve(
            kFunctionVa, args.data(), incomingEax, controlWord);
        const auto candidate = InvokeAndObserve(
            reinterpret_cast<std::uintptr_t>(&FUN_10006be0),
            args.data(), incomingEax, controlWord);
        ++comparisons;
        if (!SameObservation(original, candidate)) {
            ++mismatches;
            std::printf(
                "RANDOM MISMATCH seed=6d2b79f5 case=%zu global=%08lx mode=%lu intensity=%08lx radius=%08lx alpha=%lu cw=%04x\n",
                index,
                static_cast<unsigned long>(mode),
                static_cast<unsigned long>(coronaMode),
                static_cast<unsigned long>(g_test_intensity_bits),
                static_cast<unsigned long>(args[7]),
                static_cast<unsigned long>(args[6]), controlWord);
            break;
        }
    }

    constexpr float sceneValues[] = {-1.0f, 0.0f, 0.25f, 1.0f, 10.0f};
    constexpr float worldRadii[] = {0.125f, 1.0f, 2.5f};
    constexpr float tailIntensities[] = {-0.5f, -0.25f, 0.0f, 0.25f, 0.5f, 1.0f};
    std::size_t tailCases = 0;
    for (const auto mode : globalModes) {
        *reinterpret_cast<volatile std::uint32_t*>(
            originalImage + (0x1003c414 - kPreferredBase)) = mode;
        DAT_1003c414 = mode;
        for (const auto sceneValue : sceneValues) {
            g_test_scene_value = sceneValue;
            for (const auto worldRadius : worldRadii) {
                args[9] = FloatBits(worldRadius);
                for (const auto coronaMode : coronaModes) {
                    args[10] = coronaMode;
                    for (const auto intensity : tailIntensities) {
                        g_test_intensity_bits = FloatBits(intensity);
                        for (const auto alpha : alphaBytes) {
                            args[6] = alpha;
                            for (const auto controlWord : controlWords) {
                                if (tailCases == 0) {
                                    std::fprintf(stderr,
                                        "tail first case global=%08lx scene=%08lx world=%08lx mode=%lu intensity=%08lx\\n",
                                        static_cast<unsigned long>(mode),
                                        static_cast<unsigned long>(FloatBits(sceneValue)),
                                        static_cast<unsigned long>(args[9]),
                                        static_cast<unsigned long>(coronaMode),
                                        static_cast<unsigned long>(g_test_intensity_bits));
                                    std::fflush(stderr);
                                }
                                const auto original = InvokeAndObserve(
                                    kFunctionVa, args.data(), incomingEax,
                                    controlWord);
                                if (tailCases == 0) {
                                    std::fputs("tail original returned\\n", stderr);
                                    std::fflush(stderr);
                                }
                                const auto candidate = InvokeAndObserve(
                                    reinterpret_cast<std::uintptr_t>(
                                        &FUN_10006be0),
                                    args.data(), incomingEax, controlWord);
                                if (tailCases == 0) {
                                    std::fputs("tail candidate returned\\n", stderr);
                                    std::fflush(stderr);
                                }
                                ++comparisons;
                                ++tailCases;
                                if (!SameObservation(original, candidate)) {
                                    ++mismatches;
                                    std::printf(
                                        "TAIL MISMATCH global=%08lx scene=%08lx world=%08lx mode=%lu intensity=%08lx alpha=%lu cw=%04x calls=%lu/%lu effect=%lu/%lu\n",
                                        static_cast<unsigned long>(mode),
                                        static_cast<unsigned long>(FloatBits(sceneValue)),
                                        static_cast<unsigned long>(args[9]),
                                        static_cast<unsigned long>(coronaMode),
                                        static_cast<unsigned long>(g_test_intensity_bits),
                                        static_cast<unsigned long>(alpha), controlWord,
                                        static_cast<unsigned long>(original.render.callCount),
                                        static_cast<unsigned long>(candidate.render.callCount),
                                        static_cast<unsigned long>(original.effectCalls),
                                        static_cast<unsigned long>(candidate.effectCalls));
                                    for (std::size_t i = 0; i < 8; ++i) {
                                        if (original.render.words[i] !=
                                            candidate.render.words[i])
                                            std::printf(" render_arg%zu: %08lx != %08lx\n",
                                                i,
                                                static_cast<unsigned long>(original.render.words[i]),
                                                static_cast<unsigned long>(candidate.render.words[i]));
                                    }
                                    break;
                                }
                            }
                            if (mismatches != 0)
                                break;
                        }
                        if (mismatches != 0)
                            break;
                    }
                    if (mismatches != 0)
                        break;
                }
                if (mismatches != 0)
                    break;
            }
            if (mismatches != 0)
                break;
        }
        if (mismatches != 0)
            break;
    }

    // The regular tail matrix above uses ordinary finite values. Probe the
    // same original-vs-candidate call path with IEEE-754 boundary classes in
    // the scene/effect inputs, preserving the x87 rounding-mode coverage.
    const float tailEdgeValues[] = {
        -std::numeric_limits<float>::infinity(),
        -std::numeric_limits<float>::max(), -1.0f,
        -std::numeric_limits<float>::denorm_min(), -0.0f, 0.0f,
        std::numeric_limits<float>::denorm_min(), 0.5f, 1.0f,
        std::numeric_limits<float>::max(),
        std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::quiet_NaN()};
    std::uint32_t tailSeed = 0x9e3779b9u;
    const auto nextTailRandom = [&tailSeed]() {
        tailSeed ^= tailSeed << 13;
        tailSeed ^= tailSeed >> 17;
        tailSeed ^= tailSeed << 5;
        return tailSeed;
    };
    std::size_t tailEdgeCases = 0;
    std::size_t tailX87ConditionCodeDifferences = 0;
    for (std::size_t index = 0; index < 4096 && mismatches == 0; ++index) {
        const auto mode = globalModes[nextTailRandom() %
            (sizeof(globalModes) / sizeof(globalModes[0]))];
        *reinterpret_cast<volatile std::uint32_t*>(
            originalImage + (0x1003c414 - kPreferredBase)) = mode;
        DAT_1003c414 = mode;
        const auto sceneValue = tailEdgeValues[nextTailRandom() %
            (sizeof(tailEdgeValues) / sizeof(tailEdgeValues[0]))];
        const auto worldRadius = tailEdgeValues[nextTailRandom() %
            (sizeof(tailEdgeValues) / sizeof(tailEdgeValues[0]))];
        const auto effectIntensity = tailEdgeValues[nextTailRandom() %
            (sizeof(tailEdgeValues) / sizeof(tailEdgeValues[0]))];
        const auto rawLocal18Seed = tailEdgeValues[nextTailRandom() %
            (sizeof(tailEdgeValues) / sizeof(tailEdgeValues[0]))];
        g_test_scene_value = sceneValue;
        g_test_intensity_bits = FloatBits(effectIntensity);
        g_raw_local18_seed = FloatBits(rawLocal18Seed);
        args[9] = FloatBits(worldRadius);
        args[10] = coronaModes[nextTailRandom() %
            (sizeof(coronaModes) / sizeof(coronaModes[0]))];
        args[11] = FloatBits(tailEdgeValues[nextTailRandom() %
            (sizeof(tailEdgeValues) / sizeof(tailEdgeValues[0]))]);
        args[6] = alphaBytes[nextTailRandom() %
            (sizeof(alphaBytes) / sizeof(alphaBytes[0]))];
        const auto controlWord = controlWords[nextTailRandom() %
            (sizeof(controlWords) / sizeof(controlWords[0]))];
        const auto original = InvokeAndObserve(
            kFunctionVa, args.data(), incomingEax, controlWord);
        const auto candidate = InvokeAndObserve(
            reinterpret_cast<std::uintptr_t>(&FUN_10006be0),
            args.data(), incomingEax, controlWord);
        ++comparisons;
        ++tailEdgeCases;
        if (!SameObservation(original, candidate)) {
            if (SameObservationExceptX87ConditionCodes(original, candidate)) {
                ++tailX87ConditionCodeDifferences;
                continue;
            }
            ++mismatches;
            std::printf(
                "TAIL IEEE MISMATCH case=%zu global=%08lx scene=%08lx world=%08lx intensity=%08lx raw_local18=%08lx corona=%lu alpha=%lu cw=%04x\n",
                index, static_cast<unsigned long>(mode),
                static_cast<unsigned long>(FloatBits(sceneValue)),
                static_cast<unsigned long>(FloatBits(worldRadius)),
                static_cast<unsigned long>(g_test_intensity_bits),
                static_cast<unsigned long>(g_raw_local18_seed),
                static_cast<unsigned long>(args[10]),
                static_cast<unsigned long>(args[6]), controlWord);
            std::printf(
                "calls corona/setup/transform/alpha/effect/render: %lu/%lu/%lu/%lu/%lu/%lu vs %lu/%lu/%lu/%lu/%lu/%lu; x87 status/control/tag=%04x/%04x/%02x vs %04x/%04x/%02x; MXCSR=%08lx vs %08lx\n",
                static_cast<unsigned long>(original.corona.callCount),
                static_cast<unsigned long>(original.setupCalls),
                static_cast<unsigned long>(original.transformCalls),
                static_cast<unsigned long>(original.alphaHelperCalls),
                static_cast<unsigned long>(original.effectCalls),
                static_cast<unsigned long>(original.render.callCount),
                static_cast<unsigned long>(candidate.corona.callCount),
                static_cast<unsigned long>(candidate.setupCalls),
                static_cast<unsigned long>(candidate.transformCalls),
                static_cast<unsigned long>(candidate.alphaHelperCalls),
                static_cast<unsigned long>(candidate.effectCalls),
                static_cast<unsigned long>(candidate.render.callCount),
                original.fp.status, original.fp.control, original.fp.x87Tag,
                candidate.fp.status, candidate.fp.control, candidate.fp.x87Tag,
                static_cast<unsigned long>(original.fp.mxcsr),
                static_cast<unsigned long>(candidate.fp.mxcsr));
            std::printf(
                "x87 stage statuses setup/transform/corona=%04x/%04x/%04x vs %04x/%04x/%04x\n",
                original.x87SetupStatus, original.x87TransformStatus,
                original.x87CoronaStatus, candidate.x87SetupStatus,
                candidate.x87TransformStatus, candidate.x87CoronaStatus);
            for (std::size_t word = 0; word < 21; ++word) {
                if (original.corona.word[word] != candidate.corona.word[word])
                    std::printf("corona[%zu]=%08lx vs %08lx\n", word,
                        static_cast<unsigned long>(original.corona.word[word]),
                        static_cast<unsigned long>(candidate.corona.word[word]));
            }
            for (std::size_t word = 0; word < 8; ++word) {
                if (original.render.words[word] != candidate.render.words[word])
                    std::printf("render[%zu]=%08lx vs %08lx\n", word,
                        static_cast<unsigned long>(original.render.words[word]),
                        static_cast<unsigned long>(candidate.render.words[word]));
            }
            std::printf(
                "helper alpha/param8/param7/edx: %08lx/%08lx/%08lx/%08lx vs %08lx/%08lx/%08lx/%08lx\n",
                static_cast<unsigned long>(original.alphaInputBits),
                static_cast<unsigned long>(original.helperParam8),
                static_cast<unsigned long>(original.helperParam7),
                static_cast<unsigned long>(original.helperEdx),
                static_cast<unsigned long>(candidate.alphaInputBits),
                static_cast<unsigned long>(candidate.helperParam8),
                static_cast<unsigned long>(candidate.helperParam7),
                static_cast<unsigned long>(candidate.helperEdx));
        }
    }

    std::printf(
        "FUN_10006be0 original-binary differential: %zu/%zu semantically matched; %zu mismatches; directed edges, 4096 deterministic variations, %zu finite downstream-tail cases, %zu IEEE-boundary tail cases, %zu x87 condition-code-only differences.\n",
        comparisons - mismatches, comparisons, mismatches, tailCases,
        tailEdgeCases, tailX87ConditionCodeDifferences);
    VirtualFree(g_originalAlphaHook, 0, MEM_RELEASE);
    VirtualFree(g_candidateAlphaHook, 0, MEM_RELEASE);
    VirtualFree(originalImage, 0, MEM_RELEASE);
    return mismatches == 0 ? 0 : 1;
}
