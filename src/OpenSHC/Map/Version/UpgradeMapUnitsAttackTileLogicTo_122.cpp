#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B4F0
    void Version::UpgradeMapUnitsAttackTileLogicTo_122()
    {
        for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < 2500;
            ++DAT_CurrentUnitSlotID::instance) {
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState == Units::ULS_NORMAL) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileX
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .targetedUnitID__OR__engineerMannedSiegeEngineRef;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].attackAtTileY
                    = (short)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID;
            }
        }
    }

}
}
