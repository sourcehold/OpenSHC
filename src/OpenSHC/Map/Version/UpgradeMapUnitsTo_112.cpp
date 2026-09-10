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
        // fixme: the reimplementation always unrolls this for loop (because 2499/3 = 833), but the original isn't
        // unrolled
        for (int _unitID = 1; _unitID < 2500; _unitID++) {
            if (DAT_UnitsState::instance.units[_unitID].logicalState == Units::ULS_NORMAL) {
                DAT_UnitsState::instance.units[_unitID].buildingID
                    = DAT_UnitsState::instance.units[_unitID].workplaceBuildingID_1;
            }
        }
    }

}
}
