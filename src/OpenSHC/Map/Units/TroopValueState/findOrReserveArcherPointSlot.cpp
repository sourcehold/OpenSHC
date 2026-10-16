#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AF20
        int TroopValueState::findOrReserveArcherPointSlot(int param_1)
        {
            int _firstFree = 0;
            DAT_TroopValueState::instance.attackInfo.archerPointsNext = 0;
            for (int i = 1; i < 201; i = i + 1) {
                if (DAT_TroopValueState::instance.attackInfo.archerPointArray[i].tile == param_1) {
                    return i;
                }
                if (DAT_TroopValueState::instance.attackInfo.archerPointArray[i].tile == 0 && !_firstFree) {
                    _firstFree = i;
                    DAT_TroopValueState::instance.attackInfo.archerPointsNext = _firstFree;
                }
            }
            return 0;
        }

    }
}
}
