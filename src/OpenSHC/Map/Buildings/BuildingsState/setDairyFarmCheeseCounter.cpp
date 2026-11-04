#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F040
        void BuildingsState::setDairyFarmCheeseCounter(int playerID)
        {
            for (int buildingID = 0; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0 && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].buildingType == BT_DAIRYFARM) {
                    this->buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs = 1600;
                }
            }
        }

    }
}
}
