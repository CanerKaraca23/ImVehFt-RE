#include <cstddef>
#include <cstdint>

extern "C" std::uint32_t DAT_1003c414;
extern "C" std::uint32_t* __fastcall FUN_10016f49(std::uint32_t);

extern "C" void* __cdecl FID_conflict__memcpy(
    void* _Dst,
    void* _Src,
    std::size_t _Size)
{
    const std::uint32_t dst =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(_Dst));
    std::uint32_t src =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(_Src));
    const std::uint32_t size = static_cast<std::uint32_t>(_Size);

    std::uint32_t count;
    // The tail count defaults to the byte remainder; alignment-specific paths refine it.
    std::uint32_t remainder = size & 3U;

    if ((src < dst) && (dst < static_cast<std::uint32_t>(src + size))) {
        std::uint32_t src_word =
            static_cast<std::uint32_t>(src + size - 4U);
        std::uint32_t dst_word =
            static_cast<std::uint32_t>(dst + size - 4U);

        if ((dst_word & 3U) == 0U) {
            count = size >> 2;
            remainder = size & 3U;

            if (7U < count) {
                for (; count != 0U; --count) {
                    *reinterpret_cast<std::uint32_t*>(
                        static_cast<std::uintptr_t>(dst_word)) =
                        *reinterpret_cast<std::uint32_t*>(
                            static_cast<std::uintptr_t>(src_word));
                    src_word -= 4U;
                    dst_word -= 4U;
                }

                switch (remainder) {
                case 0:
                    return _Dst;
                case 2:
                    goto backward_case_2;
                case 3:
                    goto backward_case_3;
                }
                goto backward_case_1;
            }
        } else {
            switch (size) {
            case 0:
                goto backward_case_0;
            case 1:
                goto backward_case_1;
            case 2:
                goto backward_case_2;
            case 3:
                goto backward_case_3;
            default:
                count = size - (dst_word & 3U);

                switch (dst_word & 3U) {
                case 1:
                    remainder = count & 3U;

                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(dst_word + 3U)) =
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(src_word + 3U));

                    src_word -= 1U;
                    count >>= 2;
                    dst_word -= 1U;

                    if (7U < count) {
                        for (; count != 0U; --count) {
                            *reinterpret_cast<std::uint32_t*>(
                                static_cast<std::uintptr_t>(dst_word)) =
                                *reinterpret_cast<std::uint32_t*>(
                                    static_cast<std::uintptr_t>(src_word));
                            src_word -= 4U;
                            dst_word -= 4U;
                        }

                        switch (remainder) {
                        case 0:
                            return _Dst;
                        case 2:
                            goto backward_case_2;
                        case 3:
                            goto backward_case_3;
                        }
                        goto backward_case_1;
                    }
                    break;

                case 2:
                    remainder = count & 3U;

                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(dst_word + 3U)) =
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(src_word + 3U));

                    count >>= 2;

                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(dst_word + 2U)) =
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(src_word + 2U));

                    src_word -= 2U;
                    dst_word -= 2U;

                    if (7U < count) {
                        for (; count != 0U; --count) {
                            *reinterpret_cast<std::uint32_t*>(
                                static_cast<std::uintptr_t>(dst_word)) =
                                *reinterpret_cast<std::uint32_t*>(
                                    static_cast<std::uintptr_t>(src_word));
                            src_word -= 4U;
                            dst_word -= 4U;
                        }

                        switch (remainder) {
                        case 0:
                            return _Dst;
                        case 2:
                            goto backward_case_2;
                        case 3:
                            goto backward_case_3;
                        }
                        goto backward_case_1;
                    }
                    break;

                case 3:
                    remainder = count & 3U;

                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(dst_word + 3U)) =
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(src_word + 3U));

                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(dst_word + 2U)) =
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(src_word + 2U));

                    count >>= 2;

                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(dst_word + 1U)) =
                        *reinterpret_cast<std::uint8_t*>(
                            static_cast<std::uintptr_t>(src_word + 1U));

                    src_word -= 3U;
                    dst_word -= 3U;

                    if (7U < count) {
                        for (; count != 0U; --count) {
                            *reinterpret_cast<std::uint32_t*>(
                                static_cast<std::uintptr_t>(dst_word)) =
                                *reinterpret_cast<std::uint32_t*>(
                                    static_cast<std::uintptr_t>(src_word));
                            src_word -= 4U;
                            dst_word -= 4U;
                        }

                        switch (remainder) {
                        case 0:
                            return _Dst;
                        case 2:
                            goto backward_case_2;
                        case 3:
                            goto backward_case_3;
                        }
                        goto backward_case_1;
                    }
                    break;
                }
            }
        }

        switch (count) {
        case 7:
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(dst_word + (7U - count) * 4U)) =
                *reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(src_word + (7U - count) * 4U));
        case 6:
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(dst_word + (6U - count) * 4U)) =
                *reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(src_word + (6U - count) * 4U));
        case 5:
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(dst_word + (5U - count) * 4U)) =
                *reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(src_word + (5U - count) * 4U));
        case 4:
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(dst_word + (4U - count) * 4U)) =
                *reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(src_word + (4U - count) * 4U));
        case 3:
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(dst_word + (3U - count) * 4U)) =
                *reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(src_word + (3U - count) * 4U));
        case 2:
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(dst_word + (2U - count) * 4U)) =
                *reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(src_word + (2U - count) * 4U));
        case 1:
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(dst_word + (1U - count) * 4U)) =
                *reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(src_word + (1U - count) * 4U));
            src_word -= count * 4U;
            dst_word -= count * 4U;
        }

        switch (remainder) {
        case 1:
        backward_case_1:
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(dst_word + 3U)) =
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(src_word + 3U));
            return _Dst;

        case 2:
        backward_case_2:
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(dst_word + 3U)) =
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(src_word + 3U));
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(dst_word + 2U)) =
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(src_word + 2U));
            return _Dst;

        case 3:
        backward_case_3:
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(dst_word + 3U)) =
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(src_word + 3U));
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(dst_word + 2U)) =
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(src_word + 2U));
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(dst_word + 1U)) =
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(src_word + 1U));
            return _Dst;
        }

    backward_case_0:
        return _Dst;
    }

    if ((0x7fU < size) &&
        (DAT_1003c414 != 0U) &&
        ((dst & 0xfU) == (src & 0xfU))) {
        return reinterpret_cast<void*>(FUN_10016f49(size));
    }

    std::uint32_t dst_word = dst;

    if ((dst & 3U) == 0U) {
        count = size >> 2;
        remainder = size & 3U;

        if (7U < count) {
            for (; count != 0U; --count) {
                *reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(dst_word)) =
                    *reinterpret_cast<std::uint32_t*>(
                        static_cast<std::uintptr_t>(src));
                src += 4U;
                dst_word += 4U;
            }

            switch (remainder) {
            case 0:
                return _Dst;
            case 2:
                goto forward_case_2;
            case 3:
                goto forward_case_3;
            }
            goto forward_case_1;
        }
    } else {
        switch (size) {
        case 0:
            goto forward_case_0;
        case 1:
            goto forward_case_1;
        case 2:
            goto forward_case_2;
        case 3:
            goto forward_case_3;
        default:
            count = size - 4U + (dst & 3U);

            switch (dst & 3U) {
            case 1:
                remainder = count & 3U;

                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(dst)) =
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(src));

                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(dst + 1U)) =
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(src + 1U));

                count >>= 2;

                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(dst + 2U)) =
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(src + 2U));

                src += 3U;
                dst_word = dst + 3U;

                if (7U < count) {
                    for (; count != 0U; --count) {
                        *reinterpret_cast<std::uint32_t*>(
                            static_cast<std::uintptr_t>(dst_word)) =
                            *reinterpret_cast<std::uint32_t*>(
                                static_cast<std::uintptr_t>(src));
                        src += 4U;
                        dst_word += 4U;
                    }

                    switch (remainder) {
                    case 0:
                        return _Dst;
                    case 2:
                        goto forward_case_2;
                    case 3:
                        goto forward_case_3;
                    }
                    goto forward_case_1;
                }
                break;

            case 2:
                remainder = count & 3U;

                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(dst)) =
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(src));

                count >>= 2;

                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(dst + 1U)) =
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(src + 1U));

                src += 2U;
                dst_word = dst + 2U;

                if (7U < count) {
                    for (; count != 0U; --count) {
                        *reinterpret_cast<std::uint32_t*>(
                            static_cast<std::uintptr_t>(dst_word)) =
                            *reinterpret_cast<std::uint32_t*>(
                                static_cast<std::uintptr_t>(src));
                        src += 4U;
                        dst_word += 4U;
                    }

                    switch (remainder) {
                    case 0:
                        return _Dst;
                    case 2:
                        goto forward_case_2;
                    case 3:
                        goto forward_case_3;
                    }
                    goto forward_case_1;
                }
                break;

            case 3:
                remainder = count & 3U;

                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(dst)) =
                    *reinterpret_cast<std::uint8_t*>(
                        static_cast<std::uintptr_t>(src));

                src += 1U;
                count >>= 2;
                dst_word = dst + 1U;

                if (7U < count) {
                    for (; count != 0U; --count) {
                        *reinterpret_cast<std::uint32_t*>(
                            static_cast<std::uintptr_t>(dst_word)) =
                            *reinterpret_cast<std::uint32_t*>(
                                static_cast<std::uintptr_t>(src));
                        src += 4U;
                        dst_word += 4U;
                    }

                    switch (remainder) {
                    case 0:
                        return _Dst;
                    case 2:
                        goto forward_case_2;
                    case 3:
                        goto forward_case_3;
                    }
                    goto forward_case_1;
                }
                break;
            }
        }
    }

    switch (count) {
    case 7:
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(dst_word + (count - 7U) * 4U)) =
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(src + (count - 7U) * 4U));
    case 6:
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(dst_word + (count - 6U) * 4U)) =
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(src + (count - 6U) * 4U));
    case 5:
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(dst_word + (count - 5U) * 4U)) =
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(src + (count - 5U) * 4U));
    case 4:
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(dst_word + (count - 4U) * 4U)) =
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(src + (count - 4U) * 4U));
    case 3:
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(dst_word + (count - 3U) * 4U)) =
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(src + (count - 3U) * 4U));
    case 2:
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(dst_word + (count - 2U) * 4U)) =
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(src + (count - 2U) * 4U));
    case 1:
        *reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(dst_word + (count - 1U) * 4U)) =
            *reinterpret_cast<std::uint32_t*>(
                static_cast<std::uintptr_t>(src + (count - 1U) * 4U));
        src += count * 4U;
        dst_word += count * 4U;
    }

    switch (remainder) {
    case 1:
    forward_case_1:
        *reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(dst_word)) =
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(src));
        return _Dst;

    case 2:
    forward_case_2:
        *reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(dst_word)) =
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(src));
        *reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(dst_word + 1U)) =
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(src + 1U));
        return _Dst;

    case 3:
    forward_case_3:
        *reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(dst_word)) =
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(src));
        *reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(dst_word + 1U)) =
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(src + 1U));
        *reinterpret_cast<std::uint8_t*>(
            static_cast<std::uintptr_t>(dst_word + 2U)) =
            *reinterpret_cast<std::uint8_t*>(
                static_cast<std::uintptr_t>(src + 2U));
        return _Dst;
    }

forward_case_0:
    return _Dst;
}