#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00410290
        void BuildingsState::updateVisuallyActiveState(int buildingID)
        {
            if (this->buildings[buildingID].buildingIsVisuallyActive != 0) {
                if (this->buildings[buildingID].tickRelatedVisuallyActiveIndicator >= 5) {
                    return;
                }
                if (this->buildings[buildingID].tickRelatedVisuallyActiveIndicator == 0) {
                    this->buildings[buildingID].tickRelatedVisuallyActiveIndicator = 1;
                    return;
                }
                this->buildings[buildingID].tickRelatedVisuallyActiveIndicator += this->isFirstTickInLoop;
                return;
            }

            if (this->buildings[buildingID].tickRelatedVisuallyActiveIndicator <= 0) {
                return;
            }
            if (this->buildings[buildingID].tickRelatedVisuallyActiveIndicator == 5) {
                this->buildings[buildingID].tickRelatedVisuallyActiveIndicator = 4;
            } else {
                this->buildings[buildingID].tickRelatedVisuallyActiveIndicator -= this->isFirstTickInLoop;
            }
            this->buildings[buildingID].buildingIsVisuallyActive
                = this->buildings[buildingID].tickRelatedVisuallyActiveIndicator != 0;
        }

    }
}
}
