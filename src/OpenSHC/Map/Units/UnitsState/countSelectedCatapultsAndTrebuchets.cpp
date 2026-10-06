#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00536400
        undefined4 UnitsState::countSelectedCatapultsAndTrebuchets()
        {
            int _currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            this->field15_0x560 = 0;
            if (DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].keep.id <= 0) {
                return 0;
            }
            int _count = 0;
            for (DAT_CurrentUnitSlotID::instance = 1; (int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount;
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
                    return 0;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_S_CATAPULT
                    || this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                    _count = _count + 1;
                    this->field15_0x560 = DAT_CurrentUnitSlotID::instance;
                }
            }
            if (_count == 1) {
                return 1;
            }
            if (_count > 1) {
                return 2;
            }
            return 0;
        }

    }
}
}
