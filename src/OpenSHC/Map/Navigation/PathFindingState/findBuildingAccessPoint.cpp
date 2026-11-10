#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Navigation::Algorithms::XYPair;

        /*
          Finds where a unit should stand to work on a building. Every perimeter tile of the building whose height is
          within 32 of the building's foundation and within 16 of its terrain height, and that the unit's area can
          reach, is a candidate; the one closest to the unit wins. pResultTile receives the building tile next to
          it. Returns the access tile, or 0 if there is none.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A8860
        int PathFindingState::findBuildingAccessPoint(int unitID, int buildingID, int* pResultTile)
        {
            int const buildingY = DAT_BuildingsState::instance.buildings[buildingID].y;
            int const buildingX = DAT_BuildingsState::instance.buildings[buildingID].x;
            int const foundationHeight
                = DAT_TileMapState::instance.DefaultHeightLayer[DAT_BuildingsState::instance.buildings[buildingID]
                        .currentTilePositionAdjusted];
            int const unitArea
                = (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            int const unitOwner = DAT_UnitsState::instance.units[unitID].owner;
            uint const buildingSize = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
            int const accessibleTilesCount
                = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
            int validCount = 0;
            int accessibleIndex = 0;
            // pairs of access tile and the building tile next to it
            int accessPoints[200][2];
            for (int remaining = accessibleTilesCount; remaining > 0; --remaining) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset,
                    DAT_BuildingsState::ptr)(buildingSize, 1, accessibleIndex, 0);
                int const yOffset = DAT_BuildingsState::instance.DAT_TempYOffset;
                int const accessTile
                    = DAT_ViewportRenderState::instance.translationMatrix[buildingY + yOffset].addXgetTile
                    + DAT_BuildingsState::instance.DAT_TempXOffset + buildingX;
                int const height = DAT_TileMapState::instance.HeightLayer[accessTile];
                if (abs(foundationHeight - height) < 32
                    && ((short)DAT_TileMapState::instance.PathConnectionLayer[accessTile] == unitArea
                        || MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                 calculateCanPlayerUnitsNavigateToAreaFromArea,
                               DAT_PathFindingState::ptr)(unitOwner, unitArea,
                               (short)DAT_TileMapState::instance.PathConnectionLayer[accessTile], 0)
                            != 0)
                    && abs(DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk - height) < 16) {
                    accessPoints[validCount][0] = accessTile;
                    accessPoints[validCount][1] = 0;
                    for (int i = 0; i < 4; ++i) {
                        int const buildingTile
                            = DAT_ViewportRenderState::instance
                                  .translationMatrix
                                      [DAT_ClimbLogicDefinedData::instance.CardinalHorizontalFirstSearchOrder[i].y
                                          + yOffset + buildingY]
                                  .addXgetTile
                            + DAT_ClimbLogicDefinedData::instance.CardinalHorizontalFirstSearchOrder[i].x
                            + DAT_BuildingsState::instance.DAT_TempXOffset + buildingX;
                        if (DAT_TileMapState::instance.BuildingLayer[buildingTile] == buildingID) {
                            accessPoints[validCount][1] = buildingTile;
                            break;
                        }
                    }
                    validCount = validCount + 1;
                }
                accessibleIndex = accessibleIndex + 1;
                if (accessibleIndex >= accessibleTilesCount) {
                    accessibleIndex = 0;
                }
            }
            int closest = -1;
            *pResultTile = 0;
            int closestDistance = 10000;
            for (int i = 0; i < validCount; ++i) {
                int const accessTile = accessPoints[i][0];
                int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[accessTile];
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                    DAT_UnitsState::instance.units[unitID].y,
                    accessTile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile, y);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < closestDistance) {
                    closestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    closest = i;
                }
            }
            if (closest == -1) {
                return 0;
            }
            *pResultTile = accessPoints[closest][1];
            return accessPoints[closest][0];
        }

    }
}
}
