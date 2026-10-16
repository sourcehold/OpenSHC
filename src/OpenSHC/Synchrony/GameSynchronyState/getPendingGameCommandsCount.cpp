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
        GameCommandStateByte* pGVar3;
        int iVar1 = 0;
        int iVar3 = this->MBR_GameCommandID;
        if (iVar3 < 200) {
            pGVar3 = &this->DAT_GameCommandArray[iVar3].stateUnk;
            int iVar2 = 200 - iVar3;
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
