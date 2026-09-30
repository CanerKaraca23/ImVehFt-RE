#include <cstddef>
#include "RenderWare.h"

static_assert(offsetof(RwGlobals, dOpenDevice) == 0x10);
static_assert(offsetof(RwGlobals, stdFunc) == 0x48);
static_assert(offsetof(RwGlobals, memoryFuncs) == 0x134);
static_assert(offsetof(RwGlobals, memoryAlloc) == 0x144);
static_assert(offsetof(RwGlobals, memoryFree) == 0x148);
