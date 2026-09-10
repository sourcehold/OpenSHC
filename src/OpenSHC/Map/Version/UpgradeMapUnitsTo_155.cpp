#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::Unit;
    using OpenSHC::Map::Units::UnitLogicState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B5E0
    void Version::UpgradeMapUnitsTo_155()
    {
        DAT_CurrentUnitSlotID::instance = 2500;
        for (int _unitID = 1; _unitID < 2500; _unitID++) {
            if (DAT_UnitsState::instance.units[_unitID].logicalState != Units::ULS_INVISIBLE) {
                DAT_UnitsState::instance.units[_unitID].killedFlagUnk = 0;
            }
        }
    }

}
}
