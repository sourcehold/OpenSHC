#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B5A0
    void Version::UpgradeMapUnitsTo_154()
    {
        for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < 2500;
            ++DAT_CurrentUnitSlotID::instance) {
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState == Units::ULS_NORMAL
                && (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitType == Units::UT_S_CATAPULT
                    || DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitType
                        == Units::UT_S_TREBUCHET)) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stoneAmmunition = 20;
            }
        }
    }

}
}
