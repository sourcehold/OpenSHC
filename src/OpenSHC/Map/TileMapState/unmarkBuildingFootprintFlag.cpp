#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FAD20
    void TileMapState::unmarkBuildingFootprintFlag(int x, int y, int buildingSize)
    {
        int buildingSizeTileIndex = 0;
        // do-while, not a for loop: the bound is this->constructionTileCount, which the
        // getBuildingSizeIndexMappingData call in the body sets. Testing it before the first
        // iteration would read the count of the previous footprint.
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, buildingSize);
            buildingSizeTileIndex++;
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_PLAIN1_AND_FARM;
        } while (buildingSizeTileIndex < this->constructionTileCount);
    }

}
}
