#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419960
        void BuildingsState::updatePathLinkageTileMap(int param_1)
        {
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != 0
                    && (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_GATEHOUSELARGE
                        || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_GATEHOUSESMALL)) {
                    if (param_1 == 1) {
                        DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated1
                            = (char)DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2;
                        DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2 = 2;
                    } else if (param_1 == 2) {
                        DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated1
                            = (char)DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2;
                        DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2 = 0;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2
                            = (byte)DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated1;
                    }
                    int const climbDataID = DAT_BuildingsState::instance.buildings[buildingID].laddermanDataID;
                    if (DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2 == 2) {
                        DAT_PathFindingState::instance.climbData[climbDataID].isRecognizedByPathfinding = 0;
                    } else {
                        DAT_PathFindingState::instance.climbData[climbDataID].isRecognizedByPathfinding = 1;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                        DAT_PathFindingState::ptr)(buildingID);
                }
            }
        }

    }
}
}
