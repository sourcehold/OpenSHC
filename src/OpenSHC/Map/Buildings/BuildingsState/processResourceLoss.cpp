#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BD70
        void BuildingsState::processResourceLoss(int playerID, ResourceType resourceType, int amount, int param_4)
        {
            // param_4 != 0 only marks the amount to take (someResourceNumber) without removing it
            bool found = false;
            if (resourceType != 0) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    if (param_4 == 0) {
                        DAT_GameState::instance.playerDataArray[playerID].startResources[resourceType] -= amount;
                        return;
                    }
                } else {
                    BuildingType storageType = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingStorageTypeForResourceType, this)(
                        resourceType);
                    if (storageType == BT_MANORHOUSE) {
                        if (param_4 == 0) {
                            DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType] -= amount;
                            return;
                        }
                    } else {
                        for (int i = 1; i < this->maxBuildingsCount; ++i) {
                            if (this->buildings[i].logicalState != BLS_NORMAL
                                || this->buildings[i].buildingType != storageType
                                || this->buildings[i].owner != playerID
                                || this->buildings[i].resources[resourceType] <= 0) {
                                continue;
                            }
                            if (param_4 == 0) {
                                this->buildings[i].someResourceNumber = 0;
                            }
                            int stored = this->buildings[i].resources[resourceType];
                            found = true;
                            if (stored < amount) {
                                amount -= stored;
                                if (param_4 != 0) {
                                    this->buildings[i].someResourceNumber = stored;
                                } else {
                                    this->buildings[i].resources[resourceType] = 0;
                                    DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType]
                                        -= stored;
                                }
                            } else {
                                if (param_4 == 0) {
                                    this->buildings[i].resources[resourceType] = stored - amount;
                                    DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType]
                                        -= amount;
                                } else {
                                    this->buildings[i].someResourceNumber = amount;
                                }
                                amount = 0;
                            }
                            if (param_4 == 0) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, this)(
                                    i);
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, this)(playerID);
                            }
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(i);
                        }
                        if (found) {
                            return;
                        }
                    }
                }
            }
            DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType] = 0;
        }

    }
}
}
