#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B240
        int TroopValueState::getSiegeIndexForTile(int tile)
        {
            int _firstFree = 0;
            DAT_TroopValueState::instance.attackInfo.tentPointsNext = 0;
            for (int i = 1; i < 2001; i = i + 1) {
                if (DAT_TroopValueState::instance.attackInfo.tentPointsValues[i].tile == tile) {
                    return i;
                }
                if (DAT_TroopValueState::instance.attackInfo.tentPointsValues[i].tile == 0 && !_firstFree) {
                    _firstFree = i;
                    DAT_TroopValueState::instance.attackInfo.tentPointsNext = _firstFree;
                }
            }
            return 0;
        }

    }
}
}
