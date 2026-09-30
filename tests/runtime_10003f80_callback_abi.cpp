#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern "C" void __stdcall FUN_10003f80();
extern "C" std::uint32_t __cdecl FUN_10003fb0(std::uint32_t, std::uint32_t);
extern "C" void __cdecl FUN_10003fe0(int, int);

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kEntry = 0x10003f80;
constexpr std::uint32_t kCallbackEntry = 0x10003fb0;
struct ApiCall
{
    std::uint32_t api;
    std::uint32_t context;
    std::uint32_t callback;
    std::uint32_t mode;
};

struct Invocation
{
    std::uint32_t eax;
    std::int32_t esp_delta;
    std::uint32_t esi;
    std::uint32_t edi;
};

ApiCall g_calls[2]{};
std::uint32_t g_call_count = 0;
volatile std::uint32_t g_esp_before = 0;
volatile std::int32_t g_esp_delta = 0;

void ResetCalls()
{
    std::memset(g_calls, 0, sizeof(g_calls));
    g_call_count = 0;
}

extern "C" void __cdecl TestGtaApiA(std::uint32_t context,
                                    std::uint32_t callback,
                                    std::uint32_t mode)
{
    if (g_call_count < 2)
        g_calls[g_call_count] = {1, context, callback, mode};
    ++g_call_count;
}

extern "C" void __cdecl TestGtaApiB(std::uint32_t context,
                                    std::uint32_t callback,
                                    std::uint32_t mode)
{
    if (g_call_count < 2)
        g_calls[g_call_count] = {2, context, callback, mode};
    ++g_call_count;
}

extern "C" __declspec(naked) void __cdecl InvokeRaw(
    std::uint32_t, std::uint32_t, std::uint32_t, Invocation*)
{
    __asm {
        push ebp
        mov ebp, esp
        push esi
        push edi
        mov esi, dword ptr [ebp + 0Ch]
        mov edi, dword ptr [ebp + 10h]
        mov dword ptr [g_esp_before], esp
        mov eax, dword ptr [ebp + 8]
        call eax
        mov edx, dword ptr [ebp + 14h]
        mov dword ptr [edx], eax
        mov ecx, esp
        sub ecx, dword ptr [g_esp_before]
        mov dword ptr [g_esp_delta], ecx
        mov dword ptr [edx + 4], ecx
        mov dword ptr [edx + 8], esi
        mov dword ptr [edx + 0Ch], edi
        pop edi
        pop esi
        pop ebp
        ret
    }
}

extern "C" __declspec(naked) void __cdecl InvokeCdeclRaw(
    std::uint32_t, std::uint32_t, std::uint32_t, Invocation*)
{
    __asm {
        push ebp
        mov ebp, esp
        push esi
        push edi
        mov esi, 13579BDFh
        mov edi, 2468ACE0h
        mov dword ptr [g_esp_before], esp
        mov eax, dword ptr [ebp + 8]
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0Ch]
        call eax
        add esp, 8
        mov edx, dword ptr [ebp + 14h]
        mov dword ptr [edx], eax
        mov ecx, esp
        sub ecx, dword ptr [g_esp_before]
        mov dword ptr [g_esp_delta], ecx
        mov dword ptr [edx + 4], ecx
        mov dword ptr [edx + 8], esi
        mov dword ptr [edx + 0Ch], edi
        pop edi
        pop esi
        pop ebp
        ret
    }
}

std::uint8_t* MapReference(const char* path)
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
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0)
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

bool PatchApiTarget(std::uint8_t* code, std::size_t size,
                    std::uint32_t old_target, void* replacement)
{
    std::uint32_t count = 0;
    auto const new_target = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(replacement));
    for (std::size_t i = 1; i + sizeof(std::uint32_t) <= size; ++i)
    {
        std::uint32_t operand = 0;
        std::memcpy(&operand, code + i, sizeof(operand));
        if (code[i - 1] == 0xB8 && operand == old_target)
        {
            std::memcpy(code + i, &new_target, sizeof(new_target));
            ++count;
        }
        else if (code[i - 1] == 0xB9 && operand == old_target)
        {
            std::memcpy(code + i, &new_target, sizeof(new_target));
            ++count;
        }
    }
    return count == 1;
}

