#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EDE0
    BOOLEnum GameSynchronyState::checkAllPlayersReadyAndCleanupSlots()
    {
        if (this->isHost) {
            for (int player = 1; player < 9; ++player) {
                if (this->DAT_CurrentPlayerFullIDArray2[player] != -1 && this->unknownPlayerInfo_01[player] == 0) {
                    return FALSE;
                }
            }
            for (int player = 1; player < 9; ++player) {
                if (this->somePlayerRelatedArray[player] == 0) {
                    this->currentPlayerFullIDArray[player] = -1;
                }
            }
        } else if (!this->lobbyStateReceived) {
            return FALSE;
        }
        return TRUE;
    }

}
}
