#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0054A770
        void UnitsState::resumeMovementIfNoAttackTarget(int unitID)
        {
            if (this->units[unitID].attackedUnitID != 0) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resumeMovementAfterInterruption, this)(unitID);
            this->units[unitID].attackedUnitID = 0;
            this->units[unitID].field191_0x340 = 0;
        }

    }
}
}
