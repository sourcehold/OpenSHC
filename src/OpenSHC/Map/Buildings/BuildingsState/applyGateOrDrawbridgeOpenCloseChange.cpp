#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C570
        void BuildingsState::applyGateOrDrawbridgeOpenCloseChange(int buildingID, BOOLEnum param_2, BOOLEnum param_3)
        {
            // param_2 == FALSE opens the gate or drawbridge, otherwise it is closed
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_DRAWBRIDGE) {
                // A drawbridge controls the gatehouse it belongs to
                int gatehouse = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                    DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                    (short)DAT_BuildingsState::instance.buildings[buildingID].x,
                    (short)DAT_BuildingsState::instance.buildings[buildingID].y,
                    DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, BT_GATEHOUSELARGE, 0);
                if (gatehouse == 0) {
                    gatehouse = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                        DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                        (short)DAT_BuildingsState::instance.buildings[buildingID].x,
                        (short)DAT_BuildingsState::instance.buildings[buildingID].y,
                        DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, BT_GATEHOUSESMALL, 0);
                    if (gatehouse == 0) {
                        return;
                    }
                }
                if (param_2 != FALSE) {
                    if (DAT_BuildingsState::instance.buildings[gatehouse].pathLinkageRelated2 != 2) {
                        return;
                    }
                    if (param_3 != FALSE) {
                        DAT_BuildingsState::instance.buildings[gatehouse].gateCloseOpenTimer = 600;
                    }
                    DAT_BuildingsState::instance.buildings[gatehouse].gateState = 11;
                    return;
                }
                if (DAT_BuildingsState::instance.buildings[gatehouse].pathLinkageRelated2 != 0) {
                    return;
                }
                if (param_3 != FALSE) {
                    DAT_BuildingsState::instance.buildings[gatehouse].gateCloseOpenTimer = -1;
                }
                DAT_BuildingsState::instance.buildings[gatehouse].gateState = 10;
                return;
            }

            // A gatehouse controls up to two drawbridges next to it
            int drawbridge = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                (short)DAT_BuildingsState::instance.buildings[buildingID].x,
                (short)DAT_BuildingsState::instance.buildings[buildingID].y,
                DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, BT_DRAWBRIDGE, 0);
            int secondDrawbridge
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findParticularBuilding,
                    DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                    (short)DAT_BuildingsState::instance.buildings[buildingID].x,
                    (short)DAT_BuildingsState::instance.buildings[buildingID].y,
                    DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight, BT_DRAWBRIDGE, drawbridge);
            while (drawbridge != 0) {
                if (param_2 == FALSE) {
                    if (DAT_BuildingsState::instance.buildings[drawbridge].drawBridgeState1 == 0) {
                        DAT_BuildingsState::instance.buildings[drawbridge].drawbridgeState2 = 10;
                    }
                } else if (DAT_BuildingsState::instance.buildings[drawbridge].drawBridgeState1 == 2) {
                    DAT_BuildingsState::instance.buildings[drawbridge].drawbridgeState2 = 11;
                }
                drawbridge = secondDrawbridge;
                secondDrawbridge = 0;
            }
        }

    }
}
}
