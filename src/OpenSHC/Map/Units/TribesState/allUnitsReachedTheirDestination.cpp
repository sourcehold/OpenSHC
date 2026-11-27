#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005253F0
        BOOLEnum TribesState::allUnitsReachedTheirDestination(int tribeID)
        {
            int unitSelectionIndex = 0;
            while (unitSelectionIndex < this->tribes[tribeID].size) {
                int const unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, unitSelectionIndex);
                unitSelectionIndex = unitSelectionIndex + 1;
                if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                    && !DAT_UnitsState::instance.units[unitID].dying) {
                    BOOLEnum const _reachedDestination = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(unitID);
                    if (!_reachedDestination) {
                        return FALSE;
                    }
                }
            }
            return TRUE;
        }

    }
}
}
