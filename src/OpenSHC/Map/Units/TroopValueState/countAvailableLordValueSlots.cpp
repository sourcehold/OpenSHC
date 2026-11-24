#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A100
        void TroopValueState::countAvailableLordValueSlots(int param_1)
        {
            int* piVar1;
            int iVar2;
            DAT_TroopValueState::instance.attackInfo.lord2 = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.lord3) {
                piVar1 = &DAT_TroopValueState::instance.attackInfo.lordValuesArray[0].unitID;
                iVar2 = DAT_TroopValueState::instance.attackInfo.lord3;
                do {
                    if ((*piVar1 == 0) || (param_1)) {
                        DAT_TroopValueState::instance.attackInfo.lord2
                            = DAT_TroopValueState::instance.attackInfo.lord2 + 1;
                    }
                    piVar1 = piVar1 + 4;
                    iVar2 = iVar2 + -1;
                } while (iVar2);
            }
        }

    }
}
}
