#include <cstddef>
#include <cstdint>

struct TidDataFrameInfoView
{
    std::uint8_t reserved_00[0x98];
    unsigned long* pFrameInfoChain;
};

static_assert(offsetof(TidDataFrameInfoView, pFrameInfoChain) == 0x98);

extern "C" TidDataFrameInfoView* __cdecl __getptd(void);

unsigned long* __cdecl __CreateFrameInfo(
    unsigned long* param_1,
    unsigned long param_2)
{
    *param_1 = param_2;

    TidDataFrameInfoView* p_Var1 = __getptd();
    param_1[1] = reinterpret_cast<unsigned long>(
        p_Var1->pFrameInfoChain);

    p_Var1 = __getptd();
    p_Var1->pFrameInfoChain = param_1;

    return param_1;
}