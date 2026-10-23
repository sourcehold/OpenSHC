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

        // FUNCTION: STRONGHOLDCRUSADER 0x0040AC80
        int BuildingsState::canNavigateToDefensiveBuilding(
            int playerID, int buildingXPosition, int buildingYPosition, int buildingID)
        {
            // Finds the next tower, keep or gatehouse of the player after buildingID that can be reached from the
            // position
            int fromArea = (short)DAT_TileMapState::instance.PathConnectionLayer
                               [DAT_ViewportRenderState::instance.translationMatrix[buildingYPosition].addXgetTile
                                   + buildingXPosition];
            for (int i = 0; i < this->maxBuildingsCount; ++i) {
                ++buildingID;
                if (buildingID >= this->maxBuildingsCount) {
                    buildingID = 1;
                }
                if (this->buildings[buildingID].logicalState != 0
                    && this->buildings[buildingID].logicalState != BLS_REMOVE
                    && this->buildings[buildingID].owner == playerID
                    && (this->buildings[buildingID].buildingType == BT_TOWER1
                        || this->buildings[buildingID].buildingType == BT_TOWER2
                        || this->buildings[buildingID].buildingType == BT_TOWER3
                        || this->buildings[buildingID].buildingType == BT_TOWER4
                        || this->buildings[buildingID].buildingType == BT_TOWER5
                        || this->buildings[buildingID].buildingType == BT_MANORHOUSE
                        || this->buildings[buildingID].buildingType == BT_STONEKEEP
                        || this->buildings[buildingID].buildingType == BT_STRONGHOLD
                        || this->buildings[buildingID].buildingType == BT_KEEPFOUR
                        || this->buildings[buildingID].buildingType == BT_KEEPFIVE
                        || this->buildings[buildingID].buildingType == BT_GATEHOUSELARGE
                        || this->buildings[buildingID].buildingType == BT_GATEHOUSESMALL)
                    && this->buildings[buildingID].someX != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                             calculateCanPlayerUnitsNavigateToAreaFromArea,
                           DAT_PathFindingState::ptr)(this->buildings[buildingID].owner, fromArea,
                           (short)DAT_TileMapState::instance
                               .PathConnectionLayer[DAT_ViewportRenderState::instance
                                                        .translationMatrix[this->buildings[buildingID].someY]
                                                        .addXgetTile
                                   + this->buildings[buildingID].someX],
                           0)
                        != 0) {
                    return buildingID;
                }
            }
            return 0;
        }

    }
}
}
