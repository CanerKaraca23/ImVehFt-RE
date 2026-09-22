#include <cstdint>
#include <windows.h>

extern std::int32_t DAT_1003c248;
extern std::uint8_t DAT_1003a6c6;
extern std::int32_t DAT_1003bc04;
extern std::int32_t DAT_1003bc74;
extern std::int32_t DAT_1003b6fc;
extern std::int32_t DAT_1003bbbc;
extern std::int32_t DAT_1003bc0c;
extern std::int32_t DAT_1003bc24;
extern std::uint32_t DAT_1003bc70;
extern std::uint32_t DAT_1003aed8;

extern std::int32_t* _DAT_00b74494;
extern std::int32_t _DAT_00b7cd98;
extern std::uint32_t _DAT_00b7cb84;
extern std::uint32_t _DAT_1003bc20;
extern std::uint8_t DAT_100374bc;
extern float _DAT_10024fc0;
extern float _DAT_10024e90;
extern float _DAT_10024e78;
extern float _DAT_10024e70;
extern float _DAT_10024fb8;
extern float _DAT_10024fb0;
extern float _DAT_10024fac;
extern float _DAT_10024fa8;
extern std::uintptr_t _PTR_10024e68;

extern "C" std::int32_t __stdcall FUN_10009360();
extern "C" long double __cdecl FUN_10010120(float, float);


