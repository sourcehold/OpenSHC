#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00549B30
    BOOLEnum Units::SetRestingForUnit(int unitID)
    {
        DAT_UnitsState::instance.units[unitID].idle += 1;
        BOOLEnum restedEnough = FALSE;
        if (DAT_UnitsState::instance.units[unitID].idle > DAT_UnitsState::instance.units[unitID].target) {
            restedEnough = TRUE;
        }
        if (DAT_UnitsState::instance.units[unitID].destinationNeeded
            != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
            DAT_UnitsState::instance.units[unitID].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            int building
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::pickARandomPositiveFearFactorBuilding,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].owner);
            if (building != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, DAT_BuildingsState::instance.buildings[building].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[building].buildingEntryY, 0);
            } else {
                // No positive fear factor building available, resume normal state
                DAT_UnitsState::instance.units[unitID].state.generic
                    = DAT_UnitsState::instance.units[unitID].cachedState;
                DAT_UnitsState::instance.units[unitID].destinationNeeded = (DestinationNeededEnum)2;
            }
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                unitID)
            != FALSE) {
            if (restedEnough != FALSE) {
                if (DAT_UnitsState::instance.units[unitID].idle > DAT_UnitsState::instance.units[unitID].target) {
                    DAT_UnitsState::instance.units[unitID].banked
                        = DAT_UnitsState::instance.units[unitID].idle - DAT_UnitsState::instance.units[unitID].target;
                }
                DAT_UnitsState::instance.units[unitID].field166_0x2fe = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = DAT_UnitsState::instance.units[unitID].cachedState;
                DAT_UnitsState::instance.units[unitID].destinationNeeded = (DestinationNeededEnum)2;
                return TRUE;
            }
            if (DAT_UnitsState::instance.units[unitID].unitTypeSpecificRestingState > 0
                && DAT_UnitsState::instance.units[unitID].field166_0x2fe == 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = DAT_UnitsState::instance.units[unitID].unitTypeSpecificRestingState;
                DAT_UnitsState::instance.units[unitID].field166_0x2fe = 1;
                return FALSE;
            }
            DAT_UnitsState::instance.units[unitID].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            DAT_UnitsState::instance.units[unitID].field166_0x2fe = 0;
        }
        return TRUE;
    }

}
}
