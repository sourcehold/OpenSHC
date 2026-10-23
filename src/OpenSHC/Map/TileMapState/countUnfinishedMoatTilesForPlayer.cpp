#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_MOAT;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500180
    int TileMapState::countUnfinishedMoatTilesForPlayer(int playerID)
    {
        int unfinishedMoatTiles = 0;
        for (int moatID = 1; moatID < 16000; moatID++) {
            if (this->moats[moatID].owner != 0 && this->moats[moatID].owner == playerID
                && (this->LogicLayer[this->moats[moatID].tile] & L_MOAT) == 0) {
                unfinishedMoatTiles++;
            }
        }
        return unfinishedMoatTiles;
    }

}
}
