#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500290
    int TileMapState::returnMoatIDForPlayerIDs(int playerID, int playerID2)
    {
        for (int moatID = 1; moatID < this->currentMoatCount; moatID++) {
            if (this->moats[moatID].tile == playerID && this->moats[moatID].owner == playerID2) {
                return moatID;
            }
        }
        return 0;
    }

}
}
