#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523630
        int TribesState::getNonDyingUnit(int tribeID)
        {
            int unitID;
            if (tribeID <= 0) {
                return 0;
            }
            int unitSelectionIndex = 0;
            int const _size = this->tribes[tribeID].size;
            do {
                if (unitSelectionIndex >= _size) {
                    return 0;
                }
                unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, unitSelectionIndex);
                unitSelectionIndex = unitSelectionIndex + 1;
            } while (((DAT_UnitsState::instance.units[unitID].logicalState != Map::Units::ULS_NORMAL)
                         || (DAT_UnitsState::instance.units[unitID].dying != 0))
                || (DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue != 1));
            return unitID;
        }

    }
}
}
