#include "../UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00536DE0
        void UnitsState::clearSelectionCountsAndPlayerIDs()
        {
            for (int i = 1; i < 9; i++) {
                this->unitCountOfSelection[i] = 0;
            }
            for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                this->units[DAT_CurrentUnitSlotID::instance].ifSelectedThenPlayerID = 0;
            }
        }

    }
}
}
