
#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500640
    void TileMapState::updateMoatCountdownTimers()
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::recountTotalOwnedMoats, this)();
        for (int moatID = 0; moatID < this->currentMoatCount; moatID++) {
            if (this->moats[moatID].owner != 0 && this->moats[moatID].someCountDown > 0) {
                this->moats[moatID].someCountDown = this->moats[moatID].someCountDown - 1;
            }
        }
    }

}
}
