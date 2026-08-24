#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004188C0
void Buildings::UpdatePlacedSiegeTower()

{
int iVar1;

iVar1 = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitRefID;
if ((iVar1 == 0) ||
(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitRefUID !=
DAT_UnitsState::instance.units[iVar1].uid)) {
DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].logicalState = OpenSHC::Map::Buildings::BLS_REMOVE;
}
return;
}


}
}