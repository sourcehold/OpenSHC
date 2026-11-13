#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FB770
    void TileMapState::applyRockGraphicsToFootprint(int rockID)
    {
        int rockX = DAT_LandscapeState::instance.rocks[rockID].x;
        int rockY = DAT_LandscapeState::instance.rocks[rockID].y;
        int orientation = DAT_LandscapeState::instance.rocks[rockID].orientation + this->mapOrientation;
        int index = 0;
        if (orientation >= 8) {
            orientation -= 8;
        }
        int size = DAT_LandscapeState::instance.rocks[rockID].size;
        int surface = (orientation / 2) * size * size;

        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_LandscapeState::instance.rocks[rockID].size);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + rockY].addXgetTile + rockX
                + this->buildingX;
            if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0) {
                if (this->disableElevationRendering == 0) {
                    this->GfxLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_LandscapeState::instance.rocks[rockID].unknownGMID]
                        + DAT_LandscapeState::instance.rocks[rockID].gfx + this->buildingRotationRelatedValue + surface
                        - 1;
                } else if (DAT_LandscapeState::instance.rocks[rockID].size == 1) {
                    this->GfxLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_LandscapeState::instance.rocks[rockID].unknownGMID]
                        + DAT_LandscapeState::instance.rocks[rockID].gfx + this->buildingRotationRelatedValue + surface
                        - 1;
                } else {
                    this->GfxLayer[tile]
                        = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getRandomRockImageOffset,
                              DAT_LandscapeState::ptr)((DAT_TileMapState::instance.RandomLayer[tile] & 3) + 1)
                        + GMFirstPictureIndex::instance[DAT_LandscapeState::instance.rocks[rockID].unknownGMID]
                        + surface - 1;
                }
            }
            index++;
            if (index >= this->constructionTileCount) {
                break;
            }
        }
    }

}
}
