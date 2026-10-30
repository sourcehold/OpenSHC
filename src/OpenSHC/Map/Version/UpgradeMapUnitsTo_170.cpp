#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::States::UnitState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B800
    void Version::UpgradeMapUnitsTo_170()
    {
        for (int unitID = 1; unitID < 2500; ++unitID) {
            if (DAT_UnitsState::instance.units[unitID].unitType == Units::UT_S_CATAPULT
                || DAT_UnitsState::instance.units[unitID].unitType == Units::UT_S_TREBUCHET
                || DAT_UnitsState::instance.units[unitID].unitType == Units::UT_S_MANGONEL
                || DAT_UnitsState::instance.units[unitID].unitType == Units::UT_S_TOWER
                || DAT_UnitsState::instance.units[unitID].unitType == Units::UT_S_BATTERINGRAM
                || DAT_UnitsState::instance.units[unitID].unitType == Units::UT_S_SHIELD
                || DAT_UnitsState::instance.units[unitID].unitType == Units::UT_S_BALLISTA
                || DAT_UnitsState::instance.units[unitID].unitType == Units::UT_S_FBALLISTA) {
                for (int i = 0; i < DAT_UnitsState::instance.units[unitID]
                                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                    ++i) {
                    int crewID = DAT_UnitsState::instance.units[unitID].manningEngineerRef[i];
                    if (DAT_UnitsState::instance.units[crewID].uid
                            == DAT_UnitsState::instance.units[unitID].manningEngineerUIDRef[i]
                        && DAT_UnitsState::instance.units[crewID].state.generic == (UnitState)7) {
                        DAT_UnitsState::instance.units[crewID].state.generic = (UnitState)5;
                    }
                }
            }
        }
    }

}
}
