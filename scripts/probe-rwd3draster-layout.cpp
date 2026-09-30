#include <cstddef>

#include "RenderWare.h"

using RwD3DRaster = RwRaster::RwD3DRaster;

static_assert(sizeof(void*) == 4, "This probe must be compiled for x86.");
static_assert(sizeof(RwD3DRaster) == 0x24);
static_assert(offsetof(RwD3DRaster, swapChain) == 0x1c);
