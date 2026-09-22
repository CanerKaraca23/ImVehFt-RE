#include <cstddef>
extern "C" unsigned long long __stdcall FUN_100101c2(const char*);
extern void __stdcall FUN_1000d380(unsigned int);

extern "C" void __stdcall FUN_1000cfe0()
{
    struct VectorStorage
    {
        unsigned int begin_address;
        unsigned int end_address;
        unsigned int capacity_address;
    };

    static_assert(offsetof(VectorStorage, begin_address) == 0);
    static_assert(offsetof(VectorStorage, end_address) == 4);
    static_assert(offsetof(VectorStorage, capacity_address) == 8);

    VectorStorage* in_EAX;
    __asm mov in_EAX, eax

    unsigned int uVar1 =
        (in_EAX->end_address - in_EAX->begin_address) >> 2;

    unsigned long long uVar3 =
        (static_cast<unsigned long long>(in_EAX->begin_address) << 32) |
        static_cast<unsigned long long>(uVar1);

    if (0x3ffffffeu < uVar1)
        uVar3 = FUN_100101c2("vector<T> too long");

    unsigned int uVar2 =
        static_cast<unsigned int>(uVar3) + 1u;

    uVar1 =
        (in_EAX->capacity_address -
         static_cast<unsigned int>(uVar3 >> 32)) >> 2;

    if (uVar1 < uVar2)
    {
        if (0x3fffffffu - (uVar1 >> 1) < uVar1)
            uVar1 = 0;
        else
            uVar1 = uVar1 + (uVar1 >> 1);

        if (uVar1 < uVar2)
            uVar1 = uVar2;

        FUN_1000d380(uVar1);
    }
}