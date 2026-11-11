#include "../TileMapState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/Player/PlayerDataBuildingCategoryEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;

    using OpenSHC::Game::Player::PlayerDataBuildingCategoryEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x005146D0
    void TileMapState::placeKeep(
        int playerID, uint x, uint y, BuildingType type, uint size, int orientation, int xyValue)
    {
        if (this->clearKeepFootprintOnPlace != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::demolishBuildingsInKeepsConstructionFootprint, this)(
                playerID, x, y, type, size, orientation, xyValue);
            this->clearKeepFootprintOnPlace = 0;
        }

        int uid = DAT_GameCore::instance.uniqueGameObjectTracker;
        int keepKind = 0;
        int index = 0;
        int keepOrientation = orientation;
        // grass and scrub come back as scrub, anything else as bare earth
        int grassy = this->Logic2Layer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x]
            & (OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS | OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB);
        short keepType = (short)type;
        // the outbuildings below move x and y
        uint baseX = x;
        uint baseY = y;
        int keepID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
            DAT_BuildingsState::ptr)(playerID, x, y, xyValue, (BuildingType)keepType, size, playerID, 15);
        this->placedBuildingID = keepID;
        DAT_BuildingsState::instance.buildings[keepID].uidWhenPlaced = uid;
        DAT_BuildingsState::instance.buildings[keepID].orientation = (short)orientation;
        MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
            DAT_GameState::ptr)(keepID, playerID, OpenSHC::Game::Player::PDBCE_KEEP);
        if (orientation == 15) {
            orientation = 0;
        }

        int tile;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            if (index < countof(DAT_BuildingsState::instance.buildings[keepID].tileRefs)) {
                DAT_BuildingsState::instance.buildings[keepID].tileRefs[index] = tile;
            }
            this->HeightLayer[tile] = (byte)xyValue;
            if (keepType == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
                this->LogicLayer[tile] |= L_BUILDING;
            } else {
                this->LogicLayer[tile] |= L_KEEP_NON_MANOR_HOUSE;
            }
            this->BuildingLayer[tile] = (short)keepID;
            this->BuildingWasLayer[tile] = (uchar)keepType;
            if (grassy != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(playerID, tile,
                    this->buildingY + y, 3, OpenSHC::Map::LogicHelpers::L_NONE,
                    OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(playerID, tile,
                    this->buildingY + y, 6, OpenSHC::Map::LogicHelpers::L_NONE,
                    OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES);
            }
            this->ChangedLayer[tile] = 2;
            index++;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(keepID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(keepID);
        if (keepType == OpenSHC::Map::Buildings::BT_MANORHOUSE || keepType == OpenSHC::Map::Buildings::BT_STONEKEEP) {
            keepKind = 2;
        }

        // the three keep doors and the two outbuildings are laid out per keep type and orientation
        int group = orientation / 2 + keepType * 4 - 160;
        {
            uint doorY = DAT_TerrainDefinedData::instance.field_0x264[0][group * 3 + 0].y + y;
            int doorTile = DAT_ViewportRenderState::instance.translationMatrix[doorY].addXgetTile
                + DAT_TerrainDefinedData::instance.field_0x264[0][group * 3 + 0].x + x;
            int doorID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
                DAT_BuildingsState::ptr)(playerID, DAT_TerrainDefinedData::instance.field_0x264[0][group * 3 + 0].x + x,
                doorY, xyValue, OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT, 1, playerID, 15);
            DAT_BuildingsState::instance.buildings[doorID].uidWhenPlaced = uid;
            DAT_BuildingsState::instance.buildings[doorID].unknownManorHouseOrStoneKeepRelated = keepKind;
            DAT_BuildingsState::instance.buildings[doorID].quarryStockpileID = (short)this->placedBuildingID;
            DAT_BuildingsState::instance.buildings[doorID].orientation = (short)keepOrientation;
            this->LogicLayer[doorTile] |= L_BUILDING;
            this->BuildingLayer[doorTile] = (short)doorID;
            this->ChangedLayer[doorTile] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(DAT_BuildingsState::instance.buildings[doorID].y, doorTile);
        }

        {
            uint doorY = DAT_TerrainDefinedData::instance.field_0x264[0][group * 3 + 1].y + y;
            int doorTile = DAT_ViewportRenderState::instance.translationMatrix[doorY].addXgetTile
                + DAT_TerrainDefinedData::instance.field_0x264[0][group * 3 + 1].x + x;
            int doorID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
                DAT_BuildingsState::ptr)(playerID, DAT_TerrainDefinedData::instance.field_0x264[0][group * 3 + 1].x + x,
                doorY, xyValue, OpenSHC::Map::Buildings::BT_KEEPDOOR, 1, playerID, 15);
            DAT_BuildingsState::instance.buildings[doorID].uidWhenPlaced = uid;
            DAT_BuildingsState::instance.buildings[doorID].unknownManorHouseOrStoneKeepRelated = keepKind / 2;
            DAT_BuildingsState::instance.buildings[doorID].quarryStockpileID = (short)this->placedBuildingID;
            DAT_BuildingsState::instance.buildings[doorID].orientation = (short)keepOrientation;
            this->MiscDisplayLayer[doorTile] |= 4;
            this->BuildingLayer[doorTile] = (short)doorID;
            this->ChangedLayer[doorTile] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(DAT_BuildingsState::instance.buildings[doorID].y, doorTile);
        }

        {
            uint doorY = DAT_TerrainDefinedData::instance.field_0x264[0][group * 3 + 2].y + y;
            int doorTile = DAT_ViewportRenderState::instance.translationMatrix[doorY].addXgetTile
                + DAT_TerrainDefinedData::instance.field_0x264[0][group * 3 + 2].x + x;
            int doorID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
                DAT_BuildingsState::ptr)(playerID, DAT_TerrainDefinedData::instance.field_0x264[0][group * 3 + 2].x + x,
                doorY, xyValue, OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT, 1, playerID, 15);
            DAT_BuildingsState::instance.buildings[doorID].uidWhenPlaced = uid;
            DAT_BuildingsState::instance.buildings[doorID].unknownManorHouseOrStoneKeepRelated = keepKind;
            DAT_BuildingsState::instance.buildings[doorID].quarryStockpileID = (short)this->placedBuildingID;
            DAT_BuildingsState::instance.buildings[doorID].orientation = (short)keepOrientation;
            this->LogicLayer[doorTile] |= L_BUILDING;
            this->BuildingLayer[doorTile] = (short)doorID;
            this->ChangedLayer[doorTile] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(DAT_BuildingsState::instance.buildings[doorID].y, doorTile);
        }

        // the campground
        y = y + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[0][group].yOffset;
        x += DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[0][group].xOffset;
        int campID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
            DAT_BuildingsState::ptr)(playerID, x, y, xyValue, OpenSHC::Map::Buildings::BT_CAMPGROUND, 7, playerID, 15);
        DAT_BuildingsState::instance.buildings[campID].uidWhenPlaced = uid;
        DAT_BuildingsState::instance.buildings[campID].quarryStockpileID = (short)this->placedBuildingID;
        DAT_BuildingsState::instance.buildings[campID].orientation = (short)keepOrientation;
        MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
            DAT_GameState::ptr)(campID, playerID, OpenSHC::Game::Player::PDBCE_CAMPGROUND);

        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 7);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(
                DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + this->buildingX
                + x);
            index++;
        } while (index < this->constructionTileCount);

        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_BuildingsState::instance.buildings[campID].widthOrHeight);
            tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            if (index < countof(DAT_TerrainDefinedData::instance.field_0x444)) {
                DAT_BuildingsState::instance.buildings[campID].tileRefs[index]
                    = DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_BuildingsState::instance.buildings[campID].y
                              + DAT_TerrainDefinedData::instance.field_0x444[index].y]
                          .addXgetTile
                    + DAT_BuildingsState::instance.buildings[campID].x
                    + DAT_TerrainDefinedData::instance.field_0x444[index].x;
            }
            this->HeightLayer[tile] = (byte)xyValue;
            // only the campground's cross of five middle tiles blocks movement
            if (this->buildingX == 3 && this->buildingY == 3) {
                this->LogicLayer[tile] |= L_BUILDING;
            }
            if (this->buildingX == 3 && this->buildingY == 2) {
                this->LogicLayer[tile] |= L_BUILDING;
            }
            if (this->buildingX == 3 && this->buildingY == 4) {
                this->LogicLayer[tile] |= L_BUILDING;
            }
            if (this->buildingX == 2 && this->buildingY == 3) {
                this->LogicLayer[tile] |= L_BUILDING;
            }
            if (this->buildingX == 4 && this->buildingY == 3) {
                this->LogicLayer[tile] |= L_BUILDING;
            }
            this->BuildingLayer[tile] = (short)campID;
            this->ChangedLayer[tile] = 2;
            if (grassy != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(playerID, tile,
                    this->buildingY + y, 3, OpenSHC::Map::LogicHelpers::L_NONE,
                    OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(playerID, tile,
                    this->buildingY + y, 6, OpenSHC::Map::LogicHelpers::L_NONE,
                    OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES);
            }
            index++;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(campID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(campID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(10, x, y);

        // the stockpile is placed from the keep's own position
        x = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[0][group].xOffset + baseX;
        y = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[0][group].yOffset + baseY;
        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 5);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(
                DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + this->buildingX
                + x);
            index++;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeStockpile, this)(
            playerID, x, y, OpenSHC::Map::Buildings::BT_STOCKPILE, 5, 15, xyValue);
    }

}
}
