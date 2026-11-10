#include "../Units.func.hpp"

#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00530CF0
    BOOLEnum Units::SetStateToFreetimeWalking(int unitID, int shouldFindNewGoodThing, int substateCount)
    {
        if (DAT_UnitsState::instance.units[unitID].field_0x2fe != 1) {
            return FALSE;
        }
        DAT_UnitsState::instance.units[unitID].idle += 1;
        if (shouldFindNewGoodThing == 0) {
            return FALSE;
        }
        DAT_UnitsState::instance.units[unitID].substate += 1;
        DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
        if (DAT_UnitsState::instance.units[unitID].substate >= substateCount) {
            DAT_UnitsState::instance.units[unitID].substate = 0;
        }
        // resting
        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_UNKNOWN_121;
        return TRUE;
    }

}
}
