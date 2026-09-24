#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C310
        BOOLEnum BuildingsState::processResourceGain(int playerID, ResourceType resourceType, int amount)
        {
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getResourceSpace, this)(
                    playerID, (int*)resourceType)
                < amount) {
                return FALSE;
            }

            if (amount <= 0) {
                return TRUE;
            }
            BuildingType storageType
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingStorageTypeForResourceType,
                    this)(resourceType);
            if (storageType == BT_MANORHOUSE) {
                DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType] += amount;
                return TRUE;
            }
            if (storageType == BT_ARMORY) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToArmory, this)(
                    resourceType, playerID, amount);
                return TRUE;
            }
            if (storageType == BT_GRANARY) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToGranary, this)(
                    resourceType, playerID, amount);
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, this)(playerID);
                return TRUE;
            }

            // Fill up the stockpiles that already store this resource first. Note: the original checks
            // currentNumberOfResource twice.
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != BLS_NORMAL || this->buildings[i].owner != playerID
                    || this->buildings[i].buildingType != storageType || this->buildings[i].currentNumberOfResource == 0
                    || this->buildings[i].resources[resourceType] == 0
                    || this->buildings[i].currentNumberOfResource == 0
                    || this->buildings[i].resources[resourceType]
                        >= DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resourceType]) {
                    continue;
                }
                int space = DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resourceType]
                    - this->buildings[i].resources[resourceType];
                for (int n = 0; n < space; ++n) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                        DAT_BuildingsState::ptr)(i, this->buildings[i].uid, resourceType, 1,
                        DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resourceType], 1);
                    --amount;
                    if (amount <= 0) {
                        return TRUE;
                    }
                }
            }
            // Then continue with the empty ones
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != BLS_NORMAL || this->buildings[i].owner != playerID
                    || this->buildings[i].buildingType != storageType
                    || this->buildings[i].currentNumberOfResource != 0) {
                    continue;
                }
                int space = DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resourceType]
                    - this->buildings[i].resources[resourceType];
                for (int n = 0; n < space; ++n) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                        DAT_BuildingsState::ptr)(i, this->buildings[i].uid, resourceType, 1,
                        DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resourceType], 1);
                    --amount;
                    if (amount <= 0) {
                        return TRUE;
                    }
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, this)(playerID);
            return FALSE;
        }

    }
}
}
