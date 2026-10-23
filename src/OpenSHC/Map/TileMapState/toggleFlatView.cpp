#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F70B0
    void TileMapState::toggleFlatView(int flatView)
    {
        if (flatView != this->flatViewToggleValue1) {
            this->flatViewToggleValue1 = flatView;
            this->flatViewToggleValue2 = flatView;
        }
    }

}
}
