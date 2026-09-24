#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500720
    void TileMapState::setMoatVisualStateAtTile(int tile, undefined4 zeroOrTwo)
    {
        int const moatID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(tile);
        if (moatID != 0) {
            this->moats[moatID].zeroOrTwo = zeroOrTwo;
        }
    }

}
}
