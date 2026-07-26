#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Synchrony::GameSynchronyState;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names */

    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CAC70
    void AICState ::clearPlayerDataInformationChunk()

    {

        GameSynchronyState* piVar1;

        int* _Dst;

        _Dst = &DAT_GameState::instance.playerDataArray[0].aiFarmIndex;

        piVar1 = (GameSynchronyState*)DAT_GameSynchronyState::instance.currentAIArray;

        do {

            if ((piVar1->currentPlayerFullIDArray[0] != -1) || (piVar1->currentAIArray[0] == 0)) {

                MACRO_CALL(OpenSHC::OS_Func::_memset)(_Dst, 0, (size_t)((int)(3748)));
            }

            piVar1 = (GameSynchronyState*)(piVar1->currentAIArray + 1);

            _Dst = _Dst + 3709;

        } while ((int)piVar1 < 0x191dea0);

        return;
    }

}
}
