#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005000A0
    void TileMapState::recountTotalOwnedMoats()
    {
        this->currentMoatCount = 0;
        for (int i = 1; i < countof(this->moats); ++i) {
            if (this->moats[i].owner != 0) {
                this->currentMoatCount = i + 1;
            }
        }
    }

}
}
