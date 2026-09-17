#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D49E0
    void AICState::updateAIPlayerState(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL)
            return;
        int _aicIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;

        // an ally asked for help and is still alive: drop everything and go to their keep
        if (DAT_GameState::instance.playerDataArray[playerID].requestStateUnk != 1
            && DAT_GameState::instance.playerDataArray[playerID].requestStateUnk == 2
            && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
                DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk)) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::clearRallyFlagOnAllAIAttackTribes, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToPlayerIDsKeepIfPossible, this)(
                playerID, DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk);
            return;
        }

        int _aiPlayerState = DAT_GameState::instance.playerDataArray[playerID].aiPlayerState;
        if (_aiPlayerState == 0) {
            if (!MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiShouldAttackOrWaitForTeamCoordination, this)(
                    playerID)) {
                // send own units back to keep or campfire
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRetreatUnits, this)(playerID);
                return;
            }

            // proceed with attack
            DAT_GameState::instance.playerDataArray[playerID].attackTicker = 0;
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 1;
            DAT_GameState::instance.playerDataArray[playerID].unitPatrolRecommandRelatedDelayValue = 0;
            DAT_GameState::instance.playerDataArray[playerID].aiCoordinatedAttackPatience = 0;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAttackCoordinationLevel, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setCurrentAttackStrength, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setCurrentAttackRaidParameter, this)(playerID);
            // fixme: struct layout. This looks like an int[10][8] attack tracker starting at
            // attackedByPlayerArrayUnk (0x2BDC) and ending where aivUnitLocationSlots begins (0x2D1C).
            (&DAT_GameState::instance.playerDataArray[DAT_GameState::instance.playerDataArray[playerID]
                                                          .attackedPlayerID]
                    .attackedByPlayerArrayUnk)[playerID * 8]++;
        } else if ((MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::hasNoTroopsOrAllAreDiggers, this)(playerID)
                       && _aiPlayerState != 9)
            || (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0 && _aiPlayerState <= 5)
            || DAT_GameState::instance.playerDataArray[playerID].attackTicker >= 200) {
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 8;
        }

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::clearRallyFlagOnAllAIAttackTribes, this)(playerID);

        if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
                DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID)) {
            // attacked player is dead
            if (DAT_GameState::instance.playerDataArray[playerID].aiPlayerState <= 3) {
                DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 9;
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::disbandAIPlayerSiegeUnits, this)(playerID);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::removeSiegeBuildings, DAT_BuildingsState::ptr)(
                    DAT_GameState::instance.playerDataArray[playerID].currentAttackWave, playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addEngineersToTribe, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiReassignTunnelersToTribe, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::findAttackTribePositionAndPathToDefenses, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::makeUnitsGoDefensiveAndBackToSomeLocation, this)(
                    playerID);
            } else if (DAT_GameState::instance.playerDataArray[playerID].aiPlayerState < 7) {
                DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 7;
            }
        }

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::clearOutdatedAITribes, this)(playerID);

        _aiPlayerState = DAT_GameState::instance.playerDataArray[playerID].aiPlayerState;

        if (_aiPlayerState == 1) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recreateEngineersTribe, this)(playerID);
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::initializeGatePathfindingForOwner,
                DAT_BuildingsState::ptr)(playerID);
            // computes the first siege location for units
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeEnemyKeepApproachTile, this)(playerID);
            if (DAT_GameState::instance.playerDataArray[playerID].shortestDistanceTile > 0) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::moveAttackTribesToLocations, this)(playerID);
                return;
            }
            // no approach tile found: back to idle
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 0;
            return;
        }

        if (_aiPlayerState == 2) {
            // gathering: wait until enough of the attack force has rallied
            if (!MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiChoiceAttForceRallyPercentage, this)(playerID))
                return;
            // send the attacking units to move closer
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 3;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::useAITribe_0x12_toPlaceSiegeTentsAndAssignEngineers, this)(
                playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIPathCostToAttackedKeep, this)(playerID, 1);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeAttackPossibilities, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setNextMoveLocationForUnits, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::giveMoveCommandToAttackTribes, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::useAITribe_0xe_toPlaceTunnels, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::removeOrganismsAndSetMoveDestinationPairs, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::commandFourTribesToMove, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playTauntToAttackedPlayerBikFromPlayer, this)(playerID);
            return;
        }

        if (_aiPlayerState == 3) {
            // send the attacking units closer to the castle
            DAT_GameState::instance.playerDataArray[playerID].attackTicker++;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::moveAttackingUnitsToNextRallyPoint, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendAITribe_0xf_toAttackPatrol, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiCommandSiegeEngineTribes, this)(playerID);
            if (!MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::processAttForceRallyPercentage, this)(playerID))
                return;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIPathCostToAttackedKeep, this)(playerID, 0);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeAttackPossibilities, this)(playerID);
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 4;
            DAT_GameState::instance.playerDataArray[playerID].attackAssaultDelayRelatedValue = 0;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiCommandTribe12AggressiveApproach, this)(playerID);
            return;
        }

        if (_aiPlayerState == 4) {
            // siege: wait AttAssaultDelay (skipped without siege engines) before the assault
            DAT_GameState::instance.playerDataArray[playerID].attackTicker++;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::moveAttackingUnitsToNextRallyPoint, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendAITribe_0xf_toAttackPatrol, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiCommandSiegeEngineTribes, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendTribeToAttack, this)(playerID);
            if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::countSiegeEngineUnits, this)(playerID) <= 0)
                DAT_GameState::instance.playerDataArray[playerID].attackAssaultDelayRelatedValue = 100;
            DAT_GameState::instance.playerDataArray[playerID].attackAssaultDelayRelatedValue++;
            if (DAT_GameState::instance.playerDataArray[playerID].attackAssaultDelayRelatedValue
                <= this->aics[_aicIndex].AttAssaultDelay)
                return;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIPathCostToAttackedKeep, this)(playerID, 0);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeAttackPossibilities, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX,
                DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY, 0x14);
            if (!MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep, DAT_GameState::ptr)(
                    playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID)) {
                // castle is closed: attack the walls
                DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 5;
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiCommandTribe12AggressiveApproach, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiCommandTribe11StandGroundToGate, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiCommandTribe13DefensiveWave, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIPathCostToAttackedKeep, this)(playerID, 0);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeAttackPossibilities, this)(playerID);
                DAT_GameState::instance.playerDataArray[playerID].unknownCounter01 = 0;
                return;
            }
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 6;
            return;
        }

        if (_aiPlayerState == 5) {
            // attack walls
            if (DAT_GameState::instance.playerDataArray[playerID].shortestDistanceTile <= 0)
                DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 0;
            DAT_GameState::instance.playerDataArray[playerID].unknownCounter01++;
            DAT_GameState::instance.playerDataArray[playerID].attackTicker++;
            DAT_GameState::instance.playerDataArray[playerID].someResourceCounter = 0;
            if (DAT_GameState::instance.playerDataArray[playerID].unknownCounter01 >= 4) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIPathCostToAttackedKeep, this)(playerID, 0);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeAttackPossibilities, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiCommandWallAssaultTribes, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiCommandSiegeEngineTribes, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setTribe0x11ToAggressiveAndAttackIfConditionMet, this)(
                    playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setEightTribe0xc0TribesToAggressiveAndAttack, this)(
                    playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendTribeToAttack, this)(playerID);
                DAT_GameState::instance.playerDataArray[playerID].unknownCounter01 = 0;
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::removeOrganismsAndSetMoveDestinationPairs, this)(
                    playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::commandFourTribesToMove, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setTribe0xCtoAggressiveAndAttack, this)(playerID);
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setTribe0xbToAggressiveAndAttack, this)(playerID);
            }
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendAITribe_0xf_toAttackPatrol, this)(playerID);
            if (!MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep, DAT_GameState::ptr)(
                    playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID)
                && !MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::canUnitsNavigateFromKeepToKeep, DAT_GameState::ptr)(
                    playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID))
                return;
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 6;
            return;
        }

        if (_aiPlayerState == 6) {
            // enemy castle breached
            if (DAT_GameState::instance.playerDataArray[playerID].shortestDistanceTile <= 0)
                DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 0;
            DAT_GameState::instance.playerDataArray[playerID].attackTicker++;
            int _attackedPlayerID = DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;
            DAT_GameState::instance.playerDataArray[playerID].someResourceCounter = 0;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::calculateAttackVectorsToCampFireOfPlayer,
                DAT_GameState::ptr)(_attackedPlayerID);
            if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToAttackBreachedCastle, this)(playerID))
                return;
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep, DAT_GameState::ptr)(
                    playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID))
                return;
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::canUnitsNavigateFromKeepToKeep, DAT_GameState::ptr)(
                    playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID))
                return;
            // the breach got closed again: back to attacking the walls
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 5;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIPathCostToAttackedKeep, this)(playerID, 0);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeAttackPossibilities, this)(playerID);
            DAT_GameState::instance.playerDataArray[playerID].unknownCounter01 = 0;
            return;
        }

        if (_aiPlayerState == 7) {
            // target died mid-attack: linger for AttUnitPatrolRecommandDelay, then retreat
            DAT_GameState::instance.playerDataArray[playerID].unitPatrolRecommandRelatedDelayValue++;
            if (DAT_GameState::instance.playerDataArray[playerID].unitPatrolRecommandRelatedDelayValue
                <= this->aics[_aicIndex].AttUnitPatrolRecommandDelay)
                return;
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 9;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::disbandAIPlayerSiegeUnits, this)(playerID);
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::removeSiegeBuildings, DAT_BuildingsState::ptr)(
                DAT_GameState::instance.playerDataArray[playerID].currentAttackWave, playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addEngineersToTribe, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiReassignTunnelersToTribe, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::findAttackTribePositionAndPathToDefenses, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::makeUnitsGoDefensiveAndBackToSomeLocation, this)(playerID);
            return;
        }

        if (_aiPlayerState == 8) {
            // retreat from attack
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 9;
            DAT_GameState::instance.playerDataArray[playerID].attackTicker = 0;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::disbandAIPlayerSiegeUnits, this)(playerID);
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::removeSiegeBuildings, DAT_BuildingsState::ptr)(
                DAT_GameState::instance.playerDataArray[playerID].currentAttackWave, playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addEngineersToTribe, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiReassignTunnelersToTribe, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::findAttackTribePositionAndPathToDefenses, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::makeUnitsGoDefensiveAndBackToSomeLocation, this)(playerID);
            if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker <= 0)
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playAnger1BikFromPlayer, this)(playerID);
            return;
        }

        if (_aiPlayerState == 9) {
            // retreating: back to idle once the units are home (or after 20 ticks)
            DAT_GameState::instance.playerDataArray[playerID].attackTicker++;
            if (DAT_GameState::instance.playerDataArray[playerID].attackTicker < 20
                && !MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::percentageNonMovingTribesGTEAICSpecified, this)(
                    playerID)
                && !MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::hasNoTroopsOrAllAreDiggers, this)(playerID))
                return;
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 0;
        }
    }

}
}
