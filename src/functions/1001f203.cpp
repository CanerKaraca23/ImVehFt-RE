#include <cstddef>
#include <cstdint>
#include <corecrt.h>
using undefined = unsigned char;
using undefined1 = std::uint8_t;
using undefined2 = std::uint16_t;
using undefined4 = std::uint32_t;
using byte = unsigned char;
using uint = std::uint32_t;
using longlong = std::int64_t;
using ulonglong = std::uint64_t;
using undefined8 = std::uint64_t;
// Ghidra raw-bit concatenation helpers: operand widths are encoded in each name.
#define CONCAT22(high, low) (static_cast<std::uint32_t>(((static_cast<std::uint32_t>(high) & 0xffffU) << 16) | (static_cast<std::uint32_t>(low) & 0xffffU)))
#define CONCAT12(high, low) (static_cast<std::uint32_t>(((static_cast<std::uint32_t>(high) & 0xffU) << 16) | (static_cast<std::uint32_t>(low) & 0xffffU)))
#define CONCAT13(high, low) (static_cast<std::uint32_t>(((static_cast<std::uint32_t>(high) & 0xffU) << 24) | (static_cast<std::uint32_t>(low) & 0xffffffU)))
#include <bit>
#include <cstdint>

#pragma warning(push)
#pragma warning(disable:4201)
union GhidraPointerWordOverlay {
    std::uint16_t* pointer;
    struct { std::uint16_t _0_2_; std::uint16_t _2_2_; };
    operator std::uint16_t*() const noexcept { return pointer; }
    GhidraPointerWordOverlay& operator=(std::uint16_t* value) noexcept {
        pointer = value;
        return *this;
    }
};
static_assert(sizeof(GhidraPointerWordOverlay) == 4);
static_assert(offsetof(GhidraPointerWordOverlay, _0_2_) == 0);
union GhidraDwordOverlay {
    std::uint32_t whole;
    struct { std::uint16_t _0_2_; std::uint16_t _2_2_; };
    operator std::uint32_t() const noexcept { return whole; }
    GhidraDwordOverlay& operator=(std::uint32_t value) noexcept {
        whole = value;
        return *this;
    }
};
static_assert(sizeof(GhidraDwordOverlay) == 4);
static_assert(offsetof(GhidraDwordOverlay, _0_2_) == 0);
static_assert(offsetof(GhidraDwordOverlay, _2_2_) == 2);
#pragma warning(pop)

// Ghidra shows these as byte-addressed table bases; indexed records are read by
// the decompiled routine at byte offsets derived from its 0x0c stride.
extern "C" std::uint32_t DAT_10029490;
extern "C" std::uint8_t DAT_10039698;
extern "C" std::uint8_t DAT_100397f8;
extern "C" [[noreturn]] void __cdecl __invoke_watson(
    wchar_t*, wchar_t*, wchar_t*, unsigned int, std::uintptr_t);
#define CONCAT11(high, low) (static_cast<std::uint16_t>(((static_cast<std::uint16_t>(high) & 0xffU) << 8) | (static_cast<std::uint16_t>(low) & 0xffU)))

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

/* WARNING: Removing unreachable block (ram,0x1001f712) */

/* WARNING: Removing unreachable block (ram,0x1001f71c) */

/* WARNING: Removing unreachable block (ram,0x1001f721) */

/* Library Function - Single Match

    _$I10_OUTPUT

   

   Library: Visual Studio 2010 Release */



undefined4 __cdecl

_I10_OUTPUT(int param_1,std::uint32_t param_2,std::uint16_t param_3,int param_4,std::uint8_t param_5,short *param_6)



