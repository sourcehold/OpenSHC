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
    void AICState ::updateAIStrengthState(int playerID, int aiRecruitUnitChoicePreference)
    {
        int _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType == 0)
            return;

        if ((char)aiRecruitUnitChoicePreference == '\0') {
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
                return;
            if (DAT_GameCore::instance.isSkirmishTrail != TRUE)
                return;
            if (DAT_GameCore::instance.currentTrailType != OpenSHC::Game::TT_EXTREME)
                return;
        }

        int _aiTypeMin1 = _aiType + -1;
        int _currentGold = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf];
        DAT_GameState::instance.playerDataArray[playerID].aiStrengthState = 0;

        if (_currentGold >= 200)
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthState = (1999 < _currentGold) + 1;

        int _currentPopulation = DAT_GameState::instance.playerDataArray[playerID].currentPopulation;
        if (15 < _currentPopulation) {
            int* piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiStrengthState;
            if (_currentPopulation < 40)
                *piVar1 = *piVar1 + 1;
            else
                *piVar1 = *piVar1 + 2;
        }

        int _totalFood = DAT_GameState::instance.playerDataArray[playerID].totalFood;
        if (20 < _totalFood) {
            int* piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiStrengthState;
            if (_totalFood < 200)
                *piVar1 = *piVar1 + 1;
            else
                *piVar1 = *piVar1 + 2;
        }

        int _totalTroopCount = DAT_GameState::instance.playerDataArray[playerID].totalAttackTroops
            + DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk
            + DAT_GameState::instance.playerDataArray[playerID].totalDefensiveTroopsUnk;
        if (7 < _totalTroopCount) {
            int* piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiStrengthState;
            if (_totalTroopCount < 40)
                *piVar1 = *piVar1 + 2;
            else
                *piVar1 = *piVar1 + 4;
        }

        int _aiStrengthState = DAT_GameState::instance.playerDataArray[playerID].aiStrengthState;
        if (_aiStrengthState < 3)
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_WEAK;
        else if (_aiStrengthState < 8)
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_DEFAULT;
        else
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_STRONG;

        if ((DAT_GameState::instance.playerDataArray[playerID].aivCurrentPauseIndex == 1)
            && (0 < DAT_GameState::instance.playerDataArray[playerID].aivPauses[1]))
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_WEAK;

        int _aicOffset = DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling + _aiTypeMin1 * 169;
        int _recruitProbRaid = *(int*)((int)this + _aicOffset * 4 + 0x134);
        int _recruitProbDefensive = *(int*)((int)this + _aicOffset * 4 + 0x128);
        int _totalRecruitProb = *(int*)((int)this + _aicOffset * 4 + 0x140) + _recruitProbRaid + _recruitProbDefensive;

        int _aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_ATTACKING;
        bool bVar3 = false;
        int _subtraction = 0;
        bool _needsCheck = false;

        if (_totalRecruitProb == 0) {
            _aiRecruitUnitChoiceState = aiRecruitUnitChoicePreference;
            if (aiRecruitUnitChoicePreference == 1) {
                int _raidUnitCount = MACRO_CALL_MEMBER(
                    OpenSHC::AI::AICState_Func::getCurrentDesiredAttackRaidUnitCount, this)(_aiTypeMin1, playerID);
                int _totalDefTroops = DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk;
                bVar3 = (_totalDefTroops < _raidUnitCount);
                _subtraction = _totalDefTroops - _raidUnitCount;
                _needsCheck = true;
            } else if (aiRecruitUnitChoicePreference == 0) {
                int _totalRaidTroops = DAT_GameState::instance.playerDataArray[playerID].totalDefensiveTroopsUnk;
                int _defTotal = *(int*)((int)this + _aiTypeMin1 * 676 + 0x170);
                bVar3 = (_totalRaidTroops < _defTotal);
                _subtraction = _totalRaidTroops - _defTotal;
                _needsCheck = true;
            }
        } else {
            int _rng = (int)SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();

            if ((int)DAT_GameCore::instance.mapTimeInTicks < 4800) {
                _aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_DEFENSIVE;
                int _totalRaidTroops = DAT_GameState::instance.playerDataArray[playerID].totalDefensiveTroopsUnk;
                int _defTotal = *(int*)((int)this + _aiTypeMin1 * 676 + 0x170);
                bVar3 = (_totalRaidTroops < _defTotal);
                _subtraction = _totalRaidTroops - _defTotal;
                _needsCheck = true;
            } else if (_rng % _totalRecruitProb < _recruitProbDefensive) {
                _aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_DEFENSIVE;
                int _totalRaidTroops = DAT_GameState::instance.playerDataArray[playerID].totalDefensiveTroopsUnk;
                int _defTotal = *(int*)((int)this + _aiTypeMin1 * 676 + 0x170);
                bVar3 = (_totalRaidTroops < _defTotal);
                _subtraction = _totalRaidTroops - _defTotal;
                _needsCheck = true;
            } else if (_rng % _totalRecruitProb < _recruitProbRaid + _recruitProbDefensive) {
                _aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_RAIDING;
                int _raidUnitCount = MACRO_CALL_MEMBER(
                    OpenSHC::AI::AICState_Func::getCurrentDesiredAttackRaidUnitCount, this)(_aiTypeMin1, playerID);
                int _totalDefTroops = DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk;
                bVar3 = (_totalDefTroops < _raidUnitCount);
                _subtraction = _totalDefTroops - _raidUnitCount;
                _needsCheck = true;
            }
        }

        if (!_needsCheck || !(bVar3 == (_subtraction < 0)))
            _aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_ATTACKING;

        if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState != _aiRecruitUnitChoiceState)
            DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState = _aiRecruitUnitChoiceState;

        if ((char)aiRecruitUnitChoicePreference == '\0')
            return;

        if (0 < DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker) {
            BOOLEnum _teamWeak = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::teamIsWeakRelativeToEnemy, this)(playerID, TRUE);
            if (_teamWeak == FALSE) {
                DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker = 0;
                return;
            }
            int _currentGold_2 = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf];
            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_WEAK;
            DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_DEFENSIVE;

            if (_currentGold_2 < 500) {
                int _aiNervAct = DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker;
                if (_aiNervAct < 8) {
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                        playerID, OpenSHC::AI::AINDBC_FEAR_FACTOR_BUILDINGS);
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                        playerID, OpenSHC::AI::AINDBC_WORKSHOPS_AND_RELIGIOUS_BUILDINGS);
                } else if (!(5 < _aiNervAct)) {
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                        playerID, OpenSHC::AI::AINDBC_RESOURCE_BUILDINGS);
                }
            } else {
                short* psVar2 = &DAT_GameState::instance.playerDataArray[playerID].aiStateCounter;
                *psVar2 = *psVar2 + 1;
                if ((2500 < _currentGold_2)
                    && ((DAT_GameState::instance.playerDataArray[playerID].aiStateCounter & 1U) != 0)
                    && (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy < 20)) {
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::shareGoldAmongTeamMembers, this)(
                        playerID, _currentGold_2 / 10);
                }
            }

            int _aiNervAct2 = DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker;
            if (_aiNervAct2 < 2)
                return;
            DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker = _aiNervAct2 + -1;
            return;
        }

        int _aiBuildDestroyTracker = DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker;

        if (_aiBuildDestroyTracker < 1) {
            BOOLEnum _teamWeak2 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::teamIsWeakRelativeToEnemy, this)(playerID, FALSE);
            if (_teamWeak2 != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playNervous2BikFromPlayer, this)(playerID);
                DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker = 8;
                DAT_GameState::instance.playerDataArray[playerID].aiStateCounter = 0;
                return;
            }
            BOOLEnum _outOfSupplies = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::hasNotEnoughSupplies, this)(playerID);
            if (_outOfSupplies == FALSE)
                return;
            DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker = 8;
            return;
        }

        BOOLEnum _outOfSupplies2 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::hasNotEnoughSupplies, this)(playerID);
        if (_outOfSupplies2 == FALSE) {
            DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker = 0;
            return;
        }

        DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[2] = 20;
        DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_WEAK;
        DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_DEFENSIVE;

        if (_aiBuildDestroyTracker == 8) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                playerID, OpenSHC::AI::AINDBC_FEAR_FACTOR_BUILDINGS);
        } else if (_aiBuildDestroyTracker == 7) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                playerID, OpenSHC::AI::AINDBC_WORKSHOPS_AND_RELIGIOUS_BUILDINGS);
            DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker--;
            return;
        } else if (_aiBuildDestroyTracker == 6) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                playerID, OpenSHC::AI::AINDBC_GATEHOUSES_TOWERS_GUILDS);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                playerID, OpenSHC::AI::AINDBC_BARRACKS_MERCPOST_STABLES);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                playerID, OpenSHC::AI::AINDBC_WATER_BUILDINGS);
            DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker--;
            return;
        } else if (_aiBuildDestroyTracker == 5) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                playerID, OpenSHC::AI::AINDBC_RESOURCE_BUILDINGS);
            DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker--;
            return;
        } else if (_aiBuildDestroyTracker == 4) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                playerID, OpenSHC::AI::AINDBC_FARMS);
        }

        DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker--;
    }
}
}
