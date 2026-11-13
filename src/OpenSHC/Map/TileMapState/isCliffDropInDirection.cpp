#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004FC7C0
    BOOLEnum TileMapState::isCliffDropInDirection(int tileUnk, undefined4 unused, int y)
    {
        int direction = (this->screenSouthEastDirection + 4) % 8;
        return this->HeightLayer[tileUnk]
            > this->HeightLayer[this->directionTranslationMatrix[y][direction] + tileUnk] + 20;
    }

}
}
