#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500750
    void TileMapState::setMoatOwnerForAllMatching(int fromPlayerID, undefined4 toPlayerID)
    {
        for (int i = 1; i < 16000; ++i) {
            if (this->moats[i].owner != 0 && this->moats[i].owner == fromPlayerID) {
                this->moats[i].owner = toPlayerID;
            }
        }
    }

}
}
