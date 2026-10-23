#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500250
    int TileMapState::returnOwnedMoatAtTile(int targetedTile)
    {
        for (int moatID = 1; moatID < this->currentMoatCount; moatID++) {
            if (this->moats[moatID].owner != 0 && this->moats[moatID].tile == targetedTile) {
                return moatID;
            }
        }
        return 0;
    }

}
}