bool EqualCalls(ApiCall const (&left)[2], ApiCall const (&right)[2],
                std::uint32_t left_callback_a, std::uint32_t left_callback_b,
                std::uint32_t right_callback_a, std::uint32_t right_callback_b)
{
    if (left[0].api != right[0].api || left[1].api != right[1].api)
        return false;
    if (left[0].context != right[0].context ||
        left[1].context != right[1].context ||
        left[0].mode != right[0].mode || left[1].mode != right[1].mode)
        return false;
    return left[0].callback == left_callback_a &&
           left[1].callback == left_callback_b &&
           right[0].callback == right_callback_a &&
           right[1].callback == right_callback_b;
}
} // namespace

int main(int argc, char** argv)
{
    static_assert(sizeof(void*) == 4, "Run this harness as PE32/x86.");
    if (argc != 2)
    {
        std::fprintf(stderr, "usage: harness <pinned-ImVehFt.asi>\n");
        return 2;
    }
    auto* const reference = MapReference(argv[1]);
    if (!reference)
    {
        std::fprintf(stderr, "Could not map the pinned reference ASI.\n");
        return 3;
    }

    auto* const reference_entry = reference + (kEntry - kImageBase);
    auto* const reference_callback_entry =
        reference + (kCallbackEntry - kImageBase);
    auto* const candidate_entry = reinterpret_cast<std::uint8_t*>(FUN_10003f80);
    auto* const candidate_callback_entry =
        reinterpret_cast<std::uint8_t*>(FUN_10003fb0);
    DWORD old_protection = 0;
    constexpr std::size_t kBodySize = 0x22;
    if (!VirtualProtect(candidate_entry, kBodySize, PAGE_EXECUTE_READWRITE,
                        &old_protection))
    {
        std::fprintf(stderr, "Could not make candidate entry writable for test redirection.\n");
        return 4;
    }
    if (!PatchApiTarget(reference_entry, kBodySize, 0x007F1200,
                        reinterpret_cast<void*>(&TestGtaApiA)) ||
        !PatchApiTarget(reference_entry, kBodySize, 0x007F0DC0,
                        reinterpret_cast<void*>(&TestGtaApiB)) ||
        !PatchApiTarget(candidate_entry, kBodySize, 0x007F1200,
                        reinterpret_cast<void*>(&TestGtaApiA)) ||
        !PatchApiTarget(candidate_entry, kBodySize, 0x007F0DC0,
                        reinterpret_cast<void*>(&TestGtaApiB)))
    {
        DWORD ignored = 0;
        VirtualProtect(candidate_entry, kBodySize, old_protection, &ignored);
        std::fprintf(stderr, "API target patch precondition failed.\n");
        return 4;
    }
    constexpr std::size_t kCallbackBodySize = 0x30;
    DWORD callback_old_protection = 0;
    if (!VirtualProtect(candidate_callback_entry, kCallbackBodySize,
                        PAGE_EXECUTE_READWRITE, &callback_old_protection))
    {
        DWORD ignored = 0;
        VirtualProtect(candidate_entry, kBodySize, old_protection, &ignored);
        std::fprintf(stderr,
                     "Could not make candidate callback entry writable for test redirection.\n");
        return 4;
    }
    if (!PatchApiTarget(reference_callback_entry, kCallbackBodySize, 0x007F1200,
                        reinterpret_cast<void*>(&TestGtaApiA)) ||
        !PatchApiTarget(reference_callback_entry, kCallbackBodySize, 0x007F0DC0,
                        reinterpret_cast<void*>(&TestGtaApiB)) ||
        !PatchApiTarget(candidate_callback_entry, kCallbackBodySize, 0x007F1200,
                        reinterpret_cast<void*>(&TestGtaApiA)) ||
        !PatchApiTarget(candidate_callback_entry, kCallbackBodySize, 0x007F0DC0,
                        reinterpret_cast<void*>(&TestGtaApiB)))
    {
        DWORD ignored = 0;
        VirtualProtect(candidate_callback_entry, kCallbackBodySize,
                       callback_old_protection, &ignored);
        VirtualProtect(candidate_entry, kBodySize, old_protection, &ignored);
        std::fprintf(stderr,
                     "Callback API target patch precondition failed.\n");
        return 4;
    }
    DWORD ignored = 0;
    VirtualProtect(candidate_callback_entry, kCallbackBodySize,
                   callback_old_protection, &ignored);
    VirtualProtect(candidate_entry, kBodySize, old_protection, &ignored);

    std::uint32_t const reference_cb_a = 0x10003FE0;
    std::uint32_t const reference_cb_b = 0x10003FB0;
    std::uint32_t const candidate_cb_a = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(FUN_10003fe0));
    std::uint32_t const candidate_cb_b = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(FUN_10003fb0));

    constexpr std::uint32_t kCases = 512;
    for (std::uint32_t i = 0; i < kCases; ++i)
    {
        std::uint32_t const context = 0x81230000u ^ (i * 0x10201u);
        std::uint32_t const mode = (i & 1u) ? 0u : 1u;
        Invocation original{}, candidate{};
        ResetCalls();
        InvokeRaw(kEntry, context, mode, &original);
        ApiCall const original_calls[2] = {g_calls[0], g_calls[1]};
        if (g_call_count != 2)
        {
            std::fprintf(stderr, "Original call count mismatch at case %u.\n", i);
            return 5;
        }
        ResetCalls();
        InvokeRaw(static_cast<std::uint32_t>(
                      reinterpret_cast<std::uintptr_t>(FUN_10003f80)),
                  context, mode, &candidate);
        ApiCall const candidate_calls[2] = {g_calls[0], g_calls[1]};
        if (g_call_count != 2 || original.eax != candidate.eax ||
            original.esp_delta != candidate.esp_delta ||
            original.esi != candidate.esi || original.edi != candidate.edi ||
            !EqualCalls(original_calls, candidate_calls, reference_cb_a,
                        reference_cb_b, candidate_cb_a, candidate_cb_b))
        {
            std::fprintf(stderr, "Differential mismatch at case %u.\n", i);
            return 6;
        }

        ResetCalls();
        InvokeCdeclRaw(kCallbackEntry, context, mode, &original);
        ApiCall const original_callback_calls[2] = {g_calls[0], g_calls[1]};
        if (g_call_count != 2)
        {
            std::fprintf(stderr,
                         "Original callback call count mismatch at case %u.\n",
                         i);
            return 7;
        }
        ResetCalls();
        InvokeCdeclRaw(static_cast<std::uint32_t>(
                           reinterpret_cast<std::uintptr_t>(FUN_10003fb0)),
                       context, mode, &candidate);
        ApiCall const candidate_callback_calls[2] = {g_calls[0], g_calls[1]};
        if (g_call_count != 2 || original.eax != candidate.eax ||
            original.esp_delta != candidate.esp_delta ||
            original.esi != candidate.esi || original.edi != candidate.edi ||
            original.esi != 0x13579BDFu || original.edi != 0x2468ACE0u ||
            candidate.esi != 0x13579BDFu || candidate.edi != 0x2468ACE0u ||
            !EqualCalls(original_callback_calls, candidate_callback_calls,
                        reference_cb_a, reference_cb_b, candidate_cb_a,
                        candidate_cb_b))
        {
            std::fprintf(stderr,
                         "Callback-body mismatch case=%u count=%u orig={eax:%08x esp:%d esi:%08x edi:%08x} cand={eax:%08x esp:%d esi:%08x edi:%08x}; A orig={api:%u ctx:%08x cb:%08x mode:%08x} cand={api:%u ctx:%08x cb:%08x mode:%08x}; B orig={api:%u ctx:%08x cb:%08x mode:%08x} cand={api:%u ctx:%08x cb:%08x mode:%08x}\n",
                         i, g_call_count, original.eax, original.esp_delta,
                         original.esi, original.edi, candidate.eax,
                         candidate.esp_delta, candidate.esi, candidate.edi,
                         original_callback_calls[0].api,
                         original_callback_calls[0].context,
                         original_callback_calls[0].callback,
                         original_callback_calls[0].mode,
                         candidate_callback_calls[0].api,
                         candidate_callback_calls[0].context,
                         candidate_callback_calls[0].callback,
                         candidate_callback_calls[0].mode,
                         original_callback_calls[1].api,
                         original_callback_calls[1].context,
                         original_callback_calls[1].callback,
                         original_callback_calls[1].mode,
                         candidate_callback_calls[1].api,
                         candidate_callback_calls[1].context,
                         candidate_callback_calls[1].callback,
                         candidate_callback_calls[1].mode);
            return 8;
        }
    }

    std::printf("PASS: %u differential cases each for wrapper 0x10003f80 and callback body 0x10003fb0; callback order and identities, context/mode arguments, EAX, ESI/EDI preservation, and ESP delta matched.\n",
                kCases);
    std::puts("LIMIT: GTA API targets were replaced by test recorders; no live game/API side effects were tested.");
    return 0;
}
