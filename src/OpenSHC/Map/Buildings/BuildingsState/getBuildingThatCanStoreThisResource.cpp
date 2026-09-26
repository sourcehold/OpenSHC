#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00422230
        int BuildingsState::getBuildingThatCanStoreThisResource(ResourceType resourceType, int amount, int playerID)
        {
            // Granary or stockpile?
            BuildingType storageType
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingStorageTypeForResourceType,
                    this)(resourceType);
            if (storageType == BT_STOCKPILE) {
                // Prefer a stockpile that already stores this resource but is not full yet
                for (int i = 1; i < this->maxBuildingsCount; ++i) {
                    if (this->buildings[i].logicalState == BLS_NORMAL && this->buildings[i].buildingType == BT_STOCKPILE
                        && this->buildings[i].owner == playerID && this->buildings[i].resources[resourceType] != 0
                        && this->buildings[i].resources[resourceType]
                            < DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resourceType]) {
                        return i;
                    }
                }
                // Otherwise use an empty stockpile
                for (int i = 1; i < this->maxBuildingsCount; ++i) {
                    if (this->buildings[i].logicalState == BLS_NORMAL && this->buildings[i].buildingType == BT_STOCKPILE
                        && this->buildings[i].owner == playerID && this->buildings[i].currentNumberOfResource <= 0) {
                        return i;
                    }
                }
            } else if (storageType == BT_GRANARY) {
                for (int i = 1; i < this->maxBuildingsCount; ++i) {
                    if (this->buildings[i].logicalState == BLS_NORMAL && this->buildings[i].buildingType == BT_GRANARY
                        && this->buildings[i].owner == playerID
                        && (int)MACRO_CALL_MEMBER(
                               OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, this)(i)
                            < 250
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, this)(
                               i, 0)
                            != 0) {
                        return i;
                    }
                }
            }
            return 0;
        }

    }
}
}
