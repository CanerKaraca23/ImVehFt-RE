#include <cstddef>
#include <cstdint>

#include <corecrt.h>
#include <Windows.h>
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using undefined8 = std::uint64_t;
struct TidDataExceptionView
{
    std::uint8_t reserved_00[0x5c];
    unsigned long* pxcptacttab;
    static_assert(sizeof(unsigned long) == 4);
    void* tpxcptinfoptrs;
    int tfpecode;
};

static_assert(offsetof(TidDataExceptionView, pxcptacttab) == 0x5c);
static_assert(offsetof(TidDataExceptionView, tpxcptinfoptrs) == 0x60);
static_assert(offsetof(TidDataExceptionView, tfpecode) == 0x64);

extern "C" TidDataExceptionView* __cdecl __getptd_noexit(void);

extern "C" int __cdecl __XcptFilter(
    unsigned long _ExceptionNum,
    _EXCEPTION_POINTERS* _ExceptionPtr)
{
    TidDataExceptionView* ptd = __getptd_noexit();
    int result = 0;

    if (ptd != nullptr) {
        unsigned long* table = ptd->pxcptacttab;
        unsigned long* entry = table;

        do {
            if (*entry == _ExceptionNum) {
                break;
            }

            entry += 3;
        } while (entry < table + 0x24);

        if (entry >= table + 0x24 || *entry != _ExceptionNum) {
            entry = nullptr;
        }

        using XcptAction = void(__cdecl*)(unsigned long, ...);
        XcptAction action =
            (entry != nullptr)
                ? reinterpret_cast<XcptAction>(entry[2])
                : nullptr;

        if (entry == nullptr || action == nullptr) {
            result = 0;
        }
        else if (reinterpret_cast<unsigned long>(action) == 0x5) {
            entry[2] = 0;
            result = 1;
        }
        else {
            if (reinterpret_cast<unsigned long>(action) != 0x1) {
                void* previousExceptionInfo = ptd->tpxcptinfoptrs;
                ptd->tpxcptinfoptrs = _ExceptionPtr;

                if (entry[1] == 8) {
                    for (int offset = 0x24; offset < 0x90; offset += 0x0c) {
                        *reinterpret_cast<unsigned long*>(
                            reinterpret_cast<unsigned char*>(ptd->pxcptacttab) +
                            offset + 8) = 0;
                    }

                    unsigned long exceptionNumber = *entry;
                    int previousFpCode = ptd->tfpecode;

                    if (exceptionNumber == 0xc000008e) {
                        ptd->tfpecode = 0x83;
                    }
                    else if (exceptionNumber == 0xc0000090) {
                        ptd->tfpecode = 0x81;
                    }
                    else if (exceptionNumber == 0xc0000091) {
                        ptd->tfpecode = 0x84;
                    }
                    else if (exceptionNumber == 0xc0000093) {
                        ptd->tfpecode = 0x85;
                    }
                    else if (exceptionNumber == 0xc000008d) {
                        ptd->tfpecode = 0x82;
                    }
                    else if (exceptionNumber == 0xc000008f) {
                        ptd->tfpecode = 0x86;
                    }
                    else if (exceptionNumber == 0xc0000092) {
                        ptd->tfpecode = 0x8a;
                    }
                    else if (exceptionNumber == 0xc00002b5) {
                        ptd->tfpecode = 0x8d;
                    }
                    else if (exceptionNumber == 0xc00002b4) {
                        ptd->tfpecode = 0x8e;
                    }

                    action(8, static_cast<unsigned long>(ptd->tfpecode));
                    ptd->tfpecode = previousFpCode;
                }
                else {
                    entry[2] = 0;
                    action(entry[1]);
                }

                ptd->tpxcptinfoptrs = previousExceptionInfo;
            }

            result = -1;
        }
    }

    return result;
}