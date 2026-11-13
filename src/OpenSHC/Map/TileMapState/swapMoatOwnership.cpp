#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500790
    void TileMapState::swapMoatOwnership(int playerID, int otherPlayerID)
    {
        for (int moatID = 1; moatID < countof(this->moats); moatID++) {
            if (this->moats[moatID].owner == 0) {
                continue;
            }
            if (this->moats[moatID].owner == playerID) {
                this->moats[moatID].owner = otherPlayerID;
            } else if (this->moats[moatID].owner == otherPlayerID) {
                this->moats[moatID].owner = playerID;
            }
        }
    }

}
}
