#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CEC80
    BOOLEnum AICState::aiChoiceAttForceRallyPercentage(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL)
            return FALSE;
        int aicIndex = aiType - 1;

        int activeTribes = 0;
        int rallyingTribes = 0;
        for (int i = 0; i < 11; i++) {
            int tribeType = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeType;
            int tribeCount = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeCount;
            for (int j = 0; j < tribeCount; j++) {
                int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[tribeType + j];
                if (tribeID == 0)
                    continue;
                if (DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[j + tribeType])
                    continue;

                activeTribes++;
                if (DAT_TribesState::instance.tribes[tribeID].percentageMovingUnk < 20)
                    rallyingTribes++;
            }
        }

        if (activeTribes <= 0)
            return FALSE;
        return rallyingTribes * 100 / activeTribes >= this->aics[aicIndex].AttForceRallyPercentage;
    }

}
}
