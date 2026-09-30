#include <cstdint>

extern "C" int __cdecl _strcmp(char* left, char* right);

struct TypeInfoStorage
{
    bool __thiscall equals(const TypeInfoStorage* other) const;
    void** vtable; // offset 0; type name begins at offset 9
};

bool TypeInfoStorage::equals(const TypeInfoStorage* other) const
{
    const auto left = reinterpret_cast<const char*>(other) + 9;
    const auto right = reinterpret_cast<const char*>(this) + 9;
    return _strcmp(const_cast<char*>(left), const_cast<char*>(right)) == 0;
}
