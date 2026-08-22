#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Synchrony::GameSynchronyState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CAC70
    void AICState ::clearPlayerDataInformationChunk()

    {
        int* _Dst = &DAT_GameState::instance.playerDataArray[0].aiFarmIndex;
        int* _pAI = DAT_GameSynchronyState::instance.currentAIArray;
        int* _pFullID = DAT_GameSynchronyState::instance.currentPlayerFullIDArray;

        do {
            if (*_pFullID != -1 || *_pAI == 0) {
                MACRO_CALL(OpenSHC::OS_Func::_memset)(_Dst, 0, (size_t)((int)(3748)));
            }

            _pAI = _pAI + 1;
            _pFullID = _pFullID + 1;
            _Dst = _Dst + 3709;

        } while ((int)_pAI < 0x191dea0);

        return;
    }

}
}
