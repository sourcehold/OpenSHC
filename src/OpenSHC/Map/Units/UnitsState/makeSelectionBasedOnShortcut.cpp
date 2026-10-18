#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535FD0
        void UnitsState::makeSelectionBasedOnShortcut(int section1099ID)
        {
            for (DAT_CurrentUnitSlotID::instance = 1; (int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                    && this->units[DAT_CurrentUnitSlotID::instance].dying == 0) {
                    this->units[DAT_CurrentUnitSlotID::instance].isSelected = 0;
                }
            }
            this->totalUnitsInSelection = 0;
            for (int i = 0; i < 2500; ++i) {
                int _unitID = DAT_GameState::instance.hotkeyTribes[section1099ID].units[i].id;
                if (_unitID == -1) {
                    continue;
                }
                if (this->units[_unitID].uid == DAT_GameState::instance.hotkeyTribes[section1099ID].units[i].uid
                    && this->units[_unitID].unknownTestAgainst0_2 == 0
                    && this->units[_unitID].disappearFadeAlphaCountdown == 0) {
                    this->units[_unitID].isSelected = 1;
                    this->totalUnitsInSelection = this->totalUnitsInSelection + 1;
                } else {
                    DAT_GameState::instance.hotkeyTribes[section1099ID].units[i].id = -1;
                }
            }
            if (this->totalUnitsInSelection > 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::createTribeFromSelectedUnits, this)();
            }
        }

    }
}
}
