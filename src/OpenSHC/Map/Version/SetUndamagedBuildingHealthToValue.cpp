#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"



#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Map::Buildings::Building;
using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041A060
void Version::SetUndamagedBuildingHealthToValue()

{
short sVar1;
Building * psVar2;

psVar2 = &DAT_BuildingsState::instance.buildings[1];
do {
if ((psVar2->logicalState != ((BuildingLogicalState)0)) && (psVar2->currentHealth == psVar2->maxHealth))
{
sVar1 = DAT_BuildingDefinedData::instance.BuildingHP[(short)psVar2->buildingType].shortValue;
psVar2->maxHealth = sVar1;
psVar2->currentHealth = sVar1;
}
psVar2 = psVar2 + 0x196;
} while ((int)psVar2 < 0x1124e02);
return;
}


}
}