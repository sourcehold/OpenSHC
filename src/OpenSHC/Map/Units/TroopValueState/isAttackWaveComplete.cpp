#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00518350
        undefined4 TroopValueState::isAttackWaveComplete()
        {
            for (int i = 0; i < 50; i++) {
                // fixme: this function doesn't use this-> (would be not 100% matching!)
                if ((DAT_TroopValueState::instance.attackInfo.nof_tribes[i] != 0
                        && (DAT_TroopValueState::instance.attackInfo.value3Array01[i] != 6))) {
                    return FALSE;
                }
            }
            return TRUE;
        }

    }
}
}
