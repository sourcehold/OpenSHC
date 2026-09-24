#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F620
        void BuildingsState::updateNeededEmployeeCount(int buildingID)
        {
            short employeeCount = this->buildings[buildingID].buildingTypeBasedEmployeeCount;
            if (employeeCount <= 0) {
                return;
            }
            bool sleeping = this->buildings[buildingID].sleeping;
            this->buildings[buildingID].currentlyNeededEmployeeCount = 0;
            if (sleeping || this->buildings[buildingID].buildingType == BT_MERCENARYPOST
                || this->buildings[buildingID].buildingType == BT_BARRACKS) {
                return;
            }

            short owner = this->buildings[buildingID].owner;
            this->buildings[buildingID].currentEmployeeCount = 0;
            for (int i = 0; i < this->buildings[buildingID].buildingTypeBasedEmployeeCount; ++i) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(buildingID, i)
                    == FALSE) {
                    this->buildings[buildingID].workerUID[i] = 0;
                    this->buildings[buildingID].workerID[i] = 0;
                } else {
                    ++this->buildings[buildingID].currentEmployeeCount;
                }
            }
            short neededCount = this->buildings[buildingID].buildingTypeBasedEmployeeCount
                - this->buildings[buildingID].currentEmployeeCount;
            this->buildings[buildingID].currentlyNeededEmployeeCount = neededCount;
            DAT_GameState::instance.playerDataArray[owner].countEconomyBuilding_fixme += neededCount;
        }

    }
}
}
