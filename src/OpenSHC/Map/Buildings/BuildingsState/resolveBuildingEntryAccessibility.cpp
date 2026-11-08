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
        int BuildingsState::resolveBuildingEntryAccessibility(int buildingID, int param_2, int x, int y)
        {
            // Returns 2 if a gate is locked, 1 if accessible from (x, y) and 0 otherwise.
            // param_2 - 1 matching entrance tiles are skipped when a new entrance is searched.
            if (buildingID <= 0) {
                return 0;
            }
            // Matching note: the reference, the playerID local and the order of the lookups below are load-bearing
            Building& b = this->buildings[buildingID];
            int const playerID = b.owner;
            int const fromArea
                = DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
            int const buildingHeight
                = DAT_TileMapState::instance
                      .HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[b.y].addXgetTile + b.x];
            BOOLEnum blocked = FALSE;
            if (b.buildingEntryX == 0 && b.buildingEntryY == 0) {
                blocked = TRUE;
            } else {
                int const entryTile = b.buildingEntryX
                    + DAT_ViewportRenderState::instance.translationMatrix[b.buildingEntryY].addXgetTile;
                int entryHeight = DAT_TileMapState::instance.HeightLayer[entryTile];
                if (DAT_TileMapState::instance.BuildingLayer[entryTile] != 0) {
                    entryHeight += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(DAT_TileMapState::instance.BuildingLayer[entryTile]);
                }
                if (buildingHeight > entryHeight + 16) {
                    blocked = TRUE;
                }
                if (entryHeight > buildingHeight + 16) {
                    blocked = TRUE;
                }
                if ((DAT_TileMapState::instance.LogicLayer[entryTile]
                        & (LogicHelpers::L_SEA | LogicHelpers::L_ROCKY | LogicHelpers::L_BUILDING | LogicHelpers::L_TREE
                            | LogicHelpers::L_RIVER | LogicHelpers::L_CRENEL_VARIATIONUnk
                            | LogicHelpers::L_KEEP_NON_MANOR_HOUSE | LogicHelpers::L_MOAT))
                    != 0) {
                    blocked = TRUE;
                }
                if (fromArea != 0 && DAT_TileMapState::instance.PathConnectionLayer[entryTile] != fromArea
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                             calculateCanPlayerUnitsNavigateToAreaFromArea,
                           DAT_PathFindingState::ptr)(
                           playerID, fromArea, DAT_TileMapState::instance.PathConnectionLayer[entryTile], 0)
                        == 0) {
                    blocked = TRUE;
                }
            }

            this->buildings[buildingID].hasAccessToKeep = 1;
            if (!blocked) {
                return 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry, this)(
                buildingID, 0);
            int const found = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromCustomArea, this)(
                buildingID, param_2, 0, x, y);
            if (found == 0) {
                this->buildings[buildingID].hasAccessToKeep = 0;
                return 0;
            }
            if (found == 2) {
                return 2;
            }
            return 1;
        }

    }
}
}
