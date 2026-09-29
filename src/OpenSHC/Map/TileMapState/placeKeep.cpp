
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
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
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::LogicHelpers::Logic1;
    using OpenSHC::Map::LogicHelpers::Logic2;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005146D0
    void TileMapState::placeKeep(
        int playerID, uint x, uint y, BuildingType type, uint size, int orientation, int xyValue)
    {
        uint baseX = x;
        uint baseY = y;
        if (this->field195_0x554a24 != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::demolishBuildingsInKeepsConstructionFootprint, this)(
                playerID, x, y, type, size, orientation, xyValue);
            this->field195_0x554a24 = 0;
        }

        int uid = DAT_GameCore::instance.uniqueGameObjectTracker;
        int keepKind = 0;
        byte logic2 = this->Logic2Layer[DAT_ViewportRenderState::instance.translationMatrix[baseY].addXgetTile + baseX];
        int keepID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, baseX, baseY, xyValue, (BuildingType)(short)type, size, playerID, 0xf);
        this->placedBuildingID = keepID;
        DAT_BuildingsState::instance.buildings[keepID].uidWhenPlaced = uid;
        short keepOrientation = (short)orientation;
        DAT_BuildingsState::instance.buildings[keepID].orientation = keepOrientation;
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding, DAT_GameState::ptr)(
            keepID, playerID, OpenSHC::Game::Player::PDBCE_KEEP);
        if (orientation == 0xf) {
            orientation = 0;
        }

        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + baseY].addXgetTile + this->buildingX + baseX;
            if (index < 0x24) {
                DAT_BuildingsState::instance.buildings[keepID].tileRefs[index] = tile;
            }
            this->HeightLayer[tile] = (byte)xyValue;
            if ((short)type == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            } else {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_KEEP_NON_MANOR_HOUSE;
            }
            this->BuildingLayer[tile] = (short)keepID;
            this->BuildingWasLayer[tile] = (uchar)type;
            /* grass and scrub come back as scrub, anything else as bare earth */
            Logic2 terrain;
            uint brush;
            if ((logic2 & (OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS | OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB)) == 0) {
                terrain = OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES;
                brush = 6;
            } else {
                terrain = OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
                brush = 3;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(
                playerID, tile, this->buildingY + baseY, brush, OpenSHC::Map::LogicHelpers::L_NONE, terrain);
            this->ChangedLayer[tile] = 2;
            index++;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(keepID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(keepID);
        if ((short)type == OpenSHC::Map::Buildings::BT_MANORHOUSE || (short)type == OpenSHC::Map::Buildings::BT_STONEKEEP) {
            keepKind = 2;
        }

        /* the three keep doors and the two outbuildings are laid out per keep type and orientation */
        int group = orientation / 2 + -0xa0 + (short)type * 4;
        {
            int doorX = DAT_TerrainDefinedData::instance.field130_0x264[0][group * 3 + 0].x + baseX;
            uint doorY = DAT_TerrainDefinedData::instance.field130_0x264[0][group * 3 + 0].y + baseY;
            int doorTile = DAT_ViewportRenderState::instance.translationMatrix[doorY].addXgetTile + doorX;
            int doorID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
                playerID, doorX, doorY, xyValue, OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT, 1, playerID, 0xf);
            DAT_BuildingsState::instance.buildings[doorID].uidWhenPlaced = uid;
            DAT_BuildingsState::instance.buildings[doorID].unknownManorHouseOrStoneKeepRelated = keepKind;
            DAT_BuildingsState::instance.buildings[doorID].quarryStockpileID = (short)this->placedBuildingID;
            DAT_BuildingsState::instance.buildings[doorID].orientation = keepOrientation;
            this->LogicLayer[doorTile] = this->LogicLayer[doorTile] | L_BUILDING;
            this->BuildingLayer[doorTile] = (short)doorID;
            this->ChangedLayer[doorTile] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections, DAT_PathFindingState::ptr)(
                (short)DAT_BuildingsState::instance.buildings[doorID].y, doorTile);
        }

        {
            int doorX = DAT_TerrainDefinedData::instance.field130_0x264[0][group * 3 + 1].x + baseX;
            uint doorY = DAT_TerrainDefinedData::instance.field130_0x264[0][group * 3 + 1].y + baseY;
            int doorTile = DAT_ViewportRenderState::instance.translationMatrix[doorY].addXgetTile + doorX;
            int doorID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
                playerID, doorX, doorY, xyValue, OpenSHC::Map::Buildings::BT_KEEPDOOR, 1, playerID, 0xf);
            DAT_BuildingsState::instance.buildings[doorID].uidWhenPlaced = uid;
            DAT_BuildingsState::instance.buildings[doorID].unknownManorHouseOrStoneKeepRelated = keepKind / 2;
            DAT_BuildingsState::instance.buildings[doorID].quarryStockpileID = (short)this->placedBuildingID;
            DAT_BuildingsState::instance.buildings[doorID].orientation = keepOrientation;
            this->MiscDisplayLayer[doorTile] = this->MiscDisplayLayer[doorTile] | 4;
            this->BuildingLayer[doorTile] = (short)doorID;
            this->ChangedLayer[doorTile] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections, DAT_PathFindingState::ptr)(
                (short)DAT_BuildingsState::instance.buildings[doorID].y, doorTile);
        }

        {
            int doorX = DAT_TerrainDefinedData::instance.field130_0x264[0][group * 3 + 2].x + baseX;
            uint doorY = DAT_TerrainDefinedData::instance.field130_0x264[0][group * 3 + 2].y + baseY;
            int doorTile = DAT_ViewportRenderState::instance.translationMatrix[doorY].addXgetTile + doorX;
            int doorID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
                playerID, doorX, doorY, xyValue, OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT, 1, playerID, 0xf);
            DAT_BuildingsState::instance.buildings[doorID].uidWhenPlaced = uid;
            DAT_BuildingsState::instance.buildings[doorID].unknownManorHouseOrStoneKeepRelated = keepKind;
            DAT_BuildingsState::instance.buildings[doorID].quarryStockpileID = (short)this->placedBuildingID;
            DAT_BuildingsState::instance.buildings[doorID].orientation = keepOrientation;
            this->LogicLayer[doorTile] = this->LogicLayer[doorTile] | L_BUILDING;
            this->BuildingLayer[doorTile] = (short)doorID;
            this->ChangedLayer[doorTile] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections, DAT_PathFindingState::ptr)(
                (short)DAT_BuildingsState::instance.buildings[doorID].y, doorTile);
        }

        uint campX = baseX + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[0][group].xOffset;
        uint campY = baseY + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[0][group].yOffset;
        int campID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, campX, campY, xyValue, OpenSHC::Map::Buildings::BT_CAMPGROUND, 7, playerID, 0xf);
        DAT_BuildingsState::instance.buildings[campID].uidWhenPlaced = uid;
        DAT_BuildingsState::instance.buildings[campID].quarryStockpileID = (short)this->placedBuildingID;
        DAT_BuildingsState::instance.buildings[campID].orientation = keepOrientation;
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding, DAT_GameState::ptr)(
            campID, playerID, OpenSHC::Game::Player::PDBCE_CAMPGROUND);

        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 7);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(
                DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + campY].addXgetTile + this->buildingX + campX);
            index++;
        } while (index < this->constructionTileCount);

        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_BuildingsState::instance.buildings[campID].widthOrHeight);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + campY].addXgetTile + this->buildingX + campX;
            if (index < 0x18) {
                DAT_BuildingsState::instance.buildings[campID].tileRefs[index]
                    = DAT_ViewportRenderState::instance
                          .translationMatrix[(short)DAT_BuildingsState::instance.buildings[campID].y + DAT_TerrainDefinedData::instance.field197_0x444[index].y]
                          .addXgetTile
                    + (short)DAT_BuildingsState::instance.buildings[campID].x + DAT_TerrainDefinedData::instance.field197_0x444[index].x;
            }
            this->HeightLayer[tile] = (byte)xyValue;
            /* only the campground's cross of five middle tiles blocks movement */
            if (this->buildingX == 3 && this->buildingY == 3) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            }
            if (this->buildingX == 3 && this->buildingY == 2) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            }
            if (this->buildingX == 3 && this->buildingY == 4) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            }
            if (this->buildingX == 2 && this->buildingY == 3) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            }
            if (this->buildingX == 4 && this->buildingY == 3) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            }
            this->BuildingLayer[tile] = (short)campID;
            this->ChangedLayer[tile] = 2;
            Logic2 terrain;
            uint brush;
            if ((logic2 & (OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS | OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB)) == 0) {
                terrain = OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES;
                brush = 6;
            } else {
                terrain = OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
                brush = 3;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(
                playerID, tile, this->buildingY + campY, brush, OpenSHC::Map::LogicHelpers::L_NONE, terrain);
            index++;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(campID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(campID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer, DAT_PathFindingState::ptr)(10, campX, campY);

        int stockpileX = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[0][group].xOffset;
        int stockpileY = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[0][group].yOffset;
        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 5);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(
                DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + stockpileY + baseY].addXgetTile + this->buildingX
                + stockpileX + baseX);
            index++;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeStockpile, this)(
            playerID, stockpileX + baseX, stockpileY + baseY, 10, 5, 0xf, xyValue);
    }

}
}
