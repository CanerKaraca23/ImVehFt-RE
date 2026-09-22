#include <cstdint>
#include <new>
#include <windows.h>

#include <cstddef>
#include <corecrt.h>
template<class H, class L> constexpr std::uint32_t __re_agent_concat_31(H high, L low) { return static_cast<std::uint32_t>(((static_cast<std::uint64_t>(high) & 0xffffffULL) << 8) | (static_cast<std::uint64_t>(low) & 0xffULL)); }
static_assert(__re_agent_concat_31(0x12ULL, 0x34ULL) == static_cast<std::uint32_t>((0x12ULL << 8) | 0x34ULL));
#define CONCAT31(high, low) __re_agent_concat_31((high), (low))
template<class H, class L> constexpr std::uint64_t __re_agent_concat_44(H high, L low) { return static_cast<std::uint64_t>(((static_cast<std::uint64_t>(high) & 0xffffffffULL) << 32) | (static_cast<std::uint64_t>(low) & 0xffffffffULL)); }
static_assert(__re_agent_concat_44(0x12ULL, 0x34ULL) == static_cast<std::uint64_t>((0x12ULL << 32) | 0x34ULL));
#define CONCAT44(high, low) __re_agent_concat_44((high), (low))
using undefined1 = std::uint8_t;
using undefined = unsigned char;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
using longlong = std::int64_t;
using uchar = unsigned char;
using uint = std::uint32_t;
using ulonglong = std::uint64_t;
using undefined2 = std::uint16_t;
extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
struct _iobuf {
    char* _ptr;
    int _cnt;
    char* _base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char* _tmpfname;
};
using FILE = _iobuf;
static_assert(offsetof(_iobuf, _ptr) == 0x00);
static_assert(offsetof(_iobuf, _cnt) == 0x04);
static_assert(offsetof(_iobuf, _base) == 0x08);
static_assert(offsetof(_iobuf, _flag) == 0x0c);
static_assert(sizeof(_iobuf) == 0x20);
using int3 = std::uint32_t;
using sbyte = std::int8_t;
struct _locale_record
{
    void* lc_codepage;
    std::uint8_t reserved_04[0x9c];
    char* locale_name[4];
    std::uint8_t reserved_b0[0x0c];
};
static_assert(offsetof(_locale_record, locale_name) == 0xa0);
static_assert(sizeof(_locale_record) == 0xbc);
struct _LocaleUpdate
{
    _locale_record* locinfo;
    void* mbcinfo;
    void* ptd;
    std::uint8_t updated;
    std::uint8_t reserved_0d[3];
    _LocaleUpdate() = default;
    _LocaleUpdate(_locale_t);
};
static_assert(offsetof(_LocaleUpdate, locinfo) == 0x00);
static_assert(offsetof(_LocaleUpdate, mbcinfo) == 0x04);
static_assert(offsetof(_LocaleUpdate, ptd) == 0x08);
static_assert(offsetof(_LocaleUpdate, updated) == 0x0c);
static_assert(sizeof(_LocaleUpdate) == 0x10);
using localeinfo_struct = _LocaleUpdate;
using code = int (__cdecl)(int, wchar_t*, undefined1*, _LocaleUpdate*);
struct _WhiteoutABI { unsigned int __thiscall call(FILE*); };
extern std::uint32_t DAT_10029490;
extern undefined DAT_10029450;
extern undefined* DAT_1003c420;
extern void* PTR_LAB_10029d5c;
extern "C" int __cdecl __fileno(FILE*);
extern "C" int __cdecl _isspace(int);
extern "C" int __cdecl _isdigit(int);
extern "C" int __cdecl _isleadbyte(int);
extern "C" int __cdecl _isxdigit(int);
extern "C" void __cdecl _free(void*);
extern "C" void* __cdecl _memset(void*, int, size_t);
extern "C" int __cdecl __ungetc_nolock(int, FILE*);
extern "C" std::uint32_t __fastcall __inc(undefined4, FILE*);
inline std::uint32_t __inc(void* value, FILE* file)
{
    return __inc(static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(value)), file);
}
extern "C" undefined4 __cdecl ___check_float_string(size_t, void*, int*);
extern "C" int __cdecl __mbtowc_l(wchar_t*, char*, size_t, void*);
extern "C" std::uint32_t __cdecl __hextodec(std::uint8_t);
extern "C" longlong __stdcall __allmul(std::uint32_t, int, std::uint32_t, int);
int __cdecl __input_l(FILE* _File, uchar* param_2, _locale_t _Locale, va_list _ArgList)
{
    std::uint8_t bVar1;
    std::uint8_t bVar2;
    int* piVar3;
    std::uint32_t uVar4;
    int iVar6;
    code* pcVar7;
    std::uint32_t uVar8;
    int iVar9;
    undefined* puVar10;
    // The first fastcall register is ECX, and Ghidra helper 100119b1 never
    // reads ECX; it only updates FILE* in EDX. Values below are don't-care.
    std::uint32_t pFVar12;
    std::uint8_t bVar13;
    void* _C;
    size_t sVar14;
    size_t sVar15;
    wchar_t* pwVar16;
    std::uint8_t* pbVar17;
    std::uint32_t uVar18;
    wchar_t* pwVar19;
    std::uint8_t* pbVar20;
    bool bVar21;
    longlong lVar22;
    undefined1* puVar23;
    _LocaleUpdate* plVar24;
    va_list local_204;
    _LocaleUpdate local_200;
    wchar_t local_1f0[2];
    va_list local_1ec;
    int local_1e8;
    std::uint8_t local_1e4;
    undefined1 local_1e3;
    undefined4 local_1e0;
    int local_1dc;
    std::uint8_t local_1d5;
    int local_1d4;
    int local_1d0;
    undefined8 local_1cc;
    wchar_t* local_1c4;
    std::uint8_t* local_1c0;
    FILE* local_1bc;
    std::uint32_t local_1b8;
    undefined1* local_1b4;
    int local_1b0;
    std::uint8_t local_1ac;
    char local_1ab;
    char local_1aa;
    char local_1a9;
    FILE* local_1a8;
    char local_1a1;
    int local_1a0;
    char local_199;
    std::uint32_t local_198;
    char local_191;
    int local_190;
    std::uint8_t local_189;
    undefined1 local_188[352];
    std::uint8_t local_28[32];
    std::uint32_t local_8;
    void* pvVar5;

    local_8 = DAT_10029490 ^ static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(&local_8) & 0xfffffffcU);
    local_1ec = _ArgList;
    local_204 = _ArgList;
    local_1b4 = local_188;
    local_1a8 = _File;
    local_1e0 = 0x15e;
    local_1d4 = 0;
    local_1cc = 0;
    local_1f0[0] = L'\0';
    local_1f0[1] = L'\0';
    local_198 = 0;

    if ((param_2 == (uchar*)0) || (_File == (FILE*)0)) {
        piVar3 = __errno();
        *piVar3 = 0x16;
        FUN_1001189f();
        return -1;
    }

    if ((_File->_flag & 0x40) == 0) {
        uVar4 = __fileno(_File);
        if ((uVar4 == 0xffffffff) || (uVar4 == 0xfffffffe)) {
            puVar10 = &DAT_10029450;
        } else {
            puVar10 = (undefined*)((uVar4 & 0x1f) * 0x40 +
                (&DAT_1003c420)[(int)uVar4 >> 5]);
        }

        if ((puVar10[0x24] & 0x7f) == 0) {
            if ((uVar4 == 0xffffffff) || (uVar4 == 0xfffffffe)) {
                puVar10 = &DAT_10029450;
            } else {
                puVar10 = (undefined*)((uVar4 & 0x1f) * 0x40 +
                    (&DAT_1003c420)[(int)uVar4 >> 5]);
            }
            if ((puVar10[0x24] & 0x80) == 0) goto LAB_10011ae0;
        }

        piVar3 = __errno();
        *piVar3 = 0x16;
        FUN_1001189f();
        local_1d0 = -1;
    } else {
LAB_10011ae0:
        new (&local_200) _LocaleUpdate(_Locale);
        bVar2 = *param_2;
        local_1a9 = '\0';
        local_190 = 0;
        local_1d0 = 0;

        if (bVar2 != 0) {
LAB_10011b0d:
            pvVar5 = (void*)(std::uint32_t)bVar2;
            iVar6 = _isspace((int)pvVar5);
            if (iVar6 != 0) {
                local_190 = local_190 + -1;
                uVar4 = reinterpret_cast<_WhiteoutABI*>(pvVar5)->call(local_1a8);
                if (uVar4 != 0xffffffff) __ungetc_nolock(uVar4, local_1a8);
                do {
                    param_2 = param_2 + 1;
                    iVar6 = _isspace((std::uint32_t)*param_2);
                } while (iVar6 != 0);
                goto LAB_10012945;
            }

            if (*param_2 == 0x25) {
                if (param_2[1] == 0x25) {
                    if (param_2[1] == 0x25) param_2 = param_2 + 1;
                    goto LAB_100128cf;
                }

                local_1e8 = 0;
                local_1d5 = 0;
                local_1b0 = 0;
                local_1bc = (FILE*)0;
                local_1a0 = 0;
                local_1ac = 0;
                local_1ab = '\0';
                local_1a1 = '\0';
                local_191 = '\0';
                local_1aa = '\0';
                local_199 = '\0';
                local_189 = 1;
                local_1dc = 0;

                do {
                    pbVar17 = param_2 + 1;
                    _C = (void*)(std::uint32_t)*pbVar17;
                    pvVar5 = _C;
                    iVar6 = _isdigit((int)_C);
                    pbVar20 = pbVar17;
                    if (iVar6 == 0) {
                        if (_C < (void*)0x4f) {
                            if (_C != (void*)0x4e) {
                                if (_C == (void*)0x2a) {
                                    local_1a1 = local_1a1 + '\x01';
                                } else if (_C != (void*)0x46) {
                                    if (_C == (void*)0x49) {
                                        bVar2 = param_2[2];
                                        pvVar5 = (void*)CONCAT31((int3)((std::uint32_t)pvVar5 >> 8), bVar2);
                                        if ((bVar2 == 0x36) &&
                                            (pbVar20 = param_2 + 3, *pbVar20 == 0x34))
                                            goto LAB_10011c32;
                                        if ((((((bVar2 != 0x33) ||
                                            (pbVar20 = param_2 + 3, *pbVar20 != 0x32)) &&
                                            (pbVar20 = pbVar17, bVar2 != 100)) &&
                                            (bVar2 != 0x69 && bVar2 != 0x6f)) &&
                                            bVar2 != 0x78) && bVar2 != 0x58)
                                            goto LAB_10011c8b;
                                    } else if (_C == (void*)0x4c) {
                                        local_189 = local_189 + 1;
                                    } else {
LAB_10011c8b:
                                        local_191 = local_191 + '\x01';
                                        pbVar20 = pbVar17;
                                    }
                                }
                            }
                        } else if (_C == (void*)0x68) {
                            local_189 = local_189 - 1;
                            local_199 = local_199 + -1;
                        } else {
                            if (_C == (void*)0x6c) {
                                pbVar20 = param_2 + 2;
                                if (*pbVar20 == 0x6c) {
LAB_10011c32:
                                    local_1dc = local_1dc + 1;
                                    local_1cc = 0;
                                    goto LAB_10011cb5;
                                }
                                local_189 = local_189 + 1;
                            } else if (_C != (void*)0x77) {
                                goto LAB_10011c8b;
                            }
                            local_199 = local_199 + '\x01';
                            pbVar20 = pbVar17;
                        }
                    } else {
                        local_1bc = (FILE*)((int)&local_1bc->_ptr + 1);
                        local_1a0 = local_1a0 * 10 + -0x30 + (int)_C;
                    }
LAB_10011cb5:
                    param_2 = pbVar20;
                } while (local_191 == '\0');

                if (local_1a1 == '\0') {
                    local_1c4 = *(wchar_t**)local_1ec;
                    local_204 = local_1ec;
                    local_1ec = local_1ec + 4;
                } else {
                    local_1c4 = (wchar_t*)0;
                }

                local_191 = '\0';
                if ((local_199 == '\0') &&
                    ((*pbVar20 == 0x53 || (local_199 = -1, *pbVar20 == 0x43))))
                    local_199 = '\x01';

                uVar4 = *pbVar20 | 0x20;
                local_1c0 = pbVar20;
                local_1b8 = uVar4;
                if (uVar4 != 0x6e) {
                    if ((uVar4 == 99) || (uVar4 == 0x7b)) {
                        local_190 = local_190 + 1;
                        local_198 = __inc(pvVar5, local_1a8);
                    } else {
                        local_198 = reinterpret_cast<_WhiteoutABI*>(pvVar5)->call(local_1a8);
                    }
                    if (local_198 == 0xffffffff) goto LAB_10012985;
                }

                pFVar12 = 0;
                uVar8 = local_198;
                if ((local_1bc != (FILE*)0) && (local_1a0 == 0)) goto LAB_10012970;

                if (0x6f < uVar4) {
                    if (uVar4 == 0x70) {
                        local_189 = 1;
LAB_100125fa:
                        if (local_198 == 0x2d) {
                            local_1ab = '\x01';
                        } else if (local_198 != 0x2b) goto LAB_10012641;
                        local_1a0 = local_1a0 + -1;
                        if ((local_1a0 == 0) && (local_1bc != (FILE*)0)) {
                            local_191 = '\x01';
                        } else {
                            local_190 = local_190 + 1;
                            local_198 = __inc(local_1bc, local_1a8);
                        }
                    } else {
                        if (uVar4 == 0x73) {
LAB_100121cd:
                            if ('\0' < local_199) local_1aa = '\x01';
LAB_100121dd:
                            pwVar16 = local_1c4;
                            local_190 = local_190 + -1;
                            pwVar19 = pwVar16;
                            if (local_198 != 0xffffffff) {
                                pFVar12 = 0;
                                __ungetc_nolock(local_198, local_1a8);
                            }
                            do {
                                if ((local_1bc != (FILE*)0) &&
                                    (iVar6 = local_1a0 + -1, bVar21 = local_1a0 == 0,
                                     local_1a0 = iVar6, bVar21))
                                    goto LAB_100125a8;
                                local_190 = local_190 + 1;
                                local_198 = __inc(pFVar12, local_1a8);
                                if (local_198 == 0xffffffff) goto LAB_1001258f;
                                bVar2 = (std::uint8_t)local_198;
                                pFVar12 = 0;
                                if (uVar4 != 99) {
                                    if (uVar4 == 0x73) {
                                        if ((8 < (int)local_198) && ((int)local_198 < 0xe))
                                            goto LAB_1001258f;
                                        if (local_198 != 0x20) goto LAB_1001228f;
                                    }
                                    if ((uVar4 != 0x7b) ||
                                        (pFVar12 = static_cast<std::uint32_t>(static_cast<std::int32_t>(static_cast<std::int8_t>(
                                            local_28[(int)local_198 >> 3] ^ local_1ac))),
                                         uVar4 = local_1b8,
                                         (pFVar12 & (1u << (bVar2 & 7))) == 0))
                                        goto LAB_1001258f;
                                }
LAB_1001228f:
                                if (local_1a1 == '\0') {
                                    if (local_1aa == '\0') {
                                        *(std::uint8_t*)pwVar16 = bVar2;
                                        pwVar16 = (wchar_t*)((int)pwVar16 + 1);
                                        local_1c4 = pwVar16;
                                    } else {
                                        uVar8 = local_198 & 0xff;
                                        local_1e4 = bVar2;
                                        iVar6 = _isleadbyte(uVar8);
                                        if (iVar6 != 0) {
                                            local_190 = local_190 + 1;
                                            uVar8 = __inc(uVar8, local_1a8);
                                            local_1e3 = (undefined1)uVar8;
                                        }
                                        local_1f0[0] = L'?';
                                        local_1f0[1] = L'\0';
                                        __mbtowc_l(local_1f0, (char*)&local_1e4,
                                            (size_t)(local_200.locinfo)->locale_name[3],
                                            &local_200);
                                        *pwVar16 = local_1f0[0];
                                        pwVar16 = pwVar16 + 1;
                                        pFVar12 = 0;
                                        local_1c4 = pwVar16;
                                    }
                                } else {
                                    pwVar19 = (wchar_t*)((int)pwVar19 + 1);
                                }
                            } while (true);
                        }
                        if (uVar4 == 0x75) goto LAB_100125fa;
                        if (uVar4 != 0x78) {
                            if (uVar4 == 0x7b) {
                                if ('\0' < local_199) local_1aa = '\x01';
                                pbVar20 = local_1c0 + 1;
                                if (local_1c0[1] == 0x5e) {
                                    pbVar20 = local_1c0 + 2;
                                    local_1ac = 0xff;
                                }
                                _memset(local_28, 0, 0x20);
                                pFVar12 = 0;
                                bVar2 = local_1d5;
                                if (*pbVar20 == 0x5d) {
                                    local_28[0xb] = 0x20;
                                    pbVar20 = pbVar20 + 1;
                                    bVar2 = 0x5d;
                                }
                                while (true) {
                                    bVar13 = *pbVar20;
                                    local_1c0 = pbVar20;
                                    if (bVar13 == 0x5d) break;
                                    if ((bVar13 == 0x2d) && (bVar2 != 0) &&
                                        (bVar1 = pbVar20[1], bVar1 != 0x5d)) {
                                        bVar13 = bVar1;
                                        local_189 = bVar2;
                                        if (bVar2 < bVar1) {
                                            bVar13 = bVar2;
                                            local_189 = bVar1;
                                        }
                                        if (bVar13 < local_189) {
                                            uVar18 = (std::uint32_t)bVar13;
                                            uVar8 = (std::uint32_t)(std::uint8_t)(local_189 - bVar13);
                                            do {
                                                local_28[uVar18 >> 3] =
                                                    local_28[uVar18 >> 3] |
                                                    '\x01' << ((std::uint8_t)uVar18 & 7);
                                                uVar18 = uVar18 + 1;
                                                uVar8 = uVar8 - 1;
                                                uVar4 = local_1b8;
                                            } while (uVar8 != 0);
                                        }
                                        pFVar12 = static_cast<std::uint32_t>(local_189 & 7);
                                        local_28[local_189 >> 3] =
                                            local_28[local_189 >> 3] |
                                            '\x01' << static_cast<sbyte>(pFVar12);
                                        pbVar20 = pbVar20 + 2;
                                        bVar2 = 0;
                                    } else {
                                        pFVar12 = static_cast<std::uint32_t>(bVar13 & 7);
                                        local_28[bVar13 >> 3] =
                                            local_28[bVar13 >> 3] |
                                            '\x01' << static_cast<sbyte>(pFVar12);
                                        uVar4 = local_1b8;
                                        pbVar20 = pbVar20 + 1;
                                        bVar2 = bVar13;
                                    }
                                }
                                goto LAB_100121dd;
                            }
                            goto LAB_10012343;
                        }
LAB_10011de6:
                        if (local_198 == 0x2d) {
                            local_1ab = '\x01';
LAB_10012480:
                            local_1a0 = local_1a0 + -1;
                            if ((local_1a0 == 0) && (local_1bc != (FILE*)0)) {
                                local_191 = '\x01';
                            } else {
                                local_190 = local_190 + 1;
                                local_198 = __inc(local_1bc, local_1a8);
                                pFVar12 = 0;
                            }
                        } else if (local_198 == 0x2b) {
                            goto LAB_10012480;
                        }
                        if (local_198 == 0x30) {
                            local_190 = local_190 + 1;
                            local_198 = __inc(pFVar12, local_1a8);
                            if (((char)local_198 == 'x') || ((char)local_198 == 'X')) {
                                local_190 = local_190 + 1;
                                local_198 = __inc(std::uint32_t{0}, local_1a8);
                                if ((local_1bc != (FILE*)0) &&
                                    (local_1a0 = local_1a0 + -2, local_1a0 < 1))
                                    local_191 = local_191 + '\x01';
                                local_1b8 = 0x78;
                            } else {
                                local_1b0 = 1;
                                if (local_1b8 == 0x78) {
                                    local_190 = local_190 + -1;
                                    if (local_198 != 0xffffffff)
                                        __ungetc_nolock(local_198, local_1a8);
                                    local_198 = 0x30;
                                } else {
                                    if ((local_1bc != (FILE*)0) &&
                                        (local_1a0 = local_1a0 + -1, local_1a0 == 0))
                                        local_191 = local_191 + '\x01';
                                    local_1b8 = 0x6f;
                                }
                            }
                        }
                    }

LAB_10012641:
                    if (local_1dc == 0) {
                        iVar6 = local_1e8;
                        if (local_191 == '\0') {
                            while ((uVar4 = local_198, local_1b8 != 0x78 &&
                                    (local_1b8 != 0x70))) {
                                uVar8 = local_198 & 0xff;
                                iVar9 = _isdigit(uVar8);
                                if (iVar9 == 0) goto LAB_1001282e;
                                if (local_1b8 == 0x6f) {
                                    if (0x37 < (int)uVar4) goto LAB_1001282e;
                                    iVar6 = iVar6 << 3;
                                } else {
                                    iVar6 = iVar6 * 10;
                                }
LAB_100127f5:
                                local_1b0 = local_1b0 + 1;
                                iVar6 = iVar6 + -0x30 + uVar4;
                                if ((local_1bc != (FILE*)0) &&
                                    (local_1a0 = local_1a0 + -1, local_1a0 == 0))
                                    goto LAB_10012847;
                                local_190 = local_190 + 1;
                                local_198 = __inc(uVar8, local_1a8);
                            }
                            iVar9 = _isxdigit(local_198 & 0xff);
                            if (iVar9 != 0) {
                                iVar6 = iVar6 << 4;
                                uVar8 = uVar4;
                                uVar4 = __hextodec((std::uint8_t)uVar4);
                                local_198 = uVar4;
                                goto LAB_100127f5;
                            }
LAB_1001282e:
                            local_190 = local_190 + -1;
                            if (uVar4 != 0xffffffff) __ungetc_nolock(uVar4, local_1a8);
                        }
LAB_10012847:
                        if (local_1ab != '\0') iVar6 = -iVar6;
                    } else {
                        if (local_191 == '\0') {
                            while ((uVar4 = local_198, local_1b8 != 0x78 &&
                                    (local_1b8 != 0x70))) {
                                uVar8 = local_198 & 0xff;
                                iVar6 = _isdigit(uVar8);
                                if (iVar6 == 0) goto LAB_1001273a;
                                if (local_1b8 == 0x6f) {
                                    if (0x37 < (int)uVar4) goto LAB_1001273a;
                                    lVar22 = CONCAT44(
                                        (static_cast<std::uint32_t>(static_cast<std::uint64_t>(local_1cc) >> 32) << 3) | (std::uint32_t)local_1cc >> 0x1d,
                                        (std::uint32_t)local_1cc << 3);
                                } else {
                                    lVar22 = __allmul((std::uint32_t)local_1cc,
                                        static_cast<std::uint32_t>(static_cast<std::uint64_t>(local_1cc) >> 32), 10, 0);
                                    uVar8 = 0;
                                }
LAB_100126f1:
                                local_1b0 = local_1b0 + 1;
                                local_1cc = lVar22 + (int)(uVar4 - 0x30);
                                if ((local_1bc != (FILE*)0) &&
                                    (local_1a0 = local_1a0 + -1, local_1a0 == 0))
                                    goto LAB_10012753;
                                local_190 = local_190 + 1;
                                local_198 = __inc(uVar8, local_1a8);
                            }
                            iVar6 = _isxdigit(local_198 & 0xff);
                            if (iVar6 != 0) {
                                lVar22 = CONCAT44(
                                    (static_cast<std::uint32_t>(static_cast<std::uint64_t>(local_1cc) >> 32) << 4) | (std::uint32_t)local_1cc >> 0x1c,
                                    (std::uint32_t)local_1cc << 4);
                                uVar8 = uVar4;
                                uVar4 = __hextodec((std::uint8_t)uVar4);
                                local_198 = uVar4;
                                goto LAB_100126f1;
                            }
LAB_1001273a:
                            local_190 = local_190 + -1;
                            if (uVar4 != 0xffffffff) __ungetc_nolock(uVar4, local_1a8);
                        }
LAB_10012753:
                        iVar6 = local_1e8;
                        if (local_1ab != '\0') {
                            local_1cc = CONCAT44(
                                0u - (static_cast<std::uint32_t>(static_cast<std::uint64_t>(local_1cc) >> 32) + (std::uint32_t)((std::uint32_t)local_1cc != 0)),
                                0u - (std::uint32_t)local_1cc);
                        }
                    }

                    if (local_1b8 == 0x46) local_1b0 = 0;
                    if (local_1b0 != 0) {
                        if (local_1a1 == '\0') {
                            local_1d0 = local_1d0 + 1;
LAB_10012884:
                            if (local_1dc == 0) {
                                if (local_189 == 0) *local_1c4 = (wchar_t)iVar6;
                                else *(int*)local_1c4 = iVar6;
                            } else {
                                *(std::uint32_t*)local_1c4 = (std::uint32_t)local_1cc;
                                *(int*)(local_1c4 + 2) = static_cast<std::uint32_t>(static_cast<std::uint64_t>(local_1cc) >> 32);
                            }
                        }
                        goto LAB_100128b0;
                    }
                    goto LAB_10012985;
                }

                if (uVar4 == 0x6f) goto LAB_100125fa;
                if (uVar4 == 99) {
                    if (local_1bc == (FILE*)0) {
                        local_1a0 = local_1a0 + 1;
                        local_1bc = (FILE*)1;
                    }
                    goto LAB_100121cd;
                }
                if (uVar4 == 100) goto LAB_100125fa;

                if (uVar4 < 0x65) {
LAB_10012343:
                    if (*local_1c0 != local_198) goto LAB_10012970;
                    local_1a9 = local_1a9 + -1;
                    if (local_1a1 == '\0') local_1ec = local_204;
                } else {
                    if (0x67 < uVar4) {
                        if (uVar4 == 0x69) {
                            local_1b8 = 100;
                            goto LAB_10011de6;
                        }
                        if (uVar4 != 0x6e) goto LAB_10012343;
                        iVar6 = local_190;
                        if (local_1a1 != '\0') goto LAB_100128b0;
                        goto LAB_10012884;
                    }

                    sVar14 = 0;
                    if (local_198 == 0x2d) {
                        *local_1b4 = 0x2d;
                        sVar14 = 1;
LAB_10011e21:
                        local_1a0 = local_1a0 + -1;
                        local_190 = local_190 + 1;
                        local_198 = __inc(local_1bc, local_1a8);
                    } else if (local_198 == 0x2b) goto LAB_10011e21;

                    if (local_1bc == (FILE*)0) local_1a0 = -1;
                    while (true) {
                        uVar4 = local_198 & 0xff;
                        iVar6 = _isdigit(uVar4);
                        if ((iVar6 == 0) ||
                            (iVar6 = local_1a0 + -1, bVar21 = local_1a0 == 0,
                             local_1a0 = iVar6, bVar21))
                            break;
                        local_1b0 = local_1b0 + 1;
                        local_1b4[sVar14] = (std::uint8_t)local_198;
                        sVar14 = sVar14 + 1;
                        iVar6 = ___check_float_string(sVar14, local_188, &local_1d4);
                        if (iVar6 == 0) goto LAB_10012985;
                        local_190 = local_190 + 1;
                        local_198 = __inc(std::uint32_t{0}, local_1a8);
                    }

                    local_1ac = **(std::uint8_t**)local_200.locinfo[1].lc_codepage;
                    if ((local_1ac == (std::uint8_t)local_198) &&
                        (iVar6 = local_1a0 + -1, bVar21 = local_1a0 != 0,
                         local_1a0 = iVar6, bVar21)) {
                        local_190 = local_190 + 1;
                        local_198 = __inc(uVar4, local_1a8);
                        local_1b4[sVar14] = local_1ac;
                        sVar14 = sVar14 + 1;
                        iVar6 = ___check_float_string(sVar14, local_188, &local_1d4);
                        if (iVar6 == 0) goto LAB_10012985;
                        while ((iVar6 = _isdigit(local_198 & 0xff), iVar6 != 0) &&
                               (iVar6 = local_1a0 + -1, bVar21 = local_1a0 != 0,
                                local_1a0 = iVar6, bVar21)) {
                            local_1b0 = local_1b0 + 1;
                            local_1b4[sVar14] = (std::uint8_t)local_198;
                            sVar14 = sVar14 + 1;
                            iVar6 = ___check_float_string(sVar14, local_188, &local_1d4);
                            if (iVar6 == 0) goto LAB_10012985;
                            local_190 = local_190 + 1;
                            local_198 = __inc(std::uint32_t{0}, local_1a8);
                        }
                    }

                    sVar15 = sVar14;
                    if ((local_1b0 != 0) &&
                        (((local_198 == 0x65 || (local_198 == 0x45)) &&
                          (iVar6 = local_1a0 + -1, bVar21 = local_1a0 != 0,
                           local_1a0 = iVar6, bVar21)))) {
                        local_1b4[sVar14] = 0x65;
                        sVar15 = sVar14 + 1;
                        iVar6 = ___check_float_string(sVar15, local_188, &local_1d4);
                        if (iVar6 == 0) goto LAB_10012985;
                        local_190 = local_190 + 1;
                        local_198 = __inc(std::uint32_t{0}, local_1a8);
                        if (local_198 == 0x2d) {
                            local_1b4[sVar15] = 0x2d;
                            sVar15 = sVar14 + 2;
                            iVar6 = ___check_float_string(sVar15, local_188, &local_1d4);
                            if (iVar6 == 0) goto LAB_10012985;
LAB_10012092:
                            if (local_1a0 == 0) {
                                local_1a0 = 0;
                            } else {
                                local_190 = local_190 + 1;
                                local_1a0 = local_1a0 + -1;
                                local_198 = __inc(std::uint32_t{0}, local_1a8);
                            }
                        } else {
                            if (local_198 == 0x2b) goto LAB_10012092;
                        }
                        while ((iVar6 = _isdigit(local_198 & 0xff), iVar6 != 0) &&
                               (iVar6 = local_1a0 + -1, bVar21 = local_1a0 != 0,
                                local_1a0 = iVar6, bVar21)) {
                            local_1b0 = local_1b0 + 1;
                            local_1b4[sVar15] = (std::uint8_t)local_198;
                            sVar15 = sVar15 + 1;
                            iVar6 = ___check_float_string(sVar15, local_188, &local_1d4);
                            if (iVar6 == 0) goto LAB_10012985;
                            local_190 = local_190 + 1;
                            local_198 = __inc(std::uint32_t{0}, local_1a8);
                        }
                    }

                    local_190 = local_190 + -1;
                    if (local_198 != 0xffffffff) __ungetc_nolock(local_198, local_1a8);
                    if (local_1b0 == 0) goto LAB_10012985;
                    if (local_1a1 == '\0') {
                        local_1d0 = local_1d0 + 1;
                        plVar24 = &local_200;
                        local_1b4[sVar15] = 0;
                        iVar6 = (char)local_189 + -1;
                        pwVar16 = local_1c4;
                        puVar23 = local_1b4;
                        pcVar7 = reinterpret_cast<code*>(DecodePointer(PTR_LAB_10029d5c));
                        (*pcVar7)(iVar6, pwVar16, puVar23, plVar24);
                    }
                }
LAB_100128b0:
                local_1a9 = local_1a9 + '\x01';
                pbVar20 = local_1c0 + 1;
                local_1c0 = pbVar20;
LAB_10012929:
                param_2 = pbVar20;
                if ((local_198 == 0xffffffff) &&
                    ((*pbVar20 != 0x25) || (param_2 = local_1c0, local_1c0[1] != 0x6e)))
                    goto LAB_10012985;
LAB_10012945:
                bVar2 = *param_2;
                if (bVar2 == 0) goto LAB_10012985;
                goto LAB_10011b0d;
            }

LAB_100128cf:
            local_190 = local_190 + 1;
            uVar8 = __inc(pvVar5, local_1a8);
            pbVar20 = param_2 + 1;
            local_1c0 = pbVar20;
            local_198 = uVar8;
            if (*param_2 == uVar8) {
                uVar4 = uVar8 & 0xff;
                iVar6 = _isleadbyte(uVar4);
                if (iVar6 != 0) {
                    local_190 = local_190 + 1;
                    uVar4 = __inc(uVar4, local_1a8);
                    bVar2 = *pbVar20;
                    pbVar20 = param_2 + 2;
                    local_1c0 = pbVar20;
                    if (bVar2 != uVar4) {
                        if (uVar4 != 0xffffffff) __ungetc_nolock(uVar4, local_1a8);
                        goto LAB_10012970;
                    }
                    local_190 = local_190 + -1;
                }
                goto LAB_10012929;
            }
LAB_10012970:
            if (uVar8 != 0xffffffff) __ungetc_nolock(local_198, local_1a8);
LAB_10012985:
            if (local_1d4 == 1) _free(local_1b4);
            if (local_198 == 0xffffffff) {
                if ((local_1d0 == 0) && (local_1a9 == '\0')) local_1d0 = -1;
                if (local_200.updated == 0) return local_1d0;
                auto* locale_thread_data = reinterpret_cast<std::uint32_t*>(
                    reinterpret_cast<std::uintptr_t>(local_200.ptd) + 0x70);
                *locale_thread_data &= 0xfffffffd;
                return local_1d0;
            }
        }
        if (local_200.updated != 0) {
            auto* locale_thread_data = reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uintptr_t>(local_200.ptd) + 0x70);
            *locale_thread_data &= 0xfffffffd;
        }
    }
    return local_1d0;

LAB_1001258f:
    local_190 = local_190 + -1;
    if (local_198 != 0xffffffff) __ungetc_nolock(local_198, local_1a8);
LAB_100125a8:
    if (pwVar19 == pwVar16) goto LAB_10012985;
    if ((local_1a1 == '\0') && (local_1d0 = local_1d0 + 1, uVar4 != 99)) {
        if (local_1aa == '\0') *(std::uint8_t*)local_1c4 = 0;
        else *local_1c4 = L'\0';
    }
    goto LAB_100128b0;
}