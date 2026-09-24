#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
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

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00410B10
        int BuildingsState::findClosestReachableAlliedBuilding(int param_1)
        {
            // Finds the closest burning building of the team of unit param_1 that the unit can reach
            int unitArea
                = (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[param_1].tile];
            int closest = 0;
            int closestDistance = 1000;
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == 0 || this->buildings[i].logicalState == BLS_REMOVE
                    || DAT_GameState::instance.mapAndTime.playerTeams[this->buildings[i].owner]
                        != DAT_GameState::instance.mapAndTime.playerTeams[DAT_UnitsState::instance.units[param_1].owner]
                    || this->buildings[i].fireDuration == 0) {
                    continue;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[param_1].x,
                    DAT_UnitsState::instance.units[param_1].y, this->buildings[i].buildingEntryX,
                    this->buildings[i].buildingEntryY);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < closestDistance
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                             calculateCanPlayerUnitsNavigateToAreaFromArea,
                           DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[param_1].owner, unitArea,
                           (short)DAT_TileMapState::instance.PathConnectionLayer[this->buildings[i].buildingEntryX
                               + DAT_ViewportRenderState::instance.translationMatrix[this->buildings[i].buildingEntryY]
                                   .addXgetTile],
                           0)
                        != 0) {
                    closestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    closest = i;
                }
            }
            return closest;
        }

    }
}
}
