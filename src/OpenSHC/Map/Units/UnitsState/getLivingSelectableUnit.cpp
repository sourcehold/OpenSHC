#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053A560
        int UnitsState::getLivingSelectableUnit(int playerID)
        {
            for (int unitID = 1; unitID < this->maxUnitCount; ++unitID) {
                if (this->units[unitID].owner == playerID
                    && this->units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL && !this->units[unitID].dying
                    && this->units[unitID].isSelectable_OR_matchTime != 0) {
                    return unitID;
                }
            }
            return 0;
        }

    }
}
}
