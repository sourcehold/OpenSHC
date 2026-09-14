#include "OpenSHC/Map/TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500210
    int TileMapState::getUnownedMoatCount()
    {
        int unownedMoatCount = 0;

        for (int i = 1; i < 16000; i++) {
            if (this->moats[i].owner == 0) {
                unownedMoatCount += 1;
            }
        }

        return unownedMoatCount;
    }

} // namespace Map
} // namespace OpenSHC
