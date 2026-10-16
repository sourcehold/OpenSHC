#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B0C0
        int TroopValueState::getSupportPointIndex(int tile)
        {
            int _firstFree = 0;
            DAT_TroopValueState::instance.attackInfo.supportPointsNext = 0;
            for (int i = 1; i < 201; i = i + 1) {
                if (DAT_TroopValueState::instance.attackInfo.supportPointsArray[i].tile == tile) {
                    return i;
                }
                if (DAT_TroopValueState::instance.attackInfo.supportPointsArray[i].tile == 0 && !_firstFree) {
                    _firstFree = i;
                    DAT_TroopValueState::instance.attackInfo.supportPointsNext = _firstFree;
                }
            }
            return 0;
        }

    }
}
}
