#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EAF0
    uint GameSynchronyState::translateMultiplayerIDsIntoPlayerIDs(int playerHandle)
    {
        uint player = 0;
        if (this->currentGameMode == Game::GM_SOLITARY) {
            return this->currentPlayerSlotID;
        }

        if (this->currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER) {
            return this->currentPlayerSlotID;
        }

        // Do not return on the first match: the native function lets the last
        // matching slot win, including duplicate or sentinel-valued handles.
        for (int i = 1; i < 9; ++i) {
            if (this->currentPlayerFullIDArray[i] == playerHandle) {
                player = i;
            }
        }
        return player;
    }

} // namespace Synchrony
} // namespace OpenSHC
