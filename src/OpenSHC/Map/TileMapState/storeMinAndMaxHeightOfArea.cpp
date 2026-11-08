#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F9980
    void TileMapState::storeMinAndMaxHeightOfArea(uint x, uint y, int buildingWidthAndHeight)
    {
        this->buildingMinHeight = 1000;
        this->buildingMaxHeight = 0;
        if (x > MC_MAP_XY_LIMIT_INCLUSIVE || y > MC_MAP_XY_LIMIT_INCLUSIVE) {
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + x] == 0) {
            return;
        }

        int buildingSizeTileIndex = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, buildingWidthAndHeight);
            uint footprintY = this->buildingY + y;
            uint footprintX = this->buildingX + x;
            if (footprintX <= MC_MAP_XY_LIMIT_INCLUSIVE && footprintY <= MC_MAP_XY_LIMIT_INCLUSIVE
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[footprintY * MC_MAP_XY_LIMIT + footprintX]
                    != 0) {
                uint height
                    = this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[footprintY].addXgetTile
                        + this->buildingX + x];
                if ((int)height > this->buildingMaxHeight) {
                    this->buildingMaxHeight = height;
                }
                if ((int)height < this->buildingMinHeight) {
                    this->buildingMinHeight = height;
                }
            }
            buildingSizeTileIndex++;
            if (buildingSizeTileIndex >= this->constructionTileCount) {
                break;
            }
        }
    }

}
}
