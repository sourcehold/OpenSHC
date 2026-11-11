#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500B50
    int TileMapState::computeTileAlongAxisOffset(int tileUnk, int addend, uint offset)
    {
        int yStep = 1;
        int direction = 4;
        int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tileUnk];
        if ((int)offset < 0) {
            yStep = -1;
            direction = 0;
        }

        int count = abs((int)offset);
        for (int i = 0; i < count; i++) {
            tileUnk += this->directionTranslationMatrix[y][direction];
            y += yStep;
        }
        return tileUnk + addend;
    }

}
}
