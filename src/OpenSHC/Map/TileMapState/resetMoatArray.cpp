#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Moat.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"



#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Map::Moat;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00500680
void TileMapState::resetMoatArray()

{
Moat *destination;
int iVar1;

destination = this->moats;
iVar1 = 16000;
do {
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(0x10, '\0', (void *)((int)(destination)));
destination = destination + 1;
iVar1 = iVar1 + -1;
} while (iVar1 != 0);
this->moatTileCount = iVar1;
return;
}


}
}