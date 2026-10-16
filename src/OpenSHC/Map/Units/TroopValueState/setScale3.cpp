#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519DE0
        void TroopValueState::setScale3(int one, int playerID)
        {
            int iVar1;
            int* piVar2;
            int _counter;
            int* _ptrScale3;
            int _scale2;
            iVar1 = playerID * 0x177bc;
            _counter = 0;
            _scale2 = *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + iVar1 + -8);
            *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + iVar1 + -4) = 0;
            if (0 < _scale2) {
                piVar2 = (int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + iVar1 + 0xc);
                do {
                    if ((piVar2[-1] < 5999) && ((*piVar2 == 0 || (one)))) {
                        _ptrScale3
                            = (int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + iVar1 + -4);
                        *_ptrScale3 = *_ptrScale3 + 1;
                    }
                    _counter = _counter + 1;
                    piVar2 = piVar2 + 4;
                } while (
                    _counter < *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + iVar1 + -8));
            }
        }

    }
}
}
