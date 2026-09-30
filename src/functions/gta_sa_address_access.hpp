#pragma once

#include <cstdint>
#include <intrin.h>

// Lvalue view of a GTA SA 1.0 US global at its executable address.
#define IMVEHFT_GLOBAL_AT(type, address)                                        \
    (*reinterpret_cast<type*>(static_cast<std::uintptr_t>(address)))

// GTA SA 1.0 US: CPools::ms_pVehiclePool -> CPool::m_pObjects.
// Volatile loads preserve the two-level memory access seen in the executable.
#define IMVEHFT_VEHICLE_POOL_POINTER_B74494                                      \
    (*reinterpret_cast<volatile std::uintptr_t*>(                                \
        static_cast<std::uintptr_t>(0x00b74494)))

#define IMVEHFT_VEHICLE_OBJECTS_BASE_B74494                                      \
    (*reinterpret_cast<volatile std::int32_t*>(                                  \
        IMVEHFT_VEHICLE_POOL_POINTER_B74494))

// Win32 SEH stores the active registration-chain head at FS:[0].
static inline void* IMVEHFT_READ_EXCEPTION_LIST()
{
    return reinterpret_cast<void*>(__readfsdword(0));
}

#pragma warning(push)
#pragma warning(disable : 4733) // This helper intentionally reproduces the Win32 SEH chain write.
static inline void IMVEHFT_WRITE_EXCEPTION_LIST(void* head)
{
    __writefsdword(0, static_cast<unsigned long>(
        reinterpret_cast<std::uintptr_t>(head)));
}
#pragma warning(pop)
