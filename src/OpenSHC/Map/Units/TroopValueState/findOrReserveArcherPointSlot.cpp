#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AF20
        int TroopValueState::findOrReserveArcherPointSlot(int param_1)
        {
            DAT_TroopValueState::instance.attackInfo.archerPointsNext = 0;
            for (int i = 1; i < 200; i = i + 1) {
                if (DAT_TroopValueState::instance.attackInfo.archerPointArray[i].tile == param_1) {
                    return i;
                }
                if (DAT_TroopValueState::instance.attackInfo.archerPointArray[i].tile == 0
                    && !DAT_TroopValueState::instance.attackInfo.archerPointsNext) {
                    DAT_TroopValueState::instance.attackInfo.archerPointsNext = i;
                }
            }
            return 0;
        }

    }
}
}
