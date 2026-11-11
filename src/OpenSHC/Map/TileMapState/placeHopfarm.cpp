#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
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
    void TileMapState::placeHopfarm(
        int param_1, uint param_2, uint param_3, undefined4 param_4, undefined4 param_5, int param_6, int param_7)
    {
        int index = 0;
        int const buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            param_1, param_2, param_3, param_7, (BuildingType)(short)param_4, 3, param_1, param_6);
        this->placedBuildingID = buildingID;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::markBuildingFootprintFlag, this)(param_2, param_3, 9);
        int const variation = DAT_GameState::instance.playerDataArray[param_1].unkHopFarmVariation;
        for (int i = 0; i < 24; i++) {
            DAT_BuildingsState::instance.buildings[buildingID].tileRefs[i]
                = DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_TerrainDefinedData::instance.HopFarmProperty1[variation][i].y + param_3]
                      .addXgetTile
                + DAT_TerrainDefinedData::instance.HopFarmProperty1[variation][i].x + param_2;
        }
        DAT_BuildingsState::instance.buildings[buildingID].someFarmRelatedState = variation != 0 ? 7 : 81;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 3);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + param_3].addXgetTile
                + this->buildingX + param_2;
            this->HeightLayer[tile] = (byte)param_7;
            this->LogicLayer[tile] |= OpenSHC::Map::LogicHelpers::L_BUILDING;
            this->BuildingLayer[tile] = (short)buildingID;
            this->BuildingWasLayer[tile] = (uchar)param_4;
            this->ChangedLayer[tile] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(param_1, tile,
                this->buildingY + param_3, 2, OpenSHC::Map::LogicHelpers::L_NONE,
                OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB);
            index++;
        } while (index < this->constructionTileCount);
        for (int i = 0; i < 24; i++) {
            int const tile
                = DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_TerrainDefinedData::instance
                                             .HopFarmProperty1[*(int*)&DAT_GameState::instance.playerDataArray[param_1]
                                                     .unkHopFarmVariation][i]
                                             .y
                          + param_3]
                      .addXgetTile
                + DAT_TerrainDefinedData::instance
                      .HopFarmProperty1[DAT_GameState::instance.playerDataArray[param_1].unkHopFarmVariation][i]
                      .x
                + param_2;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->LogicLayer[tile] |= 0x2000000;
            this->BuildingLayer[tile] = (short)buildingID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(
                DAT_TerrainDefinedData::instance
                        .HopFarmProperty1[DAT_GameState::instance.playerDataArray[param_1].unkHopFarmVariation][i]
                        .y
                    + param_3,
                tile);
            this->BuildingWasLayer[tile] = (uchar)param_4;
            this->ChangedLayer[tile] = 2;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        DAT_GameState::instance.playerDataArray[param_1].unkHopFarmVariation += 1;
        if (DAT_GameState::instance.playerDataArray[param_1].unkHopFarmVariation > 1) {
            DAT_GameState::instance.playerDataArray[param_1].unkHopFarmVariation = 0;
        }
        if (param_1 == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_BuildingsState::instance.buildings[buildingID].buildingTypeBasedEmployeeCount
                > DAT_GameState::instance.playerDataArray[param_1].availablePeasantsAtFire
            && (DAT_GameState::instance.playerDataArray[param_1].populationCap
                    <= DAT_GameState::instance.playerDataArray[param_1].currentPopulation
                || DAT_GameState::instance.playerDataArray[param_1].popularity < 5000)) {
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(1, 0x4d, 1, 0, 100, 6000);
        }
    }

}
}
