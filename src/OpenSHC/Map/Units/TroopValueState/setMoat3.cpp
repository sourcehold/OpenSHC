#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A720
        void TroopValueState::setMoat3(int checkAgainstNonZero, int playerID)
        {
            int* piVar1;
            int _offset;
            AttackInfoSubArrayElement2* piVar4;
            int _index;
            int _moat2;
            _offset = playerID * 0x177bc;
            _index = 0;
            _moat2 = *(int*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + _offset + -8);
            *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + _offset + -4) = 0;
            if (0 < _moat2) {
                piVar4 = (AttackInfoSubArrayElement2*)((int)&DAT_TroopValueState::instance.attackInfo.moatValuesArray
                    + _offset + 0xc);
                do {
                    if ((piVar4->size < 5999) && ((!piVar4->unitID || (checkAgainstNonZero)))) {
                        piVar1 = (int*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + _offset + -4);
                        *piVar1 = *piVar1 + 1;
                    }
                    _index = _index + 1;
                    piVar4 = piVar4 + 4;
                } while (
                    _index < *(int*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + _offset + -8));
            }
        }

    }
}
}
