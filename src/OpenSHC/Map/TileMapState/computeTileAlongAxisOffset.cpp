#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500B50
    int TileMapState::computeTileAlongAxisOffset(int tile, int addend, uint offset)
    {
        int yStep = 1;
        int direction = 4;
        if ((int)offset < 0) {
            yStep = -1;
            direction = 0;
        }

        int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
        for (int remaining = abs((int)offset); remaining > 0; remaining--) {
            tile = tile + this->directionTranslationMatrix[y][direction];
            y = y + yStep;
        }
        return tile + addend;
    }

}
}
