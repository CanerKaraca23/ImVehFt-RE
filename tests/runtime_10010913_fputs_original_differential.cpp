#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

struct _iobuf
{
    std::uint8_t reserved[0x0C];
    std::uint32_t _flag;
};
using FILE = _iobuf;

extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
int __cdecl __fileno(FILE*);
extern "C" std::size_t __cdecl _strlen(char*);
void __cdecl __lock_file(FILE*);
extern "C" int __cdecl __stbuf(FILE*);
std::size_t __cdecl __fwrite_nolock(void*, std::size_t, std::size_t, FILE*);
extern "C" void __cdecl __ftbuf(int, FILE*);
extern "C" void __stdcall FUN_10010a11(void);
extern "C" int __cdecl fputs(char*, FILE*);

extern "C" __declspec(naked) void __cdecl __SEH_prolog4(std::uint32_t, int)
{
    __asm
    {
        push 10012e20h
        ret
    }
}

extern "C" __declspec(naked) void __stdcall __SEH_epilog4(void)
{
    __asm
    {
        push 10012e65h
        ret
    }
}

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kFunctionAddress = 0x10010913;
constexpr std::uint32_t kErrnoAddress = 0x100118f1;
constexpr std::uint32_t kInvalidParameterAddress = 0x1001189f;
constexpr std::uint32_t kFilenoAddress = 0x1001358e;
constexpr std::uint32_t kStrlenAddress = 0x10011650;
constexpr std::uint32_t kLockFileAddress = 0x100130f6;
constexpr std::uint32_t kStbufAddress = 0x10013f33;
constexpr std::uint32_t kFwriteAddress = 0x10014003;
constexpr std::uint32_t kFtbufAddress = 0x10013fcf;
constexpr std::uint32_t kFlushAddress = 0x10010a11;
constexpr std::uint32_t kStreamInfoAddress = 0x10029450;
constexpr std::uint32_t kFileInfoTableAddress = 0x1003c420;
constexpr std::uint32_t kFunctionRva = kFunctionAddress - kImageBase;
constexpr std::uint32_t kFileInfoFlagsOffset = 0x24;

struct Effects
{
    std::uint32_t errno_value = 0;
    int descriptor = 0;
    int stream_flags = 0;
    int second_stream_flags = 0;
    int stbuf_value = 0;
    int fwrite_limit = -1;
    int invalid_parameter_calls = 0;
    int lock_calls = 0;
    int ftbuf_calls = 0;
    int flush_calls = 0;
    std::uint32_t ftbuf_flag = 0;
    std::uint32_t bytes_written = 0;
    char output[256]{};
    char trace[32]{};
    std::uint32_t trace_length = 0;
};

Effects g_effects;
std::uint8_t* g_image = nullptr;
std::uint8_t* g_fixture = nullptr;
const char* g_failed_case = nullptr;

using Fputs = int(__cdecl*)(char*, FILE*);

std::uint8_t* MapOriginal(const char* path)
{
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) return nullptr;
    const DWORD size = GetFileSize(file, nullptr);
    if (size == INVALID_FILE_SIZE || size < sizeof(IMAGE_DOS_HEADER))
    {
        CloseHandle(file);
        return nullptr;
    }
    auto* bytes = new std::uint8_t[size];
    DWORD read = 0;
    const BOOL ok = ReadFile(file, bytes, size, &read, nullptr);
    CloseHandle(file);
    if (!ok || read != size)
    {
        delete[] bytes;
        return nullptr;
    }
    const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(bytes);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0)
    {
        delete[] bytes;
        return nullptr;
    }
    const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(bytes + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.ImageBase != kImageBase)
    {
        delete[] bytes;
        return nullptr;
    }
    auto* image = static_cast<std::uint8_t*>(VirtualAlloc(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(kImageBase)),
        nt->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE));
    if (image != reinterpret_cast<std::uint8_t*>(
                     static_cast<std::uintptr_t>(kImageBase)))
    {
        delete[] bytes;
        return nullptr;
    }
    std::memset(image, 0, nt->OptionalHeader.SizeOfImage);
    std::memcpy(image, bytes, nt->OptionalHeader.SizeOfHeaders);
    auto* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
    {
        if (!section->SizeOfRawData) continue;
        if (section->PointerToRawData > size ||
            section->SizeOfRawData > size - section->PointerToRawData ||
            section->VirtualAddress > nt->OptionalHeader.SizeOfImage ||
            section->SizeOfRawData > nt->OptionalHeader.SizeOfImage - section->VirtualAddress)
        {
            VirtualFree(image, 0, MEM_RELEASE);
            delete[] bytes;
            return nullptr;
        }
        std::memcpy(image + section->VirtualAddress,
                    bytes + section->PointerToRawData, section->SizeOfRawData);
    }
    delete[] bytes;
    return image;
}

