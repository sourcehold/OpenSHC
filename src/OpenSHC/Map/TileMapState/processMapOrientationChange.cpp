#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00512920
    void TileMapState::processMapOrientationChange()
    {
        if (this->DAT_FutureMapOrientation < 8) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::changeMapOrientation, this)(
                this->DAT_FutureMapOrientation);
            this->DAT_FutureMapOrientation = 8;
        }
    }

}
}
