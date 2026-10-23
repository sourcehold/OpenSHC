#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C4B0
        void BuildingsState::recomputePlayerDataStocksBasedOnStorageBuildings()
        {
            // Reset the stored resources of all players and recount them from the storage buildings, gold is kept
            int gold[10];
            for (int p = 1; p < 9; ++p) {
                gold[p]
                    = DAT_GameState::instance.playerDataArray[p].currentResources[OpenSHC::Game::Resources::RT_GOLD];
                for (int r = 0; r < 25; ++r) {
                    DAT_GameState::instance.playerDataArray[p].currentResources[r] = 0;
                }
            }
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == BLS_NORMAL
                    && (this->buildings[i].buildingType == BT_STOCKPILE || this->buildings[i].buildingType == BT_GRANARY
                        || this->buildings[i].buildingType == BT_ARMORY)) {
                    int playerID = this->buildings[i].owner;
                    for (int r = 0; r < 25; ++r) {
                        DAT_GameState::instance.playerDataArray[playerID].currentResources[r]
                            += this->buildings[i].resources[r];
                    }
                }
            }
            for (int p = 1; p < 9; ++p) {
                DAT_GameState::instance.playerDataArray[p].currentResources[OpenSHC::Game::Resources::RT_GOLD]
                    = gold[p];
            }
        }

    }
}
}
