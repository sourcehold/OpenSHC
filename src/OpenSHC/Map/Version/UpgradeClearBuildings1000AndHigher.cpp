#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"



#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Map::Buildings::Building;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041A620
void Version::UpgradeClearBuildings1000AndHigher()

{
Building *destination;

destination = DAT_BuildingsState::instance.buildings + 1000;
do {
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(0x32c, '\0', (void *)((int)(destination)));
destination = destination + 1;
} while ((int)destination < 0x1124cf4);
return;
}


}
}