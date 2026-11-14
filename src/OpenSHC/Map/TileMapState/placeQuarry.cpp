#include "../TileMapState.func.hpp"

#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;

    // FUNCTION: STRONGHOLDCRUSADER 0x00508250
    void TileMapState::placeQuarry(int playerID, uint x, uint y, undefined4 buildingType, uint buildingSize,
        int buildingOrientation, uint averageHeight)
    {
        int index = 0;
        int uid = DAT_GameCore::instance.uniqueGameObjectTracker;
        int quarryID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID, x, y,
            averageHeight, (BuildingType)(short)buildingType, buildingSize, playerID, buildingOrientation);
        this->placedBuildingID = quarryID;
        DAT_BuildingsState::instance.buildings[quarryID].uidWhenPlaced = uid;

        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, buildingSize);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x
                + this->buildingX;
            index++;
            this->HeightLayer[tile] = (byte)averageHeight;
            this->LogicLayer[tile] |= L_BUILDING;
            this->BuildingLayer[tile] = (short)quarryID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            if (index >= this->constructionTileCount) {
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(quarryID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(quarryID);

        // nine attempts at a pile location, moving further from the quarry each time
        for (int attempt = 1; attempt < 10; attempt++) {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::findQuarryPileLocation, DAT_BuildingsState::ptr)(
                playerID, x, y, buildingSize, 2, attempt, OpenSHC::Commands::M_MAPPER_QUARRYPILE);
            if (this->buildingPlacementFail == FALSE) {
                break;
            }
        }
        if (this->buildingPlacementFail != FALSE) {
            return;
        }

        // x/y now name the pile corner
        x = x + DAT_BuildingsState::instance.DAT_TempXOffset;
        y += DAT_BuildingsState::instance.DAT_TempYOffset;
        int tileIndex = 0;
        int lowest = 1000;
        int highest = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(tileIndex, 2);
            int tileHeight
                = this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                    + x + this->buildingX];
            if (tileHeight > highest) {
                highest = tileHeight;
            }
            if (tileHeight < lowest) {
                lowest = tileHeight;
            }
            tileIndex++;
            if (tileIndex >= this->constructionTileCount) {
                break;
            }
        }
        averageHeight = (highest - lowest) / 2 + lowest;

        tileIndex = 0;
        int pileID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID, x, y,
            averageHeight, OpenSHC::Map::Buildings::BT_QUARRYSTOCKPILE, 2, playerID, buildingOrientation);
        MACRO_CALL_MEMBER(OpenSHC::AI::AIVState_Func::incrementStructureHeatMapTile, DAT_AIVState::ptr)(x, y);
        DAT_BuildingsState::instance.buildings[pileID].uidWhenPlaced = uid;
        DAT_BuildingsState::instance.buildings[quarryID].quarryStockpileID = (short)pileID;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(tileIndex, 2);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x
                + this->buildingX;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->HeightLayer[tile] = (byte)averageHeight;
            this->LogicLayer[tile] |= L_BUILDING;
            this->BuildingLayer[tile] = (short)pileID;
            tileIndex++;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            if (tileIndex >= this->constructionTileCount) {
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(pileID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(pileID);

        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_BuildingsState::instance.buildings[pileID].buildingTypeBasedEmployeeCount
                > DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
            && (DAT_GameState::instance.playerDataArray[playerID].populationCap
                    <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation
                || DAT_GameState::instance.playerDataArray[playerID].popularity < 5000)) {
            // "Not enough workers available to run this building."
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(1, OpenSHC::DE::SHCDE::TEXT_PANEL_FEEDBACK, 1, 0, 100, 6000);
        }
    }

}
}
