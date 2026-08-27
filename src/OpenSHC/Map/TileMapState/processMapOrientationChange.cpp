#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x00512920
    void TileMapState::processMapOrientationChange()

    {
        if (this->DAT_FutureMapOrientation < 8) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::changeMapOrientation, this)(
                this->DAT_FutureMapOrientation);
            this->DAT_FutureMapOrientation = 8;
        }
        return;
    }

}
}
