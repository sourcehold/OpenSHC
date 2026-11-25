#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A0C0
        void TroopValueState::countAvailablePeopleValueSlots(int param_1)
        {
            DAT_TroopValueState::instance.attackInfo.people3 = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.people2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].unitID == 0 || param_1) {
                    ++DAT_TroopValueState::instance.attackInfo.people3;
                }
            }
        }

    }
}
}
