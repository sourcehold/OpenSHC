#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004654F0
    void Actions::GateOpenOrClose(undefined4 playerID, int buildingID, int newGateState, int buildingUID)
    {
        if (DAT_BuildingsState::instance.buildings[buildingID].uid == buildingUID) {
            DAT_BuildingsState::instance.buildings[buildingID].gateState = (byte)newGateState;
            DAT_BuildingsState::instance.buildings[buildingID].gateState2 = 0;
            if (newGateState == 10) {
                DAT_BuildingsState::instance.buildings[buildingID].gateCloseOpenTimer = -1;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    DAT_BuildingsState::ptr)(buildingID, FALSE, FALSE);
            } else if (newGateState == 11) {
                DAT_BuildingsState::instance.buildings[buildingID].gateCloseOpenTimer = 600;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    DAT_BuildingsState::ptr)(buildingID, TRUE, FALSE);
            }
        }
    }

}
}
