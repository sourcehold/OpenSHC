#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Units::UnitLogicState;
    using Map::Units::UnitType;
    using Map::Units::UnitTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B5A0
    void Version::UpgradeMapUnitsTo_154()
    {
        UnitTypeShort* pUVar1;
        pUVar1 = &DAT_UnitsState::instance.units[1].unitType;
        DAT_CurrentUnitSlotID::instance = 0x9c4;
        do {
            if (pUVar1[-1] == Map::Units::ULS_NORMAL
                && (*pUVar1 == Map::Units::UT_S_CATAPULT || (*pUVar1 == Map::Units::UT_S_TREBUCHET))) {
                pUVar1[0x16a] = 0x14;
            }
            pUVar1 = pUVar1 + 0x248;
        } while ((int)pUVar1 < 0x165141a);
    }

}
}
