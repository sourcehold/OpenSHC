#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EB80
    int GameSynchronyState::addPlayerToCurrentPlayerArray(int playerFullID)
    {
        // the original reads some fields through the global instance rather than this, so they stay that way
        for (int existing = 1; existing < 9; ++existing) {
            if (this->currentPlayerFullIDArray[existing] == playerFullID) {
                return existing;
            }
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER) {
            for (int slot = 1; slot < 9; ++slot) {
                if (((this->currentPlayerFullIDArray[slot] == -1)
                        || (this->currentPlayerFullIDArray[slot] == playerFullID))
                    && this->currentAIArray[slot] <= 0) {
                    this->currentPlayerFullIDArray[slot] = playerFullID;
                    return slot;
                }
            }
        }
        for (int slot = 1; slot < 9; ++slot) {
            if ((this->currentPlayerFullIDArray[slot] == -1)
                || (this->currentPlayerFullIDArray[slot] == playerFullID)) {
                this->currentPlayerFullIDArray[slot] = playerFullID;
                return slot;
            }
        }
        return 0;
    }

}
}
