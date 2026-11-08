#include "../BuildingsState.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C4B0
        void BuildingsState::recomputePlayerDataStocksBasedOnStorageBuildings()
        {
            int gold[10];
            for (int playerID = 1; playerID < 9; ++playerID) {
                gold[playerID]
                    = DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD];
                for (int resourceType = 0; resourceType < 25; ++resourceType) {
                    DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType] = 0;
                }
            }
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState == BLS_NORMAL
                    && (this->buildings[buildingID].buildingType == BT_STOCKPILE
                        || this->buildings[buildingID].buildingType == BT_GRANARY
                        || this->buildings[buildingID].buildingType == BT_ARMORY)) {
                    int const owner = this->buildings[buildingID].owner;
                    for (int resourceType = 0; resourceType < 25; ++resourceType) {
                        DAT_GameState::instance.playerDataArray[owner].currentResources[resourceType]
                            += this->buildings[buildingID].resources[resourceType];
                    }
                }
            }
            for (int playerID = 1; playerID < 9; ++playerID) {
                DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD]
                    = gold[playerID];
            }
        }

    }
}
}
