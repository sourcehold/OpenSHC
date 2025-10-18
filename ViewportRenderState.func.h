#pragma once

#include "FunctionResolver.h"
#include "ViewportRenderState.h"

namespace ViewportRenderState_Func
{
// TODO: discuss how to handle constructors and destructors

MACRO_FUNCTION_RESOLVER_EXT(BOOL (ViewportRenderState::*)(uint, uint), true, 0x00401000, &ViewportRenderState::xyAreValid, FunctionResolver::Option::USE_WRAPPER)
xyAreValid;

MACRO_FUNCTION_RESOLVER(int (ViewportRenderState::*)(int, int), true, 0x00401040, &ViewportRenderState::translateXYToTile)
translateXYToTile;

MACRO_FUNCTION_RESOLVER(int (ViewportRenderState::*)(int, int), true, 0x004092e0, &ViewportRenderState::meth_0x4092e0)
meth_0x4092e0;

MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), true, 0x004e5dd0, &ViewportRenderState::setupMouseTileXY)
setupMouseTileXY;

MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), true, 0x004e5d80, &ViewportRenderState::setupMouseTileXY2)
setupMouseTileXY2;

MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), true, 0x004e5a90, &ViewportRenderState::meth_0x4e5a90)
meth_0x4e5a90;

} // namespace ViewportRenderState_Func
