#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CEB50
    void AICState::giveMoveCommandToAttackTribes(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL)
            return;

        int destIndex = 0;
        for (int i = 0; i < 11; i++) {
            int tribeType = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeType;
            int tribeCount = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeCount;
            if (tribeType == 18 || tribeType == 190 || tribeType == 15)
                continue;

            for (int j = 0; j < tribeCount; j++) {
                int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[tribeType + j];
                if (tribeID == 0)
                    continue;
                if (DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[j + tribeType])
                    continue;

                DAT_TribesState::instance.tribes[tribeID].unitStance = (char)(SEC_RNG::instance.currentNumber2 & 1);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                    tribeID,
                    DAT_GameState::instance.mapAndTime.aiTribeMoveDestinationXYPairArray1[playerID * 5][destIndex].xOffset,
                    DAT_GameState::instance.mapAndTime.aiTribeMoveDestinationXYPairArray1[playerID * 5][destIndex].yOffset,
                    0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);
                destIndex++;
            }
        }
    }

}
}
