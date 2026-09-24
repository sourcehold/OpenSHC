#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C300
        void BuildingsState::countPlayerResources(int playerID)
        {
            int gold
                = DAT_GameState::instance.playerDataArray[playerID].currentResources[OpenSHC::Game::Resources::RT_GOLD];

            // Reset the stored resources and recount them from the storage buildings, gold is kept
            for (int i = 0; i < 25; ++i) {
                if (i != OpenSHC::Game::Resources::RT_GOLD) {
                    DAT_GameState::instance.playerDataArray[playerID].currentResources[i] = 0;
                }
            }
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != BLS_NORMAL || this->buildings[i].owner != playerID) {
                    continue;
                }
                if (this->buildings[i].buildingType == BT_STOCKPILE) {
                    for (int r = OpenSHC::Game::Resources::RT_WOOD; r <= OpenSHC::Game::Resources::RT_FLOUR; ++r) {
                        DAT_GameState::instance.playerDataArray[playerID].currentResources[r]
                            += this->buildings[i].resources[r];
                    }
                } else if (this->buildings[i].buildingType == BT_GRANARY) {
                    for (int r = OpenSHC::Game::Resources::RT_BREAD; r <= OpenSHC::Game::Resources::RT_APPLE; ++r) {
                        DAT_GameState::instance.playerDataArray[playerID].currentResources[r]
                            += this->buildings[i].resources[r];
                    }
                } else if (this->buildings[i].buildingType == BT_ARMORY) {
                    for (int r = OpenSHC::Game::Resources::RT_BOW; r < 25; ++r) {
                        DAT_GameState::instance.playerDataArray[playerID].currentResources[r]
                            += this->buildings[i].resources[r];
                    }
                }
            }
            DAT_GameState::instance.playerDataArray[playerID].currentResources[OpenSHC::Game::Resources::RT_GOLD]
                = gold;
        }

    }
}
}