extern "C" void __cdecl FUN_10004bb0_impl(std::uintptr_t object)
{

    const std::int32_t base = DAT_1003c248;
    const std::int32_t manager = FUN_10009360();

    const std::int32_t state =
        *reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(manager + 0x48) +
            ((static_cast<std::int32_t>(object) - *_DAT_00b74494) / 0xa18) * 4) +
        base;

    if (*reinterpret_cast<std::int32_t*>(object + 0x460) == 0 ||
        (*reinterpret_cast<std::uint8_t*>(object + 0x428) & 0x10) == 0)
    {
        return;
    }

    if (DAT_1003a6c6 == 1)
    {
        *reinterpret_cast<std::uint8_t*>(state + 0x1d) = 1;
    }
    else if (DAT_1003a6c6 == 2)
    {
        *reinterpret_cast<std::uint8_t*>(state + 0x1d) = 0;
    }

    if (*reinterpret_cast<std::int32_t*>(object + 0x460) == _DAT_00b7cd98)
    {
        SHORT keyState = GetKeyState(DAT_1003bc04);

        if (static_cast<char>(static_cast<std::uint16_t>(keyState) >> 8) == -1 &&
            DAT_100374bc == '\0')
        {
            *reinterpret_cast<std::uint8_t*>(state + 0x1d) =
                *reinterpret_cast<char*>(state + 0x1d) == '\0';
        }

        keyState = GetKeyState(DAT_1003bc04);
        DAT_100374bc =
            static_cast<char>(static_cast<std::uint16_t>(keyState) >> 8) == -1;

        keyState = GetKeyState(DAT_1003bc74);

        if (static_cast<char>(static_cast<std::uint16_t>(keyState) >> 8) == -1 &&
            0xfa < (_DAT_00b7cb84 - _DAT_1003bc20))
        {
            *reinterpret_cast<std::uint8_t*>(state + 0x1c) =
                *reinterpret_cast<char*>(state + 0x1c) == '\0';

            _DAT_1003bc20 = _DAT_00b7cb84;
            reinterpret_cast<void(__thiscall*)(void*, std::int32_t, float, float)>(0x506ea0)(
                reinterpret_cast<void*>(0x00b6bc90), 0x25, 0.0f, 1.0f);
        }
    }

    const char active = reinterpret_cast<char(__thiscall*)(void*)>(0x6d55c0)(
        reinterpret_cast<void*>(object));
    *reinterpret_cast<std::uint8_t*>(state + 0x20) = active != '\0';

    std::uint32_t elapsed =
        _DAT_00b7cb84 - *reinterpret_cast<std::uint32_t*>(state + 0x24);

    if (*reinterpret_cast<std::int32_t*>(object + 0x460) == _DAT_00b7cd98)
    {
        SHORT keyState = GetKeyState(DAT_1003b6fc);

        if (static_cast<char>(static_cast<std::uint16_t>(keyState) >> 8) == -1)
        {
            *reinterpret_cast<std::uint16_t*>(state + 0x1e) = 0;
            return;
        }

        keyState = GetKeyState(DAT_1003bbbc);

        if (static_cast<char>(static_cast<std::uint16_t>(keyState) >> 8) == -1)
        {
            *reinterpret_cast<std::uint16_t*>(state + 0x1e) = 0x101;
            *reinterpret_cast<std::uint32_t*>(state + 0x24) = _DAT_00b7cb84;
            return;
        }

        keyState = GetKeyState(DAT_1003bc0c);

        if (static_cast<char>(static_cast<std::uint16_t>(keyState) >> 8) == -1)
        {
            *reinterpret_cast<std::uint16_t*>(state + 0x1e) = 1;
            *reinterpret_cast<std::uint32_t*>(state + 0x24) = _DAT_00b7cb84;
            return;
        }

        keyState = GetKeyState(DAT_1003bc24);

        if (static_cast<char>(static_cast<std::uint16_t>(keyState) >> 8) == -1)
        {
            *reinterpret_cast<std::uint16_t*>(state + 0x1e) = 0x100;
            *reinterpret_cast<std::uint32_t*>(state + 0x24) = _DAT_00b7cb84;
            return;
        }
    }
    else
    {
        if (DAT_1003bc70 < elapsed)
        {
            *reinterpret_cast<std::uint32_t*>(state + 0x24) = _DAT_00b7cb84;
            return;
        }

        if (elapsed < DAT_1003aed8)
        {
            *reinterpret_cast<std::uint16_t*>(state + 0x1e) = 0;

            const std::uint16_t indexA =
                *reinterpret_cast<std::uint16_t*>(object + 0x3a8);
            const std::uint16_t indexB =
                *reinterpret_cast<std::uint16_t*>(object + 0x3a4);
            const std::uint16_t indexC =
                *reinterpret_cast<std::uint16_t*>(object + 0x3a6);

            if (indexA != 0xffff && indexB != 0xffff && indexC != 0xffff)
            {
                float scale = static_cast<float>(_DAT_10024fc0);
                float aX = 0.0f;
                float aY = 0.0f;
                float bX = 0.0f;
                float bY = 0.0f;
                float cX = 0.0f;
                float cY = 0.0f;

                if (*reinterpret_cast<std::int32_t*>(
                        0x96f854 + (static_cast<std::uint32_t>(indexA >> 10) * 4)) != 0)
                {
                    auto* point = reinterpret_cast<std::uint16_t*>(
                        *reinterpret_cast<std::int32_t*>(
                            0x96f974 + (static_cast<std::uint32_t>(indexA >> 10) * 4)) +
                        (indexA & 0x3ff) * 0xe);

                    std::uint32_t valueX = point[0];
                    std::uint32_t valueY = point[1];

                    if (0x7fff < valueX)
                        valueX = valueX - 0x10000;
                    if (0x7fff < valueY)
                        valueY = valueY - 0x10000;

                    float convertedX = static_cast<float>(
                        static_cast<std::int32_t>(valueX));
                    if (static_cast<std::int32_t>(valueX) < 0)
                        convertedX = convertedX + _DAT_10024e90;

                    aX = convertedX * scale;

                    float convertedY = static_cast<float>(
                        static_cast<std::int32_t>(valueY));
                    if (static_cast<std::int32_t>(valueY) < 0)
                        convertedY = convertedY + _DAT_10024e90;

                    aY = convertedY * scale;
                }

                if (*reinterpret_cast<std::int32_t*>(
                        0x96f854 + (static_cast<std::uint32_t>(indexB >> 10) * 4)) != 0)
                {
                    auto* point = reinterpret_cast<std::uint16_t*>(
                        *reinterpret_cast<std::int32_t*>(
                            0x96f974 + (static_cast<std::uint32_t>(indexB >> 10) * 4)) +
                        (indexB & 0x3ff) * 0xe);

                    std::uint32_t valueX = point[0];
                    std::uint32_t valueY = point[1];

                    if (0x7fff < valueX)
                        valueX = valueX - 0x10000;
                    if (0x7fff < valueY)
                        valueY = valueY - 0x10000;

                    float convertedX = static_cast<float>(
                        static_cast<std::int32_t>(valueX));
                    if (static_cast<std::int32_t>(valueX) < 0)
                        convertedX = convertedX + _DAT_10024e90;

                    bX = convertedX * scale;

                    float convertedY = static_cast<float>(
                        static_cast<std::int32_t>(valueY));
                    if (static_cast<std::int32_t>(valueY) < 0)
                        convertedY = convertedY + _DAT_10024e90;

                    bY = convertedY * scale;
                }

                if (*reinterpret_cast<std::int32_t*>(
                        0x96f854 + (static_cast<std::uint32_t>(indexC >> 10) * 4)) != 0)
                {
                    auto* point = reinterpret_cast<std::uint16_t*>(
                        *reinterpret_cast<std::int32_t*>(
                            0x96f974 + (static_cast<std::uint32_t>(indexC >> 10) * 4)) +
                        (indexC & 0x3ff) * 0xe);

                    std::uint32_t valueX = point[0];
                    std::uint32_t valueY = point[1];

                    if (0x7fff < valueX)
                        valueX = valueX - 0x10000;
                    if (0x7fff < valueY)
                        valueY = valueY - 0x10000;

                    float convertedX = static_cast<float>(
                        static_cast<std::int32_t>(valueX));
                    if (static_cast<std::int32_t>(valueX) < 0)
                        convertedX = convertedX + _DAT_10024e90;

                    cX = convertedX * scale;

                    float convertedY = static_cast<float>(
                        static_cast<std::int32_t>(valueY));
                    if (static_cast<std::int32_t>(valueY) < 0)
                        convertedY = convertedY + _DAT_10024e90;

                    cY = convertedY * scale;
                }

                long double angle =
                    FUN_10010120(cX - bX, cY - bY);

                float first =
                    static_cast<float>(
                        angle * static_cast<long double>(_DAT_10024e78) -
                        static_cast<long double>(_DAT_10024e70));

                const float period = static_cast<float>(_PTR_10024e68);

                for (; first < 0.0f; first = first + period)
                {
                }

                for (; _DAT_10024fb8 < first; first = first - period)
                {
                }

                angle = FUN_10010120(bX - aX, bY - aY);

                float second =
                    static_cast<float>(
                        angle * static_cast<long double>(_DAT_10024e78) -
                        static_cast<long double>(_DAT_10024e70));

                for (; second < 0.0f; second = second + period)
                {
                }

                for (; _DAT_10024fb8 < second; second = second - period)
                {
                }

                first = first - second;

                if (first < 0.0f)
                    first = period + first;

                if (first < _DAT_10024fb0 || _DAT_10024fac <= first)
                {
                    if (first <= _DAT_10024fa8 && _DAT_10024fac < first)
                    {
                        *reinterpret_cast<std::uint8_t*>(state + 0x1e) = 1;
                        return;
                    }
                }
                else
                {
                    *reinterpret_cast<std::uint8_t*>(state + 0x1f) = 1;
                }
            }
        }
    }
}

extern "C" __declspec(naked) void __stdcall FUN_10004bb0()
{
    __asm {
        push eax
        call FUN_10004bb0_impl
        add esp, 4
        ret
    }
}