#include <cstddef>
#include <cstdint>

#include <corecrt.h>
#include <intrin.h>
extern "C" void __cdecl ___mtold12(char*, int, std::uint32_t*);
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using uint = std::uint32_t;
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined8 = std::uint64_t;
extern "C" int* __cdecl __errno(void);
extern "C" void __stdcall FUN_1001189f(void);
extern "C" std::uint32_t DAT_10029490;

inline char locale_decimal_point(_locale_t locale) noexcept {
    const auto root = *reinterpret_cast<const std::uint32_t*>(locale);
    const auto decimal_pointer = *reinterpret_cast<const std::uint32_t*>(
        static_cast<std::uintptr_t>(root) + 0xbcU);
    return *reinterpret_cast<const char*>(static_cast<std::uintptr_t>(decimal_pointer));
}

extern "C" std::uint8_t DAT_10039698[];
extern "C" std::uint8_t DAT_100397f8[];


struct _Mtold12Output {
    std::uint32_t low;
    std::uint32_t middle;
    std::uint16_t upper_low;
    std::uint16_t upper_high;
};
static_assert(sizeof(_Mtold12Output) == 12);
static_assert(offsetof(_Mtold12Output, upper_low) == 8);

struct _LDBL12 { std::uint8_t ld12[12]; };
static_assert(sizeof(_LDBL12) == 12);
template<class H, class L> constexpr std::uint32_t CONCAT22(H high, L low) noexcept {
    return static_cast<std::uint32_t>(((static_cast<std::uint64_t>(high) & 0xffffULL) << 16) |
                                      (static_cast<std::uint64_t>(low) & 0xffffULL));
}
template<class H, class L> constexpr std::uint16_t CONCAT11(H high, L low) noexcept {
    return static_cast<std::uint16_t>(((static_cast<std::uint16_t>(high) & 0xffU) << 8) |
                                     (static_cast<std::uint16_t>(low) & 0xffU));
}
static_assert(CONCAT22(0x12, 0x3456) == 0x00123456U);
static_assert(CONCAT11(0x12, 0x34) == 0x1234U);



/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

/* Library Function - Single Match

    ___strgtold12_l

   

   Library: Visual Studio 2010 Release */



std::uint32_t __cdecl

___strgtold12_l(_LDBL12 *pld12,char **p_end_ptr,char *str,int mult12,int scale,int decpt,

               int implicit_E,_locale_t _Locale)



{

  int iVar1;

  bool bVar2;

  bool bVar3;

  bool bVar4;

  std::uint16_t uVar5;

  char cVar6;

  std::uint16_t uVar7;

  int *piVar8;

  std::uint32_t uVar9;

  std::uint32_t uVar10;

  std::uint32_t uVar11;

  std::uint16_t uVar12;

  int iVar13;

  undefined *puVar14;

  char *pcVar15;

  undefined4 uVar16;

  std::uint16_t *puVar17;

  std::uint16_t uVar18;

  std::uint32_t uVar19;

  undefined4 uVar20;

  char *pcVar21;

  std::uint16_t *puVar22;

  std::uint32_t local_70;

  int local_6c;

  int local_68;

  std::uint16_t *local_64;

  std::uint16_t *local_60;

  int local_5c;

  char *local_58;

  int local_54;

  std::uint32_t local_50;

  std::uint16_t local_4c;

  undefined2 uStack_4a;

  undefined2 uStack_48;

  undefined2 uStack_46;

  undefined4 local_44;

  _Mtold12Output numeric_parts;







  std::uint8_t local_30;

  undefined1 uStack_2f;

  std::uint16_t uStack_2e;

  std::uint16_t local_2c [4];

  char local_24 [25];



  std::uint32_t local_8;

  

  local_8 = DAT_10029490 ^ static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(_AddressOfReturnAddress()) - sizeof(void*));

  iVar13 = 0;

  pcVar21 = local_24;

  uVar5 = 0;

  local_6c = 1;

  local_50 = 0;

  bVar2 = false;

  bVar4 = false;

  bVar3 = false;

  local_68 = 0;

  local_54 = 0;

  local_70 = 0;

  if (_Locale == (_locale_t)0x0) {

    piVar8 = __errno();

    *piVar8 = 0x16;

    FUN_1001189f();

    return 0;

  }

  local_58 = str;

  for (; (((cVar6 = *str, cVar6 == ' ' || (cVar6 == '\t')) || (cVar6 == '\n')) || (cVar6 == '\r'));

      str = str + 1) {

  }

