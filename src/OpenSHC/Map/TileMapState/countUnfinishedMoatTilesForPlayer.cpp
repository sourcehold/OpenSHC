#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_MOAT;

    // FUNCTION: STRONGHOLDCRUSADER 0x00500180
    int TileMapState::countUnfinishedMoatTilesForPlayer(int playerID)
    {
        int unfinishedMoatTiles = 0;
        for (int moatID = 1; moatID < countof(this->moats); moatID++) {
            if (this->moats[moatID].owner != 0 && this->moats[moatID].owner == playerID
                && (this->LogicLayer[this->moats[moatID].tile] & L_MOAT) == 0) {
                unfinishedMoatTiles++;
            }
        }
        return unfinishedMoatTiles;
    }

}
}
