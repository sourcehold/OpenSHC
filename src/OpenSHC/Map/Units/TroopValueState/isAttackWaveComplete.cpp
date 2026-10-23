#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518350
        BOOLEnum TroopValueState::isAttackWaveComplete()
        {
            for (int i = 0; i < 50; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.nof_tribes[i] != 0
                    && DAT_TroopValueState::instance.attackInfo.value3Array01[i] != 6) {
                    return FALSE;
                }
            }
            return TRUE;
        }

    }
}
}
