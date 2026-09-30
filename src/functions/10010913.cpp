#include <cstddef>
#include <cstdint>

struct _iobuf
{
    unsigned char _reserved[0x0C];
    unsigned int _flag;
};
using FILE = _iobuf;

extern "C" void __cdecl __SEH_prolog4(std::uint32_t scope_table, int frame_size);
extern "C" void __stdcall __SEH_epilog4(void);
extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
int __cdecl __fileno(FILE*);
extern "C" std::size_t __cdecl _strlen(char*);
void __cdecl __lock_file(FILE*);
extern "C" int __cdecl __stbuf(FILE*);
std::size_t __cdecl __fwrite_nolock(void*, std::size_t, std::size_t, FILE*);
extern "C" void __cdecl __ftbuf(int, FILE*);
extern "C" void __stdcall FUN_10010a11(void);

extern unsigned char DAT_10029450;
extern unsigned char* DAT_1003C420[32];

extern "C" __declspec(naked) int __cdecl fputs(char*, FILE*)
{
    __asm
    {
        push 10h
        push 10028268h
        call __SEH_prolog4

        xor eax, eax
        cmp dword ptr [ebp + 8], eax
        setnz al
        test eax, eax
        jnz fputs_has_string

    fputs_invalid:
        call __errno
        mov dword ptr [eax], 16h
        call FUN_1001189f
        or eax, 0FFFFFFFFh
        jmp fputs_epilog

    fputs_has_string:
        xor eax, eax
        mov edi, dword ptr [ebp + 0Ch]
        test edi, edi
        setnz al
        test eax, eax
        jz fputs_invalid
        test byte ptr [edi + 0Ch], 40h
        jnz fputs_write

        push edi
        call __fileno
        pop ecx
        cmp eax, 0FFFFFFFFh
        jz fputs_special_stream_first
        cmp eax, 0FFFFFFFEh
        jz fputs_special_stream_first
        mov edx, eax
        sar edx, 5
        mov ecx, eax
        and ecx, 1Fh
        shl ecx, 6
        add ecx, dword ptr [edx * 4 + 1003C420h]
        jmp fputs_check_stream_first

    fputs_special_stream_first:
        mov ecx, 10029450h

    fputs_check_stream_first:
        test byte ptr [ecx + 24h], 7Fh
        jnz fputs_invalid
        cmp eax, 0FFFFFFFFh
        jz fputs_special_stream_second
        cmp eax, 0FFFFFFFEh
        jz fputs_special_stream_second
        mov ecx, eax
        sar ecx, 5
        and eax, 1Fh
        shl eax, 6
        add eax, dword ptr [ecx * 4 + 1003C420h]
        jmp fputs_check_stream_second

    fputs_special_stream_second:
        mov eax, 10029450h

    fputs_check_stream_second:
        test byte ptr [eax + 24h], 80h
        jnz fputs_invalid

    fputs_write:
        push dword ptr [ebp + 8]
        call _strlen
        mov dword ptr [ebp - 1Ch], eax
        push edi
        call __lock_file
        pop ecx
        pop ecx
        and dword ptr [ebp - 4], 0
        push edi
        call __stbuf
        mov esi, eax
        push edi
        push dword ptr [ebp - 1Ch]
        push 1
        push dword ptr [ebp + 8]
        call __fwrite_nolock
        mov dword ptr [ebp - 20h], eax
        push edi
        push esi
        call __ftbuf
        add esp, 1Ch
        mov dword ptr [ebp - 4], 0FFFFFFFEh
        call FUN_10010a11
        xor eax, eax
        mov ecx, dword ptr [ebp - 1Ch]
        cmp dword ptr [ebp - 20h], ecx
        setz al
        dec eax

    fputs_epilog:
        call __SEH_epilog4
        ret
    }
}
