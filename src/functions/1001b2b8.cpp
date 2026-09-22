#include <cstdint>

extern "C" std::uintptr_t PTR_LAB_10029d40;
extern "C" std::uintptr_t PTR_LAB_10029d44;
extern "C" std::uintptr_t PTR_LAB_10029d48;
extern "C" std::uintptr_t PTR_LAB_10029d4c;
extern "C" std::uintptr_t PTR_LAB_10029d50;
extern "C" std::uintptr_t PTR_LAB_10029d54;
extern "C" std::uintptr_t PTR_LAB_10029d58;
extern "C" std::uintptr_t PTR_LAB_10029d5c;
extern "C" std::uintptr_t PTR_LAB_10029d60;
extern "C" std::uintptr_t PTR_LAB_10029d64;

extern "C" void __cdecl __cfltcvt();
extern "C" void __cdecl __cropzeros();
extern "C" void __cdecl __fassign();
extern "C" void __cdecl __forcdecpt();
extern "C" void __cdecl __positive();
extern "C" void __cdecl __cfltcvt_l();
extern "C" void __cdecl __fassign_l();
extern "C" void __cdecl __cropzeros_l();
extern "C" void __cdecl __forcdecpt_l();

extern "C" void __stdcall __cfltcvt_init()
{
    PTR_LAB_10029d40 = reinterpret_cast<std::uintptr_t>(&__cfltcvt);
    PTR_LAB_10029d44 = reinterpret_cast<std::uintptr_t>(&__cropzeros);
    PTR_LAB_10029d48 = reinterpret_cast<std::uintptr_t>(&__fassign);
    PTR_LAB_10029d4c = reinterpret_cast<std::uintptr_t>(&__forcdecpt);
    PTR_LAB_10029d50 = reinterpret_cast<std::uintptr_t>(&__positive);
    PTR_LAB_10029d54 = reinterpret_cast<std::uintptr_t>(&__cfltcvt);
    PTR_LAB_10029d58 = reinterpret_cast<std::uintptr_t>(&__cfltcvt_l);
    PTR_LAB_10029d5c = reinterpret_cast<std::uintptr_t>(&__fassign_l);
    PTR_LAB_10029d60 = reinterpret_cast<std::uintptr_t>(&__cropzeros_l);
    PTR_LAB_10029d64 = reinterpret_cast<std::uintptr_t>(&__forcdecpt_l);
}