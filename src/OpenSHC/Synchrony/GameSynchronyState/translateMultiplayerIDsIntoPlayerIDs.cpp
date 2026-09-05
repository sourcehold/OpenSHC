#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EAF0
    uint GameSynchronyState::translateMultiplayerIDsIntoPlayerIDs(int playerHandle)
    {
        uint player = 0;
        if (this->currentGameMode == Game::GM_SOLITARY || this->currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER) {
            return this->currentPlayerSlotID;
        }

        // Do not return on the first match: the native function lets the last
        // matching slot win, including duplicate or sentinel-valued handles.
        if (this->currentPlayerFullIDArray[1] == playerHandle)
            player = 1;
        if (this->currentPlayerFullIDArray[2] == playerHandle)
            player = 2;
        if (this->currentPlayerFullIDArray[3] == playerHandle)
            player = 3;
        if (this->currentPlayerFullIDArray[4] == playerHandle)
            player = 4;
        if (this->currentPlayerFullIDArray[5] == playerHandle)
            player = 5;
        if (this->currentPlayerFullIDArray[6] == playerHandle)
            player = 6;
        if (this->currentPlayerFullIDArray[7] == playerHandle)
            player = 7;
        if (this->currentPlayerFullIDArray[8] == playerHandle)
            player = 8;
        return player;
    }

} // namespace Synchrony
} // namespace OpenSHC
