#include "OpenSHC/AI/AICState.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D3960
    void AICState::makeOutpostTribesAttack()
    {
        int* _tribeUIDs = this->tribeUIDArray;
        short* _tribeIDs = this->tribeIDArray;
        int _countDown = 1000;
        do {
            unsigned int _tribeID = (uint)*_tribeIDs;
            if ((_tribeID != 0) && (DAT_TribesState::instance.tribes[_tribeID].uid == *_tribeUIDs)) {
                MACRO_CALL_MEMBER(AICState_Func::decideOnTribeAttackLocation, this)(_tribeID);
            }
            _tribeIDs = _tribeIDs + 1;
            _tribeUIDs = _tribeUIDs + 1;
            _countDown = _countDown + -1;
        } while (_countDown != 0);
    }
}
}
