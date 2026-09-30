#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern "C" std::uint32_t __cdecl __except_handler4(
    void*, void*, std::uint32_t);
extern "C" std::uint32_t DAT_10029490 = 0xbb40e64eU;
extern "C" std::uint8_t IVF_RELOC_TARGET_100261E0[4] = {};
extern "C" void __fastcall __security_check_cookie(std::uintptr_t value);
extern "C" int __cdecl __IsNonwritableInCurrentImage(std::uint8_t*);

namespace
{
constexpr std::uint32_t kImageBase = 0x10000000;
constexpr std::uint32_t kHandler = 0x10012e90;
constexpr std::uint32_t kCookie = 0xbb40e64eU;
std::uint32_t g_candidate_cookie_checks = 0;
std::uint32_t g_candidate_cookie_last = 0;
int g_filter_result = 0;
extern "C" int __cdecl TestFilter() { return g_filter_result; }

std::uint8_t* MapReference(const char* path)
{
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) return nullptr;
    DWORD size = GetFileSize(file, nullptr);
    if (size == INVALID_FILE_SIZE || size < sizeof(IMAGE_DOS_HEADER))
    { CloseHandle(file); return nullptr; }
    std::vector<std::uint8_t> bytes(size);
    DWORD read = 0;
    BOOL ok = ReadFile(file, bytes.data(), size, &read, nullptr);
    CloseHandle(file);
    if (!ok || read != size) return nullptr;
    auto const* dos = reinterpret_cast<IMAGE_DOS_HEADER const*>(bytes.data());
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0) return nullptr;
    auto const* nt = reinterpret_cast<IMAGE_NT_HEADERS32 const*>(bytes.data() + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE || nt->FileHeader.Machine != IMAGE_FILE_MACHINE_I386 ||
        nt->OptionalHeader.ImageBase != kImageBase) return nullptr;
    auto* image = static_cast<std::uint8_t*>(VirtualAlloc(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(kImageBase)),
        nt->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE));
    if (image != reinterpret_cast<std::uint8_t*>(static_cast<std::uintptr_t>(kImageBase))) return nullptr;
    std::memset(image, 0, nt->OptionalHeader.SizeOfImage);
    std::memcpy(image, bytes.data(), nt->OptionalHeader.SizeOfHeaders);
    auto const* section = IMAGE_FIRST_SECTION(nt);
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section)
    {
        if (!section->SizeOfRawData) continue;
        if (section->PointerToRawData > bytes.size() || section->SizeOfRawData > bytes.size() - section->PointerToRawData ||
            section->VirtualAddress > nt->OptionalHeader.SizeOfImage || section->SizeOfRawData > nt->OptionalHeader.SizeOfImage - section->VirtualAddress)
        { VirtualFree(image, 0, MEM_RELEASE); return nullptr; }
        std::memcpy(image + section->VirtualAddress, bytes.data() + section->PointerToRawData, section->SizeOfRawData);
    }
    return image;
}

struct ExceptionRecord { std::uint32_t code, flags; };
struct ScopeHeader { std::uint32_t gs, gs_xor, eh, eh_xor; };
}

extern "C" void __fastcall __security_check_cookie(std::uintptr_t value)
{
    ++g_candidate_cookie_checks;
    g_candidate_cookie_last = static_cast<std::uint32_t>(value);
}
extern "C" int __cdecl __IsNonwritableInCurrentImage(std::uint8_t*) { return 0; }

int main(int argc, char** argv)
{
    if (argc != 2) return 2;
    auto* image = MapReference(argv[1]);
    if (!image) { std::fprintf(stderr, "cannot map reference at preferred base\n"); return 3; }
    auto* original_cookie = reinterpret_cast<std::uint32_t*>(image + (0x10029490u - kImageBase));
    if (*original_cookie != kCookie) { std::fprintf(stderr, "unexpected pinned-image EH4 cookie\n"); return 4; }

    alignas(16) struct { ScopeHeader header; std::uint32_t record[3]; } scope{
        {0xfffffffeU, 0, 0, 0}, {0xfffffffeU, 0, 0}};
    alignas(16) std::uint32_t storage[8]{};
    auto* param2 = &storage[1];
    auto* unwind_word = reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(param2) + 0x10);
    *unwind_word = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(unwind_word)) ^ kCookie;
    storage[3] = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&scope)) ^ kCookie;
    storage[4] = 0xfffffffeU;
    ExceptionRecord record{0xe0000001U, 0};

    using Handler = std::uint32_t (__cdecl*)(void*, void*, std::uint32_t);
    auto const original = reinterpret_cast<Handler>(image + (kHandler - kImageBase));
    auto const candidate = &__except_handler4;
    std::uint32_t original_result = original(&record, param2, 0x12345678U);
    std::uint32_t original_cookie_value = *original_cookie;

    storage[0] = storage[1] = storage[2] = storage[3] = storage[4] = storage[5] = 0;
    storage[3] = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&scope)) ^ DAT_10029490;
    storage[4] = 0xfffffffeU;
    *unwind_word = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(unwind_word)) ^ DAT_10029490;
    g_candidate_cookie_checks = g_candidate_cookie_last = 0;
    std::uint32_t candidate_result = candidate(&record, param2, 0x12345678U);

    if (original_cookie_value != kCookie || original_result != 1 || candidate_result != original_result ||
        g_candidate_cookie_checks != 1 || g_candidate_cookie_last != kCookie || storage[4] != 0xfffffffeU)
    {
        std::fprintf(stderr, "mismatch original=%u candidate=%u cand_cookie_checks=%u last=%08x try=%08x\n",
                     original_result, candidate_result, g_candidate_cookie_checks, g_candidate_cookie_last, storage[4]);
        return 5;
    }
    std::puts("PASS: no-scope EH4 path; return=1, try-level preserved, candidate entry cookie check=1");

    auto run_filter_case = [&](int filter_result, std::uint32_t expected) -> bool {
        scope.record[0] = 0xfffffffeU;
        scope.record[1] = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&TestFilter));
        scope.record[2] = 0x12345678U;
        g_filter_result = filter_result;
        record.code = 0xe0000001U;
        record.flags = 0;
        storage[0] = storage[1] = storage[2] = storage[3] = storage[4] = storage[5] = 0;
        storage[3] = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&scope)) ^ kCookie;
        storage[4] = 0;
        *unwind_word = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(unwind_word)) ^ kCookie;
        auto const ref_result = original(&record, param2, 0x87654321U);
        storage[0] = storage[1] = storage[2] = storage[3] = storage[4] = storage[5] = 0;
        storage[3] = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&scope)) ^ DAT_10029490;
        storage[4] = 0;
        *unwind_word = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(unwind_word)) ^ DAT_10029490;
        g_candidate_cookie_checks = g_candidate_cookie_last = 0;
        auto const cand_result = candidate(&record, param2, 0x87654321U);
        return ref_result == expected && cand_result == ref_result &&
            storage[4] == 0 && g_candidate_cookie_checks == 2 &&
            g_candidate_cookie_last == kCookie;
    };
    if (!run_filter_case(-1, 0)) {
        std::fprintf(stderr, "negative filter differential failed\n");
        return 6;
    }
    if (!run_filter_case(0, 1)) {
        std::fprintf(stderr, "zero filter differential failed\n");
        return 7;
    }
    std::puts("PASS: active-scope filter results -1 and 0; return, try-level, and EH-cookie checks matched");
    return 0;
}
