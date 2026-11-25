#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005000E0
    void TileMapState::countMoatsOwnedByEachPlayer()
    {
        for (int playerID = 1; playerID < countof(DAT_GameState::instance.playerDataArray); playerID++) {
            DAT_GameState::instance.playerDataArray[playerID].moatsOwned = 0;
        }
        for (int moatID = 1; moatID < countof(this->moats); moatID++) {
            char const owner = this->moats[moatID].owner;
            if (owner != 0) {
                int const ownerIndex = owner;
                DAT_GameState::instance.playerDataArray[ownerIndex].moatsOwned++;
            }
        }
    }

}
}
