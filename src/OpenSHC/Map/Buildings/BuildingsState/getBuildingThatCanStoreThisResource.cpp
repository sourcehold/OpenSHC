#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00422230
        int BuildingsState::getBuildingThatCanStoreThisResource(ResourceType resourceType, int amount, int playerID)
        {
            BuildingType const storageType
                = MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingStorageTypeForResourceType, this)(resourceType);
            if (storageType == BT_STOCKPILE) {
                for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                    if (this->buildings[buildingID].logicalState == BLS_NORMAL
                        && this->buildings[buildingID].buildingType == BT_STOCKPILE
                        && this->buildings[buildingID].owner == playerID
                        && this->buildings[buildingID].resources[resourceType] != 0
                        && this->buildings[buildingID].resources[resourceType]
                            < DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resourceType]) {
                        return buildingID;
                    }
                }
                for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                    if (this->buildings[buildingID].logicalState == BLS_NORMAL
                        && this->buildings[buildingID].buildingType == BT_STOCKPILE
                        && this->buildings[buildingID].owner == playerID
                        && this->buildings[buildingID].currentNumberOfResource <= 0) {
                        return buildingID;
                    }
                }
            } else if (storageType == BT_GRANARY) {
                for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                    if (this->buildings[buildingID].logicalState == BLS_NORMAL
                        && this->buildings[buildingID].buildingType == BT_GRANARY
                        && this->buildings[buildingID].owner == playerID
                        && (int)MACRO_CALL_MEMBER(BuildingsState_Func::computeResourceSumForBuilding, this)(buildingID)
                            < 250
                        && MACRO_CALL_MEMBER(BuildingsState_Func::buildingIsAccessible, this)(buildingID, 0) != 0) {
                        return buildingID;
                    }
                }
            }
            return 0;
        }

    }
}
}
