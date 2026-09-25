#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::Unit;
    using OpenSHC::Map::Units::UnitLogicState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B570
    void Version::UpgradeMapUnitsTo_149()
    {
        DAT_CurrentUnitSlotID::instance = 2500;
        for (int unitID = 1; unitID < 2500; ++unitID) {
            if (DAT_UnitsState::instance.units[unitID].logicalState == Units::ULS_NORMAL) {
                DAT_UnitsState::instance.units[unitID].shootBeforeStop = 0;
            }
        }
    }

}
}
