#include "../AICState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIC/AITargetChoice.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CACB0
    void AICState::setTargetForTribeBasedOnTargetChoiceLogic(int owner, int tribe)
    {
        if (DAT_GameState::instance.playerDataArray[owner].aiType == 0) {
            return;
        }

        int aicIndex = DAT_GameState::instance.playerDataArray[owner].aiType - 1;

        int targetPlayer = 0;
        int minDistance = 10000;
        int maxGold = 0;
        int minPoints = 1000000;
        int ownerKeepX = DAT_GameState::instance.playerDataArray[owner].campground.xEntry;
        int ownerKeepY = DAT_GameState::instance.playerDataArray[owner].campground.yEntry;
        for (int player = 1; player < 9; player++) {
            if (DAT_GameState::instance.mapAndTime.playerTeams[player]
                == DAT_GameState::instance.mapAndTime.playerTeams[owner]) {
                continue;
            }
            if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(player)
                == 0) {
                continue;
            }

            MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                DAT_DirectionAlgorithmState::ptr)(DAT_GameState::instance.playerDataArray[player].campground.xEntry,
                DAT_GameState::instance.playerDataArray[player].campground.yEntry, ownerKeepX, ownerKeepY);

            if (this->aics[aicIndex].TargetChoice == AIC::AITC_PLAYER) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] != -1
                    && DAT_DirectionAlgorithmState::instance.distanceHigh <= minDistance) {
                    minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    targetPlayer = player;
                }
            } else if (this->aics[aicIndex].TargetChoice == AIC::AITC_CLOSEST) {
                if (DAT_DirectionAlgorithmState::instance.distanceHigh <= minDistance) {
                    minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    targetPlayer = player;
                }
            } else if (this->aics[aicIndex].TargetChoice == AIC::AITC_GOLD) {
                if (DAT_GameState::instance.playerDataArray[player].currentResources[Game::Resources::RT_GOLD]
                    >= maxGold) {
                    maxGold
                        = DAT_GameState::instance.playerDataArray[player].currentResources[Game::Resources::RT_GOLD];
                    targetPlayer = player;
                }
            } else if (this->aics[aicIndex].TargetChoice == AIC::AITC_BALANCED) {
                int points = DAT_GameState::instance.playerDataArray[player].currentPopulation * 5
                    + DAT_GameState::instance.playerDataArray[player].totalTroopValue
                    + DAT_GameState::instance.playerDataArray[player].currentResources[Game::Resources::RT_GOLD] / 100
                    + DAT_DirectionAlgorithmState::instance.distanceHigh * 2;
                if (points <= minPoints) {
                    minPoints = points;
                    targetPlayer = player;
                }
            }
        }

        if (targetPlayer == 0) {
            // Fallback: pick the closest enemy with a living lord
            for (int player = 1; player < 9; player++) {
                if (DAT_GameState::instance.mapAndTime.playerTeams[player]
                    == DAT_GameState::instance.mapAndTime.playerTeams[owner]) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(player)
                    == 0) {
                    continue;
                }

                MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_GameState::instance.playerDataArray[player].campground.xEntry,
                    DAT_GameState::instance.playerDataArray[player].campground.yEntry, ownerKeepX, ownerKeepY);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh <= minDistance) {
                    minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    targetPlayer = player;
                }
            }

            if (targetPlayer == 0) {
                return;
            }
        }

        DAT_TribesState::instance.tribes[tribe].targetPlayer_outpost = (short)targetPlayer;
    }

}
}
