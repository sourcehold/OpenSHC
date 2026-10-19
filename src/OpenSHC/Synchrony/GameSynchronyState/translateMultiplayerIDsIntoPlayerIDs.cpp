#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EAF0
    uint GameSynchronyState::translateMultiplayerIDsIntoPlayerIDs(int multiplayerID)
    {
        uint _playerID = 0;
        if (this->currentGameMode == Game::GM_SOLITARY) {
            return this->currentPlayerSlotID;
        }
        if (this->currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER) {
            return this->currentPlayerSlotID;
        }
        // Do not stop at the first match: the original lets the last matching slot win, including
        // duplicate or sentinel-valued IDs.
        for (int _slot = 1; _slot < 9; _slot = _slot + 1) {
            if (this->currentPlayerFullIDArray[_slot] == multiplayerID) {
                _playerID = _slot;
            }
        }
        return _playerID;
    }

}
}
