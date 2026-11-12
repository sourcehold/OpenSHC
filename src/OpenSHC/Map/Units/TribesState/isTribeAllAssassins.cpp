#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00524060
        BOOLEnum TribesState::isTribeAllAssassins(int tribeID)
        {
            int const _size = this->tribes[tribeID].size;
            int _unitSelectionIndex = 0;
            while (_unitSelectionIndex < _size) {
                int const _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, _unitSelectionIndex);
                _unitSelectionIndex = _unitSelectionIndex + 1;
                if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL
                    && !DAT_UnitsState::instance.units[_unitID].dying
                    && DAT_UnitsState::instance.units[_unitID].unitType != Map::Units::UT_A_ASSASSIN) {
                    return FALSE;
                }
            }
            return TRUE;
        }

    }
}
}
