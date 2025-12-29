#pragma once

#include "ViewportRenderState.h"

MACRO_STRUCT_RESOLVER(ViewportRenderState, false, 0x100) ViewportRenderState_Struct;

// in this case, it will just instantiate the struct, calling the constructor, but only if implemented
MACRO_STRUCT_INSTANCE(0x100);
