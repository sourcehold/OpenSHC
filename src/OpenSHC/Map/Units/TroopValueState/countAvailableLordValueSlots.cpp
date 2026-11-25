#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A100
        void TroopValueState::countAvailableLordValueSlots(BOOLEnum includeOccupied)
        {
            DAT_TroopValueState::instance.attackInfo.lord2 = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.lord3; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].unitID == 0 || includeOccupied) {
                    DAT_TroopValueState::instance.attackInfo.lord2++;
                }
            }
        }

    }
}
}
