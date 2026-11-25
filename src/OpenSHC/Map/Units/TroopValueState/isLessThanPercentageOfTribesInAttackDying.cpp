#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00518BB0
        BOOLEnum TroopValueState::isLessThanPercentageOfTribesInAttackDying(int attackID, int leDyingPerc)
        {
            int dying = 0;
            int living = 0;
            for (int tribeID = 1; tribeID < countof(DAT_TribesState::instance.tribes); ++tribeID) {
                if (!DAT_TribesState::instance.tribes[tribeID].tribeState
                    || DAT_TribesState::instance.tribes[tribeID].tribeState == 3
                    || DAT_GameSynchronyState::instance
                            .currentPlayerFullIDArray[DAT_TribesState::instance.tribes[tribeID].owner]
                        != -1
                    || DAT_TribesState::instance.tribes[tribeID].attackWave != attackID) {
                    continue;
                }
                int const aliveStatus = MACRO_CALL_MEMBER(
                    Map::Units::TribesState_Func::getTribeAliveStatus, DAT_TribesState::ptr)(tribeID);
                if (aliveStatus < 50) {
                    ++living;
                } else {
                    ++dying;
                }
            }
            int dyingPercentage;
            if (dying + living == 0) {
                dyingPercentage = 100;
            } else {
                dyingPercentage = (dying * 100) / (dying + living);
            }
            return dyingPercentage >= leDyingPerc;
        }

    }
}
}
