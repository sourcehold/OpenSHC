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

        // FUNCTION: STRONGHOLDCRUSADER 0x00419C70
        void BuildingsState::updatePathLinkageForGatesKeepsSiegeTowers()
        {
            if ((int)this->pathLinkageKeepWasUpdatedUnk < 1) {
                return;
            }
            ++this->counter;
            this->pathLinkageKeepWasUpdatedUnk = 0;
            for (int i = 1; i < 2000; ++i) {
                if (DAT_BuildingsState::instance.buildings[i].logicalState == 0
                    || DAT_BuildingsState::instance.buildings[i].logicalState == BLS_REMOVE) {
                    continue;
                }
                if (DAT_BuildingsState::instance.buildings[i].buildingType == BT_GATEHOUSELARGE) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                        DAT_PathFindingState::ptr)(i);
                } else if (DAT_BuildingsState::instance.buildings[i].buildingType == BT_GATEHOUSESMALL) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                        DAT_PathFindingState::ptr)(i);
                } else if (DAT_BuildingsState::instance.buildings[i].buildingType == BT_WOODGATE1) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                        DAT_PathFindingState::ptr)(i);
                } else if (DAT_BuildingsState::instance.buildings[i].buildingType == BT_STONEKEEP) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps,
                        DAT_PathFindingState::ptr)(i);
                } else if (DAT_BuildingsState::instance.buildings[i].buildingType == BT_STRONGHOLD) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps,
                        DAT_PathFindingState::ptr)(i);
                } else if (DAT_BuildingsState::instance.buildings[i].buildingType == BT_KEEPFOUR) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps,
                        DAT_PathFindingState::ptr)(i);
                } else if (DAT_BuildingsState::instance.buildings[i].buildingType == BT_KEEPFIVE) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps,
                        DAT_PathFindingState::ptr)(i);
                } else if (DAT_BuildingsState::instance.buildings[i].buildingType == BT_SIEGETOWER_PLACED) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToSiegeTower,
                        DAT_PathFindingState::ptr)(i);
                }
            }
        }

    }
}
}
