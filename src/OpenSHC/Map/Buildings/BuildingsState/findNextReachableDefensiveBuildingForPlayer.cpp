#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040ADB0
        int BuildingsState::findNextReachableDefensiveBuildingForPlayer(
            int param_1, int param_2, int param_3, int param_4)
        {
            // Finds the next tower, keep, gatehouse or shrine of player param_1 after building param_4 that can be
            // reached from (param_2, param_3)
            int fromArea
                = (short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[param_3].addXgetTile
                          + param_2];
            for (int i = 0; i < this->maxBuildingsCount; ++i) {
                ++param_4;
                if (param_4 >= this->maxBuildingsCount) {
                    param_4 = 1;
                }
                if (this->buildings[param_4].logicalState != 0 && this->buildings[param_4].logicalState != BLS_REMOVE
                    && this->buildings[param_4].owner == param_1
                    && (this->buildings[param_4].buildingType == BT_TOWER1
                        || this->buildings[param_4].buildingType == BT_TOWER2
                        || this->buildings[param_4].buildingType == BT_TOWER3
                        || this->buildings[param_4].buildingType == BT_TOWER4
                        || this->buildings[param_4].buildingType == BT_TOWER5
                        || this->buildings[param_4].buildingType == BT_MANORHOUSE
                        || this->buildings[param_4].buildingType == BT_STONEKEEP
                        || this->buildings[param_4].buildingType == BT_STRONGHOLD
                        || this->buildings[param_4].buildingType == BT_KEEPFOUR
                        || this->buildings[param_4].buildingType == BT_KEEPFIVE
                        || this->buildings[param_4].buildingType == BT_GATEHOUSELARGE
                        || this->buildings[param_4].buildingType == BT_GATEHOUSESMALL
                        || this->buildings[param_4].buildingType == BT_SHRINE)
                    && this->buildings[param_4].someX != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                             calculateCanPlayerUnitsNavigateToAreaFromArea,
                           DAT_PathFindingState::ptr)(this->buildings[param_4].owner, fromArea,
                           (short)DAT_TileMapState::instance
                               .PathConnectionLayer[DAT_ViewportRenderState::instance
                                                        .translationMatrix[this->buildings[param_4].someY]
                                                        .addXgetTile
                                   + this->buildings[param_4].someX],
                           0)
                        != 0) {
                    return param_4;
                }
            }
            return 0;
        }

    }
}
}
