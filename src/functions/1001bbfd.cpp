#include <cstddef>
#include <cstdint>
struct _CRT_FLOAT { float f; };
struct CRT_FLOAT_RESULT_SLOT { _CRT_FLOAT value; std::uint32_t high_word; };
static_assert(offsetof(_CRT_FLOAT, f) == 0);
static_assert(sizeof(_CRT_FLOAT) == 4);
static_assert(offsetof(CRT_FLOAT_RESULT_SLOT, high_word) == 4);
static_assert(sizeof(CRT_FLOAT_RESULT_SLOT) == 8);
extern "C" int __cdecl FID_conflict___atoflt_l_1001db04(_CRT_FLOAT*, char*, _locale_t);
extern "C" int __cdecl FID_conflict___atoflt_l_1001da5c(_CRT_FLOAT*, char*, _locale_t);

void __cdecl __fassign_l(
    int flag,
    char* argument,
    char* number,
    _locale_t param_4)
{
    CRT_FLOAT_RESULT_SLOT local_c;

    if (flag == 0)
    {
        FID_conflict___atoflt_l_1001db04(
            reinterpret_cast<_CRT_FLOAT*>(&flag),
            number,
            param_4);

        *reinterpret_cast<int*>(argument) = flag;
    }
    else
    {
        FID_conflict___atoflt_l_1001da5c(
            &local_c.value,
            number,
            param_4);

        *reinterpret_cast<float*>(argument) = local_c.value.f;
        *reinterpret_cast<unsigned int*>(argument + 4) = local_c.high_word;
    }
}