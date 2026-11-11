#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;

    // FUNCTION: STRONGHOLDCRUSADER 0x005076A0
    void TileMapState::placeBarracks(int playerID, uint x, uint y, undefined4 buildingType, uint buildingSize,
        int buildingOrientation, undefined4 averageHeight)
    {
        uint const baseX = x;
        uint const baseY = y;
        int const uniqueID = DAT_GameCore::instance.uniqueGameObjectTracker;
        int index = 0;
        int partIndex;
        if (buildingOrientation == 15) {
            partIndex = 0;
        } else {
            partIndex = buildingOrientation / 2;
        }
        ushort placedID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, (BuildingType)(short)buildingType, buildingSize, playerID, 15);
        int buildingID = (short)placedID;
        this->placedBuildingID = buildingID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uniqueID;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, buildingSize);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            DAT_BuildingsState::instance.buildings[buildingID].tileRefs[index] = tile;
            this->HeightLayer[tile] = (byte)averageHeight;
            this->LogicLayer[tile] |= L_BUILDING;
            this->BuildingLayer[tile] = placedID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            index++;
            if (index >= this->constructionTileCount) {
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);

        x += DAT_TerrainDefinedData::instance.BuildingPartsOffsets[partIndex][0].x;
        y += DAT_TerrainDefinedData::instance.BuildingPartsOffsets[partIndex][0].y;
        placedID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, OpenSHC::Map::Buildings::BT_PARADEGROUND3, 5, playerID, 15);
        buildingID = (short)placedID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uniqueID;
        DAT_BuildingsState::instance.buildings[buildingID].quarryStockpileID = (short)this->placedBuildingID;
        int campIndex = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                campIndex, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->HeightLayer[tile] = (byte)averageHeight;
            if (this->buildingX == 2 && this->buildingY == 2) {
                this->LogicLayer[tile] |= L_BUILDING;
            }
            this->BuildingLayer[tile] = placedID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            campIndex++;
            if (campIndex >= this->constructionTileCount) {
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, x, y);

        x = DAT_TerrainDefinedData::instance.BuildingPartsOffsets[partIndex][1].x + baseX;
        y = DAT_TerrainDefinedData::instance.BuildingPartsOffsets[partIndex][1].y + baseY;
        placedID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, OpenSHC::Map::Buildings::BT_PARADEGROUND4, 5, playerID, 15);
        buildingID = (short)placedID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uniqueID;
        DAT_BuildingsState::instance.buildings[buildingID].quarryStockpileID = (short)this->placedBuildingID;
        campIndex = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                campIndex, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->HeightLayer[tile] = (byte)averageHeight;
            if (this->buildingX == 2 && this->buildingY == 2) {
                this->LogicLayer[tile] |= L_BUILDING;
            }
            this->BuildingLayer[tile] = placedID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            campIndex++;
            if (campIndex >= this->constructionTileCount) {
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, x, y);

        x = DAT_TerrainDefinedData::instance.BuildingPartsOffsets[partIndex][2].x + baseX;
        y = DAT_TerrainDefinedData::instance.BuildingPartsOffsets[partIndex][2].y + baseY;
        placedID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, OpenSHC::Map::Buildings::BT_PARADEGROUND2, 5, playerID, 15);
        buildingID = (short)placedID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uniqueID;
        DAT_BuildingsState::instance.buildings[buildingID].quarryStockpileID = (short)this->placedBuildingID;
        campIndex = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                campIndex, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->HeightLayer[tile] = (byte)averageHeight;
            if (this->buildingX == 2 && this->buildingY == 2) {
                this->LogicLayer[tile] |= L_BUILDING;
            }
            this->BuildingLayer[tile] = placedID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            campIndex++;
            if (campIndex >= this->constructionTileCount) {
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, x, y);

        if ((short)buildingType == OpenSHC::Map::Buildings::BT_MERCENARYPOST) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupMercenaryPostCampgroundPositions,
                DAT_BuildingsState::ptr)(playerID);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBarracksCampgroundPositions,
                DAT_BuildingsState::ptr)(playerID);
        }

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
