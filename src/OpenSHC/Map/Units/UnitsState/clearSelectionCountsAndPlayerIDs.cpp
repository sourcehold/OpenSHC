#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00536DE0
        void UnitsState::clearSelectionCountsAndPlayerIDs()
        {
            this->unitCountOfSelection[1] = 0;
            this->unitCountOfSelection[2] = 0;
            this->unitCountOfSelection[3] = 0;
            this->unitCountOfSelection[4] = 0;
            this->unitCountOfSelection[5] = 0;
            this->unitCountOfSelection[6] = 0;
            this->unitCountOfSelection[7] = 0;
            this->unitCountOfSelection[8] = 0;
            for (DAT_CurrentUnitSlotID::instance = 1; (int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                this->units[DAT_CurrentUnitSlotID::instance].ifSelectedThenPlayerID = 0;
            }
        }

    }
}
}
