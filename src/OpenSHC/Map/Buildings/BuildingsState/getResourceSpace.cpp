#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C1F0
        int BuildingsState::getResourceSpace(int param_1, int* resourceType)
        {
            // resourceType is actually passed as a ResourceType value
            ResourceType resource = (ResourceType)(int)resourceType;
            int space = -1;
            BuildingType storageType = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingStorageTypeForResourceType, this)(resource);
            if (storageType == BT_MANORHOUSE) {
                return 1000000;
            }

            int buildingCount = this->maxBuildingsCount;
            for (int i = 1; i < buildingCount; ++i) {
                if (this->buildings[i].logicalState != BLS_NORMAL || this->buildings[i].owner != param_1
                    || this->buildings[i].buildingType != storageType) {
                    continue;
                }
                if (space == -1) {
                    space = 0;
                }
                if (this->buildings[i].buildingType == BT_ARMORY) {
                    space += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::computeArmoryRemainingCapacity, this)(i);
                } else if (this->buildings[i].buildingType == BT_GRANARY) {
                    space += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getResourceCountThatCanBeDeposited, this)(
                        i, resource, 250);
                } else if (this->buildings[i].currentNumberOfResource == 0
                    || this->buildings[i].resources[resource] != 0) {
                    // A stockpile only stores a single resource type at a time
                    if (this->buildings[i].currentNumberOfResource == 0) {
                        space += DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resource];
                    } else if (this->buildings[i].resources[resource]
                        < DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resource]) {
                        space += DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resource]
                            - this->buildings[i].resources[resource];
                    }
                }
            }
            return space;
        }

    }
}
}
