#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500790
    void TileMapState::swapMoatOwnership(int param_1, int param_2)
    {
        for (int moatID = 1; moatID < 16000; moatID++) {
            if (this->moats[moatID].owner == 0) {
                continue;
            }
            if (this->moats[moatID].owner == param_1) {
                this->moats[moatID].owner = (char)param_2;
            } else if (this->moats[moatID].owner == param_2) {
                this->moats[moatID].owner = (char)param_1;
            }
        }
    }

}
}
