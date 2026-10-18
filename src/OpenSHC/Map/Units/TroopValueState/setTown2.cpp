#include "OpenSHC/Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519F50
        void TroopValueState::setTown2(int param_1, int playerID)
        {
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town3 = 0;
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2) {
                for (; i < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2; i = i + 1) {
                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].townValuesArray[i].unitID == 0
                        || param_1) {
                        DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town3
                            = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town3 + 1;
                    }
                }
            }
        }

    }
}
}
