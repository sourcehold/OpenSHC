#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535680
        uint UnitsState::getSelectedEngineerCarryingResource()
        {
            /* Does not dirty EDX. -TheRedDaemon */
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::selectionContainsEngineersOnly, this)()
                != FALSE) {
                int _currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                for (DAT_CurrentUnitSlotID::instance = 1;
                    (int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount;
                    DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                    if (this->units[DAT_CurrentUnitSlotID::instance].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].dying != 0) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].isSelected == 0) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner != _currentPlayerSlotID) {
                        break;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_E_ENGINEER
                        && this->units[DAT_CurrentUnitSlotID::instance].resourceToDeposit != 0) {
                        return DAT_CurrentUnitSlotID::instance;
                    }
                }
            }
            return 0;
        }

    }
}
}
