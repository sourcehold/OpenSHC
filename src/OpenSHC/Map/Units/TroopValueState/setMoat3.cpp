#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A720
        void TroopValueState::setMoat3(BOOLEnum includeAll, int playerID)
        {
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat3 = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moatValuesArray[i].buildingID
                        < 5999
                    && (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moatValuesArray[i].unitID == 0
                        || includeAll)) {
                    ++DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat3;
                }
            }
        }

    }
}
}
