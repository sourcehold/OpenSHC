#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B530
    void Version::UpgradeMapUnitsTo_130()
    {
        DAT_CurrentUnitSlotID::instance = 2500;
        for (int i = 1; i < 2500; i++) {
            if (DAT_UnitsState::instance.units[i].logicalState == Units::ULS_NORMAL
                && DAT_UnitsState::instance.units[i].unitType == Units::UT_COW) {
                DAT_UnitsState::instance.units[i].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                    = 0;
            }
        }
    }

}
}
