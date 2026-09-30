#include <cstddef>
#include <cstdint>

struct ExceptionStorage
{
    ExceptionStorage* __thiscall assign(ExceptionStorage* other);
    ExceptionStorage* __thiscall copy_construct(ExceptionStorage* other);
    void* __thiscall construct(char** text);
    void __thiscall tidy();
    void** vtable;
    char* what;
    std::uint8_t do_free;
    std::uint8_t padding[3];
};

struct TypeInfoStorage
{
    bool __thiscall equals(const TypeInfoStorage* other) const;
    void __thiscall destroy();
    TypeInfoStorage* __thiscall scalar_deleting_destructor(std::uint32_t flags);
    void** vtable;
    std::uint8_t opaque[5];
    char type_name[48];
};

struct CopyStr_this
{
    void __thiscall invoke(char* text);
    std::uint32_t vtable;
    char* what;
    std::uint8_t do_free;
};

static_assert(sizeof(void*) == 4, "This harness must be built as x86.");
static_assert(offsetof(ExceptionStorage, what) == 4);
static_assert(offsetof(ExceptionStorage, do_free) == 8);
static_assert(offsetof(TypeInfoStorage, type_name) == 9);

extern "C" {
std::uint8_t IVF_RELOC_TARGET_10022228[1] = {};
std::uint8_t IVF_RELOC_TARGET_10022248[1] = {};
}

namespace
{
alignas(16) unsigned char allocations[8][128]{};
bool allocation_used[8]{};
bool fail_next_allocation = false;
int free_calls = 0;
int type_info_dtor_calls = 0;
int delete_calls = 0;

bool text_equal(const char* left, const char* right)
{
    while (*left != '\0' && *left == *right)
    {
        ++left;
        ++right;
    }
    return *left == *right;
}
}

extern "C" void* __cdecl _malloc(std::size_t size)
{
    if (fail_next_allocation)
    {
        fail_next_allocation = false;
        return nullptr;
    }
    if (size > sizeof(allocations[0]))
    {
        return nullptr;
    }
    for (std::size_t i = 0; i < 8; ++i)
    {
        if (!allocation_used[i])
        {
            allocation_used[i] = true;
            return allocations[i];
        }
    }
    return nullptr;
}

extern "C" std::size_t __cdecl _strlen(const char* text)
{
    std::size_t size = 0;
    while (text[size] != '\0')
    {
        ++size;
    }
    return size;
}

extern "C" void __cdecl _free(void* memory)
{
    ++free_calls;
    for (std::size_t i = 0; i < 8; ++i)
    {
        if (memory == allocations[i])
        {
            allocation_used[i] = false;
            return;
        }
    }
}

extern "C" int __cdecl _strcmp(const char* left, const char* right)
{
    while (*left != '\0' && *left == *right)
    {
        ++left;
        ++right;
    }
    return static_cast<unsigned char>(*left) - static_cast<unsigned char>(*right);
}

extern "C" void __cdecl _Type_info_dtor(TypeInfoStorage*)
{
    ++type_info_dtor_calls;
}

extern "C" void __cdecl FUN_10010756(void*)
{
    ++delete_calls;
}

int main()
{
    char text[] = "owned exception text";
    char* text_pointer = text;
    ExceptionStorage original{};
    if (original.construct(&text_pointer) != &original ||
        original.vtable != reinterpret_cast<void**>(IVF_RELOC_TARGET_10022228) ||
        original.what == nullptr || original.do_free != 1 ||
        !text_equal(original.what, text))
    {
        return 1;
    }

    ExceptionStorage copied{};
    if (copied.copy_construct(&original) != &copied ||
        copied.vtable != reinterpret_cast<void**>(IVF_RELOC_TARGET_10022228) ||
        copied.what == original.what || copied.do_free != 1 ||
        !text_equal(copied.what, text))
    {
        return 2;
    }

    char* original_copy = original.what;
    original.assign(&original);
    if (original.what != original_copy || original.do_free != 1)
    {
        return 3;
    }

    ExceptionStorage borrowed{};
    borrowed.what = text;
    borrowed.do_free = 0;
    original.assign(&borrowed);
    if (original.what != text || original.do_free != 0 || free_calls != 1)
    {
        return 4;
    }

    copied.tidy();
    if (copied.what != nullptr || copied.do_free != 0 || free_calls != 2)
    {
        return 5;
    }

    fail_next_allocation = true;
    ExceptionStorage allocation_failure{};
    if (allocation_failure.construct(&text_pointer) != &allocation_failure ||
        allocation_failure.what != nullptr || allocation_failure.do_free != 0)
    {
        return 6;
    }

    CopyStr_this null_copy{0x1234U, text, 1};
    null_copy.invoke(nullptr);
    if (null_copy.what != text || null_copy.do_free != 1)
    {
        return 7;
    }

    TypeInfoStorage left{};
    TypeInfoStorage same{};
    TypeInfoStorage different{};
    const char left_name[] = "class.Widget";
    const char other_name[] = "class.Widget";
    const char different_name[] = "class.WidgeX";
    for (std::size_t i = 0; i < sizeof(left_name); ++i)
    {
        left.type_name[i] = left_name[i];
        same.type_name[i] = other_name[i];
        different.type_name[i] = different_name[i];
    }
    if (!left.equals(&same) || left.equals(&different))
    {
        return 8;
    }

    left.destroy();
    if (left.vtable != reinterpret_cast<void**>(IVF_RELOC_TARGET_10022248) ||
        type_info_dtor_calls != 1)
    {
        return 9;
    }

    TypeInfoStorage delete_without_flag{};
    delete_without_flag.scalar_deleting_destructor(0);
    if (type_info_dtor_calls != 2 || delete_calls != 0)
    {
        return 10;
    }

    TypeInfoStorage delete_with_flag{};
    delete_with_flag.scalar_deleting_destructor(1);
    if (type_info_dtor_calls != 3 || delete_calls != 1)
    {
        return 11;
    }

    return 0;
}
