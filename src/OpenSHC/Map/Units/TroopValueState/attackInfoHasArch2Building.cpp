#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051ACB0
        undefined4 TroopValueState::attackInfoHasArch2Building(int buildingID)
        {
            for (int i = 0; i < 1000; i++) {
                // fixme: this function doesn't use this-> (would be not 100% matching!)
                if (buildingID == DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[i].buildingID) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
