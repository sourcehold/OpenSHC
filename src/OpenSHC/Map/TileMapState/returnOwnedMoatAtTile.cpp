#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

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
