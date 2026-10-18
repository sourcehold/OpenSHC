#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    using Map::Buildings::BuildingType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004585F0
    int GameStateStructures::moveUnitAroundCampfire(int unitID, int availablePeasants)
    {
        int const playerID = DAT_UnitsState::instance.units[unitID].owner;
        int const campfireID = this->playerDataArray[playerID].campground.id;
        if (campfireID > 0) {
            if (DAT_BuildingsState::instance.buildings[campfireID].owner == playerID
                && DAT_BuildingsState::instance.buildings[campfireID].buildingType == Map::Buildings::BT_CAMPGROUND) {
                DAT_UnitsState::instance.units[unitID].workplaceBuildingUID
                    = DAT_BuildingsState::instance.buildings[campfireID].uid;
                DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1 = (short)campfireID;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::determinePeasantSitPosition,
                    DAT_BuildingsState::ptr)(campfireID, availablePeasants - 1);
                DAT_UnitsState::instance.units[unitID].targetX_2 = (short)DAT_BuildingsState::instance.campfireSpotX;
                DAT_UnitsState::instance.units[unitID].targetY_2 = (short)DAT_BuildingsState::instance.campfireSpotY;
                DAT_UnitsState::instance.units[unitID].field38_0x56
                    = (short)DAT_BuildingsState::instance.campfireSpotOrientation;
                if (DAT_UnitsState::instance.units[unitID].x == DAT_UnitsState::instance.units[unitID].targetX_2
                    && DAT_UnitsState::instance.units[unitID].y == DAT_UnitsState::instance.units[unitID].targetY_2) {
                    return 0;
                }
                return 1;
            }
        }
        return -1;
    }

}
}
