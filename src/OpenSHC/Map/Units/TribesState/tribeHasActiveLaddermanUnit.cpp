#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00524140
        BOOLEnum TribesState::tribeHasActiveLaddermanUnit(int tribeID)
        {
            int const _size = this->tribes[tribeID].size;
            int unitSelectionIndex = 0;
            while (unitSelectionIndex < _size) {
                int const unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, unitSelectionIndex);
                unitSelectionIndex = unitSelectionIndex + 1;
                if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].unitType == Map::Units::UT_E_LADDER
                    && DAT_UnitsState::instance.units[unitID].state.generic == 3) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
