#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B1F0
    void Version::UpgradeMapUnitsTo_117()
    {
        for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < 2500;
            ++DAT_CurrentUnitSlotID::instance) {
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState == Units::ULS_NORMAL) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementSpeed
                    = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_MOVEMENT_SPEED_ARRAY
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitType];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection == 15) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection = 4;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitType != Units::UT_A_ASSASSIN) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field306_0x418 = 0;
                }
            }
        }
    }

}
}
