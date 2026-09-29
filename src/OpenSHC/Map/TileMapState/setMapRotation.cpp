#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F70E0
    void TileMapState::setMapRotation(undefined4 newRotation)
    {
        this->DAT_FutureMapOrientation = newRotation;
        return;
    }

}
}
