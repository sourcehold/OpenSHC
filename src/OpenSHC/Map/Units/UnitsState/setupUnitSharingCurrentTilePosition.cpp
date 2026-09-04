#include "OpenSHC/Map/Units/UnitsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0053BB70
void UnitsState::setupUnitSharingCurrentTilePosition(int unitID)

{
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingTileIDs, this)(unitID, this->units[unitID].tile);
return;
}


}
}
}