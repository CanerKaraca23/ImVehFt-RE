#include <cstddef>
#include <cstdint>
#include <corecrt.h>
#include <stdio.h>
extern "C" void* DAT_10029d70;

extern "C" int __cdecl __mtinitlocknum(int _File);
extern "C" [[noreturn]] void __cdecl __amsg_exit(int _Message);
extern "C" void __stdcall EnterCriticalSection(void* lpCriticalSection);

extern "C" void __cdecl __lock(int _File)
{
    void** lockTable = reinterpret_cast<void**>(&DAT_10029d70);

    if (lockTable[_File * 2] == nullptr) {
        int result = __mtinitlocknum(_File);
        if (result == 0) {
            __amsg_exit(0x11);
        }
    }

    EnterCriticalSection(lockTable[_File * 2]);
}