{

  short *psVar1;

  int iVar2;

  bool bVar3;

  errno_t eVar4;

  std::uint16_t *puVar5;

  std::uint16_t uVar6;

  std::uint16_t *puVar7;

  int iVar8;

  std::uint32_t uVar9;

  std::uint16_t uVar10;

  std::uint32_t uVar11;

  std::int8_t cVar12;

  std::uint32_t uVar13;

  short *psVar14;

  short *psVar15;

  std::uint16_t uVar16;

  int iVar17;

  std::uint32_t uVar18;

  std::uint32_t uVar19;

  const char *pcVar20;

  std::uint16_t *local_74;

  std::uint16_t *local_70;

  undefined *local_6c;

  std::uint16_t local_64;

  GhidraPointerWordOverlay local_5c;

  int local_58;

  int local_54;

  short local_50;

  int local_4c;

  int local_48;

  int local_44;

  std::uint16_t local_40;

  undefined2 uStack_3e;

  undefined2 uStack_3c;

  undefined2 uStack_3a;

  undefined4 local_38;

  undefined4 local_34;

  undefined4 local_30;

  std::uint16_t local_2c [4];

  GhidraDwordOverlay local_24;

  GhidraDwordOverlay uStack_20;

  std::uint16_t uStack_1c;

  undefined1 local_1a;

  std::uint8_t bStack_19;

  std::uint8_t local_14;

  undefined1 uStack_13;

  std::uint16_t uStack_12;

  std::uint16_t local_10 [4];

  std::uint32_t local_8;

  

  local_8 = DAT_10029490 ^ reinterpret_cast<std::uint32_t>(&local_8);

  local_64 = param_3 & 0x8000;

  uVar11 = param_3 & 0x7fff;

  local_34 = 0xcccccccc;

  local_30 = 0xcccccccc;

  local_2c[0] = 0xcccc;

  local_2c[1] = 0x3ffb;

  if (local_64 == 0) {

    *(undefined1 *)(param_6 + 1) = 0x20;

  }

  else {

    *(undefined1 *)(param_6 + 1) = 0x2d;

  }

  if ((short)uVar11 == 0) {

    if ((param_2 == 0) && (param_1 == 0)) {

      *param_6 = 0;

      *(std::uint8_t *)(param_6 + 1) = ((local_64 != 0x8000) - 1U & 0xd) + 0x20;

      *(undefined2 *)((int)param_6 + 3) = 0x3001;

      *(undefined1 *)((int)param_6 + 5) = 0;

      return 1;

    }

  }

  else if ((short)uVar11 == 0x7fff) {

    *param_6 = 1;

    if (((param_2 == 0x80000000) && (param_1 == 0)) || ((param_2 & 0x40000000) != 0)) {

      if ((local_64 == 0) || (param_2 != 0xc0000000)) {

        if ((param_2 != 0x80000000) || (param_1 != 0)) goto LAB_1001f322;

        pcVar20 = "1#INF";

      }

      else {

        if (param_1 != 0) {

LAB_1001f322:

          pcVar20 = "1#QNAN";

          goto LAB_1001f327;

        }

        pcVar20 = "1#IND";

      }

      eVar4 = strcpy_s((char *)(param_6 + 2),0x16,pcVar20);

      if (eVar4 != 0) goto LAB_1001f2d4;

      *(undefined1 *)((int)param_6 + 3) = 5;

    }

    else {

      pcVar20 = "1#SNAN";

LAB_1001f327:

      eVar4 = strcpy_s((char *)(param_6 + 2),0x16,pcVar20);

      if (eVar4 != 0) {

LAB_1001f2d4:

                    /* WARNING: Subroutine does not return */

        __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);

      }

      *(undefined1 *)((int)param_6 + 3) = 6;

    }

    return 0;

  }

  local_50 = (short)((((uVar11 >> 8) + (param_2 >> 0x18) * 2) * 0x4d + -0x134312f4 + uVar11 * 0x4d10)
                    >> 0x10);

  local_24._0_2_ = 0;

  uVar13 = -(int)local_50;

  local_1a = (undefined1)uVar11;

  bStack_19 = (std::uint8_t)(uVar11 >> 8);

  uStack_20._2_2_ = (std::uint16_t)param_2;

  uStack_1c = (std::uint16_t)(param_2 >> 0x10);

  local_24._2_2_ = (std::uint16_t)param_1;

  iVar17 = param_1 << 0x10;

  uStack_20._0_2_ = (std::uint16_t)((std::uint32_t)param_1 >> 0x10);

  local_6c = &DAT_10039698;

  if (uVar13 != 0) {

    if ((int)uVar13 < 0) {

      local_6c = &DAT_100397f8;

      uVar13 = (int)local_50;

    }

    while (uVar13 != 0) {

      uStack_1c = (std::uint16_t)(param_2 >> 0x10);

      uStack_20._2_2_ = (std::uint16_t)param_2;

      iVar2 = CONCAT22(uStack_20._2_2_,(std::uint16_t)uStack_20);

      local_6c = local_6c + 0x54;

      if ((uVar13 & 7) != 0) {

        puVar7 = (std::uint16_t *)(local_6c + (uVar13 & 7) * 0xc);

        if (0x7fff < *puVar7) {

          local_40 = (std::uint16_t)*(undefined4 *)puVar7;

          uStack_3e = (undefined2)((std::uint32_t)*(undefined4 *)puVar7 >> 0x10);

          puVar5 = puVar7 + 4;

          uStack_3c = (undefined2)*(undefined4 *)(puVar7 + 2);

          uStack_3a = (undefined2)((std::uint32_t)*(undefined4 *)(puVar7 + 2) >> 0x10);

          puVar7 = &local_40;

          local_38 = *(undefined4 *)puVar5;

          iVar8 = CONCAT22(uStack_3c,uStack_3e) + -1;

          uStack_3e = (undefined2)iVar8;

          uStack_3c = (undefined2)((std::uint32_t)iVar8 >> 0x10);

        }

        local_4c = 0;

        local_14 = 0;

        uStack_13 = 0;

        uStack_12 = 0;

        local_10[0] = 0;

        local_10[1] = 0;

        local_10[2] = 0;

        local_10[3] = 0;

        local_5c._0_2_ = (puVar7[5] ^ CONCAT11(bStack_19,local_1a)) & 0x8000;

        uVar10 = CONCAT11(bStack_19,local_1a) & 0x7fff;

        uVar6 = puVar7[5] & 0x7fff;

        uVar16 = uVar6 + uVar10;

        if (((uVar10 < 0x7fff) && (uVar6 < 0x7fff)) && (uVar16 < 0xbffe)) {

          if (0x3fbf < uVar16) {

            if (((uVar10 == 0) &&

                (uVar16 = uVar16 + 1,

                (CONCAT13(bStack_19,CONCAT12(local_1a,uStack_1c)) & 0x7fffffff) == 0)) &&

               ((CONCAT22(uStack_20._2_2_,(std::uint16_t)uStack_20) == 0 && (iVar17 == 0)))) {

              local_1a = 0;

              bStack_19 = 0;

              goto LAB_1001f627;

            }

            if (((uVar6 == 0) && (uVar16 = uVar16 + 1, (*(std::uint32_t *)(puVar7 + 4) & 0x7fffffff) == 0))

               && ((*(int *)(puVar7 + 2) == 0 && (*(int *)puVar7 == 0)))) goto LAB_1001f447;

            local_58 = 0;

            puVar5 = local_10;

            local_44 = 5;

            do {

              local_54 = local_44;

              if (0 < local_44) {

                local_74 = (std::uint16_t *)((int)&local_24 + local_58 * 2);

                local_70 = puVar7 + 4;

                do {

                  bVar3 = false;

                  uVar11 = *(std::uint32_t *)(puVar5 + -2) + (std::uint32_t)*local_74 * (std::uint32_t)*local_70;

                  if ((uVar11 < *(std::uint32_t *)(puVar5 + -2)) ||

                     (uVar11 < (std::uint32_t)*local_74 * (std::uint32_t)*local_70)) {

                    bVar3 = true;

                  }

                  *(std::uint32_t *)(puVar5 + -2) = uVar11;

                  if (bVar3) {

                    *puVar5 = *puVar5 + 1;

                  }

                  local_74 = local_74 + 1;

                  local_70 = local_70 + -1;

                  local_54 = local_54 + -1;

                } while (0 < local_54);

              }

              puVar5 = puVar5 + 1;

              local_58 = local_58 + 1;

              local_44 = local_44 + -1;

            } while (0 < local_44);

            uVar16 = uVar16 + 0xc002;

            if ((short)uVar16 < 1) {

LAB_1001f559:

              uVar16 = uVar16 - 1;

              if ((short)uVar16 < 0) {

                uVar11 = (std::uint32_t)(std::uint16_t)-uVar16;

                uVar16 = 0;

                do {

                  if ((local_14 & 1) != 0) {

                    local_4c = local_4c + 1;

                  }

                  iVar2 = CONCAT22(local_10[3],local_10[2]);

                  uVar9 = CONCAT22(local_10[1],local_10[0]);

                  iVar17 = CONCAT22(local_10[1],local_10[0]);

                  local_10[2] = (std::uint16_t)(CONCAT22(local_10[3],local_10[2]) >> 1);

                  local_10[3] = local_10[3] >> 1;

                  local_10[1] = local_10[1] >> 1 | (std::uint16_t)((std::uint32_t)(iVar2 << 0x1f) >> 0x10);

                  uVar18 = CONCAT22(uStack_12,CONCAT11(uStack_13,local_14)) >> 1;

                  uStack_12 = uStack_12 >> 1 | (std::uint16_t)((std::uint32_t)(iVar17 << 0x1f) >> 0x10);

                  uVar11 = uVar11 - 1;

                  local_10[0] = (std::uint16_t)(uVar9 >> 1);

                  local_14 = (std::uint8_t)uVar18;

                  uStack_13 = (undefined1)(uVar18 >> 8);

                } while (uVar11 != 0);

                if (local_4c != 0) {

                  local_14 = local_14 | 1;

                }

              }

            }

            else {

              do {

                uVar10 = local_10[1];

                uVar6 = uStack_12;

                if ((local_10[3] & 0x8000) != 0) break;

                iVar17 = CONCAT22(uStack_12,CONCAT11(uStack_13,local_14)) << 1;

                local_14 = (std::uint8_t)iVar17;

                uStack_13 = (undefined1)((std::uint32_t)iVar17 >> 8);

                uStack_12 = (std::uint16_t)((std::uint32_t)iVar17 >> 0x10);

                iVar17 = CONCAT22(local_10[1],local_10[0]) * 2;

                local_10[0] = (std::uint16_t)iVar17 | uVar6 >> 0xf;

                local_10[1] = (std::uint16_t)((std::uint32_t)iVar17 >> 0x10);

                iVar17 = CONCAT22(local_10[3],local_10[2]) * 2;

                local_10[2] = (std::uint16_t)iVar17 | uVar10 >> 0xf;

                uVar16 = uVar16 - 1;

                local_10[3] = (std::uint16_t)((std::uint32_t)iVar17 >> 0x10);

              } while (0 < (short)uVar16);

              if ((short)uVar16 < 1) goto LAB_1001f559;

            }

            if ((0x8000 < CONCAT11(uStack_13,local_14)) ||

               (iVar2 = CONCAT22(local_10[2],local_10[1]), iVar17 = CONCAT22(local_10[0],uStack_12),

               (CONCAT22(uStack_12,CONCAT11(uStack_13,local_14)) & 0x1ffff) == 0x18000)) {

              if (CONCAT22(local_10[0],uStack_12) == -1) {

                iVar17 = 0;

                if (CONCAT22(local_10[2],local_10[1]) == -1) {

                  if (local_10[3] == 0xffff) {

                    local_10[3] = 0x8000;

                    uVar16 = uVar16 + 1;

                    iVar2 = 0;

                    iVar17 = 0;

                  }

                  else {

                    local_10[3] = local_10[3] + 1;

                    iVar2 = 0;

                    iVar17 = 0;

                  }

                }

                else {

                  iVar2 = CONCAT22(local_10[2],local_10[1]) + 1;

                }

              }

              else {

                iVar17 = CONCAT22(local_10[0],uStack_12) + 1;

                iVar2 = CONCAT22(local_10[2],local_10[1]);

              }

            }

            if (uVar16 < 0x7fff) {

              bStack_19 = (std::uint8_t)(uVar16 >> 8) | (std::uint8_t)(local_5c._0_2_ >> 8);

              local_24 = iVar17;

              uStack_20 = iVar2;

              uStack_1c = local_10[3];

              local_1a = (undefined1)uVar16;

            }

            else {

              uStack_20._0_2_ = 0;

              uStack_20._2_2_ = 0;

              iVar2 = 0;

              local_24._0_2_ = 0;

              local_24._2_2_ = 0;

              iVar17 = 0;

              iVar8 = ((local_5c._0_2_ == 0) - 1 & 0x80000000) + 0x7fff8000;

              uStack_1c = (std::uint16_t)iVar8;

              local_1a = (undefined1)((std::uint32_t)iVar8 >> 0x10);

              bStack_19 = (std::uint8_t)((std::uint32_t)iVar8 >> 0x18);

            }

            goto LAB_1001f627;

          }

LAB_1001f447:

          uStack_1c = 0;

          local_1a = 0;

          bStack_19 = 0;

        }

        else {

          iVar17 = ((local_5c._0_2_ == 0) - 1 & 0x80000000) + 0x7fff8000;

          uStack_1c = (std::uint16_t)iVar17;

          local_1a = (undefined1)((std::uint32_t)iVar17 >> 0x10);

          bStack_19 = (std::uint8_t)((std::uint32_t)iVar17 >> 0x18);

        }

        uStack_20._0_2_ = 0;

        uStack_20._2_2_ = 0;

        iVar2 = 0;

        local_24._0_2_ = 0;

        local_24._2_2_ = 0;

        iVar17 = 0;

      }

LAB_1001f627:

      uStack_20._2_2_ = (std::uint16_t)((std::uint32_t)iVar2 >> 0x10);

      uStack_20._0_2_ = (std::uint16_t)iVar2;

      local_24._2_2_ = (std::uint16_t)((std::uint32_t)iVar17 >> 0x10);

      local_24._0_2_ = (undefined2)iVar17;

      param_1 = CONCAT22((std::uint16_t)uStack_20,local_24._2_2_);

      param_2 = CONCAT22(uStack_1c,uStack_20._2_2_);

      uVar13 = (int)uVar13 >> 3;

    }

  }

  uStack_20._0_2_ = (std::uint16_t)((std::uint32_t)param_1 >> 0x10);

  local_24._2_2_ = (std::uint16_t)param_1;

  uStack_1c = (std::uint16_t)(param_2 >> 0x10);

  uStack_20._2_2_ = (std::uint16_t)param_2;

  uVar11 = CONCAT13(bStack_19,CONCAT12(local_1a,uStack_1c));

  if ((std::uint16_t)(uVar11 >> 0x10) < 0x3fff) goto LAB_1001f8e7;

  local_50 = local_50 + 1;

  local_54 = 0;

  local_14 = 0;

  uStack_13 = 0;

  uStack_12 = 0;

  local_10[0] = 0;

  local_10[1] = 0;

  local_10[2] = 0;

  local_10[3] = 0;

  uVar11 = uVar11 >> 0x10 & 0x7fff;

  iVar17 = uVar11 + 0x3ffb;

  if (((std::uint16_t)uVar11 < 0x7fff) && ((std::uint16_t)iVar17 < 0xbffe)) {

    if (0x3fbf < (std::uint16_t)iVar17) {

      if (((((std::uint16_t)uVar11 == 0) &&

           (iVar17 = uVar11 + 0x3ffc,

           (CONCAT13(bStack_19,CONCAT12(local_1a,uStack_1c)) & 0x7fffffff) == 0)) &&

          (CONCAT22(uStack_20._2_2_,(std::uint16_t)uStack_20) == 0)) &&

         (CONCAT22(local_24._2_2_,(undefined2)local_24) == 0)) {

        local_1a = 0;

        bStack_19 = 0;

        goto LAB_1001f8e7;

      }

      local_58 = 0;

      puVar7 = local_10;

      local_44 = 5;

      do {

        local_4c = local_44;

        if (0 < local_44) {

          local_5c = local_2c;

          puVar5 = (std::uint16_t *)((int)&local_24 + local_58 * 2);

          do {

            bVar3 = false;

            uVar11 = *(std::uint32_t *)(puVar7 + -2) + (std::uint32_t)*local_5c * (std::uint32_t)*puVar5;

            if ((uVar11 < *(std::uint32_t *)(puVar7 + -2)) || (uVar11 < (std::uint32_t)*local_5c * (std::uint32_t)*puVar5)) {

              bVar3 = true;

            }

            *(std::uint32_t *)(puVar7 + -2) = uVar11;

            if (bVar3) {

              *puVar7 = *puVar7 + 1;

            }

            local_5c = local_5c + -1;

            puVar5 = puVar5 + 1;

            local_4c = local_4c + -1;

          } while (0 < local_4c);

        }

        puVar7 = puVar7 + 1;

        local_58 = local_58 + 1;

        local_44 = local_44 + -1;

      } while (0 < local_44);

      iVar17 = iVar17 + 0xc002;

      if ((short)iVar17 < 1) {

LAB_1001f7e2:

        uVar16 = (std::uint16_t)(iVar17 + 0xffff);

        if ((short)uVar16 < 0) {

          uVar11 = -(iVar17 + 0xffff);

          uVar13 = uVar11 & 0xffff;

          uVar16 = uVar16 + (short)uVar11;

          do {

            if ((local_14 & 1) != 0) {

              local_54 = local_54 + 1;

            }

            iVar2 = CONCAT22(local_10[3],local_10[2]);

            uVar11 = CONCAT22(local_10[1],local_10[0]);

            iVar17 = CONCAT22(local_10[1],local_10[0]);

            local_10[2] = (std::uint16_t)(CONCAT22(local_10[3],local_10[2]) >> 1);

            local_10[3] = local_10[3] >> 1;

            local_10[1] = local_10[1] >> 1 | (std::uint16_t)((std::uint32_t)(iVar2 << 0x1f) >> 0x10);

            uVar9 = CONCAT22(uStack_12,CONCAT11(uStack_13,local_14)) >> 1;

            uStack_12 = uStack_12 >> 1 | (std::uint16_t)((std::uint32_t)(iVar17 << 0x1f) >> 0x10);

            uVar13 = uVar13 - 1;

            local_10[0] = (std::uint16_t)(uVar11 >> 1);

            local_14 = (std::uint8_t)uVar9;

            uStack_13 = (undefined1)(uVar9 >> 8);

          } while (uVar13 != 0);

          if (local_54 != 0) {

            local_14 = local_14 | 1;

          }

        }

      }

      else {

        do {

          uVar6 = local_10[1];

          uVar16 = uStack_12;

          if ((short)local_10[3] < 0) break;

          iVar2 = CONCAT22(uStack_12,CONCAT11(uStack_13,local_14)) << 1;

          local_14 = (std::uint8_t)iVar2;

          uStack_13 = (undefined1)((std::uint32_t)iVar2 >> 8);

          uStack_12 = (std::uint16_t)((std::uint32_t)iVar2 >> 0x10);

          iVar2 = CONCAT22(local_10[1],local_10[0]) * 2;

          local_10[0] = (std::uint16_t)iVar2 | uVar16 >> 0xf;

          local_10[1] = (std::uint16_t)((std::uint32_t)iVar2 >> 0x10);

          iVar2 = CONCAT22(local_10[3],local_10[2]) * 2;

          local_10[2] = (std::uint16_t)iVar2 | uVar6 >> 0xf;

          iVar17 = iVar17 + 0xffff;

          local_10[3] = (std::uint16_t)((std::uint32_t)iVar2 >> 0x10);

        } while (0 < (short)iVar17);

        uVar16 = (std::uint16_t)iVar17;

        if ((short)uVar16 < 1) goto LAB_1001f7e2;

      }

      if ((0x8000 < CONCAT11(uStack_13,local_14)) ||

         (iVar2 = CONCAT22(local_10[2],local_10[1]), iVar17 = CONCAT22(local_10[0],uStack_12),

         (CONCAT22(uStack_12,CONCAT11(uStack_13,local_14)) & 0x1ffff) == 0x18000)) {

        if (CONCAT22(local_10[0],uStack_12) == -1) {

          iVar17 = 0;

          if (CONCAT22(local_10[2],local_10[1]) == -1) {

            if (local_10[3] == 0xffff) {

              local_10[3] = 0x8000;

              uVar16 = uVar16 + 1;

              iVar2 = 0;

              iVar17 = 0;

            }

            else {

              local_10[3] = local_10[3] + 1;

              iVar2 = 0;

              iVar17 = 0;

            }

          }

          else {

            iVar2 = CONCAT22(local_10[2],local_10[1]) + 1;

          }

        }

        else {

          iVar17 = CONCAT22(local_10[0],uStack_12) + 1;

          iVar2 = CONCAT22(local_10[2],local_10[1]);

        }

      }

      local_10[0] = (std::uint16_t)((std::uint32_t)iVar17 >> 0x10);

      uStack_12 = (std::uint16_t)iVar17;

      local_10[2] = (std::uint16_t)((std::uint32_t)iVar2 >> 0x10);

      local_10[1] = (std::uint16_t)iVar2;

      if (uVar16 < 0x7fff) {

        bStack_19 = (std::uint8_t)(uVar16 >> 8) | bStack_19 & 0x80;

        local_24._0_2_ = uStack_12;

        param_1 = CONCAT22(local_10[1],local_10[0]);

        param_2 = CONCAT22(local_10[3],local_10[2]);

        local_1a = (undefined1)uVar16;

      }

      else {

        local_24._0_2_ = 0;

        param_1 = 0;

        iVar17 = (((bStack_19 & 0x80) == 0) - 1 & 0x80000000) + 0x7fff8000;

        param_2 = 0x80000000;

        local_1a = (undefined1)((std::uint32_t)iVar17 >> 0x10);

        bStack_19 = (std::uint8_t)((std::uint32_t)iVar17 >> 0x18);

      }

      goto LAB_1001f8e7;

    }

    iVar17 = 0;

  }

  else {

    iVar17 = (((bStack_19 & 0x80) == 0) - 1 & 0x80000000) + 0x7fff8000;

  }

  param_1 = 0;

  local_24._0_2_ = 0;

  param_2 = iVar17 << 0x10;

  local_1a = (undefined1)((std::uint32_t)iVar17 >> 0x10);

  bStack_19 = (std::uint8_t)((std::uint32_t)iVar17 >> 0x18);

