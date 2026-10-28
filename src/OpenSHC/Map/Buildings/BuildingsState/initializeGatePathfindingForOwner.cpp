#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419A30
        void BuildingsState::initializeGatePathfindingForOwner(int param_1)
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].owner == param_1
                    && (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_GATEHOUSELARGE
                        || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_GATEHOUSESMALL)
                    && DAT_BuildingsState::instance.buildings[buildingID].field200_0x2c6 == 0) {
                    DAT_PathFindingState::instance
                        .climbData[DAT_BuildingsState::instance.buildings[buildingID].laddermanDataID]
                        .isRecognizedByPathfinding = 1;
                    DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2 = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].gateState = 11;
                    DAT_BuildingsState::instance.buildings[buildingID].gateCloseOpenTimer = 2500;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                        DAT_PathFindingState::ptr)(buildingID);
                }
            }
        }

    }
}
}
