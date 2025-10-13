#pragma once

#include "FunctionResolver.h"
#include "ViewportRenderState.h"

namespace ViewportRenderState_Func
{
  //MACRO_FUNCTION_RESOLVER(BOOL(ViewportRenderState::*)(uint, uint), true, 0x00401000, &ViewportRenderState::xyAreValid) xyAreValid;
  MACRO_FUNCTION_RESOLVER_EXT(BOOL(ViewportRenderState::*)(uint, uint), true, 0x00401000, &ViewportRenderState::xyAreValid, FunctionResolver::Option::USE_WRAPPER) xyAreValid;
}


