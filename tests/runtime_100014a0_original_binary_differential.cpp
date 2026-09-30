#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <exception>
#include <vector>

struct ExceptionStorage
{
    ExceptionStorage* __thiscall copy_construct(ExceptionStorage* source);
    std::uint32_t words[3];
};

struct FUN_100014a0_this
{
    void* __thiscall FUN_100014a0(std::exception* source);
};

extern "C" std::uint8_t IVF_RELOC_TARGET_10022250[4];
std::uint8_t IVF_RELOC_TARGET_10022250[4] = {};

namespace
{
constexpr std::uint32_t kBase = 0x10000000;
constexpr std::uint32_t kTarget = 0x100014a0;
constexpr std::uint32_t kBadAllocVtable = 0x10022250;
constexpr std::uint32_t kExceptionStringCtor = 0x100102c3;
constexpr std::uint32_t kExceptionDtor = 0x1001031f;
constexpr std::uint32_t kExceptionCopyCtor = 0x10010351;
constexpr std::uint32_t kHeapAllocIat = 0x10022040;
constexpr std::uint32_t kHeapFreeIat = 0x10022044;
constexpr std::uint32_t kCrtHeapHandle = 0x10039b90;
std::uintptr_t g_exception_copy_ctor = 0;

std::uint8_t* MapOriginal(const char* path)
{
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
        return nullptr;
    const DWORD size = GetFileSize(file, nullptr);
    if (size == INVALID_FILE_SIZE || size < sizeof(IMAGE_DOS_HEADER))
    {
        CloseHandle(file);
        return nullptr;
    }
    std::vector<std::uint8_t> bytes(size);
    DWORD read = 0;
    const BOOL ok = ReadFile(file, bytes.data(), size, &read, nullptr);
    CloseHandle(file);
    if (!ok || read != size)
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

bool InitializeMappedCrtHeap(std::uint8_t* image)
{
    HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
    if (!kernel32)
        return false;
    const auto heap_alloc = GetProcAddress(kernel32, "HeapAlloc");
    const auto heap_free = GetProcAddress(kernel32, "HeapFree");
    HANDLE process_heap = GetProcessHeap();
    if (!heap_alloc || !heap_free || !process_heap)
        return false;

    const std::uint32_t alloc_address = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(heap_alloc));
    const std::uint32_t free_address = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(heap_free));
    const std::uint32_t heap_address = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(process_heap));
    std::memcpy(image + (kHeapAllocIat - kBase), &alloc_address, 4);
    std::memcpy(image + (kHeapFreeIat - kBase), &free_address, 4);
    std::memcpy(image + (kCrtHeapHandle - kBase), &heap_address, 4);
    return true;
}

bool RunCase(void* original, void* image, std::uint32_t i)
{
    alignas(4) std::uint32_t source[3] = {};
    alignas(4) std::uint32_t original_dest[3] = {
        0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc};
    alignas(4) std::uint32_t candidate_dest[3] = {
        0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc};
    char message[96] = {};
    const unsigned length = i % 90;
    for (unsigned j = 0; j < length; ++j)
        message[j] = static_cast<char>('A' + ((i + j * 7) % 26));
    message[length] = '\0';
    char* message_pointer = message;
    using StringCtor = void*(__thiscall*)(void*, char**);
    auto string_ctor = reinterpret_cast<StringCtor>(
        static_cast<std::uint8_t*>(image) + (kExceptionStringCtor - kBase));
    if (string_ctor(source, &message_pointer) != source)
        return false;

    using Original = void*(__thiscall*)(void*, void*);
    auto original_fn = reinterpret_cast<Original>(original);
    void* original_result = original_fn(original_dest, source);
    auto* candidate = reinterpret_cast<FUN_100014a0_this*>(candidate_dest);
    void* candidate_result = candidate->FUN_100014a0(
        reinterpret_cast<std::exception*>(source));

    std::uint32_t original_vtable = 0;
    std::uint32_t candidate_vtable = 0;
    std::memcpy(&original_vtable, original_dest, sizeof(original_vtable));
    std::memcpy(&candidate_vtable, candidate_dest, sizeof(candidate_vtable));
    const bool matches = original_result == original_dest && candidate_result == candidate_dest &&
           original_vtable == kBadAllocVtable &&
           candidate_vtable == reinterpret_cast<std::uintptr_t>(
                                   IVF_RELOC_TARGET_10022250) &&
           reinterpret_cast<std::uint8_t*>(original_dest)[8] == 1 &&
           reinterpret_cast<std::uint8_t*>(candidate_dest)[8] == 1 &&
           original_dest[1] != source[1] && candidate_dest[1] != source[1] &&
           std::strcmp(reinterpret_cast<const char*>(
                           static_cast<std::uintptr_t>(original_dest[1])), message) == 0 &&
           std::strcmp(reinterpret_cast<const char*>(
                           static_cast<std::uintptr_t>(candidate_dest[1])), message) == 0 &&
           std::strcmp(reinterpret_cast<const char*>(
                           static_cast<std::uintptr_t>(original_dest[1])),
                       reinterpret_cast<const char*>(
                           static_cast<std::uintptr_t>(candidate_dest[1]))) == 0;
    if (!matches)
        std::fprintf(stderr, "orig=%p/%p cand=%p/%p ovft=%08x cvft=%08x expcv=%p odata=%08x cdata=%08x otail=%08x ctail=%08x\n",
                     original_result, original_dest, candidate_result, candidate_dest,
                     original_vtable, candidate_vtable, IVF_RELOC_TARGET_10022250,
                     original_dest[1], candidate_dest[1], original_dest[2], candidate_dest[2]);

    using Dtor = void(__fastcall*)(void*);
    auto dtor = reinterpret_cast<Dtor>(
        static_cast<std::uint8_t*>(image) + (kExceptionDtor - kBase));
    dtor(original_dest);
    dtor(candidate_dest);
    dtor(source);
    return matches;
}
} // namespace

ExceptionStorage* __thiscall ExceptionStorage::copy_construct(
    ExceptionStorage* source)
{
    using CopyCtor = ExceptionStorage*(__thiscall*)(ExceptionStorage*, ExceptionStorage*);
    auto copy_ctor = reinterpret_cast<CopyCtor>(g_exception_copy_ctor);
    return copy_ctor(this, source);
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::fprintf(stderr, "usage: harness <original ImVehFt.asi>\n");
        return 2;
    }
    auto* image = MapOriginal(argv[1]);
    if (!image || !InitializeMappedCrtHeap(image))
    {
        std::fprintf(stderr, "could not map original image or initialize the test-only heap imports\n");
        return 3;
    }
    void* original = image + (kTarget - kBase);
    g_exception_copy_ctor = reinterpret_cast<std::uintptr_t>(
        image + (kExceptionCopyCtor - kBase));
    for (std::uint32_t i = 0; i < 64; ++i)
    {
        if (!RunCase(original, image, i))
        {
            std::fprintf(stderr, "exception-copy mismatch at case %u\n", i);
            return 1;
        }
    }
    VirtualFree(image, 0, MEM_RELEASE);
    std::puts("100014a0 heap-message exception-copy differential: 64/64 cases matched");
    return 0;
}
