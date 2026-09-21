#include "../AICState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIC/AITargetChoice.hpp"
#include "OpenSHC/AI/AIC/AITargetChoiceInt.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::AI::AIC::AITargetChoice;
    using OpenSHC::AI::AIC::AITargetChoiceInt;
    using OpenSHC::Game::Player::PlayerData;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4680
    void AICState::selectAttackTarget(int playerID)
    {
        int selectedPlayerID = 0;
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL) {
            return;
        }

        int aicIndex = aiType - 1;
        int fromX = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry;
        int fromY = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry;
        int lowestDistance = 10000;
        int highestGold = 0;
        int lowestPoints = 1000000;

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeNervousness, this)(playerID);

        // Drop a pending request if the asking player's lord is dead
        if ((DAT_GameState::instance.playerDataArray[playerID].requestStateUnk == 2
                || DAT_GameState::instance.playerDataArray[playerID].requestStateUnk == 1)
            && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
                   DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk)
                == 0) {
            DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 0;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].requestStateUnk == 2) {
            DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID = 0;
            return;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].requestStateUnk == 1) {
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
                    DAT_GameState::instance.playerDataArray[playerID].requestedAttackTargetUnk)
                != 0) {
                DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID
                    = DAT_GameState::instance.playerDataArray[playerID].requestedAttackTargetUnk;
                return;
            }
            DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 0;
        }

        for (int i = 1; i < 9; i++) {
            if (DAT_GameState::instance.mapAndTime.playerTeams[i]
                == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                continue;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(i)
                == 0) {
                continue;
            }

            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                DAT_DirectionAlgorithmState::ptr)(DAT_GameState::instance.playerDataArray[i].campground.xEntry,
                DAT_GameState::instance.playerDataArray[i].campground.yEntry, fromX, fromY);

            int targetChoice = this->aics[aicIndex].TargetChoice;
            if (targetChoice == OpenSHC::AI::AIC::AITC_PLAYER) {
                // Closest human player
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] != -1) {
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh <= lowestDistance) {
                        lowestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                        selectedPlayerID = i;
                    }
                }
            } else if (targetChoice == OpenSHC::AI::AIC::AITC_CLOSEST) {
                if (DAT_DirectionAlgorithmState::instance.distanceHigh <= lowestDistance) {
                    lowestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    selectedPlayerID = i;
                }
            } else if (targetChoice == OpenSHC::AI::AIC::AITC_GOLD) {
                if (DAT_GameState::instance.playerDataArray[i].currentResources[0xf] >= highestGold) {
                    highestGold = DAT_GameState::instance.playerDataArray[i].currentResources[0xf];
                    selectedPlayerID = i;
                }
            } else if (targetChoice == OpenSHC::AI::AIC::AITC_BALANCED) {
                int points = DAT_GameState::instance.playerDataArray[i].currentPopulation * 5
                    + DAT_GameState::instance.playerDataArray[i].totalTroopValue
                    + DAT_GameState::instance.playerDataArray[i].currentResources[0xf] / 100
                    + DAT_DirectionAlgorithmState::instance.distanceHigh * 2;
                if (points <= lowestPoints) {
                    lowestPoints = points;
                    selectedPlayerID = i;
                }
            }
        }

        // Fall back to the closest enemy
        if (selectedPlayerID == 0) {
            for (int i = 1; i < 9; i++) {
                if (DAT_GameState::instance.mapAndTime.playerTeams[i]
                    == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(i)
                    == 0) {
                    continue;
                }

                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_GameState::instance.playerDataArray[i].campground.xEntry,
                    DAT_GameState::instance.playerDataArray[i].campground.yEntry, fromX, fromY);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh <= lowestDistance) {
                    lowestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    selectedPlayerID = i;
                }
            }

            if (selectedPlayerID == 0) {
                return;
            }
        }

        DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID_2Unk = selectedPlayerID;
        DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID = selectedPlayerID;
    }
}
}
