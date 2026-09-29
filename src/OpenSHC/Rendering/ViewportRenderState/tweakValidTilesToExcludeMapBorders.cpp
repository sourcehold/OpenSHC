#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E25A0
    void ViewportRenderState::tweakValidTilesToExcludeMapBorders()
    {
        for (int y = 0; y < 400; y++) {
            for (int x = 0; x < 400; x++) {
                if (this->DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
                    continue;
                }
                int tile = this->translationMatrix[y].addXgetTile + x;
                this->tileTranslationMatrix_YComponent[tile] = (short)y;
                if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x30) != 0) {
                    this->DAT_BinaryTileMap400x400[y * 400 + x] = 0;
                }
            }
        }
    }

}
}
