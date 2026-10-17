#include "../AICState.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D3960
    void AICState::makeOutpostTribesAttack()
    {
        for (int i = 0; i < 1000; i++) {
            int tribeID = this->tribeIDArray[i];
            if (tribeID == 0)
                continue;
            if (DAT_TribesState::instance.tribes[tribeID].uid != this->tribeUIDArray[i])
                continue;

            MACRO_CALL_MEMBER(AICState_Func::decideOnTribeAttackLocation, this)(tribeID);
        }
    }
}
}
