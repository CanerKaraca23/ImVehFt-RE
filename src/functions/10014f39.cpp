#include <cstdint>

using _ptiddata = void*;

extern int DAT_10029c0c;
extern std::uint32_t DAT_10029c10;
extern void* DAT_10039a7c;

extern "C" void* __stdcall TlsGetValue(std::uint32_t tlsIndex);
extern "C" void* __stdcall DecodePointer(void* encodedPointer);
extern "C" int __stdcall TlsSetValue(std::uint32_t tlsIndex, void* value);
extern "C" void __stdcall __freefls_4(_ptiddata ptd);

using fls_get_value_fn = _ptiddata(__cdecl*)(int);
using fls_free_value_fn = void(__cdecl*)(int, unsigned int);

extern "C" void __cdecl __freeptd(_ptiddata _Ptd)
{
    if (DAT_10029c0c != -1)
    {
        if ((_Ptd == nullptr) &&
            (TlsGetValue(DAT_10029c10) != nullptr))
        {
            const int iVar3 = DAT_10029c0c;
            const auto pcVar2 =
                reinterpret_cast<fls_get_value_fn>(
                    TlsGetValue(DAT_10029c10));

            _Ptd = (*pcVar2)(iVar3);
        }

        const unsigned int uVar4 = 0;
        const int iVar3 = DAT_10029c0c;
        const auto pcVar2 =
            reinterpret_cast<fls_free_value_fn>(
                DecodePointer(DAT_10039a7c));

        (*pcVar2)(iVar3, uVar4);
        __freefls_4(_Ptd);
    }

    if (DAT_10029c10 != 0xffffffffU)
    {
        TlsSetValue(DAT_10029c10, nullptr);
    }
}