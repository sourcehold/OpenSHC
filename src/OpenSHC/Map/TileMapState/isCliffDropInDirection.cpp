#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FC7C0
    BOOLEnum TileMapState::isCliffDropInDirection(int tileUnk, undefined4 param_2, int y)
    {
        int direction = (this->screenSouthEastDirection + 4) % 8;
        return this->HeightLayer[tileUnk]
            > this->HeightLayer[this->directionTranslationMatrix[y][direction] + tileUnk] + 0x14;
    }

}
}
