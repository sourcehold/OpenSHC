#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::Unit;
    using OpenSHC::Map::Units::UnitLogicState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B340
    void Version::UpgradeMapUnitsTo_112()
    {
        DAT_CurrentUnitSlotID::instance = 2500;
        // fixme: the reimplementation unrolls this loop three times (2499 = 3 * 833), the original does not
        for (int unitID = 1; unitID < 2500; ++unitID) {
            if (DAT_UnitsState::instance.units[unitID].logicalState == Units::ULS_NORMAL) {
                DAT_UnitsState::instance.units[unitID].buildingID
                    = DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1;
            }
        }
    }

}
}
