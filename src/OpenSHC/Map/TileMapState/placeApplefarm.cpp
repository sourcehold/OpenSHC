#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_APPLE;
    using OpenSHC::Map::LogicHelpers::L_NONE;

    // FUNCTION: STRONGHOLDCRUSADER 0x00515740
    void TileMapState::placeApplefarm(int playerID, uint x, uint y, BuildingType buildingType, undefined4 buildingSize,
        int variation, int averageHeight)
    {
        int index = 0;
        int buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, (BuildingType)(short)buildingType, 3, playerID, variation);
        this->placedBuildingID = buildingID;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::markBuildingFootprintFlag, this)(x, y, 10);

        // the 8 apple tree tiles
        for (int i = 0; i < countof(DAT_TerrainDefinedData::instance.AppleFarmOffsets); i++) {
            DAT_BuildingsState::instance.buildings[buildingID].tileRefs[i]
                = DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_TerrainDefinedData::instance.AppleFarmOffsets[i].y + y]
                      .addXgetTile
                + DAT_TerrainDefinedData::instance.AppleFarmOffsets[i].x + x;
        }

        // the farm house
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 3);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x
                + this->buildingX;
            this->HeightLayer[tile] = (byte)averageHeight;
            this->LogicLayer[tile] |= L_BUILDING;
            this->BuildingLayer[tile] = (short)buildingID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(
                playerID, tile, this->buildingY + y, 2, L_NONE, L2_THICK_SCRUB);
            index++;
            this->ChangedLayer[tile] = 2;
            if (index >= this->constructionTileCount) {
                break;
            }
        }

        for (int i = 0; i < countof(DAT_TerrainDefinedData::instance.AppleFarmOffsets); i++) {
            int tile = DAT_BuildingsState::instance.buildings[buildingID].tileRefs[i];
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->LogicLayer[tile] |= L_FARM_FIELD_APPLE;
            this->ChangedLayer[tile] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::placeAppleTree, DAT_LandscapeState::ptr)(buildingID,
                DAT_TerrainDefinedData::instance.AppleFarmOffsets[i].x + x,
                DAT_TerrainDefinedData::instance.AppleFarmOffsets[i].y + y);
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);

        // not enough idle peasants for the workers: tell the local player
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
