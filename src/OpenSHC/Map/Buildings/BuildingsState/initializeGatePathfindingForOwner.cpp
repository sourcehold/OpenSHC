#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00419A30
        void BuildingsState::initializeGatePathfindingForOwner(int param_1)
        {
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != 0 && this->buildings[i].owner == param_1
                    && (this->buildings[i].buildingType == BT_GATEHOUSELARGE
                        || this->buildings[i].buildingType == BT_GATEHOUSESMALL)
                    && this->buildings[i].field244_0x2c6 == 0) {
                    DAT_PathFindingState::instance.climbData[this->buildings[i].laddermanDataID]
                        .isRecognizedByPathfinding = 1;
                    this->buildings[i].pathLinkageRelated2 = 0;
                    this->buildings[i].gateState = 11;
                    this->buildings[i].gateCloseOpenTimer = 2500;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                        DAT_PathFindingState::ptr)(i);
                }
            }
        }

    }
}
}
