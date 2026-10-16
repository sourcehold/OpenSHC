#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B240
        int TroopValueState::getSiegeIndexForTile(int tile)
        {
            int _index;
            AttackInfoSubArrayElement3* piVar1;
            int _index2;
            _index2 = 0;
            DAT_TroopValueState::instance.attackInfo.tentPointsNext = 0;
            _index = 1;
            piVar1 = &DAT_TroopValueState::instance.attackInfo.tentPointsValues[1];
            do {
                if (piVar1->tile == tile) {
                    return _index;
                }
                if ((!piVar1->tile) && (!_index2)) {
                    _index2 = _index;
                    DAT_TroopValueState::instance.attackInfo.tentPointsNext = _index;
                }
                piVar1 = piVar1 + 8;
                _index = _index + 1;
            } while ((int)piVar1 < 0x17a52ac);
            return 0;
        }

    }
}
}
