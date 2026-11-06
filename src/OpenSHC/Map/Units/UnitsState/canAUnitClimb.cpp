#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00536610
        BOOLEnum UnitsState::canAUnitClimb()
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
                if (this->units[DAT_CurrentUnitSlotID::instance].unitCanClimb != 0) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
