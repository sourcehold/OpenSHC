#include "OpenSHC/Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AB10
        void TroopValueState::countAvailableArcherValueSlots(int param_1)
        {
            int _remaining;
            DAT_TroopValueState::instance.attackInfo.arch3 = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.arch2) {
                for (_remaining = 0; _remaining < DAT_TroopValueState::instance.attackInfo.arch2; ++_remaining) {
                    if (DAT_BuildingsState::instance
                                .buildings[DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[_remaining]
                                        .buildingID]
                                .unknownCounterTo10000_0x2b4
                            < 9999
                        && (DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[_remaining].unitID == 0
                            || (param_1))) {
                        DAT_TroopValueState::instance.attackInfo.arch3
                            = DAT_TroopValueState::instance.attackInfo.arch3 + 1;
                    }
                }
            }
        }

    }
}
}
