#include "OpenSHC/Map/Units.func.hpp"
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
        if (DAT_UnitsState::instance.units[unitID].destinationNeeded
            != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED) {
            return FALSE;
        }
        int productivity = DAT_GameState::instance.playerDataArray[DAT_UnitsState::instance.units[unitID].owner]
                               .fearFactorProductivityUnk;
        if (productivity < 100 && DAT_UnitsState::instance.units[unitID].av > 100) {
            DAT_UnitsState::instance.units[unitID].target
                = (short)((100 - productivity) * DAT_UnitsState::instance.units[unitID].av / 100);
            if (DAT_UnitsState::instance.units[unitID].banked >= DAT_UnitsState::instance.units[unitID].target) {
                DAT_UnitsState::instance.units[unitID].banked -= DAT_UnitsState::instance.units[unitID].target;
                return FALSE;
            }
            DAT_UnitsState::instance.units[unitID].cachedState = (short)nextUnitState;
            DAT_UnitsState::instance.units[unitID].idle = DAT_UnitsState::instance.units[unitID].banked;
            DAT_UnitsState::instance.units[unitID].field166_0x2fe = 0;
            // resting
            DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)121;
            return TRUE;
        }
        return FALSE;
    }

}
}
