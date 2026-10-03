#include "../AICState.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CAC70
    void AICState::clearPlayerDataInformationChunk()
    {
        for (int i = 0; i < 9; i++) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] != -1
                || DAT_GameSynchronyState::instance.currentAIArray[i] == 0)
                MACRO_CALL(OpenSHC::OS_Func::_memset)(&DAT_GameState::instance.playerDataArray[i].aiFarmIndex, 0, 3748);
        }
    }

}
}
