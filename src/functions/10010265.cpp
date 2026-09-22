 #include <cstddef>
#include <cstring>

extern "C" int __cdecl _strcpy_s(char*, std::size_t, const char*);
extern "C" void* __cdecl _malloc(std::size_t);
extern "C" std::size_t __cdecl _strlen(const char*);
struct CopyStr_this { void __thiscall invoke(char* param_1); };

void CopyStr_this::invoke(char* param_1)
{
    void* this_ = static_cast<void*>(this);
    if (param_1 != nullptr)
    {
        const size_t length = _strlen(param_1);
        char* destination = static_cast<char*>(_malloc(length + 1));

        *reinterpret_cast<char**>(
            static_cast<unsigned char*>(this_) + 4
        ) = destination;

        if (destination != nullptr)
        {
            strcpy_s(destination, length + 1, param_1);
            *reinterpret_cast<unsigned char*>(
                static_cast<unsigned char*>(this_) + 8
            ) = 1;
        }
    }
}