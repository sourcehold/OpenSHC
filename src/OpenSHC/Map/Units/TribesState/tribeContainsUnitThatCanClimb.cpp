#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005241C0
        BOOLEnum TribesState::tribeContainsUnitThatCanClimb(int tribeID)
        {
            int const _size = this->tribes[tribeID].size;
            int unitSelectionIndex = 0;
            while (unitSelectionIndex < _size) {
                int const unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, unitSelectionIndex);
                unitSelectionIndex = unitSelectionIndex + 1;
                if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                    && !DAT_UnitsState::instance.units[unitID].dying
                    && DAT_UnitsState::instance.units[unitID].unitCanClimb) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
