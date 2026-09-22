#include <cstdint>

struct TypeInfoStorage
{
    bool __thiscall equals(const TypeInfoStorage* other) const;
    void** vtable; // offset 0; type name begins at offset 9
};

bool TypeInfoStorage::equals(const TypeInfoStorage* other) const
{
    using StrCmpFn = int (__cdecl*)(const char*, const char*);
    const auto left = reinterpret_cast<const char*>(other) + 9;
    const auto right = reinterpret_cast<const char*>(this) + 9;
    return reinterpret_cast<StrCmpFn>(static_cast<std::uintptr_t>(0x10013b50))(left, right) == 0;
}
