#include "../UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F070
        void UnitsState::makeUnitStopWalkingByClearingPathProgressState(int unitID)
        {
            this->units[unitID].currentIndexInPathPlan = 0;
            this->units[unitID].totalSizeOfPathPlan = 0;
            this->units[unitID].movementCooldown = 0;
            this->units[unitID].climbDataID = 0;
        }

    }
}
}
