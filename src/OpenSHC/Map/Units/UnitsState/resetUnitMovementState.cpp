#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053E870
        void UnitsState::resetUnitMovementState(int unitID)
        {
            int _wasPositionPending = this->units[unitID].unknownTestAgainst0_2;
            this->units[unitID].currentIndexInPathPlan = 0;
            this->units[unitID].tunnelerFinishedDigging = 0;
            this->units[unitID].movementRelated = 8;
            this->units[unitID].unknownTestAgainst0_2 = 0;
            this->units[unitID].field105_0xe8 = 0;
            this->units[unitID].unknownMovementRelated_0x2d2 = 0;
            if (_wasPositionPending != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitPendingUnitPosition, this)(unitID);
            }
        }

    }
}
}
