#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/States/UnitStateUnion.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00533F90
        void UnitsState::saveUnitStateBeforeInterruption(int unitID)
        {
            this->units[unitID].tunnelerFinishedDigging = 5;
            this->units[unitID].state_3 = this->units[unitID].state;
        }

    }
}
}
