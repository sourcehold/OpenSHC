#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x005301F0
        int UnitsState::countLivingNondyingUnitsForPlayer(int unitType)
        {
            // the original counts units of one type; the name says "for player" but the parameter is a unit type
            int _count = 0;
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                    && this->units[unitID].dying == 0 && this->units[unitID].unitType == unitType) {
                    _count = _count + 1;
                }
            }
            return _count;
        }

    }
}
}
