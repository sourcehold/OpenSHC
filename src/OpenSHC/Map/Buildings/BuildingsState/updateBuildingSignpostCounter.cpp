#include "../BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F360
        int BuildingsState::updateBuildingSignpostCounter(int buildingID, int animation)
        {
            if (animation == 2) {
                this->buildings[buildingID].animationCycleCompleted = 0;
                this->buildings[buildingID].state = 0;
                this->buildings[buildingID].animationIndex = 0;
                return 0;
            }
            if (animation == 3) {
                this->buildings[buildingID].animationIncrement = 0;
            } else {
                this->buildings[buildingID].animationIncrement = 1;
            }
            this->buildings[buildingID].renderAnimation = animation;
            if (this->buildings[buildingID].unknownStockpileOrSignpostRelated == 0) {
                this->buildings[buildingID].renderAnimation = 0;
            }
            if (this->buildings[buildingID].renderAnimation == 0) {
                this->buildings[buildingID].animationIndex = 0;
                this->buildings[buildingID].animationCycleCount = 0;
                this->buildings[buildingID].animationCycleCompleted = 0;
            }
            return this->buildings[buildingID].animationCycleCompleted;
        }

    }
}
}
