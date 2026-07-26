#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4940
    void AICState ::updateTribeLocations(int playerID)

    {

        int* piVar1;

        AITypeInt AVar2;

        AVar2 = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (AVar2 != OpenSHC::AI::AIT_NULL) {

            piVar1 = &DAT_GameState::instance.playerDataArray[playerID].defWallPatrolRallyTimeWaitCounter;

            *piVar1 = *piVar1 + 1;

            /*
                  defWallPatrolRallyTime
                */

            if (*(int*)((int)DAT_EntityState::instance.seagullArray + AVar2 * 0x2a4 + 0x2580)
                <= DAT_GameState::instance.playerDataArray[playerID].defWallPatrolRallyTimeWaitCounter) {

                piVar1 = &DAT_GameState::instance.playerDataArray[playerID].defWallPatrolRallyTimeHits;

                *piVar1 = *piVar1 + 1;

                DAT_GameState::instance.playerDataArray[playerID].defWallPatrolRallyTimeWaitCounter = 0;
            }

            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::ifHasTribe0SendUnitsToKeep, this)(playerID);

            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendTribeAtOffset1ToCampfire, this)(playerID);

            if (DAT_GameState::instance.mapAndTime.monthTicks == playerID) {

                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::digNearestMoat, this)(playerID);
            }

            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendRangedUnitTribesToAIVSlotsOrKeepIfNervous, this)(
                playerID);

            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendCertainUnitTribesToAIVSlotsOrKeepIfNervousAndNotEnclosed,
                this)(playerID);

            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendWallPatrolUnitTribesToAIVLocations, this)(playerID);

            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendOilMenForOilPickupOrToAIVLocations, this)(playerID);

            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiGiveOuterPatrolCommand, this)(playerID);
        }

        return;
    }

}
}
