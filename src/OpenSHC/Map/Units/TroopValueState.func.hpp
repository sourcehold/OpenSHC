/**
  path: 'OpenSHC/Map/Units/TroopValueState.func.hpp'
*/

#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/TroopValueState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace TroopValueState_Func {

            using OpenSHC::AI::Tribes::AITribeType;
            using OpenSHC::Commands::CommandBuildingType;
            using OpenSHC::IO::PackagedFileMagicNum;
            using OpenSHC::Map::Units::SomeTribeBehaviorType;
            using OpenSHC::Map::Units::UnitInstructionType;
            using OpenSHC::Map::Units::UnitType;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            // Constructor

            MACRO_FUNCTION_RESOLVER(TroopValueState* (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051D680,
                &TroopValueState::constructTroopValueState)
            constructTroopValueState;

            MACRO_FUNCTION_RESOLVER(
                void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x00518130, &TroopValueState::clearAttackInfo)
            clearAttackInfo;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00518180,
                &TroopValueState::initializeAttackWaveSlot)
            initializeAttackWaveSlot;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x005182A0,
                &TroopValueState::searchTribeWithProperties)
            searchTribeWithProperties;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x00518350,
                &TroopValueState::isAttackWaveComplete)
            isAttackWaveComplete;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int, int, SomeTribeBehaviorType), false,
                Address::SHC_3BB0A8C1_0x00518380, &TroopValueState::sortAttackInfoTribeIDArrayBasedOn)
            sortAttackInfoTribeIDArrayBasedOn;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(SomeTribeBehaviorType, SomeTribeBehaviorType, int, int),
                false, Address::SHC_3BB0A8C1_0x00518870, &TroopValueState::applyTribeBehaviorTypes)
            applyTribeBehaviorTypes;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(SomeTribeBehaviorType, undefined4, short, short), false,
                Address::SHC_3BB0A8C1_0x00518930, &TroopValueState::assignBehaviorTypeToNearbyTribes)
            assignBehaviorTypeToNearbyTribes;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int, SomeTribeBehaviorType, undefined4, undefined4),
                false, Address::SHC_3BB0A8C1_0x00518A10, &TroopValueState::assignBehaviorTypeAndLinkSupportTribe)
            assignBehaviorTypeAndLinkSupportTribe;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00518BB0,
                &TroopValueState::isLessThanPercentageOfTribesInAttackDying)
            isLessThanPercentageOfTribesInAttackDying;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00518C50, &TroopValueState::renderAttackInfoDebugOverlay)
            renderAttackInfoDebugOverlay;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x00519310,
                &TroopValueState::computeAttackWaveTroopComposition)
            computeAttackWaveTroopComposition;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519690,
                &TroopValueState::buildRallyPointsFromSiegeUnits)
            buildRallyPointsFromSiegeUnits;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519790,
                &TroopValueState::setRallyPointForLaddermenTribe)
            setRallyPointForLaddermenTribe;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519850,
                &TroopValueState::initializeAttackZoneSearch)
            initializeAttackZoneSearch;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x005198C0,
                &TroopValueState::recomputeTargetedBuildingTilesArray)
            recomputeTargetedBuildingTilesArray;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519960,
                &TroopValueState::getTileInTargetedBuildingTiles)
            getTileInTargetedBuildingTiles;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00519990,
                &TroopValueState::computeSiegeSpotScores)
            computeSiegeSpotScores;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519CC0,
                &TroopValueState::findEnemyWalls)
            findEnemyWalls;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00519DE0,
                &TroopValueState::setScale3)
            setScale3;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519E40,
                &TroopValueState::findNearestAvailableScalePoint)
            findNearestAvailableScalePoint;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00519F50,
                &TroopValueState::setTown2)
            setTown2;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519FB0,
                &TroopValueState::findEnemyBuildingsClosestToUnit)
            findEnemyBuildingsClosestToUnit;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A0C0,
                &TroopValueState::countAvailablePeopleValueSlots)
            countAvailablePeopleValueSlots;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A100,
                &TroopValueState::countAvailableLordValueSlots)
            countAvailableLordValueSlots;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A140,
                &TroopValueState::calculateTile2PeoplValueClosestToUnit)
            calculateTile2PeoplValueClosestToUnit;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x0051A220,
                &TroopValueState::findEnemyLord)
            findEnemyLord;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0051A2D0,
                &TroopValueState::setGate2)
            setGate2;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A330,
                &TroopValueState::findEnemyTowersOrGates)
            findEnemyTowersOrGates;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0051A550,
                &TroopValueState::setWide3)
            setWide3;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A5B0,
                &TroopValueState::getClosestWideValueBasedOnPlayer)
            getClosestWideValueBasedOnPlayer;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0051A720,
                &TroopValueState::setMoat3)
            setMoat3;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A780,
                &TroopValueState::calculateTile2MoatValueClosestToUnit)
            calculateTile2MoatValueClosestToUnit;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A8A0,
                &TroopValueState::findNearestDiggableMoatPoint)
            findNearestDiggableMoatPoint;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051A920,
                &TroopValueState::findTribeWithMoatAttackBehavior)
            findTribeWithMoatAttackBehavior;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A9A0,
                &TroopValueState::countAvailableHighValueSlots)
            countAvailableHighValueSlots;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A9F0,
                &TroopValueState::calculateHigh2ClostestToTribeTargetUnit)
            calculateHigh2ClostestToTribeTargetUnit;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051AB10,
                &TroopValueState::countAvailableArcherValueSlots)
            countAvailableArcherValueSlots;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051AB60,
                &TroopValueState::calculateArch2ClosestToTribeTargetUnit)
            calculateArch2ClosestToTribeTargetUnit;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051ACE0,
                &TroopValueState::expandAIZoneLayerStage1)
            expandAIZoneLayerStage1;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051AE00,
                &TroopValueState::expandAIZoneLayerStage2)
            expandAIZoneLayerStage2;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051AE90,
                &TroopValueState::expandAIZoneLayerStage3)
            expandAIZoneLayerStage3;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051AF20,
                &TroopValueState::findOrReserveArcherPointSlot)
            findOrReserveArcherPointSlot;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051AF70,
                &TroopValueState::pruneStaleArcherPoints)
            pruneStaleArcherPoints;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051AFF0,
                &TroopValueState::claimArcherAttackPoint)
            claimArcherAttackPoint;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051B0C0,
                &TroopValueState::getSupportPointIndex)
            getSupportPointIndex;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051B110,
                &TroopValueState::pruneStaleSupportPoints)
            pruneStaleSupportPoints;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051B240,
                &TroopValueState::getSiegeIndexForTile)
            getSiegeIndexForTile;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051B290,
                &TroopValueState::pruneStaleTentPoints)
            pruneStaleTentPoints;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int, CommandBuildingType), false,
                Address::SHC_3BB0A8C1_0x0051B310, &TroopValueState::placeSiegeTentAtAttackAngle)
            placeSiegeTentAtAttackAngle;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TroopValueState::*)(int, CommandBuildingType, uint, UnitInstructionType),
                false, Address::SHC_3BB0A8C1_0x0051B420,
                &TroopValueState::placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers)
            placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051B570,
                &TroopValueState::placeTunnelEntrances)
            placeTunnelEntrances;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051B680,
                &TroopValueState::clearAIInfoLayerOutsideStartZone)
            clearAIInfoLayerOutsideStartZone;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051B6C0,
                &TroopValueState::playAttackAlarmSound)
            playAttackAlarmSound;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0051B710,
                &TroopValueState::placeSiegeTentsAndAssignEngineers)
            placeSiegeTentsAndAssignEngineers;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051BA30,
                &TroopValueState::placeTunnelForEveryTunneler)
            placeTunnelForEveryTunneler;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(undefined4, int, AITribeType, undefined4), false,
                Address::SHC_3BB0A8C1_0x0051BC70, &TroopValueState::addUnitToNewTribe)
            addUnitToNewTribe;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051BD10,
                &TroopValueState::exitSiegeEquipmentForWave)
            exitSiegeEquipmentForWave;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051BDE0,
                &TroopValueState::getPlayerNot1AndHasKeep)
            getPlayerNot1AndHasKeep;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051BE60,
                &TroopValueState::registerSpottedEnemyTile)
            registerSpottedEnemyTile;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0051BF20,
                &TroopValueState::shouldLightPitchBasedOnTroopValue)
            shouldLightPitchBasedOnTroopValue;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051BF70,
                &TroopValueState::giveLightPitchInstructionToUnitClosestToPitch)
            giveLightPitchInstructionToUnitClosestToPitch;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0051C1A0,
                &TroopValueState::lightPitchIfNecessary)
            lightPitchIfNecessary;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051C2D0,
                &TroopValueState::updateArcherBrazierProximityFlags)
            updateArcherBrazierProximityFlags;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(UnitType), false, Address::SHC_3BB0A8C1_0x0051C360,
                &TroopValueState::getValueOfTroopType)
            getValueOfTroopType;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051C470,
                &TroopValueState::queueOilThrowForIdleArchers)
            queueOilThrowForIdleArchers;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051C570,
                &TroopValueState::ifNecessaryThrowOilAutomatically)
            ifNecessaryThrowOilAutomatically;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051C800,
                &TroopValueState::commandUnitsToMoveToKeep)
            commandUnitsToMoveToKeep;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051CA50,
                &TroopValueState::collectArcherUnitsByLocation)
            collectArcherUnitsByLocation;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051CBD0,
                &TroopValueState::redeployArchersToDefensivePositions)
            redeployArchersToDefensivePositions;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051CCB0,
                &TroopValueState::assignMacemenAndKnightsNotFromPlayer1ToTribes)
            assignMacemenAndKnightsNotFromPlayer1ToTribes;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051CF90,
                &TroopValueState::trySendMacemenTribeToAttack)
            trySendMacemenTribeToAttack;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051D020,
                &TroopValueState::trySendKnightTribeToAttack)
            trySendKnightTribeToAttack;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D0D0,
                &TroopValueState::sendAttackingPatrolTribeToComputedDestination)
            sendAttackingPatrolTribeToComputedDestination;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D1C0,
                &TroopValueState::moveTribeToReachableNearbyTile)
            moveTribeToReachableNearbyTile;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D2B0,
                &TroopValueState::decideAndExecuteTribeAttackAction)
            decideAndExecuteTribeAttackAction;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D450,
                &TroopValueState::moveTribeToNearbyGatehouse)
            moveTribeToNearbyGatehouse;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D510,
                &TroopValueState::moveTowardsParticularUnits)
            moveTowardsParticularUnits;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D690,
                &TroopValueState::advanceAttackWaveStaging)
            advanceAttackWaveStaging;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D730,
                &TroopValueState::updateActiveAttackWaveState)
            updateActiveAttackWaveState;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D7F0,
                &TroopValueState::updateTribeBehaviorBasedOnBehaviorType)
            updateTribeBehaviorBasedOnBehaviorType;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0051E300,
                &TroopValueState::recomputeAttackInfo)
            recomputeAttackInfo;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051F340,
                &TroopValueState::scanForArcherPoints)
            scanForArcherPoints;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051F4B0,
                &TroopValueState::scanForSupportPoints)
            scanForSupportPoints;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051F5C0,
                &TroopValueState::scanForSiegeTentPoints)
            scanForSiegeTentPoints;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051F950,
                &TroopValueState::processSpottedEnemyTiles)
            processSpottedEnemyTiles;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051F9C0,
                &TroopValueState::recountTotalTroopValue)
            recountTotalTroopValue;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051FA70,
                &TroopValueState::recomputeTotalTroopValueOfTroopsNearKeep)
            recomputeTotalTroopValueOfTroopsNearKeep;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(PackagedFileMagicNum, PackagedFileMagicNum), false,
                Address::SHC_3BB0A8C1_0x0051FB80, &TroopValueState::uselessFunction)
            uselessFunction;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051FB90,
                &TroopValueState::recountAttackTroopValue)
            recountAttackTroopValue;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051FE80,
                &TroopValueState::updateAttackInfoTick)
            updateAttackInfoTick;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051FF90,
                &TroopValueState::initializeOrAdvanceAttackWave)
            initializeOrAdvanceAttackWave;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005200A0,
                &TroopValueState::aiRecomputeAttacks2)
            aiRecomputeAttacks2;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(undefined4, int), false, Address::SHC_3BB0A8C1_0x005202B0,
                &TroopValueState::aiRecomputeAttacks)
            aiRecomputeAttacks;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00520450,
                &TroopValueState::updateInProgressAttackWave)
            updateInProgressAttackWave;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x005205A0,
                &TroopValueState::executeAttackWaveTargetAssignment)
            executeAttackWaveTargetAssignment;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00520CD0,
                &TroopValueState::executeDelayedAttackWaveTargetAssignment)
            executeDelayedAttackWaveTargetAssignment;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x00520F70,
                &TroopValueState::aiControlNonSkirmishUnitMovement)
            aiControlNonSkirmishUnitMovement;

        } // namespace TroopValueState_Func
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
