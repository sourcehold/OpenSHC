#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

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
            // Returns 2 if a gate is locked, 1 if accessible from (x, y) and 0 otherwise
            if (buildingID <= 0) {
                return 0;
            }

            int fromArea
                = (short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
            int buildingHeight
                = DAT_TileMapState::instance.HeightLayer[DAT_ViewportRenderState::instance
                                                             .translationMatrix[(short)this->buildings[buildingID].y]
                                                             .addXgetTile
                    + (short)this->buildings[buildingID].x];
            int blocked = 0;
            if (this->buildings[buildingID].buildingEntryX == 0 && this->buildings[buildingID].buildingEntryY == 0) {
                blocked = 1;
            } else {
                int entryTile = this->buildings[buildingID].buildingEntryX
                    + DAT_ViewportRenderState::instance.translationMatrix[this->buildings[buildingID].buildingEntryY]
                          .addXgetTile;
                int entryHeight = DAT_TileMapState::instance.HeightLayer[entryTile];
                if (DAT_TileMapState::instance.BuildingLayer[entryTile] != 0) {
                    entryHeight += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)((short)DAT_TileMapState::instance.BuildingLayer[entryTile]);
                }
                if (buildingHeight > entryHeight + 16) {
                    blocked = 1;
                }
                if (entryHeight > buildingHeight + 16) {
                    blocked = 1;
                }
                if ((DAT_TileMapState::instance.LogicLayer[entryTile] & 0x50501481) != 0) {
                    blocked = 1;
                }
                if (fromArea != 0 && (short)DAT_TileMapState::instance.PathConnectionLayer[entryTile] != fromArea
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                             calculateCanPlayerUnitsNavigateToAreaFromArea,
                           DAT_PathFindingState::ptr)(this->buildings[buildingID].owner, fromArea,
                           (short)DAT_TileMapState::instance.PathConnectionLayer[entryTile], 0)
                        == 0) {
                    blocked = 1;
                }
            }

            char result = 1;
            this->buildings[buildingID].hasAccessToKeep = 1;
            if (blocked != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry, this)(
                    buildingID, 0);
                int found = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromCustomArea, this)(
                    buildingID, param_2, 0, x, y);
                if (found == 0) {
                    this->buildings[buildingID].hasAccessToKeep = 0;
                    return 0;
                }
                result = found == 2 ? 2 : 1;
            }
            return result;
        }

    }
}
}
