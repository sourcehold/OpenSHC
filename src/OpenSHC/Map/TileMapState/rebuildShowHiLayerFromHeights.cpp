#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F79D0
    void TileMapState::rebuildShowHiLayerFromHeights()
    {
        for (int tile = 0; tile < MC_MAP_TILES_COUNT; tile += 8) {
            for (int i = 0; i < 8; i++) {
                this->ShowHiLayer[tile + i] = this->heightBasedScreenYOffset[this->HeightLayer[tile + i]];
            }
        }
    }

}
}
