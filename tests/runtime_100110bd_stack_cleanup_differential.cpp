#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern "C" std::int32_t __fastcall ___DllMainCRTStartup(
    std::int32_t, std::int32_t, std::uint32_t);
extern void __stdcall entry(std::uint32_t, std::int32_t, std::int32_t);

extern "C" std::uint8_t IVF_RELOC_TARGET_100399F0[4] = {};
extern "C" std::uint8_t IVF_RELOC_TARGET_10022268[4] = {};

struct StartupCallRecord
{
    std::uint32_t count;
    std::uint32_t event[8];
    std::uint32_t args[8][3];
};

static StartupCallRecord g_record{};
static std::int32_t g_callback_result = 0;
static std::int32_t g_crt_result = 0;
static std::int32_t g_plugin_result = 1;

static void RecordCall(std::uint32_t event, std::uint32_t a,
                       std::uint32_t b, std::uint32_t c)
{
    if (g_record.count >= 8)
        return;
    std::uint32_t const index = g_record.count++;
    g_record.event[index] = event;
    g_record.args[index][0] = a;
    g_record.args[index][1] = b;
    g_record.args[index][2] = c;
}

extern "C" void __cdecl __SEH_prolog4() {}
extern "C" void __stdcall __SEH_epilog4() {}
extern "C" void ___security_init_cookie() {}
extern "C" std::int32_t __stdcall __CRT_INIT_12(
    std::uint32_t a, std::int32_t b, std::int32_t c)
{
    RecordCall(2, a, static_cast<std::uint32_t>(b),
               static_cast<std::uint32_t>(c));
    return g_crt_result;
}
extern "C" std::int32_t __stdcall FUN_10001db0(
    std::uint32_t a, std::int32_t b, std::uint32_t c)
{
    RecordCall(3, a, static_cast<std::uint32_t>(b), c);
    return g_plugin_result;
}

extern "C" std::int32_t __stdcall TestDllMain(
    std::uint32_t a, std::int32_t b, std::uint32_t c)
{
    RecordCall(1, a, static_cast<std::uint32_t>(b), c);
    return g_callback_result;
}

// The earlier hash-pinned candidate object used the pre-ret-12 callee
// declaration. This test-only alias resolves its unreachable attach path.
#pragma comment(linker, "/alternatename:_FUN_10001db0@8=_FUN_10001db0@12")

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kStartup = 0x100110bd;
constexpr std::uint32_t kEntry = 0x100111b3;
volatile LONG g_stack_delta = 0;

std::uint8_t* MapReference(const char* path)
{
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
        return nullptr;
    DWORD size = GetFileSize(file, nullptr);
    if (size == INVALID_FILE_SIZE || size < sizeof(IMAGE_DOS_HEADER))
    {
        CloseHandle(file);
        return nullptr;
    }
    std::vector<std::uint8_t> bytes(size);
    DWORD read = 0;
    BOOL ok = ReadFile(file, bytes.data(), size, &read, nullptr);
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

bool PatchRelativeCall(std::uint8_t* image, std::uint32_t call_va,
                       std::uint32_t expected_target, void* replacement)
{
    auto* call = image + (call_va - kImageBase);
    if (call[0] != 0xe8)
        return false;
    std::int32_t old_relative = 0;
    std::memcpy(&old_relative, call + 1, sizeof(old_relative));
    if (call_va + 5 + old_relative != expected_target)
        return false;
    auto const new_relative = static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(replacement) -
        reinterpret_cast<std::uintptr_t>(call + 5));
    std::memcpy(call + 1, &new_relative, sizeof(new_relative));
    return true;
}

extern "C" __declspec(naked) std::int32_t __stdcall InvokeRaw(
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t)
{
    __asm {
        push    ebp
        mov     ebp, esp
        push    dword ptr [ebp + 14h]
        mov     ecx, dword ptr [ebp + 0Ch]
        mov     edx, dword ptr [ebp + 10h]
        mov     eax, dword ptr [ebp + 8]
        call    eax
        mov     ecx, esp
        sub     ecx, ebp
        mov     dword ptr [g_stack_delta], ecx
        mov     esp, ebp
        pop     ebp
        ret     10h
    }
}

extern "C" __declspec(naked) std::int32_t __stdcall InvokeEntry(
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t)
{
    __asm {
        push    ebp
        mov     ebp, esp
        push    dword ptr [ebp + 14h]
        push    dword ptr [ebp + 10h]
        push    dword ptr [ebp + 0Ch]
        mov     eax, dword ptr [ebp + 8]
        call    eax
        mov     ecx, esp
        sub     ecx, ebp
        mov     dword ptr [g_stack_delta], ecx
        mov     esp, ebp
        pop     ebp
        ret     10h
    }
}
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::fprintf(stderr, "usage: harness <hash-pinned-ImVehFt.asi>\n");
        return 2;
    }
    auto* image = MapReference(argv[1]);
    if (!image)
    {
        std::fprintf(stderr, "could not map reference at preferred base\n");
        return 3;
    }

    // Force the no-work process-detach branch in both images. This exercises
    // the entry ABI/SEH epilog without invoking CRT or plugin side effects.
    std::uint32_t zero = 0;
    std::memcpy(image + (0x100399f0u - kImageBase), &zero, sizeof(zero));
    std::memcpy(IVF_RELOC_TARGET_100399F0, &zero, sizeof(zero));

