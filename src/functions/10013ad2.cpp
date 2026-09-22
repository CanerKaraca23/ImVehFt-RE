#include <cstdint>
#include <cstddef>

struct TypeInfoStorage
{
    std::uint32_t vtable;
    std::int32_t* name;
};
static_assert(offsetof(TypeInfoStorage, name) == 4);

extern std::int32_t DAT_10039a44;
extern std::int32_t* DAT_10039a48;
extern "C" void __cdecl __SEH_prolog4(std::uint32_t, int);
extern "C" void __cdecl __lock(int);
extern "C" void __cdecl _free(void*);
extern "C" void __stdcall FUN_10013b39(void);
extern "C" void __stdcall __SEH_epilog4(void);

extern "C" void __cdecl _Type_info_dtor(TypeInfoStorage* param_1)
{
    __SEH_prolog4(0x0C, 0x10028308);

    __lock(0x0E);

    std::int32_t* memory = DAT_10039a48;
    auto* name = reinterpret_cast<std::int32_t*>(
        reinterpret_cast<std::uintptr_t>(param_1) + 4u);

    if (*name != 0)
    {
        std::int32_t* previous = &DAT_10039a44;
        std::int32_t* node;

        do
        {
            node = previous;

            if (DAT_10039a48 == nullptr)
                goto free_name;

            previous = DAT_10039a48;
        }
        while (*DAT_10039a48 != *name);

        node[1] = DAT_10039a48[1];
        _free(memory);

    free_name:
        _free(reinterpret_cast<void*>(
            static_cast<std::uintptr_t>(*name)));

        *name = 0;
    }

    FUN_10013b39();
    __SEH_epilog4();
}