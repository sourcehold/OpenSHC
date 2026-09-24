#include "OpenSHC/UI/GreatestLord.func.hpp"
#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::AI::AIType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0044B7D0
    int GreatestLord::IfAiGreatestLordGetAiType()
    {
        int const playerID = MACRO_CALL(OpenSHC::UI::GreatestLord_Func::GetPlayerAtRank)(0);
        if (playerID != 0 && DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
            return DAT_GameState::instance.playerDataArray[playerID].aiType - 1;
        }
        return 0;
    }

}
}