LAB_1001f8e7:

  *param_6 = local_50;

  if (((param_5 & 1) != 0) && (param_4 = param_4 + local_50, param_4 < 1)) {

    *param_6 = 0;

    *(undefined2 *)((int)param_6 + 3) = 0x3001;

    *(std::uint8_t *)(param_6 + 1) = ((local_64 != 0x8000) - 1U & 0xd) + 0x20;

    *(undefined1 *)((int)param_6 + 5) = 0;

    return 1;

  }

  if (0x15 < param_4) {

    param_4 = 0x15;

  }

  iVar17 = CONCAT11(bStack_19,local_1a) - 0x3ffe;

  local_1a = 0;

  bStack_19 = 0;

  local_48 = 8;

  do {

    uStack_1c = (std::uint16_t)(param_2 >> 0x10);

    uStack_20._2_2_ = (std::uint16_t)param_2;

    uStack_20._0_2_ = (std::uint16_t)((std::uint32_t)param_1 >> 0x10);

    local_24._2_2_ = (std::uint16_t)param_1;

    uVar6 = local_24._2_2_;

    iVar2 = CONCAT22(local_24._2_2_,(undefined2)local_24) << 1;

    local_24._0_2_ = (undefined2)iVar2;

    local_24._2_2_ = (std::uint16_t)((std::uint32_t)iVar2 >> 0x10);

    uVar11 = CONCAT22(uStack_20._2_2_,(std::uint16_t)uStack_20) * 2;

    uVar16 = uStack_20._2_2_ >> 0xf;

    uVar13 = CONCAT13(bStack_19,CONCAT12(local_1a,uStack_1c)) * 2;

    local_48 = local_48 + -1;

    uStack_20._0_2_ = (std::uint16_t)(uVar11 | uVar6 >> 0xf);

    param_1 = CONCAT22((std::uint16_t)uStack_20,local_24._2_2_);

    uStack_20._2_2_ = (std::uint16_t)(uVar11 >> 0x10);

    uStack_1c = (std::uint16_t)(uVar13 | uVar16);

    param_2 = CONCAT22(uStack_1c,uStack_20._2_2_);

    local_1a = (undefined1)(uVar13 >> 0x10);

    bStack_19 = (std::uint8_t)(uVar13 >> 0x18);

  } while (local_48 != 0);

  if ((iVar17 < 0) && (uVar11 = -iVar17 & 0xff, uVar11 != 0)) {

    do {

      iVar2 = CONCAT13(bStack_19,CONCAT12(local_1a,uStack_1c));

      uVar9 = CONCAT22(uStack_20._2_2_,(std::uint16_t)uStack_20);

      iVar17 = CONCAT22(uStack_20._2_2_,(std::uint16_t)uStack_20);

      uVar13 = CONCAT13(bStack_19,CONCAT12(local_1a,uStack_1c)) >> 1;

      uStack_1c = (std::uint16_t)uVar13;

      local_1a = (undefined1)(uVar13 >> 0x10);

      bStack_19 = bStack_19 >> 1;

      uStack_20._2_2_ = uStack_20._2_2_ >> 1 | (std::uint16_t)((std::uint32_t)(iVar2 << 0x1f) >> 0x10);

      uVar13 = CONCAT22(local_24._2_2_,(undefined2)local_24);

      local_24._2_2_ = local_24._2_2_ >> 1 | (std::uint16_t)((std::uint32_t)(iVar17 << 0x1f) >> 0x10);

      uVar11 = uVar11 - 1;

      uStack_20._0_2_ = (std::uint16_t)(uVar9 >> 1);

      local_24._0_2_ = (undefined2)(uVar13 >> 1);

    } while (0 < (int)uVar11);

  }

  uVar11 = CONCAT22(local_24._2_2_,(undefined2)local_24);

  psVar1 = param_6 + 2;

  psVar14 = psVar1;

  for (iVar17 = param_4 + 1; 0 < iVar17; iVar17 = iVar17 + -1) {

    uVar9 = (CONCAT13(bStack_19,CONCAT12(local_1a,uStack_1c)) * 2 | (std::uint32_t)(uStack_20._2_2_ >> 0xf))

            * 2 | (CONCAT22(uStack_20._2_2_,(std::uint16_t)uStack_20) & 0x7fffffff) >> 0x1e;

    uVar18 = (CONCAT22(uStack_20._2_2_,(std::uint16_t)uStack_20) * 2 | uVar11 >> 0x1f) * 2 |

             (uVar11 & 0x7fffffff) >> 0x1e;

    uVar13 = uVar11 * 5;

    if ((uVar13 < uVar11 * 4) || (uVar19 = uVar18, uVar13 < uVar11)) {

      uVar19 = uVar18 + 1;

      bVar3 = false;

      if ((uVar19 < uVar18) || (uVar19 == 0)) {

        bVar3 = true;

      }

      if (bVar3) {

        uVar9 = uVar9 + 1;

      }

    }

    uVar18 = CONCAT22(uStack_20._2_2_,(std::uint16_t)uStack_20) + uVar19;

    if ((uVar18 < uVar19) || (uVar18 < CONCAT22(uStack_20._2_2_,(std::uint16_t)uStack_20))) {

      uVar9 = uVar9 + 1;

    }

    iVar2 = (uVar9 + CONCAT13(bStack_19,CONCAT12(local_1a,uStack_1c))) * 2;

    uStack_1c = (std::uint16_t)iVar2 | (std::uint16_t)(uVar18 >> 0x1f);

    uVar11 = uVar11 * 10;

    local_1a = (undefined1)((std::uint32_t)iVar2 >> 0x10);

    uStack_20._0_2_ = (std::uint16_t)(uVar18 * 2) | (std::uint16_t)(uVar13 >> 0x1f);

    *(char *)psVar14 = (char)((std::uint32_t)iVar2 >> 0x18) + '0';

    psVar14 = (short *)((int)psVar14 + 1);

    uStack_20._2_2_ = (std::uint16_t)(uVar18 * 2 >> 0x10);

    bStack_19 = 0;

  }

  psVar15 = psVar14 + -1;

  if (*(char *)((int)psVar14 + -1) < '5') {

    for (; (psVar1 <= psVar15 && ((char)*psVar15 == '0')); psVar15 = (short *)((int)psVar15 + -1)) {

    }

    if (psVar15 < psVar1) {

      *param_6 = 0;

      *(undefined1 *)((int)param_6 + 3) = 1;

      *(std::uint8_t *)(param_6 + 1) = ((local_64 != 0x8000) - 1U & 0xd) + 0x20;

      *(char *)psVar1 = '0';

      *(undefined1 *)((int)param_6 + 5) = 0;

      return 1;

    }

  }

  else {

    for (; (psVar1 <= psVar15 && ((char)*psVar15 == '9')); psVar15 = (short *)((int)psVar15 + -1)) {

      *(char *)psVar15 = '0';

    }

    if (psVar15 < psVar1) {

      psVar15 = (short *)((int)psVar15 + 1);

      *param_6 = *param_6 + 1;

    }

    *(char *)psVar15 = (char)*psVar15 + '\x01';

  }

  const std::uint8_t ps_low = static_cast<std::uint8_t>(reinterpret_cast<std::uintptr_t>(psVar15));
  const std::uint8_t output_low = static_cast<std::uint8_t>(reinterpret_cast<std::uintptr_t>(param_6));
  const std::uint8_t delta = static_cast<std::uint8_t>(ps_low - output_low - 3U);
  cVar12 = std::bit_cast<std::int8_t>(delta);

  *(char *)((int)param_6 + 3) = cVar12;

  *(undefined1 *)(cVar12 + 4 + (int)param_6) = 0;

  return 1;

}
