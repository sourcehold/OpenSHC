#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A550
        void TroopValueState::setWide3(int param_1, int param_2)
        {
            int* piVar1;
            int iVar2;
            int iVar3;
            int* piVar4;
            int iVar5;
            iVar3 = param_2 * 0x177bc;
            iVar5 = 0;
            iVar2 = *(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + iVar3 + -8);
            *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + iVar3 + -4) = 0;
            if (0 < iVar2) {
                piVar4 = (int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + iVar3 + 0xc);
                do {
                    if ((piVar4[-1] < 5999) && ((*piVar4 == 0 || (param_1)))) {
                        piVar1 = (int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + iVar3 + -4);
                        *piVar1 = *piVar1 + 1;
                    }
                    iVar5 = iVar5 + 1;
                    piVar4 = piVar4 + 4;
                } while (iVar5 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + iVar3 + -8));
            }
        }

    }
}
}
