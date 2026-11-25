#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A9A0
        void TroopValueState::countAvailableHighValueSlots(int includeOccupied)
        {
            DAT_TroopValueState::instance.attackInfo.high3 = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.high2; ++i) {
                int const buildingID = DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].buildingID;
                if (DAT_BuildingsState::instance.buildings[buildingID].unknownCounterTo10000_0x2b4 < 9999
                    && (DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].unitID == 0 || includeOccupied)) {
                    DAT_TroopValueState::instance.attackInfo.high3++;
                }
            }
        }

    }
}
}
