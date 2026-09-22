#include <cstdint>

extern "C" void __stdcall FID_conflict__CallMemberFunction1(
    std::uint32_t param_1,
    void* member_function);

void __cdecl ___DestructExceptionObject(int* param_1)
{
    if (param_1 != nullptr)
    {
        if (*param_1 == -0x1f928c9d)
        {
            if (param_1[7] != 0)
            {
                void* member_function =
                    *reinterpret_cast<void**>(
                        static_cast<std::uintptr_t>(
                            static_cast<std::uint32_t>(param_1[7])) + 4U);

                if (member_function != nullptr)
                {
                    FID_conflict__CallMemberFunction1(
                        static_cast<std::uint32_t>(param_1[6]),
                        member_function);
                }
            }
        }
    }
}