LAB_1001eba4:

  cVar6 = *str;

  pcVar15 = str + 1;

  switch(iVar13) {

  case 0:

    if ((std::uint8_t)(cVar6 - 0x31U) < 9) {

LAB_1001ebbf:

      iVar13 = 3;

      goto LAB_1001ebc1;

    }

    if (cVar6 == (*reinterpret_cast<const char*>(static_cast<std::uintptr_t>(
    *reinterpret_cast<const std::uint32_t*>(static_cast<std::uintptr_t>(
        *reinterpret_cast<const std::uint32_t*>(_Locale)) + 0xbcU))))) {

LAB_1001ebd6:

      iVar13 = 5;

      str = pcVar15;

    }

    else if (cVar6 == '+') {

      uVar5 = 0;

      iVar13 = 2;

      str = pcVar15;

    }

    else {

      if (cVar6 != '-') {

        if (cVar6 == '0') goto LAB_1001ebf0;

        goto LAB_1001ed6c;

      }

      iVar13 = 2;

      uVar5 = 0x8000;

      str = pcVar15;

    }

    goto LAB_1001eba4;

  case 1:

    bVar2 = true;

    if ((std::uint8_t)(cVar6 - 0x31U) < 9) goto LAB_1001ebbf;

    if (cVar6 == (*reinterpret_cast<const char*>(static_cast<std::uintptr_t>(
    *reinterpret_cast<const std::uint32_t*>(static_cast<std::uintptr_t>(
        *reinterpret_cast<const std::uint32_t*>(_Locale)) + 0xbcU))))) goto LAB_1001ec25;

    if ((cVar6 == '+') || (cVar6 == '-')) goto LAB_1001ec4f;

    if (cVar6 == '0') goto LAB_1001ebf0;

    goto LAB_1001ec35;

  case 2:

    if ((std::uint8_t)(cVar6 - 0x31U) < 9) goto LAB_1001ebbf;

    if (cVar6 == (*reinterpret_cast<const char*>(static_cast<std::uintptr_t>(
    *reinterpret_cast<const std::uint32_t*>(static_cast<std::uintptr_t>(
        *reinterpret_cast<const std::uint32_t*>(_Locale)) + 0xbcU))))) goto LAB_1001ebd6;

    str = local_58;

    if (cVar6 != '0') goto LAB_1001ed95;

LAB_1001ebf0:

    iVar13 = 1;

    str = pcVar15;

    goto LAB_1001eba4;

  case 3:

    while (('/' < cVar6 && (cVar6 < ':'))) {

      if (local_50 < 0x19) {

        local_50 = local_50 + 1;

        *pcVar21 = cVar6 + -0x30;

        pcVar21 = pcVar21 + 1;

      }

      else {

        local_54 = local_54 + 1;

      }

      cVar6 = *pcVar15;

      pcVar15 = pcVar15 + 1;

    }

    if (cVar6 != (*reinterpret_cast<const char*>(static_cast<std::uintptr_t>(
    *reinterpret_cast<const std::uint32_t*>(static_cast<std::uintptr_t>(
        *reinterpret_cast<const std::uint32_t*>(_Locale)) + 0xbcU))))) goto LAB_1001ecbd;

LAB_1001ec25:

    bVar2 = true;

    iVar13 = 4;

    str = pcVar15;

    goto LAB_1001eba4;

  case 4:

    bVar4 = true;

    if (local_50 == 0) {

      while (cVar6 == '0') {

        local_54 = local_54 + -1;

        cVar6 = *pcVar15;

        pcVar15 = pcVar15 + 1;

      }

    }

    while (('/' < cVar6 && (cVar6 < ':'))) {

      if (local_50 < 0x19) {

        local_50 = local_50 + 1;

        *pcVar21 = cVar6 + -0x30;

        pcVar21 = pcVar21 + 1;

        local_54 = local_54 + -1;

      }

      cVar6 = *pcVar15;

      pcVar15 = pcVar15 + 1;

    }

LAB_1001ecbd:

    if ((cVar6 == '+') || (cVar6 == '-')) {

LAB_1001ec4f:

      bVar2 = true;

      iVar13 = 0xb;

      str = pcVar15 + -1;

    }

    else {

LAB_1001ec35:

      bVar2 = true;

      if ((cVar6 < 'D') || (('E' < cVar6 && (1 < (std::uint8_t)(cVar6 + 0x9cU))))) goto LAB_1001ed6c;

      iVar13 = 6;

      str = pcVar15;

    }

    goto LAB_1001eba4;

  case 5:

    bVar4 = true;

    str = local_58;

    if ((std::uint8_t)(cVar6 - 0x30U) < 10) {

      iVar13 = 4;

      goto LAB_1001ebc1;

    }

    goto LAB_1001ed95;

  case 6:

    local_58 = str + -1;

    if (8 < (std::uint8_t)(cVar6 - 0x31U)) {

      if (cVar6 == '+') goto LAB_1001ed53;

      if (cVar6 == '-') goto LAB_1001ed47;

LAB_1001ed3a:

      str = local_58;

      if (cVar6 != '0') goto LAB_1001ed95;

      iVar13 = 8;

      str = pcVar15;

      goto LAB_1001eba4;

    }

    break;

  case 7:

    if (8 < (std::uint8_t)(cVar6 - 0x31U)) goto LAB_1001ed3a;

    break;

  case 8:

    bVar3 = true;

    while (cVar6 == '0') {

      cVar6 = *pcVar15;

      pcVar15 = pcVar15 + 1;

    }

    if (8 < (std::uint8_t)(cVar6 - 0x31U)) goto LAB_1001ed6c;

    break;

  case 9:

    bVar3 = true;

    local_68 = 0;

    goto LAB_1001edf7;

  default:

    goto switchD_1001ebb0_caseD_a;

  case 0xb:

    if (implicit_E != 0) {

      local_58 = str;

      if (cVar6 == '+') {

LAB_1001ed53:

        iVar13 = 7;

        str = pcVar15;

      }

      else {

        if (cVar6 != '-') goto LAB_1001ed95;

LAB_1001ed47:

        local_6c = -1;

        iVar13 = 7;

        str = pcVar15;

      }

      goto LAB_1001eba4;

    }

    iVar13 = 10;

    pcVar15 = str;

switchD_1001ebb0_caseD_a:

    str = pcVar15;

    if (iVar13 != 10) goto LAB_1001eba4;

    goto LAB_1001ed95;

  }

  iVar13 = 9;

