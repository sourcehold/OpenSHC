#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Map::Buildings::Building;
using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041A2B0
void Version::SetDairyCheeseToZero()

{
Building * pBVar1;

pBVar1 = &DAT_BuildingsState::instance.buildings[1];
do {
if ((pBVar1->logicalState != ((BuildingLogicalState)0)) && (pBVar1->buildingType == OpenSHC::Map::Buildings::BT_DAIRYFARM)) {
pBVar1->flagonsOfAleOrCheeseOrReleaseDogs = 0;
}
pBVar1 = pBVar1 + 0x196;
} while ((int)pBVar1 < 0x1124dc6);
return;
}


}
}