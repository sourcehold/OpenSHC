#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/PitchDitch.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"



#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Map::PitchDitch;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x005007D0
void TileMapState::resetPitchDitchArray()

{
PitchDitch *destination;
int iVar1;

iVar1 = 4000;
this->maxPitchDitchCount = 4000;
destination = this->pitchDitches;
do {
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(0x14, '\0', (void *)((int)(destination)));
destination = destination + 1;
iVar1 = iVar1 + -1;
} while (iVar1 != 0);
return;
}


}
}