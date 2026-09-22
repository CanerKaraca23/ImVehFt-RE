#include <cstddef>
#include <cstdint>
#include <cstdio>

std::size_t __cdecl __fwrite_nolock(
    void* _DstBuf,
    std::size_t _Size,
    std::size_t _Count,
    FILE* _File)
{
    struct FILE_LAYOUT
    {
        std::uint32_t _cnt;
        std::uint32_t _ptr;
        std::uint32_t _base;
        std::uint32_t _flag;
        std::int32_t _file;
        std::uint32_t _charbuf;
        std::int32_t _bufsiz;
    };

    extern int* __cdecl __errno();

    extern void* __cdecl FID_conflict__memcpy(
        void*, const void*, std::uint32_t);
    extern int __cdecl __flush(FILE*);
    extern int __cdecl __fileno(FILE*);
    extern std::uint32_t __cdecl __write(
        int, const void*, std::uint32_t);
    extern int __cdecl __flsbuf(int, FILE*);

    if ((_Size != 0) && (_Count != 0))
    {
        if ((_File != nullptr) &&
            ((_DstBuf != nullptr) &&
             (_Count <= static_cast<std::uint32_t>(
                 0xffffffffULL /
                 static_cast<unsigned long long>(_Size)))))
        {
            auto* file =
                reinterpret_cast<FILE_LAYOUT*>(_File);

            const std::uint32_t total =
                static_cast<std::uint32_t>(_Size * _Count);

            std::uint32_t remaining = total;
            std::uint32_t buffer_size;

            if ((file->_flag & 0x10cU) == 0)
            {
                buffer_size = 0x1000U;
            }
            else
            {
                buffer_size =
                    static_cast<std::uint32_t>(file->_bufsiz);
            }

            do
            {
                while (true)
                {
                    if (remaining == 0)
                    {
                        return _Count;
                    }

                    const std::uint32_t mode =
                        file->_flag & 0x108U;

                    if (mode == 0)
                    {
                        break;
                    }

                    const std::uint32_t available = file->_cnt;

                    if (available == 0)
                    {
                        break;
                    }

                    if (static_cast<std::int32_t>(available) < 0)
                    {
                        file->_flag = file->_flag | 0x20U;
                        goto failure;
                    }

                    std::uint32_t copied = remaining;
                    if (available <= remaining)
                    {
                        copied = available;
                    }

                    FID_conflict__memcpy(
                        reinterpret_cast<void*>(
                            static_cast<std::uintptr_t>(
                                file->_ptr)),
                        _DstBuf,
                        copied);

                    file->_cnt = file->_cnt - copied;
                    file->_ptr = file->_ptr + copied;
                    remaining = remaining - copied;

                    _DstBuf = reinterpret_cast<void*>(
                        static_cast<std::uintptr_t>(
                            static_cast<std::uint32_t>(
                                reinterpret_cast<std::uintptr_t>(
                                    _DstBuf) +
                                copied)));
                }

                if (buffer_size <= remaining)
                {
                    if ((file->_flag & 0x108U) != 0 &&
                        __flush(_File) != 0)
                    {
                        goto failure;
                    }

                    std::uint32_t write_size = remaining;
                    if (buffer_size != 0)
                    {
                        write_size =
                            remaining - remaining % buffer_size;
                    }

                    const std::uint32_t written =
                        __write(
                            __fileno(_File),
                            _DstBuf,
                            write_size);

                    if (written != 0xffffffffU)
                    {
                        std::uint32_t consumed = write_size;
                        if (written <= write_size)
                        {
                            consumed = written;
                        }

                        remaining = remaining - consumed;

                        if (write_size <= written)
                        {
                            _DstBuf = reinterpret_cast<void*>(
                                static_cast<std::uintptr_t>(
                                    static_cast<std::uint32_t>(
                                        reinterpret_cast<
                                            std::uintptr_t>(
                                                _DstBuf) +
                                        consumed)));
                            continue;
                        }
                    }

                    file->_flag = file->_flag | 0x20U;
                    goto failure;
                }

                if (__flsbuf(
                        static_cast<int>(
                            *reinterpret_cast<char*>(_DstBuf)),
                        _File) == -1)
                {
                    goto failure;
                }

                _DstBuf = reinterpret_cast<void*>(
                    static_cast<std::uintptr_t>(
                        static_cast<std::uint32_t>(
                            reinterpret_cast<std::uintptr_t>(
                                _DstBuf) +
                            1)));

                buffer_size =
                    static_cast<std::uint32_t>(file->_bufsiz);

                remaining = remaining - 1;

                if (static_cast<std::int32_t>(buffer_size) < 1)
                {
                    buffer_size = 1;
                }
            }
            while (true);

        failure:
            return (total - remaining) / _Size;
        }

        *(__errno()) = 0x16;
        reinterpret_cast<void (__cdecl*)()>(0x1001189f)();
    }

    return 0;
}