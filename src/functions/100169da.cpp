#include <cstdint>

extern "C" int __cdecl __ismbblead(std::uint32_t);


/* Library Function - Single Match

    _parse_cmdline

   

   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */



void __cdecl parse_cmdline(std::uint8_t** param_1,std::uint8_t *param_2,int *param_3)



{

  bool bVar1;

  bool bVar2;

  int iVar3;

  std::uint32_t uVar4;

  std::uint8_t *in_EDX;

  std::uint8_t *pbVar5;

  std::uint8_t bVar6;

  std::uint8_t *pbVar7;

  std::uint8_t *pbVar8;

  int *unaff_EDI;

  // Entry-register inputs confirmed by x86 instructions 0x100169e7 and 0x100169e9.
#if defined(_MSC_VER) && defined(_M_IX86)
  __asm mov in_EDX, edx
  __asm mov unaff_EDI, edi
#elif defined(__GNUC__) && defined(__i386__)
  register std::uint8_t *edx_input __asm__("edx");
  register int *edi_input __asm__("edi");
  in_EDX = edx_input;
  unaff_EDI = edi_input;
#else
#error "parse_cmdline requires the x86 entry values in EDX and EDI"
#endif

  

  *unaff_EDI = 0;

  *param_3 = 1;

  if (param_1 != nullptr) {

    *param_1 = param_2;

    param_1 = param_1 + 1;

  }

  bVar2 = false;

  pbVar5 = param_2;

  do {

    if (*in_EDX == 0x22) {

      bVar2 = !bVar2;

      bVar6 = 0x22;

      pbVar7 = in_EDX + 1;

    }

    else {

      *unaff_EDI = *unaff_EDI + 1;

      if (pbVar5 != (std::uint8_t *)0x0) {

        *pbVar5 = *in_EDX;

        param_2 = pbVar5 + 1;

      }

      bVar6 = *in_EDX;

      pbVar7 = in_EDX + 1;

      iVar3 = __ismbblead((std::uint32_t)bVar6);

      if (iVar3 != 0) {

        *unaff_EDI = *unaff_EDI + 1;

        if (param_2 != (std::uint8_t *)0x0) {

          *param_2 = *pbVar7;

          param_2 = param_2 + 1;

        }

        pbVar7 = in_EDX + 2;

      }

      pbVar5 = param_2;

      if (bVar6 == 0) {

        pbVar7 = pbVar7 + -1;

        goto LAB_10016a6e;

      }

    }

    in_EDX = pbVar7;

  } while ((bVar2) || ((bVar6 != 0x20 && (bVar6 != 9))));

  if (pbVar5 != (std::uint8_t *)0x0) {

    pbVar5[-1] = 0;

  }

LAB_10016a6e:

  bVar2 = false;

  while (*pbVar7 != 0) {

    for (; (*pbVar7 == 0x20 || (*pbVar7 == 9)); pbVar7 = pbVar7 + 1) {

    }

    if (*pbVar7 == 0) break;

    if (param_1 != nullptr) {

      *param_1 = pbVar5;

      param_1 = param_1 + 1;

    }

    *param_3 = *param_3 + 1;

    while( true ) {

      bVar1 = true;

      uVar4 = 0;

      for (; *pbVar7 == 0x5c; pbVar7 = pbVar7 + 1) {

        uVar4 = uVar4 + 1;

      }

      if (*pbVar7 == 0x22) {

        pbVar8 = pbVar7;

        if (((uVar4 & 1) == 0) && ((!bVar2 || (pbVar8 = pbVar7 + 1, *pbVar8 != 0x22)))) {

          bVar1 = false;

          bVar2 = !bVar2;

          pbVar8 = pbVar7;

        }

        uVar4 = uVar4 >> 1;

        pbVar7 = pbVar8;

      }

      while (uVar4 != 0) {

        uVar4 = uVar4 - 1;

        if (pbVar5 != (std::uint8_t *)0x0) {

          *pbVar5 = 0x5c;

          pbVar5 = pbVar5 + 1;

        }

        *unaff_EDI = *unaff_EDI + 1;

        param_2 = pbVar5;

      }

      bVar6 = *pbVar7;

      if ((bVar6 == 0) || ((!bVar2 && ((bVar6 == 0x20 || (bVar6 == 9)))))) break;

      if (bVar1) {

        if (pbVar5 == (std::uint8_t *)0x0) {

          iVar3 = __ismbblead((int)(char)bVar6);

          if (iVar3 != 0) {

            pbVar7 = pbVar7 + 1;

            *unaff_EDI = *unaff_EDI + 1;

          }

        }

        else {

          iVar3 = __ismbblead((int)(char)bVar6);

          if (iVar3 != 0) {

            *param_2 = *pbVar7;

            pbVar7 = pbVar7 + 1;

            *unaff_EDI = *unaff_EDI + 1;

            param_2 = param_2 + 1;

          }

          *param_2 = *pbVar7;

          param_2 = param_2 + 1;

        }

        *unaff_EDI = *unaff_EDI + 1;

        pbVar5 = param_2;

      }

      pbVar7 = pbVar7 + 1;

    }

    if (pbVar5 != (std::uint8_t *)0x0) {

      *pbVar5 = 0;

      pbVar5 = pbVar5 + 1;

      param_2 = pbVar5;

    }

    *unaff_EDI = *unaff_EDI + 1;

  }

  if (param_1 != nullptr) {

    *param_1 = 0;

  }

  *param_3 = *param_3 + 1;

  return;

}
