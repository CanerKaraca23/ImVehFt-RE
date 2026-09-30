#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <exception>
#include <malloc.h>
#include <vector>

struct FUN_10001010_this
{
    void* __thiscall FUN_10001010(std::uint8_t flags);
};

extern "C" std::uint8_t IVF_RELOC_TARGET_10022250[4];
std::uint8_t IVF_RELOC_TARGET_10022250[4] = {};

namespace
{
constexpr std::uint32_t kBase = 0x10000000;
constexpr std::uint32_t kTarget = 0x10001010;
constexpr std::uint32_t kBaseDtor = 0x1001031f;
constexpr std::uint32_t kFreeWrapper = 0x10010756;
constexpr std::uint32_t kDtorCall = 0x1000101c;
constexpr std::uint32_t kHeapFreeIat = 0x10022044;
constexpr std::uint32_t kCrtHeapHandle = 0x10039b90;
constexpr std::uint32_t kBadAllocVtable = 0x10022250;
constexpr std::uint32_t kExceptionVtable = 0x10022228;

std::uint8_t* g_image = nullptr;
std::uint32_t g_captured_vtable = 0;
unsigned g_dtor_calls = 0;
unsigned g_free_calls = 0;
void* g_freed_pointer = nullptr;
std::uint8_t g_freed_snapshot[12] = {};
using HeapFreeFn = BOOL(WINAPI*)(HANDLE, DWORD, LPVOID);
HeapFreeFn g_real_heap_free = nullptr;
extern "C" BOOL WINAPI TrackedHeapFree(HANDLE, DWORD, LPVOID);

int Fail(const char* message)
{
    std::fprintf(stderr, "FAIL: %s\n", message);
    return 1;
}

std::uint8_t* MapOriginal(const char* path)
{
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
        return nullptr;
    const DWORD file_size = GetFileSize(file, nullptr);
    if (file_size == INVALID_FILE_SIZE || file_size < sizeof(IMAGE_DOS_HEADER))
    {
        CloseHandle(file);
        return nullptr;
    }
    std::vector<std::uint8_t> bytes(file_size);
    DWORD read = 0;
    const BOOL read_ok = ReadFile(file, bytes.data(), file_size, &read, nullptr);
    CloseHandle(file);
    if (!read_ok || read != file_size)
        return nullptr;
    const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(bytes.data());
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0)
        return nullptr;
    const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(
        bytes.data() + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.ImageBase != kBase)
        return nullptr;
    auto* image = static_cast<std::uint8_t*>(VirtualAlloc(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(kBase)),
        nt->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE));
    if (image != reinterpret_cast<std::uint8_t*>(
                     static_cast<std::uintptr_t>(kBase)))
        return nullptr;
    std::memset(image, 0, nt->OptionalHeader.SizeOfImage);
    std::memcpy(image, bytes.data(), nt->OptionalHeader.SizeOfHeaders);
    auto* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
    {
        if (section->SizeOfRawData == 0)
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
    auto* call = image + (call_va - kBase);
    if (call[0] != 0xe8)
        return false;
    std::int32_t old_relative = 0;
    std::memcpy(&old_relative, call + 1, 4);
    if (call_va + 5 + old_relative != expected_target)
        return false;
    const auto new_relative = static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(replacement) -
        (reinterpret_cast<std::uintptr_t>(call) + 5));
    std::memcpy(call + 1, &new_relative, 4);
    return true;
}

bool InitializeFreeImport(std::uint8_t* image)
{
    HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
    if (!kernel32)
        return false;
    g_real_heap_free = reinterpret_cast<HeapFreeFn>(
        GetProcAddress(kernel32, "HeapFree"));
    HANDLE process_heap = GetProcessHeap();
    if (!g_real_heap_free || !process_heap)
        return false;
    const std::uint32_t free_address = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&TrackedHeapFree));
    const std::uint32_t heap_address = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(process_heap));
    std::memcpy(image + (kHeapFreeIat - kBase), &free_address, 4);
    std::memcpy(image + (kCrtHeapHandle - kBase), &heap_address, 4);
    return true;
}

void Seed(std::uint32_t* memory, std::uint32_t i)
{
    memory[0] = 0xfeed0000u ^ i;
    memory[1] = 0xabc00000u + i * 0x103u;
    memory[2] = (0xa5c37e00u ^ (i * 0x10001u)) & 0xffffff00u;
}

