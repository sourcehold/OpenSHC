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
            if (0 < DAT_TroopValueState::instance.attackInfo.people2) {
                int* _pUnitID = &DAT_TroopValueState::instance.attackInfo.peopleValuesArray[0].unitID;
                int _remaining = DAT_TroopValueState::instance.attackInfo.people2;
                do {
                    if ((*_pUnitID == 0) || (param_1)) {
                        DAT_TroopValueState::instance.attackInfo.people3
                            = DAT_TroopValueState::instance.attackInfo.people3 + 1;
                    }
                    _pUnitID = _pUnitID + 4;
                    _remaining = _remaining + -1;
                } while (_remaining);
            }
        }

    }
}
}