constexpr LONG kExpectedOriginalStackDelta = -4;
    constexpr unsigned kCases = 256;
    std::uint32_t state = 0x110bd202u;
    for (unsigned i = 0; i != kCases; ++i)
    {
        state = state * 1664525u + 1013904223u;
        std::uint32_t const ecx_arg = state;
        state = state * 1664525u + 1013904223u;
        std::uint32_t const stack_arg = state;

        auto const original = InvokeRaw(kStartup, ecx_arg, 0, stack_arg);
        LONG const original_delta = g_stack_delta;
        auto const candidate = InvokeRaw(
            static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(
                &___DllMainCRTStartup)),
            ecx_arg, 0, stack_arg);
        LONG const candidate_delta = g_stack_delta;
        if (original != candidate || original != 0 ||
            original_delta != kExpectedOriginalStackDelta ||
            candidate_delta != original_delta)
        {
            std::fprintf(stderr,
                         "case %u: returns %ld/%ld, ESP deltas %ld/%ld\n",
                         i, original, candidate, original_delta,
                         candidate_delta);
            return 4;
        }

        auto const original_entry = InvokeEntry(
            0x100111b3u, ecx_arg, 0, stack_arg);
        LONG const original_entry_delta = g_stack_delta;
        auto const candidate_entry = InvokeEntry(
            static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&entry)),
            ecx_arg, 0, stack_arg);
        LONG const candidate_entry_delta = g_stack_delta;
        if (original_entry != candidate_entry || original_entry != 0 ||
            original_entry_delta != 0 ||
            candidate_entry_delta != original_entry_delta)
        {
            std::fprintf(stderr,
                         "entry case %u: returns %ld/%ld, ESP deltas %ld/%ld\n",
                         i, original_entry, candidate_entry,
                         original_entry_delta, candidate_entry_delta);
            return 5;
        }
    }

    if (!PatchRelativeCall(image, 0x10011111u, 0x10010f59u,
                           reinterpret_cast<void*>(&__CRT_INIT_12)) ||
        !PatchRelativeCall(image, 0x10011141u, 0x10010f59u,
                           reinterpret_cast<void*>(&__CRT_INIT_12)) ||
        !PatchRelativeCall(image, 0x10011161u, 0x10010f59u,
                           reinterpret_cast<void*>(&__CRT_INIT_12)) ||
        !PatchRelativeCall(image, 0x10011124u, 0x10001db0u,
                           reinterpret_cast<void*>(&FUN_10001db0)) ||
        !PatchRelativeCall(image, 0x10011138u, 0x10001db0u,
                           reinterpret_cast<void*>(&FUN_10001db0)))
    {
        std::fprintf(stderr, "could not patch all verified original call sites\n");
        return 6;
    }

    auto const callback_address = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&TestDllMain));
    unsigned const reasons[] = {0, 1, 2, 3};
    for (std::uint32_t reason : reasons)
    {
        for (std::uint32_t init_flag = 0; init_flag != 2; ++init_flag)
        for (std::uint32_t has_callback = 0; has_callback != 2; ++has_callback)
        for (std::uint32_t callback_ok = 0; callback_ok != 2; ++callback_ok)
        for (std::uint32_t crt_ok = 0; crt_ok != 2; ++crt_ok)
        for (std::uint32_t plugin_ok = 0; plugin_ok != 2; ++plugin_ok)
        {
            state = state * 1664525u + 1013904223u;
            std::uint32_t const module = state;
            state = state * 1664525u + 1013904223u;
            std::uint32_t const reserved = state;
            std::uint32_t const callback = has_callback ? callback_address : 0;

            std::memcpy(image + (0x100399f0u - kImageBase),
                        &init_flag, sizeof(init_flag));
            std::memcpy(image + (0x10022268u - kImageBase),
                        &callback, sizeof(callback));
            std::memcpy(IVF_RELOC_TARGET_100399F0,
                        &init_flag, sizeof(init_flag));
            std::memcpy(IVF_RELOC_TARGET_10022268,
                        &callback, sizeof(callback));
            g_callback_result = static_cast<std::int32_t>(callback_ok);
            g_crt_result = static_cast<std::int32_t>(crt_ok);
            g_plugin_result = static_cast<std::int32_t>(plugin_ok);

            g_record = {};
            auto const original = InvokeRaw(kStartup, reserved,
                static_cast<std::uint32_t>(reason), module);
            LONG const original_delta = g_stack_delta;
            StartupCallRecord const original_calls = g_record;

            g_record = {};
            auto const candidate = InvokeRaw(
                static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(
                    &___DllMainCRTStartup)),
                reserved, static_cast<std::uint32_t>(reason), module);
            LONG const candidate_delta = g_stack_delta;
            if (original != candidate || original_delta != -4 ||
                candidate_delta != original_delta ||
                std::memcmp(&original_calls, &g_record, sizeof(g_record)) != 0)
            {
                std::fprintf(stderr,
                    "startup matrix mismatch: reason=%u init=%u callback=%u cbret=%u crt=%u plugin=%u; returns=%ld/%ld ESP=%ld/%ld events=%u/%u\n",
                    reason, init_flag, has_callback, callback_ok, crt_ok,
                    plugin_ok, original, candidate, original_delta,
                    candidate_delta, original_calls.count, g_record.count);
                return 7;
            }
        }
    }

    std::printf("PASS: %u direct and %u entry-level original/candidate call pairs; zero mismatches; direct ESP delta %ld, entry delta 0.\n",
                kCases, kCases, kExpectedOriginalStackDelta);
    std::printf("PASS: 128 startup branch cases; call order/arguments, result, and ESP delta matched.\n");
    return 0;
}
