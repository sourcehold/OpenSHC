#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519DE0
        void TroopValueState::setScale3(BOOLEnum includeAll, int playerID)
        {
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale3 = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scaleValuesArray[i].buildingID
                        < 5999
                    && (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scaleValuesArray[i].unitID
                            == 0
                        || includeAll)) {
                    ++DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale3;
                }
            }
        }

    }
}
}
