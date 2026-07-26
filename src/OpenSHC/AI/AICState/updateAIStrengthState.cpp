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

    /*
      this functions info is based on np123
       decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D3320
    void AICState ::updateAIStrengthState(int playerID, int aiRecruitUnitChoicePreference)

    {

        int* piVar1;

        short* psVar2;

        int _totalTroopCount;

        int _aicOffset;

        int _rng;

        int _raidUnitCount;

        BOOLEnum _teamWeak;

        BOOLEnum _outOfSupplies2;

        BOOLEnum _teamWeak2;

        BOOLEnum _outOfSupplies;

        int _totalRecruitProb;

        bool bVar3;

        int _totalDefenseTroops;

        int _aiType;

        int _currentPopulation;

        int _totalFood;

        int _aiStrengthState;

        int _aiRecruitUnitChoiceState;

        int _subtraction;

        int _aiType_2;

        int _totalRaidTroops;

        int _defTotal;

        int _currentGold_2;

        int _aiNervousActionsTracker;

        AINervousDestroyBuildingCategoryInt _cat;

        int _aiNervousActionsTracker2;

        int _aiBuildingDestroyActionsTracker;

        int _currentGold;

        int _aiTypeMin1;

        AINervousDestroyBuildingCategory _cat2;

        int _recruitProbDefensive;

        int _recruitProbRaid;

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        /*
            is human */

        if (_aiType == 0) {

            return;
        }

        if ((char)aiRecruitUnitChoicePreference == '\0') {

            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {

                return;
            }

            if (DAT_GameCore::instance.isSkirmishTrail != TRUE) {

                return;
            }

            if (DAT_GameCore::instance.currentTrailType != OpenSHC::Game::TT_EXTREME) {

                return;
            }
        }

        _aiTypeMin1 = _aiType + -1;

        _currentGold = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf];

        DAT_GameState::instance.playerDataArray[playerID].aiStrengthState = 0;

        /*
            check if current gold less than 200 */

        if (_currentGold < 200) {

            DAT_GameState::instance.playerDataArray[playerID].aiStrengthState = 0;

        }

        else {

            /*
                  2 if currentGold > 1999 else 1 */

            DAT_GameState::instance.playerDataArray[playerID].aiStrengthState = (1999 < _currentGold) + 1;
        }

        _currentPopulation = DAT_GameState::instance.playerDataArray[playerID].currentPopulation;

        if (15 < _currentPopulation) {

            /*
                  if currentPopulation more than 14 */

            if (_currentPopulation < 40) {

                piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiStrengthState;

                /*
                        if currentPopulation less than 40 */

                *piVar1 = *piVar1 + 1;

            }

            else {

                piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiStrengthState;

                /*
                        if current Population more than 40 */

                *piVar1 = *piVar1 + 2;
            }
        }

        /*
            check if total food higher than 20 */

        _totalFood = DAT_GameState::instance.playerDataArray[playerID].totalFood;

        if (20 < _totalFood) {

            if (_totalFood < 200) {

                piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiStrengthState;

                *piVar1 = *piVar1 + 1;

            }

            else {

                piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiStrengthState;

                *piVar1 = *piVar1 + 2;
            }
        }

        _totalTroopCount = DAT_GameState::instance.playerDataArray[playerID].totalAttackTroops
            + DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk
            + DAT_GameState::instance.playerDataArray[playerID].totalDefensiveTroopsUnk;

        /*
            check if troop strength above 7 */

        if (7 < _totalTroopCount) {

            /*
                  check if troop strength smaller than 40 */

            if (_totalTroopCount < 40) {

                piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiStrengthState;

                *piVar1 = *piVar1 + 2;

            }

            else {

                piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiStrengthState;

                *piVar1 = *piVar1 + 4;
            }
        }

        _aiStrengthState = DAT_GameState::instance.playerDataArray[playerID].aiStrengthState;

        if (_aiStrengthState < 3) {

            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_WEAK;

        }

        else if (_aiStrengthState < 8) {

            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_DEFAULT;

        }

        else {

            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_STRONG;
        }

        if ((DAT_GameState::instance.playerDataArray[playerID].aivCurrentPauseIndex == 1)
            && (0 < DAT_GameState::instance.playerDataArray[playerID].aivPauses[1])) {

            /*
                  if pausing at first pause
                */

            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_WEAK;
        }

        /*
            add the aiStrengthFeeling to (aiType * 169). The AI Personality struct is a
           169*4 long element of an array of 16 elements (all ai types, maybe more?) */

        _aicOffset = DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling + _aiTypeMin1 * 169;

        /*
            fetch RecruitProbRaid<Strength> for current aiType */

        _recruitProbRaid = *(int*)((int)this + _aicOffset * 4 + 0x134);

        /*
            fetch RecruitProbDefensive<Strength> */

        _recruitProbDefensive = *(int*)((int)this + _aicOffset * 4 + 0x128);

        /*
            add RecruitProbAttack<Strength> to the other two probs */

        _totalRecruitProb = *(int*)((int)this + _aicOffset * 4 + 0x140) + _recruitProbRaid + _recruitProbDefensive;

        /*
            check if recruitProb = 0 */

        if (_totalRecruitProb == 0) {

            _aiRecruitUnitChoiceState = aiRecruitUnitChoicePreference;

            if (aiRecruitUnitChoicePreference == 1) {

            LAB_004d34e9:
                /*
                        WARNING: reused variable _aiType */

                _raidUnitCount = MACRO_CALL_MEMBER(
                    OpenSHC::AI::AICState_Func::getCurrentDesiredAttackRaidUnitCount, this)(_aiTypeMin1, playerID);

                _totalDefenseTroops = DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk;

                bVar3 = (_totalDefenseTroops < _raidUnitCount);

                _subtraction = _totalDefenseTroops - _raidUnitCount;

                goto LAB_004d3515;
            }

            if (aiRecruitUnitChoicePreference == 0)
                goto LAB_004d3502;

        }

        else {

            _rng = (int)SEC_RNG::instance.currentNumber2;

            /*
                  WARNING: prob is now randomized */

            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();

            /*
                  if DAT_01fe7da8 < 4800 */

            if ((int)DAT_GameCore::instance.mapTimeInTicks < 4800) {

                _aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_DEFENSIVE;

            LAB_004d3502:
                _totalRaidTroops = DAT_GameState::instance.playerDataArray[playerID].totalDefensiveTroopsUnk;

                /*
                        true if param1 > param0 */

                _defTotal = *(int*)((int)this + _aiTypeMin1 * 676 + 0x170);

                bVar3 = (_totalRaidTroops < _defTotal);

                _subtraction = _totalRaidTroops - _defTotal;

            LAB_004d3515:
                if (bVar3 != _subtraction < 0)
                    goto LAB_004d351c;

            }

            else {

                /*
                        if RecruitProbDefensive > RandomizedRecruitProb */

                if (_rng % _totalRecruitProb < _recruitProbDefensive) {

                    _aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_DEFENSIVE;

                    goto LAB_004d3502;
                }

                if (_rng % _totalRecruitProb < _recruitProbRaid + _recruitProbDefensive) {

                    _aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_RAIDING;

                    goto LAB_004d34e9;
                }
            }

            _aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_ATTACKING;
        }

    LAB_004d351c:
        if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState != _aiRecruitUnitChoiceState) {

            DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState = _aiRecruitUnitChoiceState;
        }

        if ((char)aiRecruitUnitChoicePreference == '\0') {

            return;
        }

        if (0 < DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker) {

            _teamWeak = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::teamIsWeakRelativeToEnemy, this)(playerID, TRUE);

            if (_teamWeak == FALSE) {

                DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker = 0;

                return;
            }

            /*
                  WARNING: aiType now means currentGold */

            _currentGold_2 = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf];

            DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_WEAK;

            DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_DEFENSIVE;

            /*
                  if gold <= 500 */

            if (_currentGold_2 < 500) {

                _aiNervousActionsTracker = DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker;

                if (_aiNervousActionsTracker < 8) {

                    /*
                              destroy a good or bad thing */

                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                        playerID, OpenSHC::AI::AINDBC_FEAR_FACTOR_BUILDINGS);

                    _cat = OpenSHC::AI::AINDBC_WORKSHOPS_AND_RELIGIOUS_BUILDINGS;

                }

                else {

                    if (5 < _aiNervousActionsTracker)
                        goto LAB_004d35fb;

                    /*
                              fixme: does this line ever happen? */

                    _cat = OpenSHC::AI::AINDBC_RESOURCE_BUILDINGS;
                }

                /*
                        destroy a workshop (2) or a resource building (iron mine... bakery) (6) */

                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, (AINervousDestroyBuildingCategory)((int)(_cat)));

            }

            else {

                /*
                        if gold > 2500 and... */

                if (((2500 < _currentGold_2)
                        && (psVar2 = &DAT_GameState::instance.playerDataArray[playerID].aiStateCounter,
                            *psVar2 = *psVar2 + 1,
                            (DAT_GameState::instance.playerDataArray[playerID].aiStateCounter & 1U) != 0))
                    && (DAT_GameState::instance.playerDataArray[playerID].relativeStrengthOfTeamComparedToEnemy < 20)) {

                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::shareGoldAmongTeamMembers, this)(
                        playerID, _currentGold_2 / 10);
                }
            }

        LAB_004d35fb:
            _aiNervousActionsTracker2 = DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker;

            if (_aiNervousActionsTracker2 < 2) {

                return;
            }

            DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker = _aiNervousActionsTracker2 + -1;

            return;
        }

        /*
         *********************************************************
         * From here on we process logic for destroying buildings
         ********************************************************* */

        _aiBuildingDestroyActionsTracker
            = DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker;

        if (_aiBuildingDestroyActionsTracker < 1) {

            _teamWeak2
                = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::teamIsWeakRelativeToEnemy, this)(playerID, FALSE);

            if (_teamWeak2 != FALSE) {

                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playNervous2BikFromPlayer, this)(playerID);

                DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker = 8;

                DAT_GameState::instance.playerDataArray[playerID].aiStateCounter = 0;

                return;
            }

            _outOfSupplies = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::hasNotEnoughSupplies, this)(playerID);

            if (_outOfSupplies == FALSE) {

                return;
            }

            DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker = 8;

            return;
        }

        _outOfSupplies2 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::hasNotEnoughSupplies, this)(playerID);

        if (_outOfSupplies2 == FALSE) {

            DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker = 0;

            return;
        }

        DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[2] = 20;

        DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling = OpenSHC::AI::AIST_WEAK;

        DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState = OpenSHC::AI::AIRUC_DEFENSIVE;

        if (_aiBuildingDestroyActionsTracker == 8) {

            _cat2 = OpenSHC::AI::AINDBC_FEAR_FACTOR_BUILDINGS;

        }

        else {

            if (_aiBuildingDestroyActionsTracker == 7) {

                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_WORKSHOPS_AND_RELIGIOUS_BUILDINGS);

                piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker;

                *piVar1 = *piVar1 + -1;

                return;
            }

            if (_aiBuildingDestroyActionsTracker == 6) {

                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_GATEHOUSES_TOWERS_GUILDS);

                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_BARRACKS_MERCPOST_STABLES);

                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_WATER_BUILDINGS);

                piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker;

                *piVar1 = *piVar1 + -1;

                return;
            }

            if (_aiBuildingDestroyActionsTracker == 5) {

                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(
                    playerID, OpenSHC::AI::AINDBC_RESOURCE_BUILDINGS);

                piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker;

                *piVar1 = *piVar1 + -1;

                return;
            }

            if (_aiBuildingDestroyActionsTracker != 4)
                goto LAB_004d3707;

            _cat2 = OpenSHC::AI::AINDBC_FARMS;
        }

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::destroyAnyBuildingInCategory, this)(playerID, _cat2);

    LAB_004d3707:
        piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker;

        *piVar1 = *piVar1 + -1;

        return;
    }

}
}
