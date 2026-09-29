#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005339F0
        BOOLEnum UnitsState::hasTunnelerNotFinishedDigging(int unitID)
        {
            return (BOOLEnum)(this->units[unitID].tunnelerFinishedDigging == 0);
        }

    }
}
}
