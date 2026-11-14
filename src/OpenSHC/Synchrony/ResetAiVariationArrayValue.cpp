#include "OpenSHC/Synchrony.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00428050
void Synchrony::ResetAiVariationArrayValue(int playerID)
{
    if ((uint)(playerID - 1) > 7) {
        return;
    }
    DAT_GameSynchronyState::instance.aiVariationArray[playerID] = -1;
    BOOLEnum variationUsed[9] = { FALSE };
    for (int other = 1; other < 9; ++other) {
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[other] == -1
            && DAT_GameSynchronyState::instance.currentAIArray[other]
                == DAT_GameSynchronyState::instance.currentAIArray[playerID]
            && DAT_GameSynchronyState::instance.aiVariationArray[other] != -1) {
            variationUsed[DAT_GameSynchronyState::instance.aiVariationArray[other]] = TRUE;
        }
    }
    for (int variation = 0; variation < 9; ++variation) {
        if (!variationUsed[variation]) {
            DAT_GameSynchronyState::instance.aiVariationArray[playerID] = variation;
            return;
        }
    }
}

}
