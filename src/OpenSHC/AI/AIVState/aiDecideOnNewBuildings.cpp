#include "../AIVState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F15C0
    void AIVState::aiDecideOnNewBuildings(PlayerID playerID)
    {
        int const aivID = DAT_GameState::instance.playerDataArray[playerID].aivID;
        int stepIncrement = 1;
        int isPausing = 0;
        if (aivID <= 0) {
            return;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].resourceRebuildDelay != 0) {
            ++DAT_GameState::instance.playerDataArray[playerID].resourceRebuildDelay;
            if (DAT_GameState::instance.playerDataArray[playerID].resourceRebuildDelay
                < MACRO_CALL_MEMBER(AICState_Func::getResourceRebuildDelay, DAT_AICState::ptr)(playerID)) {
                return;
            }
            DAT_GameState::instance.playerDataArray[playerID].resourceRebuildDelay = 0;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD] > 16000) {
            // rich
            stepIncrement = 2;
        } else if (DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD]
            > 5000) {
            stepIncrement = 1;
        } else {
            // poor
            ++this->aivs[aivID].aivPoorCounter;
            if (this->aivs[aivID].aivPoorCounter < this->aivs[aivID].aivPoorLimit_OR_AIC_buildInterval) {
                return;
            }
        }
        this->aivs[aivID].aivPoorCounter = 0;

        ++DAT_GameState::instance.playerDataArray[playerID].aiResourceBuildingFocusIndicator;
        if (DAT_GameState::instance.playerDataArray[playerID].aiResourceBuildingFocusIndicator >= 5) {
            DAT_GameState::instance.playerDataArray[playerID].aiResourceBuildingFocusIndicator = 0;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].aiResourceBuildingFocusIndicator == 0) {
            if (!MACRO_CALL_MEMBER(AICState_Func::shouldDestroyWoodCutterUnk, DAT_AICState::ptr)(playerID)
                && MACRO_CALL_MEMBER(AICState_Func::aiShouldBuildWoodcutter, DAT_AICState::ptr)(playerID)) {
                MACRO_CALL_MEMBER(AIVState_Func::aiPlaceWoodcuttershut, this)(playerID);
            }
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiResourceBuildingFocusIndicator == 1) {
            if (MACRO_CALL_MEMBER(AICState_Func::aiShouldBuildFarm, DAT_AICState::ptr)(playerID)
                && MACRO_CALL_MEMBER(AIVState_Func::aiPlaceFarm, this)(playerID,
                    (MappersEnum)MACRO_CALL_MEMBER(AICState_Func::aiFarmChoice, DAT_AICState::ptr)(playerID))) {
                MACRO_CALL_MEMBER(AICState_Func::setNextFarmTypeToBuild, DAT_AICState::ptr)(playerID);
            }
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiResourceBuildingFocusIndicator == 2) {
            if (MACRO_CALL_MEMBER(AICState_Func::aiShouldBuildQuarry, DAT_AICState::ptr)(playerID)) {
                MACRO_CALL_MEMBER(AIVState_Func::aiPlaceQuarryAndOxtether, this)(playerID);
            }
            if (MACRO_CALL_MEMBER(AICState_Func::aiRequiresExtraOxtethers, DAT_AICState::ptr)(playerID)) {
                MACRO_CALL_MEMBER(AIVState_Func::aiPlaceAdditionalOxtether, this)(playerID);
            }
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiResourceBuildingFocusIndicator == 3) {
            if (MACRO_CALL_MEMBER(AICState_Func::aiShouldBuildIronMine, DAT_AICState::ptr)(playerID)) {
                MACRO_CALL_MEMBER(AIVState_Func::aiPlaceIronMine, this)(playerID);
            }
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiResourceBuildingFocusIndicator == 4) {
            if (MACRO_CALL_MEMBER(AICState_Func::aiShouldBuildPitchrig, DAT_AICState::ptr)(playerID)) {
                MACRO_CALL_MEMBER(AIVState_Func::aiPlacePitchrig, this)(playerID);
            }
        }

        if (DAT_GameState::instance.playerDataArray[playerID].aivCurrentPause != 0) {
            if (stepIncrement > 1) {
                DAT_GameState::instance.playerDataArray[playerID].aivCurrentPause = 0;
                isPausing = 1;
            } else {
                --DAT_GameState::instance.playerDataArray[playerID].aivCurrentPause;
                isPausing = 1;
            }
        } else {
            int const pauseStep
                = DAT_GameState::instance.playerDataArray[playerID]
                      .aivPauses[DAT_GameState::instance.playerDataArray[playerID].aivCurrentPauseIndex];
            if (pauseStep > 0 && this->aivs[aivID].currentStepGoal >= pauseStep) {
                DAT_GameState::instance.playerDataArray[playerID].aivCurrentPause
                    = DAT_GameState::instance.playerDataArray[playerID].aivPauseDelay;
                ++DAT_GameState::instance.playerDataArray[playerID].aivCurrentPauseIndex;
                return;
            }
            // the step goal can advance by 2 when the player is rich
            this->aivs[aivID].currentStepGoal += stepIncrement;
        }

        if (this->aivs[aivID].aivSubType == 0) {
            MACRO_CALL_MEMBER(AIVState_Func::executeDefaultCastleAIV, this)(playerID, isPausing);
        } else if (!MACRO_CALL_MEMBER(AICState_Func::destroyHouse, DAT_AICState::ptr)(playerID)) {
            for (int step = 1; step <= this->aivs[aivID].totalSteps && step <= this->aivs[aivID].currentStepGoal;
                ++step) {
                if (MACRO_CALL_MEMBER(AIVState_Func::aiPlaceAIVBuilding, this)(playerID, step, isPausing)) {
                    break;
                }
            }
        }
        MACRO_CALL_MEMBER(AIVState_Func::aiPlaceFlag, this)(playerID);
        MACRO_CALL_MEMBER(AIVState_Func::aiPlaceBrazier, this)(playerID);
    }

}
}
