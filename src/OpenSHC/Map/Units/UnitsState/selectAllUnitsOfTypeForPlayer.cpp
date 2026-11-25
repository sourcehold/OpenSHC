#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005350B0
        void UnitsState::selectAllUnitsOfTypeForPlayer(int playerID, int unitType)
        {
            this->totalUnitsInSelection = 0;
            for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                    && !this->units[DAT_CurrentUnitSlotID::instance].dying
                    && this->units[DAT_CurrentUnitSlotID::instance].unknownTestAgainst0_2 == 0
                    && this->units[DAT_CurrentUnitSlotID::instance].state.generic
                        != OpenSHC::Map::Units::States::US_JESTER_ROAM_TO
                    && (short)this->units[DAT_CurrentUnitSlotID::instance].unitType == unitType
                    && this->units[DAT_CurrentUnitSlotID::instance].drawX != 0
                    && this->units[DAT_CurrentUnitSlotID::instance].owner == playerID) {
                    this->units[DAT_CurrentUnitSlotID::instance].isSelected = 1;
                    this->totalUnitsInSelection = this->totalUnitsInSelection + 1;
                }
            }
        }

    }
}
}
