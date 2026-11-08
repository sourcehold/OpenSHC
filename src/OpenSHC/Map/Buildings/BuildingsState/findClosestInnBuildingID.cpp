#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B1A0
        int BuildingsState::findClosestInnBuildingID(int unitID)
        {
            int const playerID = DAT_UnitsState::instance.units[unitID].owner;
            int closestDistance = 10000;
            int closestInnID = 0;
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0
                    && this->buildings[buildingID].logicalState != BLS_REMOVE
                    && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].buildingType == BT_INN
                    && this->buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs > 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                        DAT_UnitsState::instance.units[unitID].y, this->buildings[buildingID].buildingEntryX,
                        this->buildings[buildingID].buildingEntryY);
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh < closestDistance) {
                        closestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                        closestInnID = buildingID;
                    }
                }
            }
            return closestInnID;
        }

    }
}
}
