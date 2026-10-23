#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00419D70
        void BuildingsState::updateEnemyBuildings(int playerID)
        {
            // Collects the attackable buildings of the enemies of an AI player
            bool solitary = DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY;
            DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[playerID] = 0;
            if (!solitary && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                && DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0) {
                return;
            }
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == 0
                    || DAT_GameState::instance.mapAndTime.playerTeams[this->buildings[i].owner]
                        == DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                    || this->buildings[i].logicalState == BLS_REMOVE) {
                    continue;
                }
                switch (this->buildings[i].buildingType) {
                case BT_STOCKPILE:
                case BT_QUARRYSTOCKPILE:
                case BT_UNKNOWN1:
                case BT_MANORHOUSE:
                case BT_STONEKEEP:
                case BT_STRONGHOLD:
                case BT_KEEPFOUR:
                case BT_KEEPFIVE:
                case BT_DRAWBRIDGE:
                case BT_TUNNEL:
                case BT_CAMPFIRE:
                case BT_SIGNPOST:
                case BT_PARADEGROUND:
                case BT_FIREBALLISTA:
                case BT_CAMPGROUND:
                case BT_PARADEGROUND2:
                case BT_PARADEGROUND3:
                case BT_PARADEGROUND4:
                case BT_PARADEGROUND5:
                case BT_KILLINGPIT:
                case BT_KEEPDOOR_LEFT:
                case BT_KEEPDOOR_RIGHT:
                case BT_KEEPDOOR:
                case BT_CATAPULT:
                case BT_TREBUCHET:
                case BT_BATTERINGRAM:
                case BT_SIEGETOWER:
                case BT_SHIELD:
                case BT_UNKNOWN4:
                case BT_POND:
                    break;
                default:
                    DAT_GameState::instance.mapAndTime.playerEnemyBuildingIDs[playerID][DAT_GameState::instance
                            .mapAndTime.playerBuildingInfoIndex[playerID]] = i;
                    DAT_GameState::instance.mapAndTime.playerEnemyBuildingUID[playerID][DAT_GameState::instance
                            .mapAndTime.playerBuildingInfoIndex[playerID]] = this->buildings[i].uid;
                    ++DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[playerID];
                    break;
                }
            }
        }

    }
}
}
