#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00459D80
    void GameStateStructures::computeArmySizeLimit()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            this->mapAndTime.armySizeLimit = 10000;
            return;
        }
        int livingPlayers = 0;
        /*
          four players are handled per pass, exactly as the original binary does
         */
        for (int playerID = 1; playerID < 9; playerID += 4) {
            if (((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1)
                    || (DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0))
                && (DAT_GameState::instance.playerDataArray[playerID].lordKilledByPlayerID == 0)) {
                livingPlayers = livingPlayers + 1;
            }
            if (((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID + 1] != -1)
                    || (DAT_GameSynchronyState::instance.currentAIArray[playerID + 1] != 0))
                && (DAT_GameState::instance.playerDataArray[playerID + 1].lordKilledByPlayerID == 0)) {
                livingPlayers = livingPlayers + 1;
            }
            if (((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID + 2] != -1)
                    || (DAT_GameSynchronyState::instance.currentAIArray[playerID + 2] != 0))
                && (DAT_GameState::instance.playerDataArray[playerID + 2].lordKilledByPlayerID == 0)) {
                livingPlayers = livingPlayers + 1;
            }
            if (((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID + 3] != -1)
                    || (DAT_GameSynchronyState::instance.currentAIArray[playerID + 3] != 0))
                && (DAT_GameState::instance.playerDataArray[playerID + 3].lordKilledByPlayerID == 0)) {
                livingPlayers = livingPlayers + 1;
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
