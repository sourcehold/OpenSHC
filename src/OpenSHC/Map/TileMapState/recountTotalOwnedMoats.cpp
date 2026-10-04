#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005000A0
    void TileMapState::recountTotalOwnedMoats()
    {
        this->currentMoatCount = 0;
        for (int i = 1; i < 16000; ++i) {
            if (this->moats[i].owner != 0) {
                // not a count: one past the highest owned moat index, used as loop bound
                this->currentMoatCount = i + 1;
            }
        }
    }

}
}
