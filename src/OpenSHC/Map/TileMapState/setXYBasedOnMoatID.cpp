#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005003D0
    int TileMapState::setXYBasedOnMoatID(int moatID, int param_2, uint x, uint y)
    {
        if (x > 399 || y > 399) {
            return 0;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return 0;
        }

        int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        if (param_2 == 1) {
            this->ALG_MoatXResult = this->moats[moatID].x;
            this->ALG_MoatYResult = this->moats[moatID].y;
            return DAT_ViewportRenderState::instance.translationMatrix[this->ALG_MoatYResult].addXgetTile
                + this->ALG_MoatXResult;
        }
        if (param_2 != 2) {
            return 0;
        }

        for (int direction = 0; direction < 8; direction++) {
            int neighbour
                = this->directionTranslationMatrix[this->moats[moatID].y][direction] + this->moats[moatID].tile;
            if ((uint)(this->HeightLayer[tile] + 0x10) < (uint)this->HeightLayer[neighbour]) {
                continue;
            }
            if (this->PathConnectionLayer[neighbour] != this->PathConnectionLayer[tile]) {
                continue;
            }

            this->someMoatTile = this->moats[moatID].tile;
            this->ALG_MoatXResult = this->moats[moatID].x
                + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset;
            this->ALG_MoatYResult = this->moats[moatID].y
                + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset;
            return neighbour;
        }
        return 0;
    }

}
}
