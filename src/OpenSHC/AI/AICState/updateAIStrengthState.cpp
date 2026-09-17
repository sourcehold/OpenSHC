#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/AI/AINervousDestroyBuildingCategory.hpp"
#include "OpenSHC/AI/AINervousDestroyBuildingCategoryInt.hpp"
#include "OpenSHC/AI/AIRecruitUnitChoice.hpp"
#include "OpenSHC/AI/AIStrengthType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AINervousDestroyBuildingCategory;
    using OpenSHC::AI::AINervousDestroyBuildingCategoryInt;
    using OpenSHC::AI::AIRecruitUnitChoice;
    using OpenSHC::AI::AIStrengthType;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Game::TrailType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D3320
    void AICState::updateAIStrengthState(int playerID, int aiRecruitUnitChoicePreference)
    {
        int _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType == 0)
            return;

        if ((char)aiRecruitUnitChoicePreference == 0) {
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
                return;
            if (DAT_GameCore::instance.isSkirmishTrail != TRUE)
                return;
            if (DAT_GameCore::instance.currentTrailType != OpenSHC::Game::TT_EXTREME)
                return;
        }

        int _aicIndex = _aiType - 1;

        int _currentGold = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf];
        DAT_GameState::instance.playerDataArray[playerID].aiStrengthState = 0;
        if (_currentGold < 200)
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthState = 0;
        else if (_currentGold < 2000)
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthState = 1;
        else
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthState = 2;

        int _currentPopulation = DAT_GameState::instance.playerDataArray[playerID].currentPopulation;
        if (_currentPopulation >= 15) {
            if (_currentPopulation < 40)
                DAT_GameState::instance.playerDataArray[playerID].aiStrengthState += 1;
            else
                DAT_GameState::instance.playerDataArray[playerID].aiStrengthState += 2;
        }

        int _totalFood = DAT_GameState::instance.playerDataArray[playerID].totalFood;
        if (_totalFood >= 20) {
            if (_totalFood < 200)
                DAT_GameState::instance.playerDataArray[playerID].aiStrengthState += 1;
            else
                DAT_GameState::instance.playerDataArray[playerID].aiStrengthState += 2;
        }

        int _totalTroopCount = DAT_GameState::instance.playerDataArray[playerID].totalAttackTroops
            + DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk
            + DAT_GameState::instance.playerDataArray[playerID].totalDefensiveTroopsUnk;
        if (_totalTroopCount >= 8) {
            if (_totalTroopCount < 40)
                DAT_GameState::instance.playerDataArray[playerID].aiStrengthState += 2;
            else
                DAT_GameState::instance.playerDataArray[playerID].aiStrengthState += 4;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].aiStrengthState <= 2)
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_WEAK;
        else if (DAT_GameState::instance.playerDataArray[playerID].aiStrengthState <= 7)
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_DEFAULT;
        else
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_STRONG;

        // while the first AIV pause is still running, the AI always feels weak
        if (DAT_GameState::instance.playerDataArray[playerID].aivCurrentPauseIndex == 1
            && DAT_GameState::instance.playerDataArray[playerID]
                    .aivPauses[DAT_GameState::instance.playerDataArray[playerID].aivCurrentPauseIndex]
                > 0)
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_WEAK;

        // the three recruitProb* triples are laid out as Default, Weak, Strong, matching AIStrengthType
        int _aiStrengthFeeling = DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling;
        int _recruitProbDefensive = (&this->aics[_aicIndex].recruitProbDefDefault)[_aiStrengthFeeling];
        int _recruitProbAttack = (&this->aics[_aicIndex].recruitProbAttackDefault)[_aiStrengthFeeling];
        int _recruitProbRaid = (&this->aics[_aicIndex].recruitProbRaidDefault)[_aiStrengthFeeling];
        int _totalRecruitProb = _recruitProbAttack + _recruitProbRaid + _recruitProbDefensive;

        int _aiRecruitUnitChoice;
        if (_totalRecruitProb != 0) {
            int _random = SEC_RNG::instance.currentNumber2 % _totalRecruitProb;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();

            if ((int)DAT_GameCore::instance.mapTimeInTicks < 4800)
                _aiRecruitUnitChoice = OpenSHC::AI::AIRUC_DEFENSIVE;
            else if (_random < _recruitProbDefensive)
                _aiRecruitUnitChoice = OpenSHC::AI::AIRUC_DEFENSIVE;
            else if (_random < _recruitProbRaid + _recruitProbDefensive)
                _aiRecruitUnitChoice = OpenSHC::AI::AIRUC_RAIDING;
            else
                _aiRecruitUnitChoice = OpenSHC::AI::AIRUC_ATTACKING;
        } else {
            _aiRecruitUnitChoice = aiRecruitUnitChoicePreference;
        }

        if (_aiRecruitUnitChoice == OpenSHC::AI::AIRUC_RAIDING) {
            if (DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk
                >= MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::getCurrentDesiredAttackRaidUnitCount, this)(
                    _aicIndex, playerID))
                _aiRecruitUnitChoice = OpenSHC::AI::AIRUC_ATTACKING;
        } else if (_aiRecruitUnitChoice == OpenSHC::AI::AIRUC_DEFENSIVE) {
            if (DAT_GameState::instance.playerDataArray[playerID].totalDefensiveTroopsUnk
                >= this->aics[_aicIndex].DefTotal)
                _aiRecruitUnitChoice = OpenSHC::AI::AIRUC_ATTACKING;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState != _aiRecruitUnitChoice)
            DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState = _aiRecruitUnitChoice;

        if ((char)aiRecruitUnitChoicePreference == 0)
            return;

        if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0) {
            if (!MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::teamIsWeakRelativeToEnemy, this)(playerID, TRUE)) {
                DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker = 0;
                return;
            }

            int _gold = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf];
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_WEAK;
            DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_DEFENSIVE;

            if (_gold > 500) {
                if (_gold > 2500) {
                    DAT_GameState::instance.playerDataArray[playerID].aiStateCounter++;
                    if ((DAT_GameState::instance.playerDataArray[playerID].aiStateCounter & 1)
                        && DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy
                            <= 20) {
                        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::shareGoldAmongTeamMembers, this)(
                            playerID, _gold / 10);
                    }
                }
            } else if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker <= 7) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_FEAR_FACTOR_BUILDINGS);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_WORKSHOPS_AND_RELIGIOUS_BUILDINGS);
            } else if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker <= 5) {
                // unreachable in the original as well: anything <= 5 is already handled by the <= 7 branch
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_RESOURCE_BUILDINGS);
            }

            if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 1)
                DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker--;
            return;
        }

        int _destroyChoice = DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker;
        if (_destroyChoice > 0) {
            if (!MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::hasNotEnoughSupplies, this)(playerID)) {
                DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker = 0;
                return;
            }

            DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[2] = 20;
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_WEAK;
            DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_DEFENSIVE;

            if (_destroyChoice == 8) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_FEAR_FACTOR_BUILDINGS);
            } else if (_destroyChoice == 7) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_WORKSHOPS_AND_RELIGIOUS_BUILDINGS);
            } else if (_destroyChoice == 6) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_GATEHOUSES_TOWERS_GUILDS);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_BARRACKS_MERCPOST_STABLES);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_WATER_BUILDINGS);
            } else if (_destroyChoice == 5) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_RESOURCE_BUILDINGS);
            } else if (_destroyChoice == 4) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_FARMS);
            }

            DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker--;
        } else if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::teamIsWeakRelativeToEnemy, this)(
                       playerID, FALSE)) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playNervous2BikFromPlayer, this)(playerID);
            DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker = 8;
            DAT_GameState::instance.playerDataArray[playerID].aiStateCounter = 0;
        } else if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::hasNotEnoughSupplies, this)(playerID)) {
            DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker = 8;
        }
    }
}
}
