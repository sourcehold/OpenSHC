#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::States::UnitStateShort;

        // FUNCTION: STRONGHOLDCRUSADER 0x00525300
        void TribesState::setStateForAllTribeUnits(int tribeID, UnitStateShort unitState)
        {
            int unitSelectionIndex = 0;
            while (unitSelectionIndex < this->tribes[tribeID].size) {
                int const unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, unitSelectionIndex);
                unitSelectionIndex = unitSelectionIndex + 1;
                if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                    && !DAT_UnitsState::instance.units[unitID].dying) {
                    DAT_UnitsState::instance.units[unitID].state.generic = unitState;
                    DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[unitID].seated = 0;
                }
            }
        }

    }
}
}
