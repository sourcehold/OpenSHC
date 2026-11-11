#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_ROCKY;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FB970
    void TileMapState::clearRockFootprintFlags(int rockID)
    {
        int rockX = (short)DAT_LandscapeState::instance.rocks[rockID].x;
        int rockY = (short)DAT_LandscapeState::instance.rocks[rockID].y;
        int buildingSizeTileIndex = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, DAT_LandscapeState::instance.rocks[rockID].size);
            buildingSizeTileIndex++;
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + rockY].addXgetTile + rockX
                + this->buildingX;
            this->LogicLayer[tile] &= ~L_ROCKY;
            this->OrganismLayer[tile] = 0;
        } while (buildingSizeTileIndex < this->constructionTileCount);
    }

}
}
