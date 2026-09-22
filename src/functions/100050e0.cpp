#include <cstdint>

extern "C" void __cdecl FUN_006d3db0();
extern "C" char __cdecl FUN_006c2130(int);
extern "C" char __cdecl FUN_0052cee0(int, int);

extern "C" int __stdcall FUN_10009360();
extern "C" void __stdcall FUN_10004bb0();

extern "C" int DAT_1003c248;
extern "C" int* _DAT_00b74494;
extern "C" int _DAT_00b7cb84;
extern "C" int DAT_1003bc70;
extern "C" int DAT_1003aed8;

void __fastcall FUN_100050e0(int param_1)
{
    int iVar1;
    int iVar2;
    int iVar3;
    char cVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    int local_8 = 0;

    FUN_006d3db0();

    iVar7 = DAT_1003c248;
    iVar5 = FUN_10009360();

    iVar7 =
        *reinterpret_cast<int*>(
            *reinterpret_cast<int*>(
                static_cast<std::uintptr_t>(iVar5) + 0x48u) +
            ((param_1 - *_DAT_00b74494) / 0xa18) * 4) +
        iVar7;

    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar7) + 0x04u) = 0;
    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar7) + 0x08u) = 0;
    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar7) + 0x0cu) = 0;
    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar7) + 0x10u) = 0;
    *reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(iVar7) + 0x14u) = 0;
    *reinterpret_cast<std::uint8_t*>(
        static_cast<std::uintptr_t>(iVar7) + 0x18u) = 0;

    iVar5 = DAT_1003c248;

    if (0.0f < *reinterpret_cast<float*>(
                   static_cast<std::uintptr_t>(param_1) + 0x4c0u)) {
        iVar1 = *reinterpret_cast<int*>(
            static_cast<std::uintptr_t>(param_1) + 0x4c4u);
        iVar2 = *reinterpret_cast<int*>(
            static_cast<std::uintptr_t>(param_1) + 0x594u);
        iVar3 = *reinterpret_cast<int*>(
            static_cast<std::uintptr_t>(param_1) + 0x460u);

        if ((iVar1 != 0) &&
            (*reinterpret_cast<int*>(
                 static_cast<std::uintptr_t>(iVar1) + 0x594u) == 0xb)) {
            iVar6 = FUN_10009360();

            local_8 =
                *reinterpret_cast<int*>(
                    *reinterpret_cast<int*>(
                        static_cast<std::uintptr_t>(iVar6) + 0x48u) +
                    ((iVar1 - *_DAT_00b74494) / 0xa18) * 4) +
                4 +
                iVar5;
        }

        FUN_10004bb0();

        if ((0.0f < *reinterpret_cast<float*>(
                        static_cast<std::uintptr_t>(param_1) + 0x4a0u)) &&
            (iVar3 != 0)) {
            cVar4 = FUN_006c2130(3);
            if (cVar4 == '\0')
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(iVar7) + 8u) = 1;

            cVar4 = FUN_006c2130(2);
            if (cVar4 == '\0')
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(iVar7) + 9u) = 1;

            if ((iVar1 != 0) &&
                (*reinterpret_cast<int*>(
                     static_cast<std::uintptr_t>(iVar1) + 0x594u) == 0xb)) {
                cVar4 = FUN_006c2130(3);
                if (cVar4 == '\0')
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(local_8) + 4u) = 1;

                cVar4 = FUN_006c2130(2);
                if (cVar4 == '\0')
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(local_8) + 5u) = 1;
            }
        }

        if ((*reinterpret_cast<char*>(
                 static_cast<std::uintptr_t>(param_1) + 0x4b4u) == '\0') &&
            (*reinterpret_cast<float*>(
                 static_cast<std::uintptr_t>(param_1) + 0x48u) != 0.0f) &&
            (iVar3 != 0)) {
            if ((iVar2 == 0) || (iVar2 == 1)) {
                cVar4 = FUN_006c2130(3);
                if (cVar4 == '\0')
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x0au) = 1;

                cVar4 = FUN_006c2130(2);
                if (cVar4 == '\0')
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x0bu) = 1;

                if ((iVar1 != 0) &&
                    (*reinterpret_cast<int*>(
                         static_cast<std::uintptr_t>(iVar1) + 0x594u) == 0xb)) {
                    cVar4 = FUN_006c2130(3);
                    if (cVar4 == '\0')
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(local_8) + 6u) = 1;

                    cVar4 = FUN_006c2130(2);
                    if (cVar4 == '\0')
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(local_8) + 7u) = 1;
                }
            }
            else if (iVar2 == 2) {
                cVar4 = FUN_006c2130(2);
                if (cVar4 == '\0')
                    *reinterpret_cast<std::uint16_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x0au) = 0x101;
            }
            else if (iVar2 == 9) {
                *reinterpret_cast<std::uint16_t*>(
                    static_cast<std::uintptr_t>(iVar7) + 0x0au) = 0x101;
            }
        }

        if (*reinterpret_cast<char*>(
                static_cast<std::uintptr_t>(iVar7) + 0x1du) != '\0') {
            if ((iVar2 == 0) || (iVar2 == 1)) {
                cVar4 = FUN_006c2130(0);
                if (cVar4 == '\0')
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x0cu) = 1;

                cVar4 = FUN_006c2130(1);
                if (cVar4 == '\0')
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x0du) = 1;

                if ((iVar1 != 0) &&
                    (*reinterpret_cast<int*>(
                         static_cast<std::uintptr_t>(iVar1) + 0x594u) == 0xb)) {
                    cVar4 = FUN_006c2130(0);
                    if (cVar4 == '\0')
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(local_8) + 8u) = 1;

                    cVar4 = FUN_006c2130(1);
                    if (cVar4 == '\0')
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(local_8) + 9u) = 1;
                }
            }
            else if (iVar2 == 2) {
                cVar4 = FUN_006c2130(1);
                if (cVar4 == '\0')
                    *reinterpret_cast<std::uint16_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x0cu) = 0x101;
            }
            else if (iVar2 == 9) {
                *reinterpret_cast<std::uint16_t*>(
                    static_cast<std::uintptr_t>(iVar7) + 0x0cu) = 0x101;
            }
        }

        iVar5 = _DAT_00b7cb84 -
                *reinterpret_cast<int*>(
                    static_cast<std::uintptr_t>(iVar7) + 0x24u);

        if (DAT_1003bc70 < iVar5) {
            *reinterpret_cast<int*>(
                static_cast<std::uintptr_t>(iVar7) + 0x24u) =
                _DAT_00b7cb84;
        }
        else if (iVar5 < DAT_1003aed8) {
            if (*reinterpret_cast<char*>(
                    static_cast<std::uintptr_t>(iVar7) + 0x1fu) != '\0') {
                if ((iVar2 == 0) || (iVar2 == 1)) {
                    cVar4 = FUN_006c2130(0);
                    if (cVar4 == '\0')
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(iVar7) + 0x0eu) = 1;

                    cVar4 = FUN_006c2130(3);
                    if (cVar4 == '\0')
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(iVar7) + 0x10u) = 1;

                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x0fu) = 1;

                    if ((iVar1 != 0) &&
                        (*reinterpret_cast<int*>(
                             static_cast<std::uintptr_t>(iVar1) + 0x594u) == 0xb)) {
                        cVar4 = FUN_006c2130(0);
                        if (cVar4 == '\0')
                            *reinterpret_cast<std::uint8_t*>(
                                static_cast<std::uintptr_t>(local_8) + 0x0au) = 1;

                        cVar4 = FUN_006c2130(3);
                        if (cVar4 == '\0')
                            *reinterpret_cast<std::uint8_t*>(
                                static_cast<std::uintptr_t>(local_8) + 0x0cu) = 1;

                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(local_8) + 0x0bu) = 1;
                    }
                }
                else if (iVar2 == 2) {
                    cVar4 = FUN_006c2130(1);
                    if (cVar4 == '\0') {
                        cVar4 = FUN_006c2130(0);
                        if (cVar4 == '\0')
                            *reinterpret_cast<std::uint8_t*>(
                                static_cast<std::uintptr_t>(iVar7) + 0x0eu) = 1;

                        cVar4 = FUN_006c2130(3);
                        if (cVar4 == '\0')
                            *reinterpret_cast<std::uint8_t*>(
                                static_cast<std::uintptr_t>(iVar7) + 0x10u) = 1;
                    }

                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x0fu) = 1;
                }
                else if (iVar2 == 9) {
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x0eu) = 1;
                    *reinterpret_cast<std::uint16_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x0fu) = 0x101;
                }
            }

            if (*reinterpret_cast<char*>(
                    static_cast<std::uintptr_t>(iVar7) + 0x1eu) != '\0') {
                if ((iVar2 == 0) || (iVar2 == 1)) {
                    cVar4 = FUN_006c2130(1);
                    if (cVar4 == '\0')
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(iVar7) + 0x11u) = 1;

                    cVar4 = FUN_006c2130(2);
                    if (cVar4 == '\0')
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(iVar7) + 0x13u) = 1;

                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x12u) = 1;

                    if ((iVar1 != 0) &&
                        (*reinterpret_cast<int*>(
                             static_cast<std::uintptr_t>(iVar1) + 0x594u) == 0xb)) {
                        cVar4 = FUN_006c2130(1);
                        if (cVar4 == '\0')
                            *reinterpret_cast<std::uint8_t*>(
                                static_cast<std::uintptr_t>(local_8) + 0x0du) = 1;

                        cVar4 = FUN_006c2130(2);
                        if (cVar4 == '\0')
                            *reinterpret_cast<std::uint8_t*>(
                                static_cast<std::uintptr_t>(local_8) + 0x0fu) = 1;

                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(local_8) + 0x0eu) = 1;
                    }
                }
                else if (iVar2 == 2) {
                    cVar4 = FUN_006c2130(1);
                    if (cVar4 == '\0') {
                        cVar4 = FUN_006c2130(1);
                        if (cVar4 == '\0')
                            *reinterpret_cast<std::uint8_t*>(
                                static_cast<std::uintptr_t>(iVar7) + 0x11u) = 1;

                        cVar4 = FUN_006c2130(2);
                        if (cVar4 == '\0')
                            *reinterpret_cast<std::uint8_t*>(
                                static_cast<std::uintptr_t>(iVar7) + 0x13u) = 1;
                    }

                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x12u) = 1;
                }
                else if (iVar2 == 9) {
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x11u) = 1;
                    *reinterpret_cast<std::uint16_t*>(
                        static_cast<std::uintptr_t>(iVar7) + 0x12u) = 0x101;
                }
            }
        }

        *reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(iVar7) + 0x15u) = 1;

        cVar4 = FUN_0052cee0(0x15, 7);
        if (cVar4 == '\0') {
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(iVar7) + 0x18u) = 1;

            if ((iVar1 != 0) &&
                (*reinterpret_cast<int*>(
                     static_cast<std::uintptr_t>(iVar1) + 0x594u) == 0xb)) {
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(local_8) + 0x14u) = 1;
            }
        }
        else {
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(iVar7) + 0x14u) = 1;

            if ((iVar1 != 0) &&
                (*reinterpret_cast<int*>(
                     static_cast<std::uintptr_t>(iVar1) + 0x594u) == 0xb)) {
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(local_8) + 0x10u) = 1;
                return;
            }
        }
    }
}