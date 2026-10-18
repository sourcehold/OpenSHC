#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A550
        void TroopValueState::setWide3(int param_1, int param_2)
        {
            DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].wide3 = 0;
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].wide2) {
                for (; i < DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].wide2; i = i + 1) {
                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].wideValuesArray[i].buildingID
                            < 5999
                        && (DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].wideValuesArray[i].unitID
                                == 0
                            || param_1)) {
                        DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].wide3
                            = DAT_TroopValueState::instance.attackInfo.playerInfo[param_2 - 1].wide3 + 1;
                    }
                }
            }
        }

    }
}
}
