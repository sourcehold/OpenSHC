#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500310
    void TileMapState::clearMoatDataAtTile(int x, int y)
    {
        for (int moatID = 0; moatID < this->currentMoatCount; moatID++) {
            if (this->moats[moatID].x == x && this->moats[moatID].y == y) {
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(Moat), 0, &this->moats[moatID]);
                this->moatTileCount = this->moatTileCount - 1;
            }
        }
    }

}
}
