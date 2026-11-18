#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/LogicHelpers/MiscDisplay.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;
    using OpenSHC::Map::LogicHelpers::MD_GATEHOUSE_RAISED;
    using OpenSHC::Map::LogicHelpers::MD_RUBBLE_EDGEUnk;
    using OpenSHC::Map::LogicHelpers::MD_RUBBLE_INNERUnk;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FAD70
    void TileMapState::clearBuildingFootprintWithEdgeRubble(int x, int y, int size)
    {
        int buildingSizeTileIndex = 0;

        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, size);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            this->LogicLayer[tile] &= ~(L_WALL_OR_GATEHOUSE | L_CRENEL | L_BUILDING | L_STAIRS | L_CRENEL_VARIATIONUnk
                | L_KEEP_NON_MANOR_HOUSE);
            if ((this->MiscDisplayLayer[tile] & MD_GATEHOUSE_RAISED) != 0) {
                this->MiscDisplayLayer[tile] &= ~MD_GATEHOUSE_RAISED;
                this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
            }
            int buildingID = this->BuildingLayer[tile];
            this->BuildingLayer[tile] = 0;
            if (DAT_BuildingsState::instance.buildings[buildingID].noRubble == 0) {
                this->BuildingWasLayer[tile] = 0;
            } else if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isFootprintIndexOnEdge, this)(
                           buildingSizeTileIndex, size)) {
                this->MiscDisplayLayer[tile] |= MD_RUBBLE_EDGEUnk;
            } else {
                this->MiscDisplayLayer[tile] |= MD_RUBBLE_INNERUnk;
            }
            buildingSizeTileIndex++;
            this->ChangedLayer[tile] = 2;
        } while (buildingSizeTileIndex < this->constructionTileCount);
    }

}
}
