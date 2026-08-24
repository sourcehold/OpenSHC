#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041A0A0
void Version::UpgradeFirst9Buildings()

{
int buildingID;

buildingID = 1;
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBarracksCampgroundPositions, DAT_BuildingsState::ptr)(buildingID);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupMercenaryPostCampgroundPositions, DAT_BuildingsState::ptr)(buildingID)
;
buildingID = buildingID + 1;
} while (buildingID < 9);
return;
}


}
}