#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004FC7C0
    BOOLEnum TileMapState::isCliffDropInDirection(int tile, undefined4 param_2, int y)
    {
        int direction = (this->screenSouthEastDirection + 4) % 8;
        return (uint)this->HeightLayer[tile]
            > (uint)(this->HeightLayer[this->directionTranslationMatrix[y][direction] + tile] + 0x14);
    }

}
}
