#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A550
        void TroopValueState::setWide3(BOOLEnum includeAll, int playerID)
        {
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide3 = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wideValuesArray[i].buildingID
                        < 5999
                    && (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wideValuesArray[i].unitID == 0
                        || includeAll)) {
                    ++DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide3;
                }
            }
        }

    }
}
}
