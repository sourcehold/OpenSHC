#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B260
    void Version::UpgradeMapUnitsTo_UnknownVersion2()
    {
        for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < 2500;
            ++DAT_CurrentUnitSlotID::instance) {
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState == Units::ULS_NORMAL) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].someUnitStat2_meleeDamageUnk
                    = (short)DAT_UnitPropertiesDefinedData::instance
                          .UNIT_CAN_MELEE[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitType];
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementCooldown > 1) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].movementCooldown = 0;
                }
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].health
                    >= DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].maxHealth) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].health
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].maxHealth
                        = DAT_UnitPropertiesDefinedData::instance
                              .BASE_HP[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitType];
                    int maxHealth = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].maxHealth;
                    int percentage = maxHealth == 0
                        ? 100
                        : DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].health * 100 / maxHealth;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].healthPercentage
                        = (short)percentage;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].healthbar = (short)percentage / 10;
                }
            }
        }
    }

}
}
