#include <cstdint>

extern "C" void __cdecl __SEH_prolog4();
extern "C" void __cdecl __SEH_epilog4();
extern "C" int __cdecl _ValidateRead(void* address, std::uint32_t size);
extern "C" int __cdecl ___AdjustPointer(int pointer, int* displacement);
extern "C" void* __cdecl FID_conflict__memcpy(
    void* destination,
    void* source,
    std::uint32_t size);
extern "C" void __cdecl _inconsistency(void);

char __cdecl ___BuildCatchObjectHelper(
    int param_1,
    int* param_2,
    std::uint32_t* param_3,
    std::uint8_t* param_4)
{
    int iVar1;
    void* pvVar2;
    std::uint32_t size;
    // Ghidra confirms _ValidateRead ignores its size argument and tests only the pointer.
    std::uint32_t in_stack_ffffffd0 = 0;
    char return_value = '\0';

    __SEH_prolog4();

    if (((param_3[1] == 0U) ||
         (*reinterpret_cast<char*>(
             static_cast<std::uintptr_t>(param_3[1]) + 8U) == '\0')) ||
        ((param_3[2] == 0U) &&
         ((*param_3 & 0x80000000U) == 0U)))
    {
        goto finish;
    }

    if (static_cast<std::int32_t>(*param_3) >= 0)
    {
        const std::uint32_t param_2_address =
            static_cast<std::uint32_t>(
                reinterpret_cast<std::uintptr_t>(param_2));

        param_2 = reinterpret_cast<int*>(
            static_cast<std::uintptr_t>(
                param_3[2] + 0x0CU + param_2_address));
    }

    if ((*param_3 & 8U) == 0U)
    {
        pvVar2 = *reinterpret_cast<void**>(
            static_cast<std::uintptr_t>(
                static_cast<std::uint32_t>(param_1)) + 0x18U);

        if ((*param_4 & 1U) == 0U)
        {
            if (*reinterpret_cast<int*>(param_4 + 0x18U) == 0)
            {
                iVar1 = _ValidateRead(pvVar2, 1U);

                if ((iVar1 != 0) &&
                    ((iVar1 = _ValidateRead(param_2, 1U)) != 0))
                {
                    size = *reinterpret_cast<std::uint32_t*>(
                        param_4 + 0x14U);

                    pvVar2 = reinterpret_cast<void*>(
                        static_cast<std::uintptr_t>(
                            ___AdjustPointer(
                                *reinterpret_cast<int*>(
                                    static_cast<std::uintptr_t>(
                                        static_cast<std::uint32_t>(param_1)) +
                                    0x18U),
                                reinterpret_cast<int*>(param_4 + 8U))));

                    FID_conflict__memcpy(param_2, pvVar2, size);
                    goto finish;
                }
            }
            else
            {
                iVar1 = _ValidateRead(pvVar2, 1U);

                if ((iVar1 != 0) &&
                    ((iVar1 = _ValidateRead(param_2, 1U)) != 0) &&
                    ((iVar1 = _ValidateRead(
                          *reinterpret_cast<void**>(param_4 + 0x18U),
                          in_stack_ffffffd0)) != 0))
                {
                    const char result =
                        static_cast<char>((*param_4 & 4U) != 0U) + '\x01';
                    return_value = result;
                    goto finish;
                }
            }
        }
        else
        {
            iVar1 = _ValidateRead(pvVar2, 1U);

            if ((iVar1 != 0) &&
                ((iVar1 = _ValidateRead(param_2, 1U)) != 0))
            {
                FID_conflict__memcpy(
                    param_2,
                    *reinterpret_cast<void**>(
                        static_cast<std::uintptr_t>(
                            static_cast<std::uint32_t>(param_1)) + 0x18U),
                    *reinterpret_cast<std::uint32_t*>(param_4 + 0x14U));

                if (*reinterpret_cast<std::int32_t*>(param_4 + 0x14U) != 4)
                {
                    goto finish;
                }

                iVar1 = *param_2;

                if (iVar1 == 0)
                {
                    goto finish;
                }

                goto LAB_1001d290;
            }
        }
    }
    else
    {
        iVar1 = _ValidateRead(
            *reinterpret_cast<void**>(
                static_cast<std::uintptr_t>(
                    static_cast<std::uint32_t>(param_1)) + 0x18U),
            1U);

        if ((iVar1 != 0) &&
            ((iVar1 = _ValidateRead(param_2, 1U)) != 0))
        {
            iVar1 = *reinterpret_cast<int*>(
                static_cast<std::uintptr_t>(
                    static_cast<std::uint32_t>(param_1)) + 0x18U);

            *param_2 = iVar1;

        LAB_1001d290:
            iVar1 = ___AdjustPointer(
                iVar1,
                reinterpret_cast<int*>(param_4 + 8U));

            *param_2 = iVar1;
            goto finish;
        }
    }

    _inconsistency();
finish:
    __SEH_epilog4();
    return return_value;
}