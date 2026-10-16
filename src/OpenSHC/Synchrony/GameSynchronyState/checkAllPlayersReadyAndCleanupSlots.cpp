#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EDE0
    undefined4 GameSynchronyState::checkAllPlayersReadyAndCleanupSlots()
    {
        if (this->isHost) {
            int iVar2 = 1;
            int* piVar1 = this->unknownPlayerInfo_01 + 1;
            do {
                if ((piVar1[-0x419c2] != -1) && (*piVar1 == 0)) {
                    return (undefined4)(0);
                }
                iVar2 = iVar2 + 1;
                piVar1 = piVar1 + 1;
            } while (iVar2 < 9);
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
            return (undefined4)(1);
        }
        if (this->lobbyStateReceived) {
            return (undefined4)(1);
        }
        return (undefined4)(0);
    }

}
}
