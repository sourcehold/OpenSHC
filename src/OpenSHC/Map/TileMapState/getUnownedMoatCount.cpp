#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500210
    int TileMapState::getUnownedMoatCount()
    {
        int unownedMoatCount = 0;
        for (int moatID = 1; moatID < 16000; moatID++) {
            if (this->moats[moatID].owner == 0) {
                unownedMoatCount++;
            }
        }
        return unownedMoatCount;
    }

}
}
