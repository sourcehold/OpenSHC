#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_ROCKY;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FB970
    void TileMapState::clearRockFootprintFlags(int rockID)
    {
        int const rockX = DAT_LandscapeState::instance.rocks[rockID].x;
        int const rockY = DAT_LandscapeState::instance.rocks[rockID].y;
        int buildingSizeTileIndex = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, DAT_LandscapeState::instance.rocks[rockID].size);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + rockY].addXgetTile
                + this->buildingX + rockX;
            buildingSizeTileIndex++;
            this->LogicLayer[tile] &= ~L_ROCKY;
            this->OrganismLayer[tile] = 0;
            if (buildingSizeTileIndex >= this->constructionTileCount) {
                break;
            }
        }
    }

}
}
