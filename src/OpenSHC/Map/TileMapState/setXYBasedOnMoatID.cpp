#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005003D0
    int TileMapState::setXYBasedOnMoatID(int moatID, int mode, uint x, uint y)
    {
        bool const isOnMap
            = x <= 399 && y <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0;
        if (!isOnMap) {
            return 0;
        }

        int const tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        int const tilePathConnection = (short)this->PathConnectionLayer[tile];
        int const tileHeight = this->HeightLayer[tile];
        if (mode == 1) {
            this->ALG_MoatXResult = this->moats[moatID].x;
            this->ALG_MoatYResult = this->moats[moatID].y;
            return DAT_ViewportRenderState::instance.translationMatrix[this->ALG_MoatYResult].addXgetTile
                + this->ALG_MoatXResult;
        }
        if (mode != 2) {
            return 0;
        }

        for (int direction = 0; direction < countof(this->directionTranslationMatrix[0]); direction++) {
            int const neighbour
                = this->directionTranslationMatrix[this->moats[moatID].y][direction] + this->moats[moatID].tile;
            if (this->HeightLayer[neighbour] > tileHeight + 16) {
                continue;
            }
            if ((short)this->PathConnectionLayer[neighbour] != tilePathConnection) {
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
