#include <cstddef>
#include <cstdint>

extern "C" std::int32_t DAT_1003c414;
extern "C" std::uint32_t* __fastcall FUN_10016f49(std::uint32_t);

void* __cdecl FID_conflict__memcpy(
    void* _Dst,
    void* _Src,
    std::size_t _Size)
{
    const std::uint32_t dst =
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(_Dst));
    const std::uint32_t src =
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(_Src));
    const std::uint32_t size =
        static_cast<std::uint32_t>(_Size);

    std::uint32_t* puVar1;
    std::uint32_t* puVar4;
    std::uint32_t uVar2;
    // Every non-returning path assigns the tail count before it is consumed.
    std::uint32_t uVar3 = 0;

    if ((src < dst) && (dst < src + size))
    {
        puVar1 = reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(src + size - 4u));
        puVar4 = reinterpret_cast<std::uint32_t*>(
            static_cast<std::uintptr_t>(dst + size - 4u));

        if ((static_cast<std::uint32_t>(
                 reinterpret_cast<std::uintptr_t>(puVar4)) & 3u) == 0)
        {
            uVar2 = size >> 2;
            uVar3 = size & 3u;

            if (7u < uVar2)
            {
                for (; uVar2 != 0; uVar2 = uVar2 - 1u)
                {
                    *puVar4 = *puVar1;
                    puVar1 = puVar1 - 1;
                    puVar4 = puVar4 - 1;
                }

                switch (uVar3)
                {
                case 0:
                    return _Dst;
                case 2:
                    goto backward_case_2;
                case 3:
                    goto backward_case_3;
                }
                goto backward_case_1;
            }
        }
        else
        {
            switch (size)
            {
            case 0:
                goto backward_case_0;
            case 1:
                goto backward_case_1;
            case 2:
                goto backward_case_2;
            case 3:
                goto backward_case_3;
            default:
                uVar2 = size -
                    (static_cast<std::uint32_t>(
                         reinterpret_cast<std::uintptr_t>(puVar4)) & 3u);

                switch (static_cast<std::uint32_t>(
                            reinterpret_cast<std::uintptr_t>(puVar4)) & 3u)
                {
                case 1:
                    uVar3 = uVar2 & 3u;
                    reinterpret_cast<std::uint8_t*>(puVar4)[3] =
                        reinterpret_cast<std::uint8_t*>(puVar1)[3];
                    puVar1 = reinterpret_cast<std::uint32_t*>(
                        reinterpret_cast<std::uintptr_t>(puVar1) - 1u);
                    uVar2 = uVar2 >> 2;
                    puVar4 = reinterpret_cast<std::uint32_t*>(
                        reinterpret_cast<std::uintptr_t>(puVar4) - 1u);

                    if (7u < uVar2)
                    {
                        for (; uVar2 != 0; uVar2 = uVar2 - 1u)
                        {
                            *puVar4 = *puVar1;
                            puVar1 = puVar1 - 1;
                            puVar4 = puVar4 - 1;
                        }

                        switch (uVar3)
                        {
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
                    uVar3 = uVar2 & 3u;
                    reinterpret_cast<std::uint8_t*>(puVar4)[3] =
                        reinterpret_cast<std::uint8_t*>(puVar1)[3];
                    uVar2 = uVar2 >> 2;
                    reinterpret_cast<std::uint8_t*>(puVar4)[2] =
                        reinterpret_cast<std::uint8_t*>(puVar1)[2];
                    puVar1 = reinterpret_cast<std::uint32_t*>(
                        reinterpret_cast<std::uintptr_t>(puVar1) - 2u);
                    puVar4 = reinterpret_cast<std::uint32_t*>(
                        reinterpret_cast<std::uintptr_t>(puVar4) - 2u);

                    if (7u < uVar2)
                    {
                        for (; uVar2 != 0; uVar2 = uVar2 - 1u)
                        {
                            *puVar4 = *puVar1;
                            puVar1 = puVar1 - 1;
                            puVar4 = puVar4 - 1;
                        }

                        switch (uVar3)
                        {
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
                    uVar3 = uVar2 & 3u;
                    reinterpret_cast<std::uint8_t*>(puVar4)[3] =
                        reinterpret_cast<std::uint8_t*>(puVar1)[3];
                    reinterpret_cast<std::uint8_t*>(puVar4)[2] =
                        reinterpret_cast<std::uint8_t*>(puVar1)[2];
                    uVar2 = uVar2 >> 2;
                    reinterpret_cast<std::uint8_t*>(puVar4)[1] =
                        reinterpret_cast<std::uint8_t*>(puVar1)[1];
                    puVar1 = reinterpret_cast<std::uint32_t*>(
                        reinterpret_cast<std::uintptr_t>(puVar1) - 3u);
                    puVar4 = reinterpret_cast<std::uint32_t*>(
                        reinterpret_cast<std::uintptr_t>(puVar4) - 3u);

                    if (7u < uVar2)
                    {
                        for (; uVar2 != 0; uVar2 = uVar2 - 1u)
                        {
                            *puVar4 = *puVar1;
                            puVar1 = puVar1 - 1;
                            puVar4 = puVar4 - 1;
                        }

                        switch (uVar3)
                        {
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

        switch (uVar2)
        {
        case 7:
            puVar4[7u - uVar2] = puVar1[7u - uVar2];
        case 6:
            puVar4[6u - uVar2] = puVar1[6u - uVar2];
        case 5:
            puVar4[5u - uVar2] = puVar1[5u - uVar2];
        case 4:
            puVar4[4u - uVar2] = puVar1[4u - uVar2];
        case 3:
            puVar4[3u - uVar2] = puVar1[3u - uVar2];
        case 2:
            puVar4[2u - uVar2] = puVar1[2u - uVar2];
        case 1:
            puVar4[1u - uVar2] = puVar1[1u - uVar2];
            puVar1 = puVar1 - uVar2;
            puVar4 = puVar4 - uVar2;
        }

        switch (uVar3)
        {
        case 1:
        backward_case_1:
            reinterpret_cast<std::uint8_t*>(puVar4)[3] =
                reinterpret_cast<std::uint8_t*>(puVar1)[3];
            return _Dst;

        case 2:
        backward_case_2:
            reinterpret_cast<std::uint8_t*>(puVar4)[3] =
                reinterpret_cast<std::uint8_t*>(puVar1)[3];
            reinterpret_cast<std::uint8_t*>(puVar4)[2] =
                reinterpret_cast<std::uint8_t*>(puVar1)[2];
            return _Dst;

        case 3:
        backward_case_3:
            reinterpret_cast<std::uint8_t*>(puVar4)[3] =
                reinterpret_cast<std::uint8_t*>(puVar1)[3];
            reinterpret_cast<std::uint8_t*>(puVar4)[2] =
                reinterpret_cast<std::uint8_t*>(puVar1)[2];
            reinterpret_cast<std::uint8_t*>(puVar4)[1] =
                reinterpret_cast<std::uint8_t*>(puVar1)[1];
            return _Dst;
        }

    backward_case_0:
        return _Dst;
    }

    if ((size > 0x7fu) &&
        (DAT_1003c414 != 0) &&
        ((dst & 0xfu) == (src & 0xfu)))
    {
        puVar1 = FUN_10016f49(size);
        return puVar1;
    }

    puVar1 = reinterpret_cast<std::uint32_t*>(
        static_cast<std::uintptr_t>(dst));

    if ((dst & 3u) == 0)
    {
        uVar2 = size >> 2;
        uVar3 = size & 3u;

        if (7u < uVar2)
        {
            for (; uVar2 != 0; uVar2 = uVar2 - 1u)
            {
                *puVar1 = *reinterpret_cast<std::uint32_t*>(_Src);
                _Src = reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(_Src) + 4u);
                puVar1 = puVar1 + 1;
            }

            switch (uVar3)
            {
            case 0:
                return _Dst;
            case 2:
                goto forward_case_2;
            case 3:
                goto forward_case_3;
            }
            goto forward_case_1;
        }
    }
    else
    {
        switch (size)
        {
        case 0:
            goto forward_case_0;
        case 1:
            goto forward_case_1;
        case 2:
            goto forward_case_2;
        case 3:
            goto forward_case_3;
        default:
            uVar2 = (size - 4u) + (dst & 3u);

            switch (dst & 3u)
            {
            case 1:
                uVar3 = uVar2 & 3u;
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(dst)) =
                    *reinterpret_cast<std::uint8_t*>(_Src);
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(dst + 1u)) =
                    *reinterpret_cast<std::uint8_t*>(
                        reinterpret_cast<std::uintptr_t>(_Src) + 1u);
                uVar2 = uVar2 >> 2;
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(dst + 2u)) =
                    *reinterpret_cast<std::uint8_t*>(
                        reinterpret_cast<std::uintptr_t>(_Src) + 2u);
                _Src = reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(_Src) + 3u);
                puVar1 = reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(dst + 3u));

                if (7u < uVar2)
                {
                    for (; uVar2 != 0; uVar2 = uVar2 - 1u)
                    {
                        *puVar1 =
                            *reinterpret_cast<std::uint32_t*>(_Src);
                        _Src = reinterpret_cast<void*>(
                            reinterpret_cast<std::uintptr_t>(_Src) + 4u);
                        puVar1 = puVar1 + 1;
                    }

                    switch (uVar3)
                    {
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
                uVar3 = uVar2 & 3u;
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(dst)) =
                    *reinterpret_cast<std::uint8_t*>(_Src);
                uVar2 = uVar2 >> 2;
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(dst + 1u)) =
                    *reinterpret_cast<std::uint8_t*>(
                        reinterpret_cast<std::uintptr_t>(_Src) + 1u);
                _Src = reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(_Src) + 2u);
                puVar1 = reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(dst + 2u));

                if (7u < uVar2)
                {
                    for (; uVar2 != 0; uVar2 = uVar2 - 1u)
                    {
                        *puVar1 =
                            *reinterpret_cast<std::uint32_t*>(_Src);
                        _Src = reinterpret_cast<void*>(
                            reinterpret_cast<std::uintptr_t>(_Src) + 4u);
                        puVar1 = puVar1 + 1;
                    }

                    switch (uVar3)
                    {
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
                uVar3 = uVar2 & 3u;
                *reinterpret_cast<std::uint8_t*>(
                    static_cast<std::uintptr_t>(dst)) =
                    *reinterpret_cast<std::uint8_t*>(_Src);
                _Src = reinterpret_cast<void*>(
                    reinterpret_cast<std::uintptr_t>(_Src) + 1u);
                uVar2 = uVar2 >> 2;
                puVar1 = reinterpret_cast<std::uint32_t*>(
                    static_cast<std::uintptr_t>(dst + 1u));

                if (7u < uVar2)
                {
                    for (; uVar2 != 0; uVar2 = uVar2 - 1u)
                    {
                        *puVar1 =
                            *reinterpret_cast<std::uint32_t*>(_Src);
                        _Src = reinterpret_cast<void*>(
                            reinterpret_cast<std::uintptr_t>(_Src) + 4u);
                        puVar1 = puVar1 + 1;
                    }

                    switch (uVar3)
                    {
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

    switch (uVar2)
    {
    case 7:
        puVar1[uVar2 - 7u] =
            *reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uintptr_t>(_Src) +
                (uVar2 - 7u) * 4u);
    case 6:
        puVar1[uVar2 - 6u] =
            *reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uintptr_t>(_Src) +
                (uVar2 - 6u) * 4u);
    case 5:
        puVar1[uVar2 - 5u] =
            *reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uintptr_t>(_Src) +
                (uVar2 - 5u) * 4u);
    case 4:
        puVar1[uVar2 - 4u] =
            *reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uintptr_t>(_Src) +
                (uVar2 - 4u) * 4u);
    case 3:
        puVar1[uVar2 - 3u] =
            *reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uintptr_t>(_Src) +
                (uVar2 - 3u) * 4u);
    case 2:
        puVar1[uVar2 - 2u] =
            *reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uintptr_t>(_Src) +
                (uVar2 - 2u) * 4u);
    case 1:
        puVar1[uVar2 - 1u] =
            *reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uintptr_t>(_Src) +
                (uVar2 - 1u) * 4u);
        _Src = reinterpret_cast<void*>(
            reinterpret_cast<std::uintptr_t>(_Src) + uVar2 * 4u);
        puVar1 = puVar1 + uVar2;
    }

    switch (uVar3)
    {
    case 1:
    forward_case_1:
        *reinterpret_cast<std::uint8_t*>(puVar1) =
            *reinterpret_cast<std::uint8_t*>(_Src);
        return _Dst;

    case 2:
    forward_case_2:
        *reinterpret_cast<std::uint8_t*>(puVar1) =
            *reinterpret_cast<std::uint8_t*>(_Src);
        *reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<std::uintptr_t>(puVar1) + 1u) =
            *reinterpret_cast<std::uint8_t*>(
                reinterpret_cast<std::uintptr_t>(_Src) + 1u);
        return _Dst;

    case 3:
    forward_case_3:
        *reinterpret_cast<std::uint8_t*>(puVar1) =
            *reinterpret_cast<std::uint8_t*>(_Src);
        *reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<std::uintptr_t>(puVar1) + 1u) =
            *reinterpret_cast<std::uint8_t*>(
                reinterpret_cast<std::uintptr_t>(_Src) + 1u);
        *reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<std::uintptr_t>(puVar1) + 2u) =
            *reinterpret_cast<std::uint8_t*>(
                reinterpret_cast<std::uintptr_t>(_Src) + 2u);
        return _Dst;
    }

forward_case_0:
    return _Dst;
}