#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Rocks/Rock.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"



#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Map::Rocks::Rock;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004F3900
void Version::UpgradeRemoveRocksBeyond1000()

{
Rock *destination;

destination = DAT_LandscapeState::instance.rocks + 2000;
do {
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(32, '\0', (void *)((int)(destination)));
destination = destination + 1;
} while ((int)destination < 0xf98330);
return;
}


}
}