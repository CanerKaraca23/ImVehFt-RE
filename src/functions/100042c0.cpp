#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" {

using u32 = std::uint32_t;
using i32 = std::int32_t;
using u16 = std::uint16_t;
using u8  = std::uint8_t;

extern i32 DAT_1003c248;
extern u16 DAT_1003bd8c;
extern u32 DAT_1003b700[];
extern i32* DAT_1003c25c;
extern i32* _DAT_00b74494;
extern i32 _DAT_1003b6f8;
extern i32 _DAT_1003c1e8;

extern "C" i32 __stdcall FUN_10009360();
void FUN_10010756(void*);
extern "C" u32 __cdecl FUN_10010230(std::size_t);

void FUN_10004430();

using AddressCall1 = void(__cdecl*)(u32);
using AddressCall3 = void(__cdecl*)(u32, void(*)(), void*);
using ThisCall = void(__thiscall*)(void*, u32);

}

struct __single_inheritance FUN_100042c0_this {
    void __thiscall FUN_100042c0(u32 param_1);
};

void FUN_100042c0_this::FUN_100042c0(u32 param_1)
{
    void* self = static_cast<void*>(this);
    reinterpret_cast<void(__cdecl*)(unsigned int)>(0x6d10e0)(param_1);

    const int baseOffset = DAT_1003c248;
    const int manager = FUN_10009360();

    const int objectIndex =
        (static_cast<int>(reinterpret_cast<unsigned long>(self)) -
         *_DAT_00b74494) /
        0xa18;

    const int objectBase =
        *reinterpret_cast<int*>(
            *reinterpret_cast<int*>(manager + 0x48) +
            objectIndex * 4);

    _DAT_1003b6f8 =
        *reinterpret_cast<int*>(
            reinterpret_cast<unsigned long>(self) + 0x18);

    const int state = objectBase + baseOffset;

    const unsigned int callbackContext =
        *reinterpret_cast<unsigned int*>(
            static_cast<unsigned long>(_DAT_1003b6f8) + 4);

    _DAT_1003c1e8 = state;

    reinterpret_cast<void*(__cdecl*)(void*, int, unsigned long)>(
        0x10016740)(
        *reinterpret_cast<void**>(objectBase + 0x28 + baseOffset),
        0,
        0x518);

    *reinterpret_cast<unsigned int*>(state + 0x1c) = 0;
    *reinterpret_cast<unsigned int*>(state + 0x20) = 0;
    *reinterpret_cast<unsigned int*>(state + 0x24) = 0;

    const short typeId =
        *reinterpret_cast<short*>(
            reinterpret_cast<unsigned long>(self) + 0x22);

    unsigned int* typeEntry = nullptr;

    if (typeId != -1 && DAT_1003bd8c != 0) {
        unsigned short index = 0;

        do {
            if (DAT_1003b700[static_cast<unsigned int>(index) * 3] ==
                static_cast<unsigned int>(typeId)) {
                typeEntry =
                    &DAT_1003b700[static_cast<unsigned int>(index) * 3];
                goto found_type_entry;
            }

            index = static_cast<unsigned short>(index + 1);
        } while (index < DAT_1003bd8c);
    }

    typeEntry = nullptr;

found_type_entry:
    *reinterpret_cast<unsigned int**>(
        *reinterpret_cast<int*>(state + 0x28) + 0x350) = typeEntry;

    reinterpret_cast<void(__cdecl*)(
        unsigned int,
        void(__cdecl*)(),
        void*)>(
        0x7f0dc0)(
        callbackContext,
        FUN_10004430,
        reinterpret_cast<void*>(
            *reinterpret_cast<int*>(state + 0x28)));

    if (*reinterpret_cast<void**>(state + 0x30) != nullptr) {
        FUN_10010756(
            *reinterpret_cast<void**>(state + 0x30));
    }

    int* entry =
        reinterpret_cast<int*>(
            static_cast<unsigned long>(*DAT_1003c25c));

    if (entry != DAT_1003c25c) {
        while (
            static_cast<unsigned int>(
                *reinterpret_cast<unsigned short*>(entry + 2)) !=
            static_cast<unsigned int>(typeId)) {
            entry =
                reinterpret_cast<int*>(
                    static_cast<unsigned long>(*entry));

            if (entry == DAT_1003c25c) {
                return;
            }
        }

        if (entry != reinterpret_cast<int*>(0xfffffff8u)) {
            *reinterpret_cast<unsigned char*>(state + 0x2c) =
                *reinterpret_cast<unsigned char*>(
                    reinterpret_cast<unsigned long>(entry) + 10);

            const unsigned int data =
                FUN_10010230(
                    static_cast<unsigned int>(
                        *reinterpret_cast<unsigned char*>(
                            reinterpret_cast<unsigned long>(entry) + 10)) *
                    4);

            *reinterpret_cast<unsigned int*>(state + 0x30) = data;

            int index = 0;

            if (*reinterpret_cast<char*>(
                    reinterpret_cast<unsigned long>(entry) + 10) != '\0') {
                do {
                    *reinterpret_cast<unsigned int*>(
                        static_cast<unsigned long>(data) + index * 4) =
                        *reinterpret_cast<unsigned int*>(
                            static_cast<unsigned long>(entry[3]) +
                            index * 4);

                    index = index + 1;
                } while (
                    index <
                    static_cast<int>(
                        static_cast<unsigned int>(
                            *reinterpret_cast<unsigned char*>(
                                reinterpret_cast<unsigned long>(entry) + 10))));
            }
        }
    }
}