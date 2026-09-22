#include <cstdint>

extern "C" void* __cdecl __getptd();

extern "C" std::uint32_t __cdecl __IsExceptionObjectToBeDestroyed(int param_1)
{
    struct FrameInfoNode
    {
        int exception_object;
        std::uint32_t next;
    };

    struct PtidData
    {
        std::uint32_t frame_info_chain;
    };

    PtidData* p_Var1 = static_cast<PtidData*>(__getptd());
    std::uint32_t frame_info_address = p_Var1->frame_info_chain;

    while (true)
    {
        if (frame_info_address == 0u)
        {
            return 1u;
        }

        FrameInfoNode* piVar2 =
            reinterpret_cast<FrameInfoNode*>(
                static_cast<std::uintptr_t>(frame_info_address));

        if (piVar2->exception_object == param_1)
        {
            break;
        }

        frame_info_address = piVar2->next;
    }

    return 0u;
}