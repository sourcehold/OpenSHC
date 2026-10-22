#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00421BE0
        char BuildingsState::resolveBuildingEntryAccessibility(int buildingID, int param_2, int x, int y)
        {
            if (buildingID <= 0) {
                return 0;
            }
            int const targetArea
                = (short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
            int const buildingHeight
                = DAT_TileMapState::instance.HeightLayer
                      [DAT_ViewportRenderState::instance.translationMatrix[this->buildings[buildingID].y].addXgetTile
                          + this->buildings[buildingID].x];
            int blocked = 0;
            if (this->buildings[buildingID].buildingEntryX == 0 && this->buildings[buildingID].buildingEntryY == 0) {
                blocked = 1;
            } else {
                int const entryTile
                    = DAT_ViewportRenderState::instance.translationMatrix[this->buildings[buildingID].buildingEntryY]
                          .addXgetTile
                    + this->buildings[buildingID].buildingEntryX;
                int entryHeight = DAT_TileMapState::instance.HeightLayer[entryTile];
                if (DAT_TileMapState::instance.BuildingLayer[entryTile] != 0) {
                    entryHeight += MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)((short)DAT_TileMapState::instance.BuildingLayer[entryTile]);
                }
                if (buildingHeight > entryHeight + 16) {
                    blocked = 1;
                }
                if (entryHeight > buildingHeight + 16) {
                    blocked = 1;
                }
                if ((DAT_TileMapState::instance.LogicLayer[entryTile]
                        & (LogicHelpers::L_SEA | LogicHelpers::L_ROCKY | LogicHelpers::L_BUILDING | LogicHelpers::L_TREE
                            | LogicHelpers::L_RIVER | LogicHelpers::L_CRENEL_VARIATIONUnk
                            | LogicHelpers::L_KEEP_NON_MANOR_HOUSE | LogicHelpers::L_MOAT))
                    != 0) {
                    blocked = 1;
                }
                if (targetArea != 0) {
                    int const entryArea = (short)DAT_TileMapState::instance.PathConnectionLayer[entryTile];
                    if (entryArea != targetArea
                        && MACRO_CALL_MEMBER(
                               Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                               DAT_PathFindingState::ptr)(this->buildings[buildingID].owner, targetArea, entryArea, 0)
                            == 0) {
                        blocked = 1;
                    }
                }
            }
            this->buildings[buildingID].hasAccessToKeep = 1;
            if (blocked == 0) {
                return 1;
            }
            MACRO_CALL_MEMBER(BuildingsState_Func::setBuildingInitialEntryTileTry, this)(buildingID, 0);
            int const result = MACRO_CALL_MEMBER(BuildingsState_Func::determineBuildingEntranceFromCustomArea, this)(
                buildingID, param_2, 0, x, y);
            if (result == 0) {
                this->buildings[buildingID].hasAccessToKeep = 0;
                return 0;
            }
            return result == 2 ? 2 : 1;
        }

    }
}
}
