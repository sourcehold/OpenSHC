#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E25A0
    void ViewportRenderState::tweakValidTilesToExcludeMapBorders()
    {
        for (int y = 0; y < Map::MC_MAP_XY_LIMIT; y++) {
            for (int x = 0; x < Map::MC_MAP_XY_LIMIT; x++) {
                if (this->DAT_BinaryTileMap400x400[y * Map::MC_MAP_XY_LIMIT + x] == 0) {
                    continue;
                }
                int tile = this->translationMatrix[y].addXgetTile + x;
                this->tileTranslationMatrix_YComponent[tile] = (short)y;
                if ((DAT_TileMapState::instance.LogicLayer[tile]
                        & (Map::LogicHelpers::L_BORDER | Map::LogicHelpers::L_BORDER_EDGE))
                    != 0) {
                    this->DAT_BinaryTileMap400x400[y * Map::MC_MAP_XY_LIMIT + x] = 0;
                }
            }
        }
    }

}
}
