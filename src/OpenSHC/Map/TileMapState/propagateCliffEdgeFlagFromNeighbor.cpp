#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS;
    using OpenSHC::Map::LogicHelpers::L2_STONES_OR_DRIVEN_SANDUnk;
    using OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
    using OpenSHC::Map::LogicHelpers::L_RIVER;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FC280
    void TileMapState::propagateCliffEdgeFlagFromNeighbor(int tile, int x, int y)
    {
        int height = this->HeightLayer[tile];
        if (this->Logic2Layer[tile] != 0) {
            return;
        }

        for (int index = 0; index < 8; index++) {
            uint neighbourY = DAT_TerrainDefinedData::instance.field2476_0x372c[index].y + y;
            uint neighbourX = DAT_TerrainDefinedData::instance.field2476_0x372c[index].x + x;
            if (neighbourX > 399 || neighbourY > 399) {
                continue;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[neighbourY * 400 + neighbourX] == 0) {
                continue;
            }
            int neighbour = DAT_ViewportRenderState::instance.translationMatrix[neighbourY].addXgetTile
                + DAT_TerrainDefinedData::instance.field2476_0x372c[index].x + x;
            if ((this->LogicLayer[neighbour] & L_RIVER) == 0) {
                continue;
            }
            if ((this->Logic2Layer[neighbour] & (L2_OASIS_GRASS | L2_STONES_OR_DRIVEN_SANDUnk)) == 0) {
                continue;
            }
            if (this->HeightLayer[neighbour] < height) {
                continue;
            }
            this->Logic2Layer[tile] = L2_THICK_SCRUB;
            return;
        }
    }

}
}
