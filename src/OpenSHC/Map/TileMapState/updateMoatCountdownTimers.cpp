#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Moat.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Moat;

    // FUNCTION: STRONGHOLDCRUSADER 0x00500640
    void TileMapState::updateMoatCountdownTimers()
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::recountTotalOwnedMoats, this)();
        for (int i = 0; i < this->currentMoatCount; i++) {
            if (this->moats[i].owner != 0 && this->moats[i].someCountDown > 0) {
                this->moats[i].someCountDown -= 1;
            }
        }
    }

}
}
