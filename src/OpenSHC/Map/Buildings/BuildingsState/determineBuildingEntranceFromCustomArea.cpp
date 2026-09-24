#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041B2B0
        undefined4 BuildingsState::determineBuildingEntranceFromCustomArea(
            int buildingID, int param_2, int param_3, int x, int y)
        {
            // Finds an entrance tile of the building that can be reached from the tile (x, y).
            // param_3 enlarges the area around the building by one tile, param_2 - 1 matching tiles are skipped.
            // Returns 1 if an entrance was found, 2 if only an unreachable one (e.g. behind a locked gate) and 0
            // otherwise.
            int playerID = this->buildings[buildingID].owner;
            int index = 0;
            int areaFrom
                = (short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
            int found = 0;
            int heightStep = 16;
            if (this->buildings[buildingID].buildingType == BT_QUARRY) {
                heightStep = 32;
            }
            int size = this->buildings[buildingID].widthOrHeight + param_3 * 2;
            int tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
            if (tileCount > 0) {
                index = this->buildings[buildingID].entranceAttemptTileIndex % tileCount;
                this->buildings[buildingID].entranceAttemptTileIndex = index;
            }
            int height = this->buildings[buildingID].terrainHeightUnk;
            this->buildings[buildingID].buildingEntryX = 0;
            this->buildings[buildingID].buildingEntryY = 0;

            // Tiles next to the building
            for (int tries = 0; tries < tileCount; ++tries) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(
                    size, 1, index, 0);
                int tile
                    = DAT_ViewportRenderState::instance
                          .translationMatrix[(short)this->buildings[buildingID].y - param_3 + this->DAT_TempYOffset]
                          .addXgetTile
                    + (short)this->buildings[buildingID].x - param_3 + this->DAT_TempXOffset;
                int tileHeight = DAT_TileMapState::instance.HeightLayer[tile];
                if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                    tileHeight += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)((short)DAT_TileMapState::instance.BuildingLayer[tile]);
                }
                if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x50501481) == 0 && height <= tileHeight + heightStep
                    && tileHeight - heightStep <= height
                    && (areaFrom == 0 || (short)DAT_TileMapState::instance.PathConnectionLayer[tile] == areaFrom
                        || MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                 calculateCanPlayerUnitsNavigateToAreaFromArea,
                               DAT_PathFindingState::ptr)(
                               playerID, areaFrom, (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                            != 0)
                    && ++found >= param_2) {
                    this->buildings[buildingID].buildingEntryX
                        = this->DAT_TempXOffset - param_3 + this->buildings[buildingID].x;
                    this->buildings[buildingID].buildingEntryY
                        = this->buildings[buildingID].y - param_3 + this->DAT_TempYOffset;
                    return 1;
                }
                ++index;
                if (index >= tileCount) {
                    index = 0;
                }
            }

            // Tiles one step further away
            int largerTileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCountForOneLarger[size];
            for (int tries = 0; tries < largerTileCount; ++tries) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::setupNextCandidateLocationComputeOffsets2, this)(
                    size, 1, index, 0);
                int tile
                    = DAT_ViewportRenderState::instance
                          .translationMatrix[(short)this->buildings[buildingID].y - param_3 + this->DAT_TempYOffset]
                          .addXgetTile
                    + (short)this->buildings[buildingID].x - param_3 + this->DAT_TempXOffset;
                int tileHeight = DAT_TileMapState::instance.HeightLayer[tile];
                if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                    tileHeight += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)((short)DAT_TileMapState::instance.BuildingLayer[tile]);
                }
                if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x50501481) == 0 && height <= tileHeight + 16
                    && tileHeight - 16 <= height
                    && (areaFrom == 0 || (short)DAT_TileMapState::instance.PathConnectionLayer[tile] == areaFrom
                        || MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                 calculateCanPlayerUnitsNavigateToAreaFromArea,
                               DAT_PathFindingState::ptr)(
                               playerID, areaFrom, (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                            != 0
                        || DAT_BuildingDefinedData::instance
                                .ABuildingTypeValueArray[this->buildings[buildingID].buildingType]
                            != FALSE)
                    && ++found >= param_2) {
                    this->buildings[buildingID].buildingEntryX
                        = this->DAT_TempXOffset - param_3 + this->buildings[buildingID].x;
                    this->buildings[buildingID].buildingEntryY
                        = this->buildings[buildingID].y - param_3 + this->DAT_TempYOffset;
                    return 1;
                }
                ++index;
                if (index >= largerTileCount) {
                    index = 0;
                }
            }

            // Accept any walkable tile next to the building
            tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
            if (tileCount <= 0) {
                index = 0;
            } else {
                index = this->buildings[buildingID].entranceAttemptTileIndex % tileCount;
                this->buildings[buildingID].entranceAttemptTileIndex = index;
            }
            for (int tries = 0; tries < tileCount; ++tries) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(
                    size, 1, index, 0);
                int tile
                    = DAT_ViewportRenderState::instance
                          .translationMatrix[(short)this->buildings[buildingID].y - param_3 + this->DAT_TempYOffset]
                          .addXgetTile
                    + (short)this->buildings[buildingID].x - param_3 + this->DAT_TempXOffset;
                int tileHeight = DAT_TileMapState::instance.HeightLayer[tile];
                if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                    tileHeight += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)((short)DAT_TileMapState::instance.BuildingLayer[tile]);
                }
                if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x50501481) == 0 && height <= tileHeight + 16
                    && tileHeight - 16 <= height && DAT_TileMapState::instance.PathConnectionLayer[tile] != 0
                    && ++found >= param_2) {
                    this->buildings[buildingID].buildingEntryX
                        = this->DAT_TempXOffset - param_3 + this->buildings[buildingID].x;
                    this->buildings[buildingID].buildingEntryY
                        = this->buildings[buildingID].y - param_3 + this->DAT_TempYOffset;
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
