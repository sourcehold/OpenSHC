#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingTypeShort;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040A4A0
uint BuildingsState::isReligiousBuilding(int buildingID)

{
BuildingTypeShort BVar1;

BVar1 = this->buildings[buildingID].buildingType;
if ((BVar1 != OpenSHC::Map::Buildings::BT_CHAPEL) && (BVar1 != OpenSHC::Map::Buildings::BT_CHURCH)) {
return (uint)(BVar1 == OpenSHC::Map::Buildings::BT_CATHEDRAL);
}
return 1;
}


}
}
}