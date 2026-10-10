#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Commands/GameCommandState.hpp"
#include "OpenSHC/Commands/GameCommandStateByte.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandState;
    using Commands::GameCommandStateByte;

    // FUNCTION: STRONGHOLDCRUSADER 0x00480580
    int GameSynchronyState::getPendingGameCommandsCount()
    {
        int iVar1;
        int iVar2;
        GameCommandStateByte* pGVar3;
        iVar1 = 0;
        if (this->MBR_GameCommandID < 200) {
            pGVar3 = &this->DAT_GameCommandArray[this->MBR_GameCommandID].stateUnk;
            iVar2 = 200 - this->MBR_GameCommandID;
            do {
                if (*pGVar3 != (GameCommandState)0 && (char)*pGVar3 < '\n') {
                    iVar1 = iVar1 + 1;
                }
                pGVar3 = pGVar3 + 0x4f8;
                iVar2 = iVar2 + -1;
            } while (iVar2);
        }
        return iVar1;
    }

}
}
