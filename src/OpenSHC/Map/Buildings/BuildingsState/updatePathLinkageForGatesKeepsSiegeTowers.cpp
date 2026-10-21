#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419C70
        void BuildingsState::updatePathLinkageForGatesKeepsSiegeTowers()
        {
            if ((int)this->pathLinkageKeepWasUpdatedUnk < 1) {
                return;
            }
            this->counter += 1;
            this->pathLinkageKeepWasUpdatedUnk = 0;
            for (int buildingID = 1; buildingID < 2000; ++buildingID) {
                if (DAT_BuildingsState::instance.buildings[buildingID].logicalState == 0
                    || DAT_BuildingsState::instance.buildings[buildingID].logicalState == BLS_REMOVE) {
                    continue;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_GATEHOUSELARGE) {
                    MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                        DAT_PathFindingState::ptr)(buildingID);
                } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_GATEHOUSESMALL) {
                    MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                        DAT_PathFindingState::ptr)(buildingID);
                } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_WOODGATE1) {
                    MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                        DAT_PathFindingState::ptr)(buildingID);
                } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_STONEKEEP) {
                    MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps,
                        DAT_PathFindingState::ptr)(buildingID);
                } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_STRONGHOLD) {
                    MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps,
                        DAT_PathFindingState::ptr)(buildingID);
                } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_KEEPFOUR) {
                    MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps,
                        DAT_PathFindingState::ptr)(buildingID);
                } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_KEEPFIVE) {
                    MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps,
                        DAT_PathFindingState::ptr)(buildingID);
                } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_SIEGETOWER_PLACED) {
                    MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToSiegeTower,
                        DAT_PathFindingState::ptr)(buildingID);
                }
            }
        }

    }
}
}
