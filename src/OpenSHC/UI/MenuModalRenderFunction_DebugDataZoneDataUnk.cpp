#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"



#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004AAAA0
void UI::MenuModalRenderFunction_DebugDataZoneDataUnk(int x,int y,int width,int height)

{
MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::renderAttackInfoDebugOverlay, DAT_TroopValueState::ptr)(x, y, width, height);
return;
}


}