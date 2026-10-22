#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BD70
        void BuildingsState::processResourceLoss(int playerID, ResourceType resourceType, int amount, int param_4)
        {
            int foundStorage = 0;
            if (resourceType == 0) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
                if (param_4 == 0) {
                    DAT_GameState::instance.playerDataArray[playerID].startResources[resourceType] -= amount;
                }
                return;
            }
            BuildingType const storageType
                = MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingStorageTypeForResourceType, this)(resourceType);
            if (storageType == BT_MANORHOUSE) {
                if (param_4 == 0) {
                    DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType] -= amount;
                }
                return;
            }
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != BLS_NORMAL) {
                    continue;
                }
                if (this->buildings[buildingID].buildingType != storageType
                    || this->buildings[buildingID].owner != playerID
                    || this->buildings[buildingID].resources[resourceType] <= 0) {
                    continue;
                }
                if (param_4 == 0) {
                    this->buildings[buildingID].someResourceNumber = 0;
                }
                foundStorage = 1;
                if (this->buildings[buildingID].resources[resourceType] >= amount) {
                    if (param_4 != 0) {
                        this->buildings[buildingID].someResourceNumber = amount;
                    } else {
                        this->buildings[buildingID].resources[resourceType] -= amount;
                        DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType] -= amount;
                    }
                    amount = 0;
                } else {
                    amount -= this->buildings[buildingID].resources[resourceType];
                    if (param_4 != 0) {
                        this->buildings[buildingID].someResourceNumber
                            = this->buildings[buildingID].resources[resourceType];
                    } else {
                        DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType]
                            -= this->buildings[buildingID].resources[resourceType];
                        this->buildings[buildingID].resources[resourceType] = 0;
                    }
                }
                if (param_4 == 0) {
                    MACRO_CALL_MEMBER(BuildingsState_Func::computeResourceSumForBuilding, this)(buildingID);
                    MACRO_CALL_MEMBER(BuildingsState_Func::countPlayerResources, this)(playerID);
                }
                MACRO_CALL_MEMBER(TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
            }
            if (foundStorage == 0) {
                DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType] = 0;
            }
        }

    }
}
}
