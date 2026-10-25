#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00459D80
    void GameStateStructures::computeArmySizeLimit()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == GM_SOLITARY) {
            this->mapAndTime.armySizeLimit = 10000;
            return;
        }
        int livingPlayers = 0;
        for (int playerID = 1; playerID < 9; playerID += 1) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
                if(DAT_GameState::instance.playerDataArray[playerID].lordKilledByPlayerID == 0) {
                    ++livingPlayers;
                }
                
            } else if(DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
                if(DAT_GameState::instance.playerDataArray[playerID].lordKilledByPlayerID == 0) {
                    ++livingPlayers;
                }
            }
        }
        if (livingPlayers != 0) {
            this->mapAndTime.armySizeLimit = 2400 / livingPlayers - 40;
            return;
        }
        this->mapAndTime.armySizeLimit = 10000;
    }

}
}
