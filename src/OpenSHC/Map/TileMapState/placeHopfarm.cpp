#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005151C0
    void TileMapState::placeHopfarm(int playerID, uint x, uint y, undefined4 buildingType, undefined4 buildingSize,
        int variation, int averageHeight)
    {
        int index = 0;
        int const buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, (BuildingType)(short)buildingType, 3, playerID, variation);
        this->placedBuildingID = buildingID;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::markBuildingFootprintFlag, this)(x, y, 9);
        int const layout = DAT_GameState::instance.playerDataArray[playerID].unkHopFarmVariation;
        for (int i = 0; i < 24; i++) {
            DAT_BuildingsState::instance.buildings[buildingID].tileRefs[i]
                = DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_TerrainDefinedData::instance.HopFarmProperty1[layout][i].y + y]
                      .addXgetTile
                + DAT_TerrainDefinedData::instance.HopFarmProperty1[layout][i].x + x;
        }
        DAT_BuildingsState::instance.buildings[buildingID].someFarmRelatedState = layout != 0 ? 7 : 81;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 3);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            this->HeightLayer[tile] = (byte)averageHeight;
            this->LogicLayer[tile] |= OpenSHC::Map::LogicHelpers::L_BUILDING;
            this->BuildingLayer[tile] = (short)buildingID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(playerID, tile, this->buildingY + y, 2,
                OpenSHC::Map::LogicHelpers::L_NONE, OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB);
            index++;
            if (index >= this->constructionTileCount) {
                break;
            }
        }
        for (int i = 0; i < 24; i++) {
            int const tile
                = DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_TerrainDefinedData::instance
                                             .HopFarmProperty1[DAT_GameState::instance.playerDataArray[playerID]
                                                     .unkHopFarmVariation][i]
                                             .y
                          + y]
                      .addXgetTile
                + DAT_TerrainDefinedData::instance
                      .HopFarmProperty1[DAT_GameState::instance.playerDataArray[playerID].unkHopFarmVariation][i]
                      .x
                + x;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->LogicLayer[tile] |= OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP;
            this->BuildingLayer[tile] = (short)buildingID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(
                DAT_TerrainDefinedData::instance
                        .HopFarmProperty1[DAT_GameState::instance.playerDataArray[playerID].unkHopFarmVariation][i]
                        .y
                    + y,
                tile);
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        DAT_GameState::instance.playerDataArray[playerID].unkHopFarmVariation += 1;
        if (DAT_GameState::instance.playerDataArray[playerID].unkHopFarmVariation > 1) {
            DAT_GameState::instance.playerDataArray[playerID].unkHopFarmVariation = 0;
        }
        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_BuildingsState::instance.buildings[buildingID].buildingTypeBasedEmployeeCount
                > DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
            && (DAT_GameState::instance.playerDataArray[playerID].populationCap
                    <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation
                || DAT_GameState::instance.playerDataArray[playerID].popularity < 5000)) {
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(1, OpenSHC::DE::SHCDE::TEXT_PANEL_FEEDBACK, 1, 0, 100, 6000);
        }
    }

}
}
