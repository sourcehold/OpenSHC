#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"



#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004AAB20
void UI::MenuModalRenderFunction_DebugDataMapData(int x,int y,int width,int height)

{
MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::renderDebugDataMapData, DAT_WildlifeState::ptr)(x, y, width, height);
return;
}


}