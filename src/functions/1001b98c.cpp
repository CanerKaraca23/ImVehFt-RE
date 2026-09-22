#include <cstdint>

static_assert(sizeof(void*) == 4, "Requires 32-bit pointers.");

extern "C" void* __cdecl __getptd();
extern "C" void __cdecl _inconsistency();

extern "C" void __cdecl __FindAndUnlinkFrame(void* param_1)
{
    struct FrameInfoNode
    {
        std::uint32_t reserved_0;
        std::uint32_t next;
    };

    struct _tiddata
    {
        FrameInfoNode* _pFrameInfoChain;
    };

    void* pvVar1;
    _tiddata* p_Var2;
    void* pvVar3;

    p_Var2 = static_cast<_tiddata*>(__getptd());

    if (param_1 == p_Var2->_pFrameInfoChain)
    {
        p_Var2 = static_cast<_tiddata*>(__getptd());
        p_Var2->_pFrameInfoChain =
            reinterpret_cast<FrameInfoNode*>(
                static_cast<std::uintptr_t>(
                    reinterpret_cast<FrameInfoNode*>(param_1)->next));
    }
    else
    {
        p_Var2 = static_cast<_tiddata*>(__getptd());
        pvVar1 = p_Var2->_pFrameInfoChain;

        do
        {
            pvVar3 = pvVar1;

            if (reinterpret_cast<FrameInfoNode*>(pvVar3)->next == 0)
            {
                _inconsistency();
                return;
            }

            pvVar1 = reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    reinterpret_cast<FrameInfoNode*>(pvVar3)->next));
        }
        while (
            param_1 != reinterpret_cast<void*>(
                static_cast<std::uintptr_t>(
                    reinterpret_cast<FrameInfoNode*>(pvVar3)->next)));

        reinterpret_cast<FrameInfoNode*>(pvVar3)->next =
            reinterpret_cast<FrameInfoNode*>(param_1)->next;
    }
}