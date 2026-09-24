#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/States/UnitStateUnion.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00533F90
        void UnitsState::saveUnitStateBeforeInterruption(int param_1)
        {
            this->units[param_1].tunnelerFinishedDigging = 5;
            this->units[param_1].state_3 = this->units[param_1].state;
        }

    }
}
}
