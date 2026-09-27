#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535190
        void UnitsState::deselectUnit(int unitID)
        {
            if (this->units[unitID].isSelected == 0) {
                return;
            }
            this->units[unitID].isSelected = 0;
            this->totalUnitsInSelection = this->totalUnitsInSelection - 1;
        }

    }
}
}
