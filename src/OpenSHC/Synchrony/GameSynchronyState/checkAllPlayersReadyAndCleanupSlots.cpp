#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EDE0
    BOOLEnum GameSynchronyState::checkAllPlayersReadyAndCleanupSlots()
    {
        if (this->isHost) {
            for (int player = 1; player < 9; player++) {
                if ((this->DAT_CurrentPlayerFullIDArray2[player] != -1) && (this->unknownPlayerInfo_01[player] == 0)) {
                    return FALSE;
                }
            }
            if (this->somePlayerRelatedArray[1] == 0) {
                this->currentPlayerFullIDArray[1] = -1;
            }
            if (this->somePlayerRelatedArray[2] == 0) {
                this->currentPlayerFullIDArray[2] = -1;
            }
            if (this->somePlayerRelatedArray[3] == 0) {
                this->currentPlayerFullIDArray[3] = -1;
            }
            if (this->somePlayerRelatedArray[4] == 0) {
                this->currentPlayerFullIDArray[4] = -1;
            }
            if (this->somePlayerRelatedArray[5] == 0) {
                this->currentPlayerFullIDArray[5] = -1;
            }
            if (this->somePlayerRelatedArray[6] == 0) {
                this->currentPlayerFullIDArray[6] = -1;
            }
            if (this->somePlayerRelatedArray[7] == 0) {
                this->currentPlayerFullIDArray[7] = -1;
            }
            if (this->somePlayerRelatedArray[8] == 0) {
                this->currentPlayerFullIDArray[8] = -1;
            }
        } else if (!this->lobbyStateReceived) {
            return FALSE;
        }
        return TRUE;
    }

}
}
