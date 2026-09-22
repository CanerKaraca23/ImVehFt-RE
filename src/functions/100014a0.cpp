#include <exception>

struct ExceptionCopyThis
{
    void __thiscall FUN_10010351(std::exception* source);
};
extern void* PTR_std_bad_alloc_vftable;

struct FUN_100014a0_this
{
    void* __thiscall FUN_100014a0(std::exception* source);
};

void* FUN_100014a0_this::FUN_100014a0(std::exception* source)
{
    reinterpret_cast<ExceptionCopyThis*>(this)->FUN_10010351(source);
    *reinterpret_cast<void***>(this) =
        reinterpret_cast<void**>(PTR_std_bad_alloc_vftable);
    return this;
}