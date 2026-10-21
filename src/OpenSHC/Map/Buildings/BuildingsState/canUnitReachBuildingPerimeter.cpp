#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

#include <stdlib.h>

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00410440
        undefined4 BuildingsState::canUnitReachBuildingPerimeter(int buildingID, int unitID)
        {
            if (buildingID == 0 || buildingID >= 2000) {
                return 0;
            }
            int const unitArea
                = (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            int const buildingHeight
                = DAT_TileMapState::instance.DefaultHeightLayer[DAT_BuildingsState::instance.buildings[buildingID]
                        .currentTilePositionAdjusted];
            int const size = this->buildings[buildingID].widthOrHeight;
            int const tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
            int onlyAssassins = 0;
            if (MACRO_CALL_MEMBER(Units::UnitsState_Func::selectionContainsOnlyArabAssassins, DAT_UnitsState::ptr)()
                != FALSE) {
                onlyAssassins = 1;
            }
            for (int i = 0; i < tileCount; ++i) {
                MACRO_CALL_MEMBER(BuildingsState_Func::setupNextCandidateLocationComputeOffsets2, this)(size, 1, i, 0);
                int const tile = DAT_ViewportRenderState::instance
                                     .translationMatrix[this->buildings[buildingID].y + this->DAT_TempYOffset]
                                     .addXgetTile
                    + this->buildings[buildingID].x + this->DAT_TempXOffset;
                int const area = (short)DAT_TileMapState::instance.PathConnectionLayer[tile];
                int tileHeight = DAT_TileMapState::instance.HeightLayer[tile];
                if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                    tileHeight += MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(DAT_TileMapState::instance.BuildingLayer[tile]);
                }
                if (abs(buildingHeight - tileHeight) >= 16 || area == 0) {
                    continue;
                }
                int reachable;
                if (onlyAssassins == 1) {
                    reachable
                        = MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::calculateCanReachUsingCachedAreaLogic,
                            DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].tile, tile);
                } else {
                    reachable = MACRO_CALL_MEMBER(
                        Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                        DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].owner, unitArea, area,
                        MACRO_CALL_MEMBER(Units::UnitsState_Func::canAUnitClimb, DAT_UnitsState::ptr)());
                }
                if (reachable != 0) {
                    return 1;
                }
            }
            return 0;
        }

    }
}
}
