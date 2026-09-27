#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/AI/AIUnitBehaviourType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC070
    AIUnitBehaviourType AICState::randomlySelectAttackUnitTypeToRecruit(int playerID)
    {
        AITypeInt aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;
        if (aiType == AIT_NULL) {
            return AIUBT_ATTUNITMAIN;
        }

        int aiIndex = aiType - 1;
        int attackedPlayerID = DAT_GameState::ptr->playerDataArray[playerID].attackedPlayerID;
        int requiredCount = 0;
        for (int index = 0; index < 11; ++index) {
            DAT_SkirmishDefinedData::ptr->attackUnitRequired[index].required = 0;
        }

        dword const maximumEngineers = this->aics[aiIndex].AttMaxEngineers;
        dword engineersNeeded = DAT_GameState::ptr->playerDataArray[playerID].currentAttackWave * 4;
        if (static_cast<int>(engineersNeeded) > static_cast<int>(maximumEngineers)) {
            engineersNeeded = maximumEngineers;
        }
        if (maximumEngineers != 0
            && DAT_GameState::ptr->playerDataArray[playerID].totalAttackingEngineerTroops
                < static_cast<int>(engineersNeeded)) {
            ++requiredCount;
            DAT_SkirmishDefinedData::ptr->attackUnitRequired[0].required = 1;
        }

        if (this->aics[aiIndex].AttDiggingUnitMax != 0
            && DAT_GameState::ptr->playerDataArray[playerID].totalDiggingUnitTroops
                < static_cast<int>(this->aics[aiIndex].AttDiggingUnitMax)
            && DAT_GameState::ptr->playerDataArray[attackedPlayerID].moatsOwned > 5) {
            ++requiredCount;
            DAT_SkirmishDefinedData::ptr->attackUnitRequired[1].required = 1;
        }
        if (this->aics[aiIndex].AttMaxAssassins != 0
            && DAT_GameState::ptr->playerDataArray[playerID].totalAssassinTroops
                < static_cast<int>(this->aics[aiIndex].AttMaxAssassins)) {
            ++requiredCount;
            DAT_SkirmishDefinedData::ptr->attackUnitRequired[2].required = 1;
        }
        if (this->aics[aiIndex].AttUnit2Max != 0
            && DAT_GameState::ptr->playerDataArray[playerID].totalUnit2Troops
                < static_cast<int>(this->aics[aiIndex].AttUnit2Max)) {
            ++requiredCount;
            DAT_SkirmishDefinedData::ptr->attackUnitRequired[3].required = 1;
        }
        if (this->aics[aiIndex].AttMaxLaddermen != 0
            && DAT_GameState::ptr->playerDataArray[playerID].totalLaddermenTroops
                < static_cast<int>(this->aics[aiIndex].AttMaxLaddermen)) {
            ++requiredCount;
            DAT_SkirmishDefinedData::ptr->attackUnitRequired[4].required = 1;
        }
        if (this->aics[aiIndex].AttMaxTunnelers != 0
            && DAT_GameState::ptr->playerDataArray[playerID].totalTunnelerTroops
                < static_cast<int>(this->aics[aiIndex].AttMaxTunnelers)) {
            ++requiredCount;
            DAT_SkirmishDefinedData::ptr->attackUnitRequired[5].required = 1;
        }
        if (this->aics[aiIndex].AttUnitPatrolMax != 0
            && DAT_GameState::ptr->playerDataArray[playerID].totalUnitPatrolTroops
                < static_cast<int>(this->aics[aiIndex].AttUnitPatrolMax)) {
            ++requiredCount;
            DAT_SkirmishDefinedData::ptr->attackUnitRequired[6].required = 1;
        }
        if (this->aics[aiIndex].AttUnitBackupMax != 0
            && DAT_GameState::ptr->playerDataArray[playerID].totalUnitBackupTroops
                < static_cast<int>(this->aics[aiIndex].AttUnitBackupMax)) {
            ++requiredCount;
            DAT_SkirmishDefinedData::ptr->attackUnitRequired[7].required = 1;
        }
        if (this->aics[aiIndex].AttUnitEngageMax != 0
            && DAT_GameState::ptr->playerDataArray[playerID].totalUnitEngageTroops
                < static_cast<int>(this->aics[aiIndex].AttUnitEngageMax)) {
            ++requiredCount;
            DAT_SkirmishDefinedData::ptr->attackUnitRequired[8].required = 1;
        }
        if (this->aics[aiIndex].AttUnitSiegeDefMax != 0
            && DAT_GameState::ptr->playerDataArray[playerID].totalUnitSiegeDefTroops
                < static_cast<int>(this->aics[aiIndex].AttUnitSiegeDefMax)) {
            ++requiredCount;
            DAT_SkirmishDefinedData::ptr->attackUnitRequired[9].required = 1;
        }
        if (this->aics[aiIndex].AttMaxDefault != 0
            && DAT_GameState::ptr->playerDataArray[playerID].totalMaxDefaultTroops
                < static_cast<int>(this->aics[aiIndex].AttMaxDefault)) {
            ++requiredCount;
            DAT_SkirmishDefinedData::ptr->attackUnitRequired[10].required = 1;
        }

        if (requiredCount == 0) {
            return AIUBT_ATTUNITMAIN;
        }

        int ticket = SEC_RNG::instance.currentNumber2 % requiredCount;
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        for (int index = 0; index < 11; ++index) {
            if (DAT_SkirmishDefinedData::ptr->attackUnitRequired[index].required == 0) {
                continue;
            }
            if (ticket == 0) {
                return static_cast<AIUnitBehaviourType>(
                    DAT_SkirmishDefinedData::ptr->attackUnitRequired[index].unitBehaviourType);
            }
            --ticket;
        }
        return AIUBT_ATTUNITMAIN;
    }
}
}
