#include "OpenSHC/Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A9A0
        void TroopValueState::countAvailableHighValueSlots(int param_1)
        {
            int _remaining;
            DAT_TroopValueState::instance.attackInfo.high3 = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.high2) {
                for (_remaining = 0; _remaining < DAT_TroopValueState::instance.attackInfo.high2; ++_remaining) {
                    if (DAT_BuildingsState::instance
                                .buildings[DAT_TroopValueState::instance.attackInfo.high2ValuesArray[_remaining]
                                        .buildingID]
                                .unknownCounterTo10000_0x2b4
                            < 9999
                        && (DAT_TroopValueState::instance.attackInfo.high2ValuesArray[_remaining].unitID == 0
                            || (param_1))) {
                        DAT_TroopValueState::instance.attackInfo.high3
                            = DAT_TroopValueState::instance.attackInfo.high3 + 1;
                    }
                }
            }
        }

    }
}
}
