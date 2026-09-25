#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::States::UnitState;

    // FUNCTION: STRONGHOLDCRUSADER 0x00530CF0
    undefined4 Units::SetStateToFreetimeWalking(int unitID, int shouldFindNewGoodThing, int param_3)
    {
        if (DAT_UnitsState::instance.units[unitID].field166_0x2fe != 1) {
            return 0;
        }
        DAT_UnitsState::instance.units[unitID].idle += 1;
        if (shouldFindNewGoodThing == 0) {
            return 0;
        }
        DAT_UnitsState::instance.units[unitID].substate += 1;
        DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
        if (DAT_UnitsState::instance.units[unitID].substate >= param_3) {
            DAT_UnitsState::instance.units[unitID].substate = 0;
        }
        // resting
        DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)121;
        return 1;
    }

}
}
