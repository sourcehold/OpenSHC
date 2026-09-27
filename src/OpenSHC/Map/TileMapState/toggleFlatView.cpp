#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F70B0
    void TileMapState::toggleFlatView(int param_1)
    {
        if (param_1 != this->flatViewToggleValue1) {
            this->flatViewToggleValue1 = param_1;
            this->flatViewToggleValue2 = param_1;
        }
        return;
    }

}
}
