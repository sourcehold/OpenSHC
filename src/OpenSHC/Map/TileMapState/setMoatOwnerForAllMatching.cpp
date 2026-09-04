#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500750
    void TileMapState::setMoatOwnerForAllMatching(int param_1, undefined4 param_2)
    {
        for (int i = 1; i < 16000; i++) {
            if (this->moats[i].owner != 0 && this->moats[i].owner == param_1) {
                this->moats[i].owner = param_2;
            }
        }
    }

}
}
