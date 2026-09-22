#include <cstddef>
#include <cstdint>

extern "C" std::uint32_t DAT_1003d550;
extern "C" std::uint32_t DAT_10039b8c;
extern "C" char DAT_10039a88[0x104];
extern "C" char* _DAT_10039a2c;
extern "C" char* DAT_1003d558;
extern "C" std::uint32_t _DAT_10039a10;
extern "C" std::uint32_t* _DAT_10039a14;

extern "C" void __stdcall ___initmbctable(void);

extern "C" void __cdecl parse_cmdline(
    std::uint32_t* argv,
    std::uint8_t* command_line,
    int* argc,
    std::uint32_t* string_size);

extern "C" void* __cdecl __malloc_crt(std::size_t size);

extern "C" unsigned long __stdcall GetModuleFileNameA(
    void* module,
    char* filename,
    unsigned long size);

extern "C" int __cdecl __setargv(void)
{
    std::uint32_t size;
    std::uint32_t argc;
    std::uint32_t* argv;
    std::uint32_t string_size;
    char* command_line;

    if (DAT_1003d550 == 0)
    {
        ___initmbctable();
    }

    DAT_10039b8c = 0;

    GetModuleFileNameA(nullptr, DAT_10039a88, 0x104);

    _DAT_10039a2c = DAT_10039a88;

    if (DAT_1003d558 == nullptr || *DAT_1003d558 == '\0')
    {
        command_line = DAT_10039a88;
    }
    else
    {
        command_line = DAT_1003d558;
    }

    parse_cmdline(
        nullptr,
        reinterpret_cast<std::uint8_t*>(command_line),
        reinterpret_cast<int*>(&argc),
        &string_size);

    size = string_size;

    if (argc < 0x3fffffff && string_size != 0xffffffffu)
    {
        size = argc * 4 + string_size;

        if (string_size <= size &&
            (argv = static_cast<std::uint32_t*>(__malloc_crt(size))) != nullptr)
        {
            parse_cmdline(
                argv,
                reinterpret_cast<std::uint8_t*>(argv + argc),
                reinterpret_cast<int*>(&argc),
                &string_size);

            _DAT_10039a10 = argc - 1;
            _DAT_10039a14 = argv;
            return 0;
        }
    }

    return -1;
}