#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005000A0
    void TileMapState::recountTotalOwnedMoats()
    {
        this->currentMoatCount = 0;
        for (int i = 1; i < 16000; i++) {
            if (this->moats[i].owner != 0) {
                // fixme: this must be wrong, but it is 100% Why not this->currentMoatCount += 1 ?
                this->currentMoatCount = i + 1;
            }
        }
    }

}
}
