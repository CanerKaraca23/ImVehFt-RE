#include <cstdint>
#include <windows.h>

extern "C" PVOID __stdcall FUN_10014c40();

extern "C" PVOID DAT_1003a380;
extern "C" PVOID DAT_1003a384;
extern "C" PVOID DAT_1003a388;
extern "C" PVOID DAT_1003a38c;
extern "C" PVOID DAT_1003a390;
extern "C" std::uint32_t DAT_10029490;
extern "C" void __fastcall __security_check_cookie(std::uintptr_t);

extern "C" int __cdecl ___crtMessageBoxW(
    LPCWSTR _LpText,
    LPCWSTR _LpCaption,
    UINT _UType)
{
    const std::uint32_t stack_cookie = DAT_10029490 ^
        static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&stack_cookie));
    int result = 0;
    const LPCWSTR local_24 = _LpText;
    const LPCWSTR local_20 = _LpCaption;
    const PVOID local_1c = FUN_10014c40();

    HWND owner_window = nullptr;

    do {
    if (DAT_1003a380 == nullptr) {
        const HMODULE user32_module = LoadLibraryW(L"USER32.DLL");
        if (user32_module == nullptr) {
            break;
        }

        FARPROC procedure =
            GetProcAddress(user32_module, "MessageBoxW");
        if (procedure == nullptr) {
            break;
        }

        DAT_1003a380 = EncodePointer(procedure);

        procedure = GetProcAddress(user32_module, "GetActiveWindow");
        DAT_1003a384 = EncodePointer(procedure);

        procedure = GetProcAddress(user32_module, "GetLastActivePopup");
        DAT_1003a388 = EncodePointer(procedure);

        procedure =
            GetProcAddress(user32_module, "GetUserObjectInformationW");
        DAT_1003a390 = EncodePointer(procedure);

        if (DAT_1003a390 != nullptr) {
            procedure =
                GetProcAddress(user32_module, "GetProcessWindowStation");
            DAT_1003a38c = EncodePointer(procedure);
        }
    }

    if (DAT_1003a38c != local_1c &&
        DAT_1003a390 != local_1c) {
        using GetProcessWindowStationFunction =
            decltype(&::GetProcessWindowStation);
        using GetUserObjectInformationWFunction =
            decltype(&::GetUserObjectInformationW);

        const auto get_process_window_station =
            reinterpret_cast<GetProcessWindowStationFunction>(
                DecodePointer(DAT_1003a38c));

        const auto get_user_object_information =
            reinterpret_cast<GetUserObjectInformationWFunction>(
                DecodePointer(DAT_1003a390));

        DWORD required_length;
        unsigned char user_object_information[12];

        if (get_process_window_station != nullptr &&
            get_user_object_information != nullptr &&
            ((get_process_window_station() == nullptr ||
              get_user_object_information(
                  get_process_window_station(),
                  1,
                  user_object_information,
                  0x0Cu,
                  &required_length) == FALSE) ||
             ((user_object_information[8] & 1u) == 0))) {
            _UType |= 0x200000u;
            goto invoke_message_box;
        }
    }

    if (DAT_1003a384 != local_1c) {
        using GetActiveWindowFunction = decltype(&::GetActiveWindow);

        const auto get_active_window =
            reinterpret_cast<GetActiveWindowFunction>(
                DecodePointer(DAT_1003a384));

        if (get_active_window != nullptr &&
            (owner_window = get_active_window()) != nullptr &&
            DAT_1003a388 != local_1c) {
            using GetLastActivePopupFunction =
                decltype(&::GetLastActivePopup);

            const auto get_last_active_popup =
                reinterpret_cast<GetLastActivePopupFunction>(
                    DecodePointer(DAT_1003a388));

            if (get_last_active_popup != nullptr) {
                owner_window = get_last_active_popup(owner_window);
            }
        }
    }

invoke_message_box:
    using MessageBoxWFunction =
        int(WINAPI*)(HWND, LPCWSTR, LPCWSTR, UINT);

    const auto message_box =
        reinterpret_cast<MessageBoxWFunction>(
            DecodePointer(DAT_1003a380));

    if (message_box == nullptr) {
        break;
    }

    result = message_box(owner_window, local_24, local_20, _UType);
    } while (false);

    __security_check_cookie(
        stack_cookie ^ static_cast<std::uint32_t>(
            reinterpret_cast<std::uintptr_t>(&stack_cookie)));
    return result;
}
