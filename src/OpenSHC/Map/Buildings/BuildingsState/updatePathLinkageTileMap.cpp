#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00419960
        void BuildingsState::updatePathLinkageTileMap(int param_1)
        {
            // Matching note: After the if/else the original reloads pathLinkageRelated2 from memory before
            // comparing it with 2; our compiler forwards the stored constants and reorders the blocks. No source
            // form was found that prevents the store forwarding.
            // param_1: 1 = open all gatehouses, 2 = close all gatehouses, otherwise restore the previous state
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (DAT_BuildingsState::instance.buildings[i].logicalState == 0
                    || (DAT_BuildingsState::instance.buildings[i].buildingType != BT_GATEHOUSELARGE
                        && DAT_BuildingsState::instance.buildings[i].buildingType != BT_GATEHOUSESMALL)) {
                    continue;
                }
                if (param_1 == 1) {
                    DAT_BuildingsState::instance.buildings[i].pathLinkageRelated1
                        = (char)DAT_BuildingsState::instance.buildings[i].pathLinkageRelated2;
                    DAT_BuildingsState::instance.buildings[i].pathLinkageRelated2 = 2;
                } else if (param_1 == 2) {
                    DAT_BuildingsState::instance.buildings[i].pathLinkageRelated1
                        = (char)DAT_BuildingsState::instance.buildings[i].pathLinkageRelated2;
                    DAT_BuildingsState::instance.buildings[i].pathLinkageRelated2 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[i].pathLinkageRelated2
                        = (byte)DAT_BuildingsState::instance.buildings[i].pathLinkageRelated1;
                }
                if (DAT_BuildingsState::instance.buildings[i].pathLinkageRelated2 == 2) {
                    DAT_PathFindingState::instance.climbData[DAT_BuildingsState::instance.buildings[i].laddermanDataID]
                        .isRecognizedByPathfinding = 0;
                } else {
                    DAT_PathFindingState::instance.climbData[DAT_BuildingsState::instance.buildings[i].laddermanDataID]
                        .isRecognizedByPathfinding = 1;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                    DAT_PathFindingState::ptr)(i);
            }
        }

    }
}
}
