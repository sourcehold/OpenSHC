#include "../GreatestLord.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D5780
    int GreatestLord::ComputeSkMasterScore(int playerID)
    {
        int score = DAT_GameSynchronyState::instance.finalResults.finalBuildingsDestroyedWeighted[playerID] * 100
            + DAT_GameSynchronyState::instance.finalResults.finalGold[playerID] / 10
            + DAT_GameSynchronyState::instance.finalResults.finalTroopsKilledWeighted[playerID];
        score += DAT_GameSynchronyState::instance.finalResults.finalKilledLords[playerID] * score / 4;
        int months = (DAT_GameSynchronyState::instance.finalResults.tail.tail1.yearEnd
                         - DAT_GameSynchronyState::instance.finalResults.tail.tail1.yearStart)
                * 12
            - DAT_GameSynchronyState::instance.finalResults.tail.tail1.monthStart
            + DAT_GameSynchronyState::instance.finalResults.tail.tail1.monthEnd;
        if (months < 1) {
            months = 1;
        }
        return score * 200 / (months + 200);
    }

}
}
