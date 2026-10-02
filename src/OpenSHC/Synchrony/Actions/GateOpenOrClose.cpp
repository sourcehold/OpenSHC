#include "../../Synchrony.func.hpp"
#include "../Actions.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004654F0
    void Actions::GateOpenOrClose(undefined4 playerID, int buildingID, int newGateState, int buildingUID)
    {
        if (DAT_BuildingsState::instance.buildings[buildingID].uid == buildingUID) {
            DAT_BuildingsState::instance.buildings[buildingID].gateState = (byte)newGateState;
            DAT_BuildingsState::instance.buildings[buildingID].gateState2 = 0;
            if (newGateState == 10) {
                DAT_BuildingsState::instance.buildings[buildingID].gateCloseOpenTimer = -1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    DAT_BuildingsState::ptr)(buildingID, FALSE, FALSE);
            }
            if (newGateState == 0xb) {
                DAT_BuildingsState::instance.buildings[buildingID].gateCloseOpenTimer = 600;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    DAT_BuildingsState::ptr)(buildingID, TRUE, FALSE);
            }
        }
    }

}
}
