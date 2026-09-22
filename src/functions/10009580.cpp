#include <windows.h>
struct MappedObject
{
    unsigned int field_00;
    HANDLE field_04;
};

static_assert(offsetof(MappedObject, field_04) == 4);
extern "C" HANDLE DAT_1003c3e8;
extern "C" MappedObject* DAT_1003c3ec;

extern "C" void __stdcall FUN_10009580()
{
    HANDLE hHeap;
    HANDLE hObject;

    if (DAT_1003c3e8 != (HANDLE)0x0)
    {
        hHeap = DAT_1003c3ec->field_04;
        UnmapViewOfFile(DAT_1003c3ec);
        DAT_1003c3ec = (MappedObject*)0x0;
        CloseHandle(DAT_1003c3e8);
        DAT_1003c3e8 = (HANDLE)0x0;

        hObject = OpenFileMappingA(0xf001f, 0, "GTA_PLUGIN_SDK");
        if (hObject != (HANDLE)0x0)
        {
            CloseHandle(hObject);
            return;
        }

        HeapDestroy(hHeap);
    }
}