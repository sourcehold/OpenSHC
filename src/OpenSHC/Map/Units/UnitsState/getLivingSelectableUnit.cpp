#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053A560
        int UnitsState::getLivingSelectableUnit(int playerID)
        {
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].owner == playerID
                    && this->units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                    && this->units[unitID].dying == 0 && this->units[unitID].isSelectable_OR_matchTime != 0) {
                    return unitID;
                }
            }
            return 0;
        }

    }
}
}
