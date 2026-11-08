#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041ADE0
        undefined4 BuildingsState::determineBuildingEntranceFromKeepArea(
            int buildingID, int workerIndexPlus1, BOOLEnum flag)
        {
            // Finds an entrance tile of the building that can be reached from the campground of the owner.
            // flag enlarges the area around the building by one tile, workerIndexPlus1 - 1 matching tiles are skipped.
            // Returns 1 if an entrance was found, 2 if only an unreachable one (e.g. behind a locked gate) and 0
            // otherwise.

            // Tiles that cannot hold an entrance
            enum {
                BLOCKING_LOGIC = LogicHelpers::L_SEA | LogicHelpers::L_ROCKY | LogicHelpers::L_BUILDING
                    | LogicHelpers::L_TREE | LogicHelpers::L_RIVER | LogicHelpers::L_CRENEL_VARIATIONUnk
                    | LogicHelpers::L_KEEP_NON_MANOR_HOUSE | LogicHelpers::L_MOAT
            };
            int const playerID = this->buildings[buildingID].owner;
            int found = 0;
            int const areaFrom
                = DAT_TileMapState::instance.PathConnectionLayer[DAT_GameState::instance.playerDataArray[playerID]
                        .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                        .tileEntry];
            // Only the first search allows the larger height difference for quarries
            int heightStep = 16;
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_QUARRY) {
                heightStep = 32;
            }
            int const size = this->buildings[buildingID].widthOrHeight + flag * 2;
            int tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
            int index;
            if (tileCount > 0) {
                index = (short)this->buildings[buildingID].entranceAttemptTileIndex % tileCount;
                this->buildings[buildingID].entranceAttemptTileIndex = index;
            } else {
                index = 0;
            }
            this->buildings[buildingID].buildingEntryX = 0;
            this->buildings[buildingID].buildingEntryY = 0;
            int const height = this->buildings[buildingID].terrainHeightUnk;

            // Tiles next to the building.
            // Matching note: the three searches share one counter; a counter per for loop changes the stack slots
            int tries;
            for (tries = 0; tries < tileCount; ++tries) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(
                    size, 1, index, 0);
                int const tile = DAT_ViewportRenderState::instance
                                     .translationMatrix[this->buildings[buildingID].y - flag + this->DAT_TempYOffset]
                                     .addXgetTile
                    + this->buildings[buildingID].x - flag + this->DAT_TempXOffset;
                int tileHeight = DAT_TileMapState::instance.HeightLayer[tile];
                if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                    tileHeight += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(DAT_TileMapState::instance.BuildingLayer[tile]);
                }
                if ((DAT_TileMapState::instance.LogicLayer[tile] & BLOCKING_LOGIC) == 0
                    && height <= tileHeight + heightStep && height >= tileHeight - heightStep
                    && (areaFrom == 0 || DAT_TileMapState::instance.PathConnectionLayer[tile] == areaFrom
                        || MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                 calculateCanPlayerUnitsNavigateToAreaFromArea,
                               DAT_PathFindingState::ptr)(
                               playerID, areaFrom, DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                            != 0
                        || DAT_BuildingDefinedData::instance
                            .ABuildingTypeValueArray[this->buildings[buildingID].buildingType])
                    && ++found >= workerIndexPlus1) {
                    this->buildings[buildingID].buildingEntryX
                        = this->buildings[buildingID].x - flag + this->DAT_TempXOffset;
                    this->buildings[buildingID].buildingEntryY
                        = this->buildings[buildingID].y - flag + this->DAT_TempYOffset;
                    return 1;
                }
                ++index;
                if (index >= tileCount) {
                    index = 0;
                }
            }

            // Tiles one step further away (the original reuses the tile count variable)
            tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCountForOneLarger[size];
            for (tries = 0; tries < tileCount; ++tries) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::setupNextCandidateLocationComputeOffsets2, this)(
                    size, 1, index, 0);
                int const tile = DAT_ViewportRenderState::instance
                                     .translationMatrix[this->buildings[buildingID].y - flag + this->DAT_TempYOffset]
                                     .addXgetTile
                    + this->buildings[buildingID].x - flag + this->DAT_TempXOffset;
                int tileHeight = DAT_TileMapState::instance.HeightLayer[tile];
                if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                    tileHeight += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(DAT_TileMapState::instance.BuildingLayer[tile]);
                }
                if ((DAT_TileMapState::instance.LogicLayer[tile] & BLOCKING_LOGIC) == 0 && height <= tileHeight + 16
                    && height >= tileHeight - 16
                    && (areaFrom == 0 || DAT_TileMapState::instance.PathConnectionLayer[tile] == areaFrom
                        || MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                 calculateCanPlayerUnitsNavigateToAreaFromArea,
                               DAT_PathFindingState::ptr)(
                               playerID, areaFrom, DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                            != 0
                        || DAT_BuildingDefinedData::instance
                            .ABuildingTypeValueArray[this->buildings[buildingID].buildingType])
                    && ++found >= workerIndexPlus1) {
                    this->buildings[buildingID].buildingEntryX
                        = this->buildings[buildingID].x - flag + this->DAT_TempXOffset;
                    this->buildings[buildingID].buildingEntryY
                        = this->buildings[buildingID].y - flag + this->DAT_TempYOffset;
                    return 1;
                }
                ++index;
                if (index >= tileCount) {
                    index = 0;
                }
            }

            // Accept any walkable tile next to the building
            tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
            if (tileCount > 0) {
                index = (short)this->buildings[buildingID].entranceAttemptTileIndex % tileCount;
                this->buildings[buildingID].entranceAttemptTileIndex = index;
            } else {
                index = 0;
            }
            for (tries = 0; tries < tileCount; ++tries) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(
                    size, 1, index, 0);
                int const tile = DAT_ViewportRenderState::instance
                                     .translationMatrix[this->buildings[buildingID].y - flag + this->DAT_TempYOffset]
                                     .addXgetTile
                    + this->buildings[buildingID].x - flag + this->DAT_TempXOffset;
                int tileHeight = DAT_TileMapState::instance.HeightLayer[tile];
                if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                    tileHeight += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(DAT_TileMapState::instance.BuildingLayer[tile]);
                }
                if ((DAT_TileMapState::instance.LogicLayer[tile] & BLOCKING_LOGIC) == 0 && height <= tileHeight + 16
                    && height >= tileHeight - 16 && DAT_TileMapState::instance.PathConnectionLayer[tile] != 0
                    && ++found >= workerIndexPlus1) {
                    this->buildings[buildingID].buildingEntryX
                        = this->buildings[buildingID].x - flag + this->DAT_TempXOffset;
                    this->buildings[buildingID].buildingEntryY
                        = this->buildings[buildingID].y - flag + this->DAT_TempYOffset;
                    return 2;
                }
                ++index;
                if (index >= tileCount) {
                    index = 0;
                }
            }
            return 0;
        }

    }
}
}
