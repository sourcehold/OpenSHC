#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AB10
        void TroopValueState::countAvailableArcherValueSlots(int param_1)
        {
            int* piVar1;
            int iVar2;
            DAT_TroopValueState::instance.attackInfo.arch3 = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.arch2) {
                piVar1 = &DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[0].unitID;
                iVar2 = DAT_TroopValueState::instance.attackInfo.arch2;
                do {
                    if ((DAT_BuildingsState::instance.buildings[piVar1[-1]].unknownCounterTo10000_0x2b4 < 9999)
                        && ((*piVar1 == 0 || (param_1)))) {
                        DAT_TroopValueState::instance.attackInfo.arch3
                            = DAT_TroopValueState::instance.attackInfo.arch3 + 1;
                    }
                    piVar1 = piVar1 + 4;
                    iVar2 = iVar2 + -1;
                } while (iVar2);
            }
        }

    }
}
}
