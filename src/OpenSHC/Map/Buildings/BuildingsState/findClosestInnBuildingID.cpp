#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B1A0
        int BuildingsState::findClosestInnBuildingID(int unitID)
        {
            // Finds the closest inn of the owner of the unit that still has ale
            short playerID = DAT_UnitsState::instance.units[unitID].owner;
            int closestDistance = 10000;
            int closest = 0;
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == 0 || this->buildings[i].logicalState == BLS_REMOVE
                    || this->buildings[i].owner != playerID || this->buildings[i].buildingType != BT_INN
                    || this->buildings[i].flagonsOfAleOrCheeseOrReleaseDogs <= 0) {
                    continue;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                    DAT_UnitsState::instance.units[unitID].y, this->buildings[i].buildingEntryX,
                    this->buildings[i].buildingEntryY);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < closestDistance) {
                    closestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    closest = i;
                }
            }
            return closest;
        }

    }
}
}
