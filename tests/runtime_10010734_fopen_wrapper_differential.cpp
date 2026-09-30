#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern "C" FILE* __cdecl fopen(char const*, char const*);
FILE* __cdecl __fsopen(char*, char*, int);

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kOriginalEntry = 0x10010734;
constexpr std::uint32_t kOriginalCall = 0x10010741;
constexpr std::uint32_t kExpectedFsopen = 0x10010678;
constexpr std::uint32_t kShareFlag = 0x40;

struct Invocation
{
    std::int32_t esp_after_call;
    std::int32_t esp_after_caller_cleanup;
    std::uint32_t result;
};

struct Capture
{
    std::uint32_t calls;
    char* filename;
    char* mode;
    int share_flag;
};

Capture g_capture{};
volatile std::uint32_t g_esp_before = 0;

extern "C" __declspec(naked) void __cdecl InvokeRaw(
    std::uint32_t, char*, char*, Invocation*)
{
    __asm {
        push ebp
        mov ebp, esp
        mov dword ptr [g_esp_before], esp
        push dword ptr [ebp + 10h]
        push dword ptr [ebp + 0Ch]
        mov eax, dword ptr [ebp + 8]
        call eax
        mov edx, esp
        sub edx, dword ptr [g_esp_before]
        mov ecx, dword ptr [ebp + 14h]
        mov dword ptr [ecx], edx
        mov dword ptr [ecx + 8], eax
        add esp, 8
        mov edx, esp
        sub edx, dword ptr [g_esp_before]
        mov dword ptr [ecx + 4], edx
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

bool RedirectOriginalFsopen(std::uint8_t* image)
{
    auto* const call = image + (kOriginalCall - kImageBase);
    if (call[0] != 0xE8)
        return false;
    std::int32_t old_relative = 0;
    std::memcpy(&old_relative, call + 1, sizeof(old_relative));
    if (static_cast<std::int64_t>(kOriginalCall) + 5 + old_relative !=
        kExpectedFsopen)
        return false;
    auto const replacement = static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(&__fsopen) -
        reinterpret_cast<std::uintptr_t>(call + 5));
    std::memcpy(call + 1, &replacement, sizeof(replacement));
    return FlushInstructionCache(GetCurrentProcess(), call, 5) != FALSE;
}

bool SameCapture(Capture const& left, Capture const& right)
{
    return left.calls == right.calls && left.filename == right.filename &&
           left.mode == right.mode && left.share_flag == right.share_flag;
}
} // namespace

FILE* __cdecl __fsopen(char* filename, char* mode, int share_flag)
{
    ++g_capture.calls;
    g_capture.filename = filename;
    g_capture.mode = mode;
    g_capture.share_flag = share_flag;
    return reinterpret_cast<FILE*>(static_cast<std::uintptr_t>(0x13572468u));
}

int main(int argc, char** argv)
{
    static_assert(sizeof(void*) == 4, "Run this harness as PE32/x86.");
    if (argc != 2)
    {
        std::fprintf(stderr, "usage: harness <ImVehFt.asi>\n");
        return 2;
    }

    auto* const reference = MapReference(argv[1]);
    if (!reference || !RedirectOriginalFsopen(reference))
    {
        std::fprintf(stderr, "Could not map reference or verify original __fsopen call.\n");
        return 3;
    }

    struct TestCase
    {
        char filename[80];
        char mode[16];
    } cases[] = {
        {"C:\\mods\\vehicle.dat", "rb"},
        {"relative path with spaces.ini", "w"},
        {"", "a+"},
        {"unicode-placeholder-\xC3\xA9.bin", "r+b"},
        {"nested\\folder\\texture.txd", "x"},
    };

    auto const candidate_address = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&fopen));
    for (std::uint32_t i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i)
    {
        auto* const filename = cases[i].filename;
        auto* const mode = cases[i].mode;
        Invocation original{}, candidate{};

        g_capture = {};
        InvokeRaw(kOriginalEntry, filename, mode, &original);
        Capture const original_capture = g_capture;

        g_capture = {};
        InvokeRaw(candidate_address, filename, mode, &candidate);
        Capture const candidate_capture = g_capture;

        if (!SameCapture(original_capture, candidate_capture) ||
            original_capture.calls != 1 || original_capture.filename != filename ||
            original_capture.mode != mode ||
            original_capture.share_flag != static_cast<int>(kShareFlag) ||
            original.result != 0x13572468u || candidate.result != original.result ||
            original.esp_after_call != -8 || candidate.esp_after_call != -8 ||
            original.esp_after_caller_cleanup != 0 ||
            candidate.esp_after_caller_cleanup != 0)
        {
            std::fprintf(stderr, "Mismatch in case %u.\n", i);
            VirtualFree(reference, 0, MEM_RELEASE);
            return 4;
        }
    }

    VirtualFree(reference, 0, MEM_RELEASE);
    std::printf("PASS: %u original/candidate wrapper cases; filename, mode, share flag 0x40, return value, and cdecl stack cleanup matched.\n",
                static_cast<unsigned>(sizeof(cases) / sizeof(cases[0])));
    std::puts("LIMIT: __fsopen was redirected to a recorder; file-system/CRT behavior was not exercised.");
    return 0;
}
