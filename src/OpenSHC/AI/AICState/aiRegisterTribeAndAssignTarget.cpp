#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1950
    void AICState::aiRegisterTribeAndAssignTarget(int tribeID, int tribeUID)
    {
        if (DAT_TribesState::instance.tribes[tribeID].size > 0) {
            if (DAT_GameState::instance.playerDataArray[DAT_TribesState::instance.tribes[tribeID].owner].aiType
                == OpenSHC::AI::AIT_NULL)
                return;

            for (int i = 0; i < 1000; i++) {
                int existingTribeID = this->tribeIDArray[i];
                if (existingTribeID != 0
                    && DAT_TribesState::instance.tribes[existingTribeID].uid == this->tribeUIDArray[i])
                    continue;

                this->tribeIDArray[i] = tribeID;
                this->tribeUIDArray[i] = tribeUID;
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setTargetForTribeBasedOnTargetChoiceLogic, this)(
                    DAT_TribesState::instance.tribes[tribeID].owner, tribeID);
                return;
            }
            return;
        }
        DAT_TribesState::instance.tribes[tribeID].tribeState = 3;
    }

}
}
