#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B240
        int TroopValueState::getSiegeIndexForTile(int tile)
        {
            int _firstFree = 0;
            DAT_TroopValueState::instance.attackInfo.tentPointsNext = 0;
            for (int i = 1; i < 2000; i = i + 1) {
                if (DAT_TroopValueState::instance.attackInfo.tentPointsValues[i].tile == tile) {
                    return i;
                }
                if (DAT_TroopValueState::instance.attackInfo.tentPointsValues[i].tile == 0
                    && !DAT_TroopValueState::instance.attackInfo.tentPointsNext) {
                    DAT_TroopValueState::instance.attackInfo.tentPointsNext = i;
                }
            }
            return 0;
        }

    }
}
}
