#include "../SFX.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044C400
        int ComputeCurrentPlayerRanking()
        {
            return MACRO_CALL(SFX_Func::ComputePlayerRanking)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
        }

    }
}
}
