#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F620
        void BuildingsState::updateNeededEmployeeCount(int buildingID)
        {
            if (this->buildings[buildingID].buildingTypeBasedEmployeeCount <= 0) {
                return;
            }
            this->buildings[buildingID].currentlyNeededEmployeeCount = 0;
            if (this->buildings[buildingID].sleeping) {
                return;
            }
            if (this->buildings[buildingID].buildingType == BT_MERCENARYPOST
                || this->buildings[buildingID].buildingType == BT_BARRACKS) {
                return;
            }
            int const owner = this->buildings[buildingID].owner;
            this->buildings[buildingID].currentEmployeeCount = 0;
            for (int workerSlot = 0; workerSlot < this->buildings[buildingID].buildingTypeBasedEmployeeCount;
                ++workerSlot) {
                if (MACRO_CALL_MEMBER(BuildingsState_Func::hasWorker, this)(buildingID, workerSlot) == FALSE) {
                    this->buildings[buildingID].workerUID[workerSlot] = 0;
                    this->buildings[buildingID].workerID[workerSlot] = 0;
                } else {
                    this->buildings[buildingID].currentEmployeeCount += 1;
                }
            }
            this->buildings[buildingID].currentlyNeededEmployeeCount
                = this->buildings[buildingID].buildingTypeBasedEmployeeCount
                - this->buildings[buildingID].currentEmployeeCount;
            DAT_GameState::instance.playerDataArray[owner].countEconomyBuilding_fixme
                += this->buildings[buildingID].currentlyNeededEmployeeCount;
        }

    }
}
}
