#pragma once

#if defined(_MSC_VER) && defined(_M_IX86)
#pragma comment(linker, "/alternatename:_IVF_LocaleUpdate_ctor_relocatable=??0_LocaleUpdate@@QAE@PAUlocaleinfo_struct@@@Z")
extern "C" void __cdecl IVF_LocaleUpdate_ctor_relocatable();
#else
#error "The recovered _LocaleUpdate constructor bridge requires MSVC x86."
#endif
