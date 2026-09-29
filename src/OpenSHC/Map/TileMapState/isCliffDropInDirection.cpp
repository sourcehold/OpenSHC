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
    BOOLEnum TileMapState::isCliffDropInDirection(int tile, undefined4 param_2, int y)
    {
        int direction = (this->field84_0x5548a4 + 4) % 8;
        return (uint)this->HeightLayer[tile]
            > (uint)(this->HeightLayer[this->directionTranslationMatrix[y][direction] + tile] + 0x14);
    }

}
}
