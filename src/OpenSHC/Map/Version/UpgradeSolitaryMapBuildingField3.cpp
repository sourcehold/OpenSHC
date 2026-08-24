#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"



#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Map::Buildings::Building;
using OpenSHC::Game::GameMode;
using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041A3F0
void Version::UpgradeSolitaryMapBuildingField3()

{
Building * piVar1;

if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
piVar1 = &DAT_BuildingsState::instance.buildings[1];
do {
if (piVar1->logicalState != ((BuildingLogicalState)0)) {
piVar1->playerColorUnk = 0;
}
piVar1 = piVar1 + 0xcb;
} while ((int)piVar1 < 0x1124cfc);
}
return;
}


}
}