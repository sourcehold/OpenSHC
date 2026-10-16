#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;

    /*
      in multiplayer, player IDS are unique numbers of some sort   decompilerscript: committed: 2025-01-30
      21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0047EAF0
    uint GameSynchronyState::translateMultiplayerIDsIntoPlayerIDs(int multiplayerID)
    {
        uint _playerID = 0;
        if ((this->currentGameMode == Game::GM_SOLITARY)
            || (this->currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            /*
              Used in singleplayer
             */
            return (uint)(this->currentPlayerSlotID);
        }
        /*
          if in multiplayer
         */
        if (this->currentPlayerFullIDArray[1] == multiplayerID) {
            _playerID = 1;
        }
        if (this->currentPlayerFullIDArray[2] == multiplayerID) {
            _playerID = 2;
        }
        if (this->currentPlayerFullIDArray[3] == multiplayerID) {
            _playerID = 3;
        }
        if (this->currentPlayerFullIDArray[4] == multiplayerID) {
            _playerID = 4;
        }
        if (this->currentPlayerFullIDArray[5] == multiplayerID) {
            _playerID = 5;
        }
        if (this->currentPlayerFullIDArray[6] == multiplayerID) {
            _playerID = 6;
        }
        if (this->currentPlayerFullIDArray[7] == multiplayerID) {
            _playerID = 7;
        }
        if (this->currentPlayerFullIDArray[8] == multiplayerID) {
            _playerID = 8;
        }
        return _playerID;
    }

}
}
