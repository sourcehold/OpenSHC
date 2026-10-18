#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005351C0
        void UnitsState::filterUnitSelectionExcludeUnitType(int unitType)
        {
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].isSelected != 0 && (short)this->units[unitID].unitType == unitType) {
                    this->units[unitID].isSelected = 0;
                    this->totalUnitsInSelection = this->totalUnitsInSelection - 1;
                }
            }
        }

    }
}
}
