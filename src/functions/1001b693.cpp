#include <cstdint>

struct EHRegistrationNode;
struct EHExceptionRecord;

extern "C" void* ExceptionList;

extern "C" void __stdcall RtlUnwind(
    void* target_frame,
    void* target_ip,
    void* exception_record,
    void* return_value);

extern "C" void __stdcall _UnwindNestedFrames(
    EHRegistrationNode* param_1,
    EHExceptionRecord* param_2)
{
    void* saved_exception_list = ExceptionList;

    RtlUnwind(
        param_1,
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x1001b6beu)),
        param_2,
        nullptr);

    auto* exception_flags = reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(param_2) + 4);

    *exception_flags &= 0xfffffffdu;

    *reinterpret_cast<void**>(saved_exception_list) = ExceptionList;
    ExceptionList = saved_exception_list;
}