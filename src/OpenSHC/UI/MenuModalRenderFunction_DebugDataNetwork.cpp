#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"



#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {




/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004AAAE0
void UI::MenuModalRenderFunction_DebugDataNetwork(int x,int y,int width,int height)

{
MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::renderDebugDataNetwork, DAT_GameSynchronyState::ptr)(x, y, width, height);
return;
}


}