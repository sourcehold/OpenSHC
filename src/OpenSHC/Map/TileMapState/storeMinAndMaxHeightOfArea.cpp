#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F9980
    void TileMapState::storeMinAndMaxHeightOfArea(uint x, uint y, int buildingWidthAndHeight)
    {
        this->buildingMinHeight = 1000;
        this->buildingMaxHeight = 0;
        if (x > 399 || y > 399) {
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return;
        }

        int buildingSizeTileIndex = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, buildingWidthAndHeight);
            uint footprintY = this->buildingY + y;
            uint footprintX = this->buildingX + x;
            if (footprintX <= 399 && footprintY <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[footprintY * 400 + footprintX] != 0) {
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
        } while (buildingSizeTileIndex < this->constructionTileCount);
    }

}
}
