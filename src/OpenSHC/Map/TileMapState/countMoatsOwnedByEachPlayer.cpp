#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005000E0
    void TileMapState::countMoatsOwnedByEachPlayer()
    {
        DAT_GameState::instance.playerDataArray[1].moatsOwned = 0;
        DAT_GameState::instance.playerDataArray[2].moatsOwned = 0;
        DAT_GameState::instance.playerDataArray[3].moatsOwned = 0;
        DAT_GameState::instance.playerDataArray[4].moatsOwned = 0;
        DAT_GameState::instance.playerDataArray[5].moatsOwned = 0;
        DAT_GameState::instance.playerDataArray[6].moatsOwned = 0;
        DAT_GameState::instance.playerDataArray[7].moatsOwned = 0;
        DAT_GameState::instance.playerDataArray[8].moatsOwned = 0;
        for (int moatID = 1; moatID < 16000; moatID++) {
            char owner = this->moats[moatID].owner;
            if (owner != 0) {
                DAT_GameState::instance.playerDataArray[owner].moatsOwned
                    = DAT_GameState::instance.playerDataArray[owner].moatsOwned + 1;
            }
        }
    }

}
}
