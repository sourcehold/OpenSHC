#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C570
        void BuildingsState::applyGateOrDrawbridgeOpenCloseChange(int buildingID, BOOLEnum open, BOOLEnum setTimer)
        {
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_DRAWBRIDGE) {
                int gateID = MACRO_CALL_MEMBER(BuildingsState_Func::findParticularBuilding, DAT_BuildingsState::ptr)(
                    DAT_BuildingsState::instance.buildings[buildingID].owner,
                    DAT_BuildingsState::instance.buildings[buildingID].x,
                    DAT_BuildingsState::instance.buildings[buildingID].y,
                    DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, BT_GATEHOUSELARGE, 0);
                if (gateID == 0) {
                    gateID = MACRO_CALL_MEMBER(BuildingsState_Func::findParticularBuilding, DAT_BuildingsState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].owner,
                        DAT_BuildingsState::instance.buildings[buildingID].x,
                        DAT_BuildingsState::instance.buildings[buildingID].y,
                        DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, BT_GATEHOUSESMALL, 0);
                    if (gateID == 0) {
                        return;
                    }
                }
                if (open != FALSE) {
                    if (DAT_BuildingsState::instance.buildings[gateID].pathLinkageRelated2 != 2) {
                        return;
                    }
                    if (setTimer != FALSE) {
                        DAT_BuildingsState::instance.buildings[gateID].gateCloseOpenTimer = 600;
                    }
                    DAT_BuildingsState::instance.buildings[gateID].gateState = 11;
                } else {
                    if (DAT_BuildingsState::instance.buildings[gateID].pathLinkageRelated2 != 0) {
                        return;
                    }
                    if (setTimer != FALSE) {
                        DAT_BuildingsState::instance.buildings[gateID].gateCloseOpenTimer = -1;
                    }
                    DAT_BuildingsState::instance.buildings[gateID].gateState = 10;
                }
                return;
            }
            int drawbridgeID = MACRO_CALL_MEMBER(BuildingsState_Func::findParticularBuilding, DAT_BuildingsState::ptr)(
                DAT_BuildingsState::instance.buildings[buildingID].owner,
                DAT_BuildingsState::instance.buildings[buildingID].x,
                DAT_BuildingsState::instance.buildings[buildingID].y,
                DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, BT_DRAWBRIDGE, 0);
            int nextDrawbridgeID = MACRO_CALL_MEMBER(BuildingsState_Func::findParticularBuilding,
                DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                DAT_BuildingsState::instance.buildings[buildingID].x,
                DAT_BuildingsState::instance.buildings[buildingID].y,
                DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, BT_DRAWBRIDGE, drawbridgeID);
            while (drawbridgeID != 0) {
                if (open == FALSE) {
                    if (DAT_BuildingsState::instance.buildings[drawbridgeID].drawBridgeState1 == 0) {
                        DAT_BuildingsState::instance.buildings[drawbridgeID].drawbridgeState2 = 10;
                    }
                } else if (DAT_BuildingsState::instance.buildings[drawbridgeID].drawBridgeState1 == 2) {
                    DAT_BuildingsState::instance.buildings[drawbridgeID].drawbridgeState2 = 11;
                }
                drawbridgeID = nextDrawbridgeID;
                nextDrawbridgeID = 0;
            }
        }

    }
}
}
