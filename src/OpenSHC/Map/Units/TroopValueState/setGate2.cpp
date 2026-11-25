#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A2D0
        void TroopValueState::setGate2(BOOLEnum includeAll, int playerID)
        {
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gate2 = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex_2;
                ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gateValuesArray[i].buildingID
                        < 5999
                    && (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gateValuesArray[i].unitID == 0
                        || includeAll)) {
                    ++DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gate2;
                }
            }
        }

    }
}
}
