#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A0C0
        void TroopValueState::countAvailablePeopleValueSlots(int param_1)
        {
            int* piVar1;
            int iVar2;
            DAT_TroopValueState::instance.attackInfo.people3 = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.people2) {
                piVar1 = &DAT_TroopValueState::instance.attackInfo.peopleValuesArray[0].unitID;
                iVar2 = DAT_TroopValueState::instance.attackInfo.people2;
                do {
                    if ((*piVar1 == 0) || (param_1)) {
                        DAT_TroopValueState::instance.attackInfo.people3 = DAT_TroopValueState::instance.attackInfo.people3 + 1;
                    }
                    piVar1 = piVar1 + 4;
                    iVar2 = iVar2 + -1;
                } while (iVar2);
            }
        }

    }
}
}
