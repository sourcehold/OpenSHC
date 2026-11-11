#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FAE50
    void TileMapState::clearFixedSizeTwoBuildingFootprint(int x, int y)
    {
        int buildingSizeTileIndex = 0;

        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, 2);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            this->LogicLayer[tile] &= ~(L_STOCKPILEUnk | L_WALL_OR_GATEHOUSE | L_CRENEL | L_BUILDING | L_STAIRS
                | L_CRENEL_VARIATIONUnk | L_KEEP_NON_MANOR_HOUSE);
            int buildingID = this->BuildingLayer[tile];
            this->BuildingLayer[tile] = 0;
            if (DAT_BuildingsState::instance.buildings[buildingID].noRubble == 0) {
                this->BuildingWasLayer[tile] = 0;
            } else {
                this->MiscDisplayLayer[tile] |= 0x4000;
            }
            buildingSizeTileIndex++;
            this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
            if (buildingSizeTileIndex >= this->constructionTileCount) {
                break;
            }
        }
    }

}
}
