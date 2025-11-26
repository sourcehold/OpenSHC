#pragma once

#include "ViewportRenderState.h"

namespace ViewportRenderState_Func {
// constructors and destructors are handled by a this call function called by the "real" constructor/destructor
MACRO_FUNCTION_RESOLVER(
    ViewportRenderState* (ViewportRenderState::*)(), false, 0x004e1fa0, &ViewportRenderState::_constructor_)
_constructor_;

MACRO_FUNCTION_RESOLVER(BOOL (ViewportRenderState::*)(uint, uint), true, 0x00401000, &ViewportRenderState::xyAreValid)
xyAreValid;

MACRO_FUNCTION_RESOLVER(
    int (ViewportRenderState::*)(int, int), false, 0x00401040, &ViewportRenderState::translateXYToTile)
translateXYToTile;

MACRO_FUNCTION_RESOLVER(int (ViewportRenderState::*)(int, int), false, 0x004092e0, &ViewportRenderState::meth_0x4092e0)
meth_0x4092e0;

MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), false, 0x004e5dd0, &ViewportRenderState::setupMouseTileXY)
setupMouseTileXY;

MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), false, 0x004e5d80, &ViewportRenderState::setupMouseTileXY2)
setupMouseTileXY2;

MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), false, 0x004e5a90, &ViewportRenderState::meth_0x4e5a90)
meth_0x4e5a90;

} // namespace ViewportRenderState_Func
