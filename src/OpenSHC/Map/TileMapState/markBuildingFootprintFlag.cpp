#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FA9D0
    void TileMapState::markBuildingFootprintFlag(int x, int y, int buildingSize)
    {
        int buildingSizeTileIndex = 0;

        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, buildingSize);
            buildingSizeTileIndex++;
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            this->LogicLayer[tile] |= L_PLAIN1_AND_FARM;
            this->MiscDisplayLayer[tile] &= ~0xc;
            if (buildingSizeTileIndex >= this->constructionTileCount) {
                break;
            }
        }
    }

}
}
