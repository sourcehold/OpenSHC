#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F79D0
    void TileMapState::rebuildShowHiLayerFromHeights()
    {
        for (int tile = 0; tile < 80400; tile += 8) {
            this->ShowHiLayer[tile] = (uchar)this->heightBasedScreenYOffset[this->HeightLayer[tile]];
            this->ShowHiLayer[tile + 1] = (uchar)this->heightBasedScreenYOffset[this->HeightLayer[tile + 1]];
            this->ShowHiLayer[tile + 2] = (uchar)this->heightBasedScreenYOffset[this->HeightLayer[tile + 2]];
            this->ShowHiLayer[tile + 3] = (uchar)this->heightBasedScreenYOffset[this->HeightLayer[tile + 3]];
            this->ShowHiLayer[tile + 4] = (uchar)this->heightBasedScreenYOffset[this->HeightLayer[tile + 4]];
            this->ShowHiLayer[tile + 5] = (uchar)this->heightBasedScreenYOffset[this->HeightLayer[tile + 5]];
            this->ShowHiLayer[tile + 6] = (uchar)this->heightBasedScreenYOffset[this->HeightLayer[tile + 6]];
            this->ShowHiLayer[tile + 7] = (uchar)this->heightBasedScreenYOffset[this->HeightLayer[tile + 7]];
        }
    }

}
}