bool RunOne(void* original, std::uint32_t i, std::uint8_t flags)
{
    auto* original_object = flags
        ? static_cast<std::uint32_t*>(HeapAlloc(GetProcessHeap(), 0, 12))
        : static_cast<std::uint32_t*>(_alloca(12));
    auto* candidate_object = flags
        ? static_cast<std::uint32_t*>(HeapAlloc(GetProcessHeap(), 0, 12))
        : static_cast<std::uint32_t*>(_alloca(12));
    if (!original_object || !candidate_object)
        return false;
    Seed(original_object, i);
    Seed(candidate_object, i);

    g_captured_vtable = 0;
    g_dtor_calls = 0;
    g_free_calls = 0;
    g_freed_pointer = nullptr;
    std::memset(g_freed_snapshot, 0, sizeof(g_freed_snapshot));
    using OriginalFn = void*(__thiscall*)(void*, std::uint8_t);
    void* original_result = reinterpret_cast<OriginalFn>(original)(
        original_object, flags);
    const auto original_transient_vtable = g_captured_vtable;
    const auto original_dtor_calls = g_dtor_calls;
    const auto original_free_calls = g_free_calls;
    const auto original_freed_pointer = g_freed_pointer;
    std::uint8_t original_freed_snapshot[12];
    std::memcpy(original_freed_snapshot, g_freed_snapshot, 12);
    std::uint8_t original_live_snapshot[12] = {};
    if (!flags)
        std::memcpy(original_live_snapshot, original_object, 12);

    g_captured_vtable = 0;
    g_dtor_calls = 0;
    g_free_calls = 0;
    g_freed_pointer = nullptr;
    std::memset(g_freed_snapshot, 0, sizeof(g_freed_snapshot));
    auto* candidate = reinterpret_cast<FUN_10001010_this*>(candidate_object);
    void* candidate_result = candidate->FUN_10001010(flags);
    const auto candidate_transient_vtable = g_captured_vtable;
    const auto candidate_dtor_calls = g_dtor_calls;
    const auto candidate_free_calls = g_free_calls;
    const auto candidate_freed_pointer = g_freed_pointer;
    std::uint8_t candidate_freed_snapshot[12];
    std::memcpy(candidate_freed_snapshot, g_freed_snapshot, 12);
    std::uint8_t candidate_live_snapshot[12] = {};
    if (!flags)
        std::memcpy(candidate_live_snapshot, candidate_object, 12);

    const std::uint32_t expected_candidate_vtable = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(IVF_RELOC_TARGET_10022250));
    const bool common = original_result == original_object &&
        candidate_result == candidate_object &&
        original_transient_vtable == kBadAllocVtable &&
        candidate_transient_vtable == expected_candidate_vtable &&
        original_dtor_calls == 1 && candidate_dtor_calls == 1;
    const bool live_ok = flags ||
        (reinterpret_cast<const std::uint32_t*>(original_live_snapshot)[0] == kExceptionVtable &&
         reinterpret_cast<const std::uint32_t*>(candidate_live_snapshot)[0] == kExceptionVtable &&
         original_live_snapshot[4] == 0 && candidate_live_snapshot[4] == 0 &&
         original_live_snapshot[8] == 0 && candidate_live_snapshot[8] == 0 &&
         std::memcmp(original_live_snapshot + 9, candidate_live_snapshot + 9, 3) == 0);
    const bool free_ok = !flags ||
        (original_free_calls == 1 && candidate_free_calls == 1 &&
         original_freed_pointer == original_object &&
         candidate_freed_pointer == candidate_object &&
         std::memcmp(original_freed_snapshot, candidate_freed_snapshot, 12) == 0 &&
         *reinterpret_cast<const std::uint32_t*>(original_freed_snapshot) == kExceptionVtable &&
         *reinterpret_cast<const std::uint32_t*>(candidate_freed_snapshot) == kExceptionVtable);
    return common && live_ok && free_ok;
}
} // namespace

extern "C" void __fastcall FUN_1001031f(std::exception* object)
{
    auto* words = reinterpret_cast<std::uint32_t*>(object);
    g_captured_vtable = words[0];
    ++g_dtor_calls;
    using Dtor = void(__fastcall*)(std::exception*);
    reinterpret_cast<Dtor>(g_image + (kBaseDtor - kBase))(object);
}

extern "C" void __cdecl FUN_10010756(void* object)
{
    using FreeWrapper = void(__cdecl*)(void*);
    reinterpret_cast<FreeWrapper>(g_image + (kFreeWrapper - kBase))(object);
}

extern "C" BOOL WINAPI TrackedHeapFree(HANDLE heap, DWORD flags, LPVOID memory)
{
    ++g_free_calls;
    g_freed_pointer = memory;
    std::memcpy(g_freed_snapshot, memory, sizeof(g_freed_snapshot));
    return g_real_heap_free(heap, flags, memory);
}

int main(int argc, char** argv)
{
    if (argc != 2)
        return Fail("usage: harness <hash-pinned original ImVehFt.asi>");
    g_image = MapOriginal(argv[1]);
    if (!g_image || !InitializeFreeImport(g_image))
        return Fail("could not map original or bind test-only HeapFree import");
    if (!PatchRelativeCall(g_image, kDtorCall, kBaseDtor,
                           reinterpret_cast<void*>(&FUN_1001031f)))
        return Fail("Ghidra-confirmed base-destructor callsite did not match");

    void* original = g_image + (kTarget - kBase);
    for (std::uint32_t i = 0; i < 64; ++i)
    {
        if (!RunOne(original, i, 0) || !RunOne(original, i, 1))
        {
            std::fprintf(stderr, "vtable/destruction differential mismatch at case %u\n", i);
            return 1;
        }
    }
    VirtualFree(g_image, 0, MEM_RELEASE);
    std::puts("10001010 vtable/destruction differential: 128/128 cases matched");
    return 0;
}