LAB_1001ebc1:

  str = pcVar15 + -1;

  goto LAB_1001eba4;

LAB_1001edf7:

  if ((cVar6 < '0') || ('9' < cVar6)) goto LAB_1001ee12;

  local_68 = local_68 * 10 + -0x30 + (int)cVar6;

  if (local_68 < 0x1451) {

    cVar6 = *pcVar15;

    pcVar15 = pcVar15 + 1;

    goto LAB_1001edf7;

  }

  local_68 = 0x1451;

LAB_1001ee12:

  while (('/' < cVar6 && (cVar6 < ':'))) {

    cVar6 = *pcVar15;

    pcVar15 = pcVar15 + 1;

  }

LAB_1001ed6c:

  str = pcVar15 + -1;

LAB_1001ed95:

  *p_end_ptr = str;

  if (bVar2) {

    if (0x18 < local_50) {

      if ('\x04' < local_24[23]) {

        local_24[23] = local_24[23] + '\x01';

      }

      pcVar21 = pcVar21 + -1;

      local_54 = local_54 + 1;

      local_50 = 0x18;

    }

    if (local_50 != 0) {

      while (pcVar21 = pcVar21 + -1, *pcVar21 == '\0') {

        local_50 = local_50 - 1;

        local_54 = local_54 + 1;

      }

      ___mtold12(local_24,local_50,&numeric_parts.low);

      uVar10 = CONCAT22(numeric_parts.upper_high,numeric_parts.upper_low);

      iVar13 = CONCAT22(static_cast<undefined2>(static_cast<std::uint32_t>(numeric_parts.middle) >> 16),(undefined2)numeric_parts.middle);

      uVar19 = CONCAT22(static_cast<undefined2>(static_cast<std::uint32_t>(numeric_parts.low) >> 16),(undefined2)numeric_parts.low);

      if (local_6c < 0) {

        local_68 = -local_68;

      }

      local_58 = (char *)(local_68 + local_54);

      if (!bVar3) {

        local_58 = (char *)((int)local_58 + scale);

      }

      if (!bVar4) {

        local_58 = (char *)((int)local_58 - decpt);

      }

      if (0x1450 < (int)local_58) {

        uVar20 = 0;

        numeric_parts.upper_high = 0x7fff;

        uVar16 = 0x80000000;

        numeric_parts.low = (numeric_parts.low & 0xffff0000U) | (static_cast<std::uint32_t>(0) & 0xffffU);

        local_70 = 2;

        goto LAB_1001f1ab;

      }

      if (-0x1451 < (int)local_58) {

        puVar14 = DAT_10039698;

        if (local_58 != (char *)0x0) {

          if ((int)local_58 < 0) {

            local_58 = (char *)-(int)local_58;

            puVar14 = DAT_100397f8;

          }

          if (mult12 == 0) {

            numeric_parts.low = (numeric_parts.low & 0xffff0000U) | (static_cast<std::uint32_t>(0) & 0xffffU);

          }

          uVar19 = CONCAT22(static_cast<undefined2>(static_cast<std::uint32_t>(numeric_parts.low) >> 16),(undefined2)numeric_parts.low);

          iVar13 = CONCAT22(static_cast<undefined2>(static_cast<std::uint32_t>(numeric_parts.middle) >> 16),(undefined2)numeric_parts.middle);

          uVar10 = CONCAT22(numeric_parts.upper_high,numeric_parts.upper_low);

joined_r0x1001ee9f:

          if (local_58 != (char *)0x0) {

            numeric_parts.upper_high = (std::uint16_t)(uVar10 >> 0x10);

            uVar11 = (int)local_58 >> 3;

            puVar14 = puVar14 + 0x54;

            uVar9 = (std::uint32_t)local_58 & 7;

            local_58 = (char *)uVar11;

            if (uVar9 != 0) {

              puVar17 = (std::uint16_t *)(puVar14 + uVar9 * 0xc);

              if (0x7fff < *puVar17) {

                local_4c = (std::uint16_t)*(undefined4 *)puVar17;

                uStack_4a = (undefined2)((std::uint32_t)*(undefined4 *)puVar17 >> 0x10);

                uStack_48 = (undefined2)*(undefined4 *)(puVar17 + 2);

                uStack_46 = (undefined2)((std::uint32_t)*(undefined4 *)(puVar17 + 2) >> 0x10);

                local_44 = *(undefined4 *)(puVar17 + 4);

                iVar1 = CONCAT22(uStack_48,uStack_4a) + -1;

                uStack_4a = (undefined2)iVar1;

                uStack_48 = (undefined2)((std::uint32_t)iVar1 >> 0x10);

                puVar17 = &local_4c;

              }

              local_54 = 0;

              local_30 = 0;

              uStack_2f = 0;

              uStack_2e = 0;

              local_2c[0] = 0;

              local_2c[1] = 0;

              local_2c[2] = 0;

              local_2c[3] = 0;

              uVar7 = puVar17[5] & 0x7fff;

              uVar18 = (puVar17[5] ^ numeric_parts.upper_high) & 0x8000;

              uVar12 = uVar7 + (numeric_parts.upper_high & 0x7fff);

              if ((((numeric_parts.upper_high & 0x7fff) < 0x7fff) && (uVar7 < 0x7fff)) && (uVar12 < 0xbffe)) {

                if (0x3fbf < uVar12) {

                  if ((((uVar10 & 0x7fff0000) == 0) &&

                      (uVar12 = uVar12 + 1, (uVar10 & 0x7fffffff) == 0)) &&

                     ((iVar13 == 0 && (uVar19 == 0)))) {

                    numeric_parts.upper_high = 0;

                    uVar10 = uVar10 & 0xffff;

                  }

                  else if (((uVar7 == 0) &&

                           (uVar12 = uVar12 + 1, (*(std::uint32_t *)(puVar17 + 4) & 0x7fffffff) == 0)) &&

                          ((*(int *)(puVar17 + 2) == 0 && (*(int *)puVar17 == 0)))) {

                    numeric_parts.upper_low = 0;

                    numeric_parts.upper_high = 0;

                    uVar10 = 0;

                    numeric_parts.middle = (numeric_parts.middle & 0xffff0000U) | (static_cast<std::uint32_t>(0) & 0xffffU);

                    numeric_parts.middle = (numeric_parts.middle & 0x0000ffffU) | ((static_cast<std::uint32_t>(0) & 0xffffU) << 16);

                    iVar13 = 0;

                    numeric_parts.low = (numeric_parts.low & 0xffff0000U) | (static_cast<std::uint32_t>(0) & 0xffffU);

                    numeric_parts.low = (numeric_parts.low & 0x0000ffffU) | ((static_cast<std::uint32_t>(0) & 0xffffU) << 16);

                    uVar19 = 0;

                  }

                  else {

                    local_6c = 0;

                    puVar22 = local_2c;

                    local_5c = 5;

                    do {

                      local_68 = local_5c;

                      if (0 < local_5c) {

                        local_60 = (std::uint16_t *)((int)&numeric_parts.low + local_6c * 2);

                        local_64 = puVar17 + 4;

                        do {

                          bVar2 = false;

                          uVar19 = *(std::uint32_t *)(puVar22 + -2) + (std::uint32_t)*local_64 * (std::uint32_t)*local_60;

                          if ((uVar19 < *(std::uint32_t *)(puVar22 + -2)) ||

                             (uVar19 < (std::uint32_t)*local_64 * (std::uint32_t)*local_60)) {

                            bVar2 = true;

                          }

                          *(std::uint32_t *)(puVar22 + -2) = uVar19;

                          if (bVar2) {

                            *puVar22 = *puVar22 + 1;

                          }

                          local_60 = local_60 + 1;

                          local_64 = local_64 + -1;

                          local_68 = local_68 + -1;

                        } while (0 < local_68);

                      }

                      puVar22 = puVar22 + 1;

                      local_6c = local_6c + 1;

                      local_5c = local_5c + -1;

                    } while (0 < local_5c);

                    uVar12 = uVar12 + 0xc002;

                    if ((short)uVar12 < 1) {

LAB_1001f05b:

                      uVar12 = uVar12 - 1;

                      if ((short)uVar12 < 0) {

                        uVar19 = (std::uint32_t)(std::uint16_t)-uVar12;

                        uVar12 = 0;

                        do {

                          if ((local_30 & 1) != 0) {

                            local_54 = local_54 + 1;

                          }

                          iVar1 = CONCAT22(local_2c[3],local_2c[2]);

                          uVar10 = CONCAT22(local_2c[1],local_2c[0]);

                          iVar13 = CONCAT22(local_2c[1],local_2c[0]);

                          local_2c[2] = (std::uint16_t)(CONCAT22(local_2c[3],local_2c[2]) >> 1);

                          local_2c[3] = local_2c[3] >> 1;

                          local_2c[1] = local_2c[1] >> 1 | (std::uint16_t)((std::uint32_t)(iVar1 << 0x1f) >> 0x10);

                          uVar11 = CONCAT22(uStack_2e,CONCAT11(uStack_2f,local_30)) >> 1;

                          uStack_2e = uStack_2e >> 1 | (std::uint16_t)((std::uint32_t)(iVar13 << 0x1f) >> 0x10);

                          uVar19 = uVar19 - 1;

                          local_2c[0] = (std::uint16_t)(uVar10 >> 1);

                          local_30 = (std::uint8_t)uVar11;

                          uStack_2f = (undefined1)(uVar11 >> 8);

                        } while (uVar19 != 0);

                        if (local_54 != 0) {

                          local_30 = local_30 | 1;

                        }

                      }

                    }

                    else {

                      do {

                        uVar7 = uStack_2e;

                        if ((short)local_2c[3] < 0) break;

                        iVar13 = CONCAT22(uStack_2e,CONCAT11(uStack_2f,local_30)) << 1;

                        local_30 = (std::uint8_t)iVar13;

                        uStack_2f = (undefined1)((std::uint32_t)iVar13 >> 8);

                        uStack_2e = (std::uint16_t)((std::uint32_t)iVar13 >> 0x10);

                        iVar13 = CONCAT22(local_2c[1],local_2c[0]) * 2;

                        local_2c[0] = (std::uint16_t)iVar13 | uVar7 >> 0xf;

                        iVar1 = CONCAT22(local_2c[3],local_2c[2]) * 2;

                        local_2c[2] = (std::uint16_t)iVar1 | local_2c[1] >> 0xf;

                        uVar12 = uVar12 - 1;

                        local_2c[1] = (std::uint16_t)((std::uint32_t)iVar13 >> 0x10);

                        local_2c[3] = (std::uint16_t)((std::uint32_t)iVar1 >> 0x10);

                      } while (0 < (short)uVar12);

                      if ((short)uVar12 < 1) goto LAB_1001f05b;

                    }

                    if ((0x8000 < CONCAT11(uStack_2f,local_30)) ||

                       (iVar13 = CONCAT22(local_2c[2],local_2c[1]),

                       uVar19 = CONCAT22(local_2c[0],uStack_2e),

                       (CONCAT22(uStack_2e,CONCAT11(uStack_2f,local_30)) & 0x1ffff) == 0x18000)) {

                      if (CONCAT22(local_2c[0],uStack_2e) == -1) {

                        uVar19 = 0;

                        if (CONCAT22(local_2c[2],local_2c[1]) == -1) {

                          if (local_2c[3] == 0xffff) {

                            local_2c[3] = 0x8000;

                            uVar12 = uVar12 + 1;

                            iVar13 = 0;

                            uVar19 = 0;

                          }

                          else {

                            local_2c[3] = local_2c[3] + 1;

                            iVar13 = 0;

                            uVar19 = 0;

                          }

                        }

                        else {

                          iVar13 = CONCAT22(local_2c[2],local_2c[1]) + 1;

                        }

                      }

                      else {

                        uVar19 = CONCAT22(local_2c[0],uStack_2e) + 1;

                        iVar13 = CONCAT22(local_2c[2],local_2c[1]);

                      }

                    }

                    if (uVar12 < 0x7fff) {

                      numeric_parts.low = uVar19;

                      numeric_parts.middle = iVar13;

                      numeric_parts.upper_low = local_2c[3];

                      numeric_parts.upper_high = uVar12 | uVar18;

                      uVar10 = CONCAT22(uVar12 | uVar18,local_2c[3]);

                    }

                    else {

                      numeric_parts.middle = (numeric_parts.middle & 0xffff0000U) | (static_cast<std::uint32_t>(0) & 0xffffU);

                      numeric_parts.middle = (numeric_parts.middle & 0x0000ffffU) | ((static_cast<std::uint32_t>(0) & 0xffffU) << 16);

                      iVar13 = 0;

                      numeric_parts.low = (numeric_parts.low & 0xffff0000U) | (static_cast<std::uint32_t>(0) & 0xffffU);

                      numeric_parts.low = (numeric_parts.low & 0x0000ffffU) | ((static_cast<std::uint32_t>(0) & 0xffffU) << 16);

                      uVar19 = 0;

                      uVar10 = ((uVar18 == 0) - 1 & 0x80000000) + 0x7fff8000;

                      numeric_parts.upper_low = (std::uint16_t)uVar10;

                      numeric_parts.upper_high = (std::uint16_t)(uVar10 >> 0x10);

                    }

                  }

                  goto joined_r0x1001ee9f;

                }

                uVar10 = 0;

                numeric_parts.middle = (numeric_parts.middle & 0xffff0000U) | (static_cast<std::uint32_t>(0) & 0xffffU);

                numeric_parts.middle = (numeric_parts.middle & 0x0000ffffU) | ((static_cast<std::uint32_t>(0) & 0xffffU) << 16);

                numeric_parts.low = (numeric_parts.low & 0xffff0000U) | (static_cast<std::uint32_t>(0) & 0xffffU);

                numeric_parts.low = (numeric_parts.low & 0x0000ffffU) | ((static_cast<std::uint32_t>(0) & 0xffffU) << 16);

              }

              else {

                numeric_parts.middle = (numeric_parts.middle & 0xffff0000U) | (static_cast<std::uint32_t>(0) & 0xffffU);

                numeric_parts.middle = (numeric_parts.middle & 0x0000ffffU) | ((static_cast<std::uint32_t>(0) & 0xffffU) << 16);

                uVar10 = ((uVar18 == 0) - 1 & 0x80000000) + 0x7fff8000;

                numeric_parts.low = (numeric_parts.low & 0xffff0000U) | (static_cast<std::uint32_t>(0) & 0xffffU);

                numeric_parts.low = (numeric_parts.low & 0x0000ffffU) | ((static_cast<std::uint32_t>(0) & 0xffffU) << 16);

              }

              iVar13 = 0;

              uVar19 = 0;

              numeric_parts.upper_low = (std::uint16_t)uVar10;

              numeric_parts.upper_high = (std::uint16_t)(uVar10 >> 0x10);

            }

            goto joined_r0x1001ee9f;

          }

        }

        numeric_parts.upper_high = (std::uint16_t)(uVar10 >> 0x10);

        numeric_parts.upper_low = (std::uint16_t)uVar10;

        numeric_parts.middle = (numeric_parts.middle & 0x0000ffffU) | ((static_cast<std::uint32_t>((undefined2)((std::uint32_t)iVar13 >> 0x10)) & 0xffffU) << 16);

        numeric_parts.middle = (numeric_parts.middle & 0xffff0000U) | (static_cast<std::uint32_t>((undefined2)iVar13) & 0xffffU);

        numeric_parts.low = (numeric_parts.low & 0x0000ffffU) | ((static_cast<std::uint32_t>((undefined2)(uVar19 >> 0x10)) & 0xffffU) << 16);

        numeric_parts.low = (numeric_parts.low & 0xffff0000U) | (static_cast<std::uint32_t>((undefined2)uVar19) & 0xffffU);

        uVar20 = CONCAT22((undefined2)numeric_parts.middle,static_cast<undefined2>(static_cast<std::uint32_t>(numeric_parts.low) >> 16));

        uVar16 = CONCAT22(numeric_parts.upper_low,static_cast<undefined2>(static_cast<std::uint32_t>(numeric_parts.middle) >> 16));

        goto LAB_1001f1ab;

      }

      local_70 = 1;

    }

  }

  else {

    local_70 = 4;

  }

  numeric_parts.low = (numeric_parts.low & 0xffff0000U) | (static_cast<std::uint32_t>(0) & 0xffffU);

  numeric_parts.upper_high = 0;

  uVar16 = 0;

  uVar20 = 0;

LAB_1001f1ab:

  *(undefined2 *)pld12->ld12 = (undefined2)numeric_parts.low;

  *(std::uint16_t *)(pld12->ld12 + 10) = numeric_parts.upper_high | uVar5;

  *(undefined4 *)(pld12->ld12 + 2) = uVar20;

  *(undefined4 *)(pld12->ld12 + 6) = uVar16;

  return local_70;

}