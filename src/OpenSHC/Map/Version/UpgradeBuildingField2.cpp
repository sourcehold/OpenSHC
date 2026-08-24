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


// FUNCTION: STRONGHOLDCRUSADER 0x0041A3C0
void Version::UpgradeBuildingField2()

{
Building * psVar1;

psVar1 = &DAT_BuildingsState::instance.buildings[1];
do {
if (psVar1->logicalState != ((BuildingLogicalState)0)) {
psVar1->field207_0x288 = 0;
psVar1->field189_0x264 = 0;
}
psVar1 = psVar1 + 0x196;
} while ((int)psVar1 < 0x1124f7c);
return;
}


}
}