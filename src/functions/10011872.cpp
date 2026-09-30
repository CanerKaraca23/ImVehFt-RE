#include <cstdint>

extern std::uint32_t DAT_10039a04;
extern "C" void* __stdcall DecodePointer(void* pointer);
extern "C" [[noreturn]] void __cdecl __invoke_watson(
    wchar_t*, wchar_t*, wchar_t*, std::uint32_t, std::uintptr_t);

extern "C" __declspec(naked) void __stdcall FUN_10011872(
    wchar_t*, wchar_t*, wchar_t*, std::uint32_t, std::uintptr_t)
{
    __asm {
        push dword ptr [DAT_10039a04]
        call DecodePointer
        test eax, eax
        jz use_watson
        jmp eax

    use_watson:
        jmp __invoke_watson
    }
}
