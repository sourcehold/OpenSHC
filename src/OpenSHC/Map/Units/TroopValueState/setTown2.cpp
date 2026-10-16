#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519F50
        void TroopValueState::setTown2(int param_1, int playerID)
        {
            int iVar1;
            int iVar2;
            int* piVar3;
            int _index;
            int* _ptrTown2;
            iVar1 = playerID * 0x177bc;
            iVar2 = 0;
            _index = *(int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + iVar1 + -8);
            *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + iVar1 + -4) = 0;
            if (0 < _index) {
                piVar3 = (int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + iVar1 + 0xc);
                do {
                    if ((*piVar3 == 0) || (param_1)) {
                        _ptrTown2 = (int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + iVar1 + -4);
                        *_ptrTown2 = *_ptrTown2 + 1;
                    }
                    iVar2 = iVar2 + 1;
                    piVar3 = piVar3 + 4;
                } while (iVar2 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + iVar1 + -8));
            }
        }

    }
}
}
