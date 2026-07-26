#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1950
    void AICState ::aiRegisterTribeAndAssignTarget(int tribeID, int tribeUID)

    {

        int _index;

        short* _tribe;

        int* _uid;

        if (DAT_TribesState::instance.tribes[tribeID].size < 1) {

            DAT_TribesState::instance.tribes[tribeID].tribeState = 3;

            return;
        }

        if (DAT_GameState::instance.playerDataArray[DAT_TribesState::instance.tribes[tribeID].owner].aiType
            != OpenSHC::AI::AIT_NULL) {

            _index = 0;

            _uid = this->tribeUIDArray;

            _tribe = this->tribeIDArray;

            do {

                if ((*_tribe == 0) || (DAT_TribesState::instance.tribes[*_tribe].uid != *_uid)) {

                    this->tribeIDArray[_index] = (short)tribeID;

                    this->tribeUIDArray[_index] = tribeUID;

                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setTargetForTribeBasedOnTargetChoiceLogic, this)(
                        DAT_TribesState::instance.tribes[tribeID].owner, tribeID);

                    return;
                }

                _index = _index + 1;

                _tribe = _tribe + 1;

                _uid = _uid + 1;

            } while (_index < 1000);
        }

        return;
    }

}
}
