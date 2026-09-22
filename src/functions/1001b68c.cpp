#include <cstdint>

extern "C" void LOCK();
extern "C" void UNLOCK();

void __stdcall FID_conflict__CallMemberFunction1(
    std::uint32_t ,
    void* UNRECOVERED_JUMPTABLE)
{
    LOCK();
    UNLOCK();

    reinterpret_cast<void (*)()>(UNRECOVERED_JUMPTABLE)();
}