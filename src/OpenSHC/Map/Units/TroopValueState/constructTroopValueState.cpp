#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::TroopValueState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D680
        TroopValueState* TroopValueState::constructTroopValueState()
        {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::clearAttackInfo, this)();
            return this;
        }

    }
}
}
