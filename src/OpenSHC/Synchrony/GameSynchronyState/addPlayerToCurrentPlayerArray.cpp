#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EB80
    int GameSynchronyState::addPlayerToCurrentPlayerArray(int playerFullID)
    {
        int slot;
        for (int existing = 1; existing < 9; existing = existing + 1) {
            if (this->currentPlayerFullIDArray[existing] == playerFullID) {
                return existing;
            }
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER) {
            for (slot = 1; slot < 9; slot = slot + 1) {
                if (((this->currentPlayerFullIDArray[slot] == -1)
                        || (this->currentPlayerFullIDArray[slot] == playerFullID))
                    && this->currentAIArray[slot] <= 0)
                    goto takeSlot;
            }
        }
        for (slot = 1; slot < 9; slot = slot + 1) {
            if ((this->currentPlayerFullIDArray[slot] == -1) || (this->currentPlayerFullIDArray[slot] == playerFullID))
                goto takeSlot;
        }
        return 0;
    takeSlot:
        this->currentPlayerFullIDArray[slot] = playerFullID;
        return slot;
    }

}
}
