#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F79D0
    void TileMapState::rebuildShowHiLayerFromHeights()
    {
        for (int tile = 0; tile < countof(this->ShowHiLayer); tile += 8) {
            for (int i = 0; i < 8; i++) {
                this->ShowHiLayer[tile + i] = this->heightBasedScreenYOffset[this->HeightLayer[tile + i]];
            }
        }
    }

}
}
