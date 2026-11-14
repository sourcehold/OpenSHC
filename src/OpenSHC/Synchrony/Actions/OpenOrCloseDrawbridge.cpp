#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004653B0
    void Actions::OpenOrCloseDrawbridge(undefined4 param_1, int buildingID, int value, int buildingUID)
    {
        if (DAT_BuildingsState::instance.buildings[buildingID].uid == buildingUID) {
            DAT_BuildingsState::instance.buildings[buildingID].drawbridgeState2 = (byte)value;
            if (value == 10) {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    DAT_BuildingsState::ptr)(buildingID, FALSE, TRUE);
            } else {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    DAT_BuildingsState::ptr)(buildingID, TRUE, TRUE);
            }
        }
    }

}
}
