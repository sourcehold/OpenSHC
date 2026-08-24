#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"



#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Map::Buildings::Building;
using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041A0D0
void Version::UpgradeBuildingField1()

{
Building * psVar1;

psVar1 = &DAT_BuildingsState::instance.buildings[1];
do {
if (psVar1->logicalState != ((BuildingLogicalState)0)) {
psVar1->uidWhenPlaced = (int)*(short *)psVar1;
}
psVar1 = psVar1 + 0x32c;
} while ((int)psVar1 < 0x1124e82);
return;
}


}
}