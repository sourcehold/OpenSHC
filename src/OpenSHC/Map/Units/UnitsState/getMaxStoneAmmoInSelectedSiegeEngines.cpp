#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00536370
        int UnitsState::getMaxStoneAmmoInSelectedSiegeEngines()
        {
            int _maxStoneAmmunition = 0;
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
                if (this->units[DAT_CurrentUnitSlotID::instance].owner
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    return 0;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].unitType != OpenSHC::Map::Units::UT_S_CATAPULT
                    && this->units[DAT_CurrentUnitSlotID::instance].unitType != OpenSHC::Map::Units::UT_S_TREBUCHET) {
                    continue;
                }
                if (_maxStoneAmmunition < this->units[DAT_CurrentUnitSlotID::instance].stoneAmmunition) {
                    _maxStoneAmmunition = this->units[DAT_CurrentUnitSlotID::instance].stoneAmmunition;
                }
            }
            return _maxStoneAmmunition;
        }

    }
}
}
