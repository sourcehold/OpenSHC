#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519F50
        void TroopValueState::setTown2(BOOLEnum includeAll, int playerID)
        {
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town3 = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].townValuesArray[i].unitID == 0
                    || includeAll) {
                    ++DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].town3;
                }
            }
        }

    }
}
}
