#include "../Units.func.hpp"

#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00530C40
    BOOLEnum Units::ConsiderHavingABreakNowUnk(int unitID, UnitState nextUnitState)
    {
        // read here and used twice below: read at its use, or with the productivity in a local, it loses the match
        int const owner = DAT_UnitsState::instance.units[unitID].owner;
        if (DAT_UnitsState::instance.units[unitID].destinationNeeded
            != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED) {
            return FALSE;
        }
        if (DAT_GameState::instance.playerDataArray[owner].fearFactorProductivityUnk < 100
            && DAT_UnitsState::instance.units[unitID].av > 100) {
            DAT_UnitsState::instance.units[unitID].target
                = (100 - DAT_GameState::instance.playerDataArray[owner].fearFactorProductivityUnk)
                * DAT_UnitsState::instance.units[unitID].av / 100;
            if (DAT_UnitsState::instance.units[unitID].banked >= DAT_UnitsState::instance.units[unitID].target) {
                DAT_UnitsState::instance.units[unitID].banked -= DAT_UnitsState::instance.units[unitID].target;
                return FALSE;
            }
            DAT_UnitsState::instance.units[unitID].cachedState = nextUnitState;
            DAT_UnitsState::instance.units[unitID].idle = DAT_UnitsState::instance.units[unitID].banked;
            DAT_UnitsState::instance.units[unitID].field_0x2fe = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_UNKNOWN_121;
            return TRUE;
        }
        return FALSE;
    }

}
}
