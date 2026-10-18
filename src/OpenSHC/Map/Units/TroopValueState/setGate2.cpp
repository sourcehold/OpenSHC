#include "OpenSHC/Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A2D0
        void TroopValueState::setGate2(int param_1, int param_2)
        {
            DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].gate2 = 0;
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].some1000ArrayIndex_2) {
                for (; i < DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].some1000ArrayIndex_2;
                    i = i + 1) {
                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].gateValuesArray[i].buildingID
                            < 5999
                        && (DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].gateValuesArray[i].unitID
                                == 0
                            || param_1)) {
                        DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].gate2
                            = DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].gate2 + 1;
                    }
                }
            }
        }

    }
}
}
