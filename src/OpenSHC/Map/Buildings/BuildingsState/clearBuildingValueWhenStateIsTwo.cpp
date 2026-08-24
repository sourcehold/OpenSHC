#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::Building;
using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F3F0
void BuildingsState::clearBuildingValueWhenStateIsTwo()

{
Building * piVar1;
int iVar1;

iVar1 = 1;
if (1 < this->maxBuildingsCount) {
piVar1 = &this->buildings[1];
do {
if (piVar1->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) {
piVar1->animStateCounterTracker = 0;
}
iVar1 = iVar1 + 1;
piVar1 = piVar1 + 0xcb;
} while (iVar1 < this->maxBuildingsCount);
}
return;
}


}
}
}