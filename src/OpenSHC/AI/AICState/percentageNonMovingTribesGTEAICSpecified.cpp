#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CED90
    BOOLEnum AICState::percentageNonMovingTribesGTEAICSpecified(int playerID)
    {
        AITypeInt aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL) {
            return FALSE;
        }

        int aicIndex = aiType - 1;
        int tribeTotal = 0;
        int notReallyMoving = 0;

        for (int i = 0; i < 11; i++) {
            int tribeIndex = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeType;
            int tribeCount = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeCount;

            for (int j = 0; j < tribeCount; j++) {
                int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[tribeIndex + j];
                if (tribeID == 0) {
                    continue;
                }
                if (DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[tribeIndex + j]) {
                    continue;
                }

                tribeTotal++;
                if (DAT_TribesState::instance.tribes[tribeID].percentageMovingUnk < 20) {
                    notReallyMoving++;
                }
            }
        }

        if (tribeTotal <= 0) {
            return FALSE;
        }

        return notReallyMoving * 100 / tribeTotal >= this->aics[aicIndex].AttMovingTribesThreshold;
    }

}
}
