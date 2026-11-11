#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FA760
    void TileMapState::demolishBuildingsInKeepsConstructionFootprint(undefined4 unusedPlayerID, int x, int y,
        undefined4 buildingType, int sizeIndex, int unusedOrientation, int unusedAverageHeight)
    {
        int const keepX = x;
        int const keepY = y;
        int index = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, sizeIndex);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            if (this->BuildingLayer[tile] != 0) {
                this->showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                    DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
            }
            index++;
            if (index >= this->constructionTileCount) {
                break;
            }
        }

        // the keep drags three towers and two outbuildings with it, laid out per keep variant
        buildingType = (short)buildingType - OpenSHC::Map::Buildings::BT_MANORHOUSE;
        {
            int const tile = DAT_ViewportRenderState::instance
                                 .translationMatrix[DAT_TerrainDefinedData::instance.field_0x264[buildingType][0].y + y]
                                 .addXgetTile
                + DAT_TerrainDefinedData::instance.field_0x264[buildingType][0].x + x;
            if (this->BuildingLayer[tile] != 0) {
                this->showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                    DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
            }
        }

        {
            int const tile = DAT_ViewportRenderState::instance
                                 .translationMatrix[DAT_TerrainDefinedData::instance.field_0x264[buildingType][1].y + y]
                                 .addXgetTile
                + DAT_TerrainDefinedData::instance.field_0x264[buildingType][1].x + x;
            if (this->BuildingLayer[tile] != 0) {
                this->showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                    DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
            }
        }

        {
            int const tile = DAT_ViewportRenderState::instance
                                 .translationMatrix[DAT_TerrainDefinedData::instance.field_0x264[buildingType][2].y + y]
                                 .addXgetTile
                + DAT_TerrainDefinedData::instance.field_0x264[buildingType][2].x + x;
            if (this->BuildingLayer[tile] != 0) {
                this->showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                    DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
            }
        }

        x += DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[buildingType][0].xOffset;
        y += DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[buildingType][0].yOffset;
        index = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 7);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            if (this->BuildingLayer[tile] != 0) {
                this->showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                    DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
            }
            index++;
            if (index >= this->constructionTileCount) {
                break;
            }
        }

        x = keepX + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[buildingType][0].xOffset;
        y = keepY + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[buildingType][0].yOffset;
        index = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 5);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            if (this->BuildingLayer[tile] != 0) {
                this->showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                    DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
            }
            index++;
            if (index >= this->constructionTileCount) {
                break;
            }
        }

        for (int buildingID = 1; buildingID < 2000; buildingID++) {
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState
                == OpenSHC::Map::Buildings::BLS_REMOVE) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(buildingID);
            }
        }
    }

}
}
