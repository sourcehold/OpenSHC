#include "../AICState.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/AI/AIUnitBehaviourType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::AI::AIUnitBehaviourType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC070
    AIUnitBehaviourType AICState::randomlySelectAttackUnitTypeToRecruit(int playerID)
    {
        AITypeInt aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL) {
            return OpenSHC::AI::AIUBT_ATTUNITMAIN;
        }

        int attackedPlayerID = DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;
        int aicIndex = aiType - 1;
        int requiredCount = 0;

        // clear out flags
        for (int i = 0; i < 11; i++) {
            DAT_SkirmishDefinedData::instance.attackUnitRequired[i].required = 0;
        }

        int engineersCount = DAT_GameState::instance.playerDataArray[playerID].currentAttackWave * 4;
        if (engineersCount > (int)this->aics[aicIndex].AttMaxEngineers) {
            engineersCount = this->aics[aicIndex].AttMaxEngineers;
        }
        if (this->aics[aicIndex].AttMaxEngineers != 0
            && DAT_GameState::instance.playerDataArray[playerID].totalAttackingEngineerTroops < engineersCount) {
            requiredCount = 1;
            DAT_SkirmishDefinedData::instance.attackUnitRequired[0].required = 1;
        }

        if (this->aics[aicIndex].AttDiggingUnitMax != 0
            && DAT_GameState::instance.playerDataArray[playerID].totalDiggingUnitTroops
                < (int)this->aics[aicIndex].AttDiggingUnitMax
            && DAT_GameState::instance.playerDataArray[attackedPlayerID].moatsOwned > 5) {
            requiredCount++;
            DAT_SkirmishDefinedData::instance.attackUnitRequired[1].required = 1;
        }

        if (this->aics[aicIndex].AttMaxAssassins != 0
            && DAT_GameState::instance.playerDataArray[playerID].totalAssassinTroops
                < (int)this->aics[aicIndex].AttMaxAssassins) {
            requiredCount++;
            DAT_SkirmishDefinedData::instance.attackUnitRequired[2].required = 1;
        }

        if (this->aics[aicIndex].AttUnit2Max != 0
            && DAT_GameState::instance.playerDataArray[playerID].totalUnit2Troops
                < (int)this->aics[aicIndex].AttUnit2Max) {
            requiredCount++;
            DAT_SkirmishDefinedData::instance.attackUnitRequired[3].required = 1;
        }

        if (this->aics[aicIndex].AttMaxLaddermen != 0
            && DAT_GameState::instance.playerDataArray[playerID].totalLaddermenTroops
                < (int)this->aics[aicIndex].AttMaxLaddermen) {
            requiredCount++;
            DAT_SkirmishDefinedData::instance.attackUnitRequired[4].required = 1;
        }

        if (this->aics[aicIndex].AttMaxTunnelers != 0
            && DAT_GameState::instance.playerDataArray[playerID].totalTunnelerTroops
                < (int)this->aics[aicIndex].AttMaxTunnelers) {
            requiredCount++;
            DAT_SkirmishDefinedData::instance.attackUnitRequired[5].required = 1;
        }

        if (this->aics[aicIndex].AttUnitPatrolMax != 0
            && DAT_GameState::instance.playerDataArray[playerID].totalUnitPatrolTroops
                < (int)this->aics[aicIndex].AttUnitPatrolMax) {
            requiredCount++;
            DAT_SkirmishDefinedData::instance.attackUnitRequired[6].required = 1;
        }

        if (this->aics[aicIndex].AttUnitBackupMax != 0
            && DAT_GameState::instance.playerDataArray[playerID].totalUnitBackupTroops
                < (int)this->aics[aicIndex].AttUnitBackupMax) {
            requiredCount++;
            DAT_SkirmishDefinedData::instance.attackUnitRequired[7].required = 1;
        }

        if (this->aics[aicIndex].AttUnitEngageMax != 0
            && DAT_GameState::instance.playerDataArray[playerID].totalUnitEngageTroops
                < (int)this->aics[aicIndex].AttUnitEngageMax) {
            requiredCount++;
            DAT_SkirmishDefinedData::instance.attackUnitRequired[8].required = 1;
        }

        if (this->aics[aicIndex].AttUnitSiegeDefMax != 0
            && DAT_GameState::instance.playerDataArray[playerID].totalUnitSiegeDefTroops
                < (int)this->aics[aicIndex].AttUnitSiegeDefMax) {
            requiredCount++;
            DAT_SkirmishDefinedData::instance.attackUnitRequired[9].required = 1;
        }

        if (this->aics[aicIndex].AttMaxDefault != 0
            && DAT_GameState::instance.playerDataArray[playerID].totalMaxDefaultTroops
                < (int)this->aics[aicIndex].AttMaxDefault) {
            requiredCount++;
            DAT_SkirmishDefinedData::instance.attackUnitRequired[10].required = 1;
        }

        if (requiredCount <= 0) {
            return OpenSHC::AI::AIUBT_ATTUNITMAIN;
        }

        int selection = (int)SEC_RNG::instance.currentNumber2 % requiredCount;
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();

        for (int i = 0; i < 11; i++) {
            if (DAT_SkirmishDefinedData::instance.attackUnitRequired[i].required == 0) {
                continue;
            }
            if (selection == 0) {
                return (AIUnitBehaviourType)DAT_SkirmishDefinedData::instance.attackUnitRequired[i].unitBehaviourType;
            }
            selection--;
        }

        return OpenSHC::AI::AIUBT_ATTUNITMAIN;
    }

}
}
