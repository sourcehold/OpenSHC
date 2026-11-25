#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00512920
    void TileMapState::processMapOrientationChange()
    {
        if ((int)this->DAT_FutureMapOrientation < OpenSHC::Map::Enums::MO_UPPER_LIMIT) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::changeMapOrientation, this)(
                (MapOrientation)this->DAT_FutureMapOrientation);
            this->DAT_FutureMapOrientation = OpenSHC::Map::Enums::MO_UPPER_LIMIT;
        }
    }

}
}
