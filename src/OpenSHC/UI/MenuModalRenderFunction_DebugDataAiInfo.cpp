#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/AI/AICState.func.hpp"



#include "OpenSHC/Globals/DAT_AICState.hpp"

namespace OpenSHC {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004AAA60
void UI::MenuModalRenderFunction_DebugDataAiInfo(int x,int y,int width,int height)

{
MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::renderDebugDataAiInfo, DAT_AICState::ptr)(x, y, width, height);
return;
}


}