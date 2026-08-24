#include "OpenSHC/UI/MinimapViewState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace UI {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004B6640
void MinimapViewState::setMapPropertyDependingOnMapSize(uint param_1,int param_2)

{
if (200 < DAT_TileMapState::instance.mapSize) {
MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapTileStripWithLuminescence, this)(4, 2, 1, param_1, param_2);
return;
}
MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapTileStripWithLuminescence, this)(4, 4, 2, param_1, param_2);
return;
}


}
}