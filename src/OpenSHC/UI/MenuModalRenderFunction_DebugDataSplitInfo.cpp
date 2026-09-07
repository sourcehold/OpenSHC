#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004AAB00
void UI::MenuModalRenderFunction_DebugDataSplitInfo(int x,int y,int width,int height)
{
MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::renderDebugDataSplitInfo, DAT_GameSynchronyState::ptr)(x, y, width, height);
}

}
