#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519DE0
        void TroopValueState::setScale3(int one, int playerID)
        {
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale3 = 0;
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2) {
                for (; i < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2; i = i + 1) {
                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scaleValuesArray[i].buildingID
                            < 5999
                        && (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scaleValuesArray[i].unitID
                                == 0
                            || one)) {
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale3
                            = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale3 + 1;
                    }
                }
            }
        }

    }
}
}
