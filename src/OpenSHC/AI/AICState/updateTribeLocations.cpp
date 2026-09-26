#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4940
    void AICState::updateTribeLocations(int playerID)
    {
        AITypeInt _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (_aiType == OpenSHC::AI::AIT_NULL) {
            return;
        }

        DAT_GameState::instance.playerDataArray[playerID].defWallPatrolRallyTimeWaitCounter
            = DAT_GameState::instance.playerDataArray[playerID].defWallPatrolRallyTimeWaitCounter + 1;

        if (DAT_GameState::instance.playerDataArray[playerID].defWallPatrolRallyTimeWaitCounter
            >= this->aics[_aiType - 1].defWallPatrolRallyTime) {

            DAT_GameState::instance.playerDataArray[playerID].defWallPatrolRallyTimeHits
                = DAT_GameState::instance.playerDataArray[playerID].defWallPatrolRallyTimeHits + 1;

            DAT_GameState::instance.playerDataArray[playerID].defWallPatrolRallyTimeWaitCounter = 0;
        }

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::ifHasTribe0SendUnitsToKeep, this)(playerID);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendTribeAtOffset1ToCampfire, this)(playerID);

        if (DAT_GameState::instance.mapAndTime.monthTicks == playerID) {

            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::digNearestMoat, this)(playerID);
        }

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendRangedUnitTribesToAIVSlotsOrKeepIfNervous, this)(playerID);

        MACRO_CALL_MEMBER(
            OpenSHC::AI::AICState_Func::sendCertainUnitTribesToAIVSlotsOrKeepIfNervousAndNotEnclosed, this)(playerID);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendWallPatrolUnitTribesToAIVLocations, this)(playerID);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendOilMenForOilPickupOrToAIVLocations, this)(playerID);

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiGiveOuterPatrolCommand, this)(playerID);
    }

}
}
