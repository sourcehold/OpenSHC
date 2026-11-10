#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005251A0
        void TribesState::applyMovementDistanceToUnitsInTribeBasedOnUnitNumberInTribe(int tribeID)
        {
            int unitSelectionIndex = 0;
            while (unitSelectionIndex < this->tribes[tribeID].size) {
                int const unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, unitSelectionIndex);
                unitSelectionIndex = unitSelectionIndex + 1;
                if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                    && !DAT_UnitsState::instance.units[unitID].dying) {
                    DAT_UnitsState::instance.units[unitID].movementDistance
                        = DAT_UnitsState::instance.units[unitID].idInTribe;
                }
            }
        }

    }
}
}
