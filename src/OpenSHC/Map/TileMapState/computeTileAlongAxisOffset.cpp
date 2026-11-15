#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Enums::CD_NORTH;
    using OpenSHC::Map::Enums::CD_SOUTH;

    // FUNCTION: STRONGHOLDCRUSADER 0x00500B50
    int TileMapState::computeTileAlongAxisOffset(int tileUnk, int addend, uint offset)
    {
        int yStep = 1;
        int direction = CD_SOUTH;
        int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tileUnk];
        if ((int)offset < 0) {
            yStep = -1;
            direction = CD_NORTH;
        }

        int count = abs(offset);
        for (int i = 0; i < count; i++) {
            tileUnk += this->directionTranslationMatrix[y][direction];
            y += yStep;
        }
        return tileUnk + addend;
    }

}
}
