#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B0C0
        int TroopValueState::getSupportPointIndex(int tile)
        {
            DAT_TroopValueState::instance.attackInfo.supportPointsNext = 0;
            for (int i = 1; i < countof(DAT_TroopValueState::instance.attackInfo.supportPointsArray) - 1; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.supportPointsArray[i].tile == tile) {
                    return i;
                }
                if (DAT_TroopValueState::instance.attackInfo.supportPointsArray[i].tile == 0
                    && !DAT_TroopValueState::instance.attackInfo.supportPointsNext) {
                    DAT_TroopValueState::instance.attackInfo.supportPointsNext = i;
                }
            }
            return 0;
        }

    }
}
}
