#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitLogicStateShort.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitLogicStateShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B310
    void Version::UpgradeMapUnitsTo_114()
    {
        DAT_CurrentUnitSlotID::instance = 2500;
        for (int i = 1; i < 2500; i++) {
            if (DAT_UnitsState::instance.units[i].logicalState == Units::ULS_NORMAL) {
                DAT_UnitsState::instance.units[i].calculatedOwnerPlayerIndex = 0;
            }
        }
    }

}
}