bool PatchJump(std::uint32_t address, const void* target)
{
    auto* site = reinterpret_cast<std::uint8_t*>(static_cast<std::uintptr_t>(address));
    const auto destination = reinterpret_cast<std::uintptr_t>(target);
    const auto displacement = static_cast<std::int32_t>(destination - (address + 5u));
    DWORD old_protection = 0;
    if (!VirtualProtect(site, 5, PAGE_EXECUTE_READWRITE, &old_protection)) return false;
    site[0] = 0xE9;
    std::memcpy(site + 1, &displacement, sizeof(displacement));
    FlushInstructionCache(GetCurrentProcess(), site, 5);
    DWORD ignored = 0;
    VirtualProtect(site, 5, old_protection, &ignored);
    return true;
}

bool PatchOriginalHelpers()
{
    return PatchJump(kErrnoAddress, reinterpret_cast<const void*>(&__errno)) &&
           PatchJump(kInvalidParameterAddress, reinterpret_cast<const void*>(&FUN_1001189f)) &&
           PatchJump(kFilenoAddress, reinterpret_cast<const void*>(&__fileno)) &&
           PatchJump(kStrlenAddress, reinterpret_cast<const void*>(&_strlen)) &&
           PatchJump(kLockFileAddress, reinterpret_cast<const void*>(&__lock_file)) &&
           PatchJump(kStbufAddress, reinterpret_cast<const void*>(&__stbuf)) &&
           PatchJump(kFwriteAddress, reinterpret_cast<const void*>(&__fwrite_nolock)) &&
           PatchJump(kFtbufAddress, reinterpret_cast<const void*>(&__ftbuf)) &&
           PatchJump(kFlushAddress, reinterpret_cast<const void*>(&FUN_10010a11));
}

void Reset(std::uint32_t file_info_flags)
{
    g_effects = Effects{};
    g_effects.descriptor = 0;
    auto* table = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(kFileInfoTableAddress));
    table[0] = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(g_fixture));
    table[1] = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(g_fixture));
    std::memset(g_fixture, 0, 0x80);
    *reinterpret_cast<std::uint32_t*>(g_fixture + kFileInfoFlagsOffset) = file_info_flags;
    *reinterpret_cast<std::uint32_t*>(static_cast<std::uintptr_t>(
        kStreamInfoAddress + kFileInfoFlagsOffset)) = 0;
}

bool SameEffects(const Effects& left, const Effects& right)
{
    return left.errno_value == right.errno_value &&
           left.invalid_parameter_calls == right.invalid_parameter_calls &&
           left.lock_calls == right.lock_calls && left.ftbuf_calls == right.ftbuf_calls &&
           left.flush_calls == right.flush_calls && left.ftbuf_flag == right.ftbuf_flag &&
           left.bytes_written == right.bytes_written &&
           std::memcmp(left.output, right.output, sizeof(left.output)) == 0 &&
           left.trace_length == right.trace_length &&
           std::memcmp(left.trace, right.trace, sizeof(left.trace)) == 0;
}

void Record(char event)
{
    if (g_effects.trace_length < sizeof(g_effects.trace))
        g_effects.trace[g_effects.trace_length++] = event;
}

bool RunPair(const char* label, char* text, FILE* stream,
             int descriptor, std::uint32_t file_info_flags,
             std::uint32_t stream_flags, int fwrite_limit)
{
    g_effects.descriptor = descriptor;
    g_effects.fwrite_limit = fwrite_limit;
    Reset(file_info_flags);
    g_effects.descriptor = descriptor;
    g_effects.fwrite_limit = fwrite_limit;
    if (stream) stream->_flag = stream_flags;
    const auto original_fn = reinterpret_cast<Fputs>(
        static_cast<std::uintptr_t>(kFunctionAddress));
    const int original_result = original_fn(text, stream);
    const Effects original_effects = g_effects;

    Reset(file_info_flags);
    g_effects.descriptor = descriptor;
    g_effects.fwrite_limit = fwrite_limit;
    if (stream) stream->_flag = stream_flags;
    const int candidate_result = fputs(text, stream);
    const Effects candidate_effects = g_effects;
    if (original_result != candidate_result || !SameEffects(original_effects, candidate_effects))
    {
        g_failed_case = label;
        return false;
    }
    return true;
}
} // namespace

