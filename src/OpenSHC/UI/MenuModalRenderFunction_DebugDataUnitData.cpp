#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004AAA80
void UI::MenuModalRenderFunction_DebugDataUnitData(int x,int y,int width,int height)

{
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::renderDebugDataUnitData, DAT_UnitsState::ptr)(x, y, width, height);
return;
}


}