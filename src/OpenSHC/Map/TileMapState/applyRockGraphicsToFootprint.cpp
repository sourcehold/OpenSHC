
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FB770
    void TileMapState::applyRockGraphicsToFootprint(int rockID)
    {
        short rockX = DAT_LandscapeState::instance.rocks[rockID].x;
        short rockY = DAT_LandscapeState::instance.rocks[rockID].y;
        int orientation = DAT_LandscapeState::instance.rocks[rockID].orientation + this->mapOrientation;
        if (orientation > 7) {
            orientation = orientation - 8;
        }
        short size = DAT_LandscapeState::instance.rocks[rockID].size;
        short surface = (short)(orientation / 2) * size * size;

        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_LandscapeState::instance.rocks[rockID].size);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + rockY].addXgetTile + rockX
                + this->buildingX;
            if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0) {
                if (this->field93_0x5548c8 == 0) {
                    this->GfxLayer[tile]
                        = ((short)GMTotalPicturesProcessed::instance[DAT_LandscapeState::instance.rocks[rockID]
                                   .unknownGMID]
                              + (short)DAT_LandscapeState::instance.rocks[rockID].gfx
                              + (short)this->buildingRotationRelatedValue + surface)
                        - 1;
                } else if (DAT_LandscapeState::instance.rocks[rockID].size == 1) {
                    this->GfxLayer[tile]
                        = ((short)GMTotalPicturesProcessed::instance[DAT_LandscapeState::instance.rocks[rockID]
                                   .unknownGMID]
                              + (short)DAT_LandscapeState::instance.rocks[rockID].gfx
                              + (short)this->buildingRotationRelatedValue + surface)
                        - 1;
                } else {
                    this->GfxLayer[tile]
                        = (short)MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getRandomRockImageOffset,
                              DAT_LandscapeState::ptr)(((byte)this->RandomLayer[tile] & 3) + 1)
                        + (short)
                            GMTotalPicturesProcessed::instance[DAT_LandscapeState::instance.rocks[rockID].unknownGMID]
                        + surface - 1;
                }
            }
            index++;
        } while (index < this->constructionTileCount);
    }

}
}
