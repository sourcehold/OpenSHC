#include "../GreatestLord.func.hpp"

#include "OpenSHC/Audio/SFX.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044B760
    int GreatestLord::GetPlayerAtRank(int rankingPosition)
    {
        int ranking[9] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 };
        for (int playerID = 0; playerID < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray);
            ++playerID) {
            // isAIPlayer(playerID) || the full-ID test: the original inlines isAIPlayer
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                    && DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0)
                || DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
                int const rank = MACRO_CALL(OpenSHC::Audio::SFX_Func::ComputePlayerRanking)(playerID);
                ranking[rank] = playerID;
            }
        }
        return ranking[rankingPosition + 1];
    }

}
}
