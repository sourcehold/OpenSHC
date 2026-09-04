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
        int _highestRankingPlayer = MACRO_CALL(OpenSHC::UI::GreatestLord_Func::GetPlayerAtRank)(0);
        if ((_highestRankingPlayer != 0)
            && (DAT_GameSynchronyState::instance.currentAIArray[_highestRankingPlayer] != 0)) {
            return DAT_GameState::instance.playerDataArray[_highestRankingPlayer].aiType - 1;
        }
        return 0;
    }

}
}
