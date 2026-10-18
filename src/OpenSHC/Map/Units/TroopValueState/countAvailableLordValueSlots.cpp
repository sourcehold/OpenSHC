#include "OpenSHC/Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A100
        void TroopValueState::countAvailableLordValueSlots(int param_1)
        {
            int* _pUnitID;
            int _remaining;
            DAT_TroopValueState::instance.attackInfo.lord2 = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.lord3) {
                _pUnitID = &DAT_TroopValueState::instance.attackInfo.lordValuesArray[0].unitID;
                _remaining = DAT_TroopValueState::instance.attackInfo.lord3;
                do {
                    if ((*_pUnitID == 0) || (param_1)) {
                        DAT_TroopValueState::instance.attackInfo.lord2
                            = DAT_TroopValueState::instance.attackInfo.lord2 + 1;
                    }
                    _pUnitID = _pUnitID + 4;
                    _remaining = _remaining + -1;
                } while (_remaining);
            }
        }

    }
}
}
