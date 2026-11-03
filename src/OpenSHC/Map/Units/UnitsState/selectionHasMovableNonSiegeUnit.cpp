#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00536260
        BOOLEnum UnitsState::selectionHasMovableNonSiegeUnit()
        {
            int _currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].dying) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].isSelected == 0) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].owner != _currentPlayerSlotID) {
                    return FALSE;
                }
                int _unitType = this->units[DAT_CurrentUnitSlotID::instance].unitType;
                if (_unitType < UT_S_TREBUCHET) {
                    return TRUE;
                }
                if (_unitType > UT_S_MANGONEL && _unitType != UT_S_BALLISTA) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