extern "C" int* __cdecl __errno(void)
{
    Record('E');
    return reinterpret_cast<int*>(&g_effects.errno_value);
}
extern "C" void __stdcall FUN_1001189f(void)
{
    Record('I');
    ++g_effects.invalid_parameter_calls;
}
int __cdecl __fileno(FILE*)
{
    Record('F');
    return g_effects.descriptor;
}
extern "C" std::size_t __cdecl _strlen(char* text)
{
    Record('N');
    return std::strlen(text);
}
void __cdecl __lock_file(FILE*)
{
    Record('L');
    ++g_effects.lock_calls;
}
extern "C" int __cdecl __stbuf(FILE*)
{
    Record('S');
    return g_effects.stbuf_value;
}
std::size_t __cdecl __fwrite_nolock(void* text, std::size_t size,
                                    std::size_t count, FILE*)
{
    Record('W');
    const auto bytes = size * count;
    const auto written = g_effects.fwrite_limit < 0
        ? bytes
        : (bytes < static_cast<std::size_t>(g_effects.fwrite_limit)
               ? bytes : static_cast<std::size_t>(g_effects.fwrite_limit));
    g_effects.bytes_written = static_cast<std::uint32_t>(written);
    const auto copy = written < sizeof(g_effects.output) - 1
        ? written : sizeof(g_effects.output) - 1;
    std::memcpy(g_effects.output, text, copy);
    g_effects.output[copy] = '\0';
    return size == 0 ? 0 : written / size;
}
extern "C" void __cdecl __ftbuf(int flag, FILE*)
{
    Record('T');
    ++g_effects.ftbuf_calls;
    g_effects.ftbuf_flag = static_cast<std::uint32_t>(flag);
}
extern "C" void __stdcall FUN_10010a11(void)
{
    Record('X');
    ++g_effects.flush_calls;
}

int main(int argc, char** argv)
{
    if (argc != 2) return 2;
    g_image = MapOriginal(argv[1]);
    if (!g_image || !PatchOriginalHelpers()) return 3;
    g_fixture = static_cast<std::uint8_t*>(VirtualAlloc(nullptr, 0x1000,
        MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
    if (!g_fixture) return 4;

    FILE stream{};
    char text[] = "controlled fputs payload";
    const bool passed =
        RunPair("valid-flag-full-write", text, &stream, 0, 0, 0x40, -1) &&
        RunPair("valid-flag-short-write", text, &stream, 0, 0, 0x40, 7) &&
        RunPair("normal-descriptor-stream", text, &stream, 0, 0, 0, -1) &&
        RunPair("second-descriptor-page", text, &stream, 32, 0, 0, -1) &&
        RunPair("invalid-descriptor-flags", text, &stream, 0, 0x02, 0, -1) &&
        RunPair("invalid-second-stream-flags", text, &stream, -1, 0x80, 0, -1) &&
        RunPair("special-stream-minus-one", text, &stream, -1, 0, 0, -1) &&
        RunPair("special-stream-minus-two", text, &stream, -2, 0, 0, -1) &&
        RunPair("null-text", nullptr, &stream, 0, 0, 0x40, -1) &&
        RunPair("null-stream", text, nullptr, 0, 0, 0x40, -1);

    VirtualFree(g_fixture, 0, MEM_RELEASE);
    VirtualFree(g_image, 0, MEM_RELEASE);
    if (!passed)
    {
        OutputDebugStringA(g_failed_case ? g_failed_case : "setup");
        static constexpr char message[] = "FAIL: 0x10010913 original-vs-candidate mismatch.\r\n";
        DWORD written = 0;
        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), message, sizeof(message) - 1, &written, nullptr);
        return 1;
    }
    static constexpr char message[] = "PASS: 0x10010913 original-vs-candidate matched 10 controlled cases.\r\n";
    DWORD written = 0;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), message, sizeof(message) - 1, &written, nullptr);
    return 0;
}
