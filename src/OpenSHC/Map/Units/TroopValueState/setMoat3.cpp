#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A720
        void TroopValueState::setMoat3(int checkAgainstNonZero, int playerID)
        {
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat3 = 0;
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2) {
                for (; i < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2; i = i + 1) {
                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moatValuesArray[i].buildingID < 5999
                        && (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moatValuesArray[i].unitID == 0 || checkAgainstNonZero)) {
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat3 = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat3 + 1;
                    }
                }
            }
        }

    }
}
}
