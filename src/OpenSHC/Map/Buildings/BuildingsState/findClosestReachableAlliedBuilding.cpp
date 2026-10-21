#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00410B10
        int BuildingsState::findClosestReachableAlliedBuilding(int unitID)
        {
            int closestBuildingID = 0;
            int closestDistance = 1000;
            int const fromArea
                = (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState == 0
                    || this->buildings[buildingID].logicalState == BLS_REMOVE) {
                    continue;
                }
                if (DAT_GameState::instance.mapAndTime.playerTeams[this->buildings[buildingID].owner]
                    != DAT_GameState::instance.mapAndTime.playerTeams[DAT_UnitsState::instance.units[unitID].owner]) {
                    continue;
                }
                if (this->buildings[buildingID].fireDuration == 0) {
                    continue;
                }
                MACRO_CALL_MEMBER(Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                    DAT_UnitsState::instance.units[unitID].y, this->buildings[buildingID].buildingEntryX,
                    this->buildings[buildingID].buildingEntryY);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh >= closestDistance) {
                    continue;
                }
                int const toArea
                    = (short)DAT_TileMapState::instance
                          .PathConnectionLayer[DAT_ViewportRenderState::instance
                                                   .translationMatrix[this->buildings[buildingID].buildingEntryY]
                                                   .addXgetTile
                              + this->buildings[buildingID].buildingEntryX];
                if (MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                        DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].owner, fromArea, toArea, 0)
                    != 0) {
                    closestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    closestBuildingID = buildingID;
                }
            }
            if (closestBuildingID != 0) {
                return closestBuildingID;
            }
            return 0;
        }

    }
}
}
