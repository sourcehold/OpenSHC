#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535150
        void UnitsState::deselectAllUnitsOneByOne()
        {
            for (DAT_CurrentUnitSlotID::instance = 1; (int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                this->units[DAT_CurrentUnitSlotID::instance].isSelected = 0;
            }
            this->totalUnitsInSelection = 0;
        }

    }
}
}
