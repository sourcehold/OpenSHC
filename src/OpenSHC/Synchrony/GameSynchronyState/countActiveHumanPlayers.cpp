#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E830
    int GameSynchronyState::countActiveHumanPlayers()
    {
        uint uVar1 = 0;
        if (this->currentPlayerFullIDArray[1] != -1) {
            uVar1 = 1;
        }
        if (this->currentPlayerFullIDArray[2] != -1) {
            uVar1 = uVar1 + 1;
        }
        if (this->currentPlayerFullIDArray[3] != -1) {
            uVar1 = uVar1 + 1;
        }
        if (this->currentPlayerFullIDArray[4] != -1) {
            uVar1 = uVar1 + 1;
        }
        if (this->currentPlayerFullIDArray[5] != -1) {
            uVar1 = uVar1 + 1;
        }
        if (this->currentPlayerFullIDArray[6] != -1) {
            uVar1 = uVar1 + 1;
        }
        if (this->currentPlayerFullIDArray[7] != -1) {
            uVar1 = uVar1 + 1;
        }
        if (this->currentPlayerFullIDArray[8] != -1) {
            uVar1 = uVar1 + 1;
        }
        return uVar1;
    }

}
}
