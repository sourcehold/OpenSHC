#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // Helper shared by state 4 (canNavigate==FALSE) and state 6 (canUnitsNavigate==FALSE)
    __forceinline static void recomputeAndReset(OpenSHC::AI::AICState* pThis, int playerID)
    {
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIPathCostToAttackedKeep, pThis)(playerID, 0);
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeAttackPossibilities, pThis)(playerID);
        DAT_GameState::instance.playerDataArray[playerID].unknownCounter01 = 0;
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x004D49E0
    void AICState ::updateAIPlayerState(int playerID)
    {
        AITypeInt AVar4 = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (AVar4 == OpenSHC::AI::AIT_NULL)
            return;

        int _aiType = AVar4 + ~OpenSHC::AI::AIT_NULL;

        int iVar5 = DAT_GameState::instance.playerDataArray[playerID].requestStateUnk;
        if (((iVar5 != 1) && (iVar5 == 2))
            && (iVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
                    DAT_UnitsState::ptr)(DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk),
                iVar5 != 0)) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::clearRallyFlagOnAllAIAttackTribes, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToPlayerIDsKeepIfPossible, this)(
                playerID, ((int)(DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk)));
            return;
        }

        int _aiPlayerState = DAT_GameState::instance.playerDataArray[playerID].aiPlayerState;

        if (_aiPlayerState == 0) {
            BOOLEnum _shouldAttack = MACRO_CALL_MEMBER(
                OpenSHC::AI::AICState_Func::aiShouldAttackOrWaitForTeamCoordination, this)(playerID);
            if (_shouldAttack == FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRetreatUnits, this)(playerID);
                return;
            }
            DAT_GameState::instance.playerDataArray[playerID].attackTicker = 0;
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 1;
            DAT_GameState::instance.playerDataArray[playerID].unitPatrolRecommandRelatedDelayValue = 0;
            DAT_GameState::instance.playerDataArray[playerID].aiCoordinatedAttackPatience = 0;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setAttackCoordinationLevel, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setCurrentAttackStrength, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::setCurrentAttackRaidParameter, this)(playerID);
            int* piVar2 = (int*)(DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID * 0x39f4 + 0x115e9d4
                + playerID * 0x20);
            *piVar2 = *piVar2 + 1;
        } else {
            BOOLEnum BVar6 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::hasNoTroopsOrAllAreDiggers, this)(playerID);
            if ((((BVar6 != FALSE) && (_aiPlayerState != 9))
                    || ((0 < DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker
                        && (_aiPlayerState < 6))))
                || (199 < DAT_GameState::instance.playerDataArray[playerID].attackTicker))
                DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 8;
        }

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::clearRallyFlagOnAllAIAttackTribes, this)(playerID);

        int _attackedPlayerAlive = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
            DAT_UnitsState::ptr)(DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID);

        if (_attackedPlayerAlive == 0) {
            iVar5 = DAT_GameState::instance.playerDataArray[playerID].aiPlayerState;
            if (iVar5 < 4) {
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
            } else if (iVar5 < 7) {
                DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 7;
            }
        }

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::clearOutdatedAITribes, this)(playerID);

        int _aiPlayerState_2 = DAT_GameState::instance.playerDataArray[playerID].aiPlayerState;
        BOOLEnum BVar6;
        int* piVar2;

        if (_aiPlayerState_2 == 1) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recreateEngineersTribe, this)(playerID);
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::initializeGatePathfindingForOwner,
                DAT_BuildingsState::ptr)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeEnemyKeepApproachTile, this)(playerID);
            if (0 < DAT_GameState::instance.playerDataArray[playerID].shortestDistanceTile) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::moveAttackTribesToLocations, this)(playerID);
                return;
            }
            // state 1 with no path: reset to 0
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 0;
            return;
        }

        if (_aiPlayerState_2 == 2) {
            uint _rallyReady
                = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiChoiceAttForceRallyPercentage, this)(playerID);
            if (_rallyReady == 0)
                return;
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

        if (_aiPlayerState_2 == 3) {
            piVar2 = &DAT_GameState::instance.playerDataArray[playerID].attackTicker;
            *piVar2 = *piVar2 + 1;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::moveAttackingUnitsToNextRallyPoint, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendAITribe_0xf_toAttackPatrol, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiCommandSiegeEngineTribes, this)(playerID);
            BVar6 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::processAttForceRallyPercentage, this)(playerID);
            if (BVar6 == FALSE)
                return;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIPathCostToAttackedKeep, this)(playerID, 0);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeAttackPossibilities, this)(playerID);
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 4;
            DAT_GameState::instance.playerDataArray[playerID].attackAssaultDelayRelatedValue = 0;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiCommandTribe12AggressiveApproach, this)(playerID);
            return;
        }

        if (_aiPlayerState_2 == 4) {
            piVar2 = &DAT_GameState::instance.playerDataArray[playerID].attackTicker;
            *piVar2 = *piVar2 + 1;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::moveAttackingUnitsToNextRallyPoint, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendAITribe_0xf_toAttackPatrol, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiCommandSiegeEngineTribes, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendTribeToAttack, this)(playerID);
            iVar5 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::countSiegeEngineUnits, this)(playerID);
            if (iVar5 < 1)
                DAT_GameState::instance.playerDataArray[playerID].attackAssaultDelayRelatedValue = 100;
            piVar2 = &DAT_GameState::instance.playerDataArray[playerID].attackAssaultDelayRelatedValue;
            *piVar2 = *piVar2 + 1;
            if (DAT_GameState::instance.playerDataArray[playerID].attackAssaultDelayRelatedValue
                <= ((int)this->aics[_aiType].AttAssaultDelay))
                return;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIPathCostToAttackedKeep, this)(playerID, 0);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeAttackPossibilities, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX,
                DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY, 0x14);
            BVar6 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep,
                DAT_GameState::ptr)(playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID);
            if (BVar6 == FALSE) {
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

        if (_aiPlayerState_2 == 5) {
            if (DAT_GameState::instance.playerDataArray[playerID].shortestDistanceTile < 1)
                DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 0;
            short* psVar1 = &DAT_GameState::instance.playerDataArray[playerID].unknownCounter01;
            *psVar1 = *psVar1 + 1;
            short sVar3 = DAT_GameState::instance.playerDataArray[playerID].unknownCounter01;
            piVar2 = &DAT_GameState::instance.playerDataArray[playerID].attackTicker;
            *piVar2 = *piVar2 + 1;
            DAT_GameState::instance.playerDataArray[playerID].someResourceCounter = 0;
            if (3 < sVar3) {
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
            BVar6 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep,
                DAT_GameState::ptr)(playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID);
            if ((BVar6 == FALSE)
                && (BVar6 = MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::canUnitsNavigateFromKeepToKeep, DAT_GameState::ptr)(
                        playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID),
                    BVar6 == FALSE))
                return;
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 6;
            return;
        }

        if (_aiPlayerState_2 == 6) {
            if (DAT_GameState::instance.playerDataArray[playerID].shortestDistanceTile < 1)
                DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 0;
            piVar2 = &DAT_GameState::instance.playerDataArray[playerID].attackTicker;
            *piVar2 = *piVar2 + 1;
            int _playerID = DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;
            DAT_GameState::instance.playerDataArray[playerID].someResourceCounter = 0;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::calculateAttackVectorsToCampFireOfPlayer,
                DAT_GameState::ptr)(_playerID);
            iVar5 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToAttackBreachedCastle, this)(playerID);
            if (iVar5 != 0)
                return;
            BVar6 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep,
                DAT_GameState::ptr)(playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID);
            if (BVar6 != FALSE)
                return;
            BVar6 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canUnitsNavigateFromKeepToKeep,
                DAT_GameState::ptr)(playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID);
            if (BVar6 != FALSE)
                return;
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 5;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIPathCostToAttackedKeep, this)(playerID, 0);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeAttackPossibilities, this)(playerID);
            DAT_GameState::instance.playerDataArray[playerID].unknownCounter01 = 0;
            return;
        }

        if (_aiPlayerState_2 == 7) {
            piVar2 = &DAT_GameState::instance.playerDataArray[playerID].unitPatrolRecommandRelatedDelayValue;
            *piVar2 = *piVar2 + 1;
            if (DAT_GameState::instance.playerDataArray[playerID].unitPatrolRecommandRelatedDelayValue
                <= ((int)this->aics[_aiType].AttUnitPatrolRecommandDelay))
                return;
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 9;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::disbandAIPlayerSiegeUnits, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::removeSiegeBuildings,
                DAT_BuildingsState::ptr)(DAT_GameState::instance.playerDataArray[playerID].currentAttackWave, playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addEngineersToTribe, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiReassignTunnelersToTribe, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::findAttackTribePositionAndPathToDefenses, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::makeUnitsGoDefensiveAndBackToSomeLocation, this)(playerID);
            return;
        }

        if (_aiPlayerState_2 == 8) {
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 9;
            DAT_GameState::instance.playerDataArray[playerID].attackTicker = 0;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::disbandAIPlayerSiegeUnits, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::removeSiegeBuildings,
                DAT_BuildingsState::ptr)(DAT_GameState::instance.playerDataArray[playerID].currentAttackWave, playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addEngineersToTribe, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiReassignTunnelersToTribe, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::findAttackTribePositionAndPathToDefenses, this)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::makeUnitsGoDefensiveAndBackToSomeLocation, this)(playerID);
            if (0 < DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker)
                return;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playAnger1BikFromPlayer, this)(playerID);
            return;
        }

        if (_aiPlayerState_2 == 9) {
            DAT_GameState::instance.playerDataArray[playerID].attackTicker += 1;
            if (((DAT_GameState::instance.playerDataArray[playerID].attackTicker < 20)
                    && (BVar6 = MACRO_CALL_MEMBER(
                            OpenSHC::AI::AICState_Func::percentageNonMovingTribesGTEAICSpecified, this)(playerID),
                        BVar6 == FALSE))
                && (BVar6 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::hasNoTroopsOrAllAreDiggers, this)(playerID),
                    BVar6 == FALSE))
                return;
            // was LAB_004d4ff7
            DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 0;
        }
    }
}
}
