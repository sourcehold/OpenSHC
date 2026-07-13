/**
  path: 'OpenSHC/Map/Units/TroopValueState.func.hpp'
*/

#include "OpenSHC/AI/Tribes/AITribeTypeShort.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorTypeInt.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorTypeShort.hpp"
#include "OpenSHC/Map/Units/TroopValueState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace TroopValueState_Func {

            using OpenSHC::AI::Tribes::AITribeTypeShort;
            using OpenSHC::Commands::CommandBuildingTypeInt;
            using OpenSHC::IO::PackagedFileMagicNumInt;
            using OpenSHC::Map::Units::SomeTribeBehaviorTypeInt;
            using OpenSHC::Map::Units::SomeTribeBehaviorTypeShort;
            using OpenSHC::Map::Units::UnitInstructionTypeInt;
            using OpenSHC::Map::Units::UnitTypeInt;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(
                void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x00518130, &TroopValueState::clearAttackInfo)
            clearAttackInfo;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00518180,
                &TroopValueState::resetAttackAndAssignSignpost)
            resetAttackAndAssignSignpost;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x005182A0,
                &TroopValueState::searchTribeWithProperties)
            searchTribeWithProperties;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x00518350,
                &TroopValueState::areAllAttacksFinished)
            areAllAttacksFinished;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int, int, SomeTribeBehaviorTypeInt), false,
                Address::SHC_3BB0A8C1_0x00518380, &TroopValueState::sortAttackInfoTribeIDArrayBasedOn)
            sortAttackInfoTribeIDArrayBasedOn;

            MACRO_FUNCTION_RESOLVER(
                void (TroopValueState::*)(SomeTribeBehaviorTypeInt, SomeTribeBehaviorTypeInt, int, int), false,
                Address::SHC_3BB0A8C1_0x00518870, &TroopValueState::applyTribeBehaviorTypes)
            applyTribeBehaviorTypes;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(SomeTribeBehaviorTypeShort, undefined4, short, short),
                false, Address::SHC_3BB0A8C1_0x00518930, &TroopValueState::assignBehaviorToReachableTribes)
            assignBehaviorToReachableTribes;

            MACRO_FUNCTION_RESOLVER(
                void (TroopValueState::*)(int, int, SomeTribeBehaviorTypeShort, undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x00518A10, &TroopValueState::assignTribeBehaviorAndPairArchers)
            assignTribeBehaviorAndPairArchers;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00518BB0,
                &TroopValueState::isLessThanPercentageOfTribesInAttackDying)
            isLessThanPercentageOfTribesInAttackDying;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00518C50, &TroopValueState::renderAIAttackDebugOverlay)
            renderAIAttackDebugOverlay;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x00519310,
                &TroopValueState::computeAttackWaveScaling)
            computeAttackWaveScaling;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519690,
                &TroopValueState::buildSiegeRallyPoints)
            buildSiegeRallyPoints;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519790,
                &TroopValueState::setLaddermanRallyPoint)
            setLaddermanRallyPoint;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519850,
                &TroopValueState::initAttackInfoStartZone)
            initAttackInfoStartZone;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x005198C0,
                &TroopValueState::recomputeTargetedBuildingTilesArray)
            recomputeTargetedBuildingTilesArray;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519960,
                &TroopValueState::getTileInTargetedBuildingTiles)
            getTileInTargetedBuildingTiles;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00519990,
                &TroopValueState::hack2related)
            hack2related;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519CC0,
                &TroopValueState::findEnemyWalls)
            findEnemyWalls;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00519DE0,
                &TroopValueState::setScale3)
            setScale3;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519E40,
                &TroopValueState::findAttackInfoScaleTarget)
            findAttackInfoScaleTarget;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00519F50,
                &TroopValueState::setTown2)
            setTown2;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00519FB0,
                &TroopValueState::findEnemyBuildingsClosestToUnit)
            findEnemyBuildingsClosestToUnit;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A0C0,
                &TroopValueState::countAvailablePeopleTargets)
            countAvailablePeopleTargets;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A100,
                &TroopValueState::countAvailableLordTargets)
            countAvailableLordTargets;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A140,
                &TroopValueState::calculateTile2PeoplValueClosestToUnit)
            calculateTile2PeoplValueClosestToUnit;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x0051A220,
                &TroopValueState::assignUnitToEnemyLordTarget)
            assignUnitToEnemyLordTarget;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0051A2D0,
                &TroopValueState::setGate2)
            setGate2;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A330,
                &TroopValueState::assignUnitToNearestEnemyGateTarget)
            assignUnitToNearestEnemyGateTarget;

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
                &TroopValueState::findMoatTileToDig)
            findMoatTileToDig;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051A920,
                &TroopValueState::findMoatDiggingTribeTarget)
            findMoatDiggingTribeTarget;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A9A0,
                &TroopValueState::countAvailableHighTargets)
            countAvailableHighTargets;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051A9F0,
                &TroopValueState::calculateHigh2ClostestToTribeTargetUnit)
            calculateHigh2ClostestToTribeTargetUnit;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051AB10,
                &TroopValueState::countAvailableArcherTargets)
            countAvailableArcherTargets;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051AB60,
                &TroopValueState::calculateArch2ClosestToTribeTargetUnit)
            calculateArch2ClosestToTribeTargetUnit;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051ACE0,
                &TroopValueState::recomputeAIApproachLayer1)
            recomputeAIApproachLayer1;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051AE00,
                &TroopValueState::recomputeAIApproachLayer2)
            recomputeAIApproachLayer2;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051AE90,
                &TroopValueState::recomputeAIApproachLayer4)
            recomputeAIApproachLayer4;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051AF20,
                &TroopValueState::findArcherPointIndexForTile)
            findArcherPointIndexForTile;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051AF70,
                &TroopValueState::validateAttackInfoEntries)
            validateAttackInfoEntries;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051AFF0,
                &TroopValueState::assignTribeArcherAttackPosition)
            assignTribeArcherAttackPosition;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051B0C0,
                &TroopValueState::getSupportPointIndex)
            getSupportPointIndex;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051B110,
                &TroopValueState::validateSupportPointEntries)
            validateSupportPointEntries;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051B240,
                &TroopValueState::getSiegeIndexForTile)
            getSiegeIndexForTile;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051B290,
                &TroopValueState::validateTentPointEntries)
            validateTentPointEntries;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int, CommandBuildingTypeInt), false,
                Address::SHC_3BB0A8C1_0x0051B310, &TroopValueState::placeSiegeTentAndOrderConstruction)
            placeSiegeTentAndOrderConstruction;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (TroopValueState::*)(int, CommandBuildingTypeInt, uint, UnitInstructionTypeInt), false,
                Address::SHC_3BB0A8C1_0x0051B420,
                &TroopValueState::placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers)
            placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051B570,
                &TroopValueState::placeTunnelEntrances)
            placeTunnelEntrances;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051B680,
                &TroopValueState::clearAIInfoLayerOutsideStartZone)
            clearAIInfoLayerOutsideStartZone;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051B6C0,
                &TroopValueState::playAttackStartHorn)
            playAttackStartHorn;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0051B710,
                &TroopValueState::placeSiegeTentsAndAssignEngineers)
            placeSiegeTentsAndAssignEngineers;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051BA30,
                &TroopValueState::placeTunnelForEveryTunneler)
            placeTunnelForEveryTunneler;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(undefined4, int, AITribeTypeShort, undefined4), false,
                Address::SHC_3BB0A8C1_0x0051BC70, &TroopValueState::addUnitToNewTribe)
            addUnitToNewTribe;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051BD10,
                &TroopValueState::commandSiegeCrewsExitEquipment)
            commandSiegeCrewsExitEquipment;

            MACRO_FUNCTION_RESOLVER(undefined (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051BDE0,
                &TroopValueState::getPlayerNot1AndHasKeep)
            getPlayerNot1AndHasKeep;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051BE60,
                &TroopValueState::addAttackTargetTile)
            addAttackTargetTile;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0051BF20,
                &TroopValueState::shouldLightPitchBecauseOfTroopValue)
            shouldLightPitchBecauseOfTroopValue;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051BF70,
                &TroopValueState::giveLightPitchInstructionToUnitClosestToPitch)
            giveLightPitchInstructionToUnitClosestToPitch;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0051C1A0,
                &TroopValueState::lightPitchIfNecessary)
            lightPitchIfNecessary;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051C2D0,
                &TroopValueState::updateArcherBrazierFlags)
            updateArcherBrazierFlags;

            MACRO_FUNCTION_RESOLVER(int (TroopValueState::*)(UnitTypeInt), false, Address::SHC_3BB0A8C1_0x0051C360,
                &TroopValueState::getValueOfTroopType)
            getValueOfTroopType;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051C470,
                &TroopValueState::aiEngineersThrowOil)
            aiEngineersThrowOil;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051C570,
                &TroopValueState::ifNecessaryThrowOilAutomatically)
            ifNecessaryThrowOilAutomatically;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051C800,
                &TroopValueState::commandUnitsToMoveToKeep)
            commandUnitsToMoveToKeep;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051CA50,
                &TroopValueState::collectAIArchersForRepositioning)
            collectAIArchersForRepositioning;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051CBD0,
                &TroopValueState::refillWallArcherPositions)
            refillWallArcherPositions;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051CCB0,
                &TroopValueState::assignMacemenAndKnightsNotFromPlayer1ToTribes)
            assignMacemenAndKnightsNotFromPlayer1ToTribes;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051CF90,
                &TroopValueState::dispatchAggressiveMacemenTribe)
            dispatchAggressiveMacemenTribe;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051D020,
                &TroopValueState::dispatchAggressiveKnightTribe)
            dispatchAggressiveKnightTribe;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D0D0,
                &TroopValueState::sendAttackingPatrolTribeToComputedDestination)
            sendAttackingPatrolTribeToComputedDestination;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D1C0,
                &TroopValueState::sendTribeAlongAttackPath)
            sendTribeAlongAttackPath;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D2B0,
                &TroopValueState::decideTribeAttackTarget)
            decideTribeAttackTarget;

            MACRO_FUNCTION_RESOLVER(undefined4 (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D450,
                &TroopValueState::commandTribeMoveToNearestEnemyGatehouse)
            commandTribeMoveToNearestEnemyGatehouse;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D510,
                &TroopValueState::moveTowardsParticularUnits)
            moveTowardsParticularUnits;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D690,
                &TroopValueState::dispatchAttackWavePeopleAssault)
            dispatchAttackWavePeopleAssault;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D730,
                &TroopValueState::processSiegeRetreatWave)
            processSiegeRetreatWave;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051D7F0,
                &TroopValueState::updateTribeBehaviorBasedOnBehaviorType)
            updateTribeBehaviorBasedOnBehaviorType;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0051E300,
                &TroopValueState::recomputeAttackInfo)
            recomputeAttackInfo;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051F340,
                &TroopValueState::computeAIArcherAttackPoints)
            computeAIArcherAttackPoints;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051F4B0,
                &TroopValueState::computeAISupportPoints)
            computeAISupportPoints;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051F5C0,
                &TroopValueState::computeAISiegeTentPoints)
            computeAISiegeTentPoints;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051F9C0,
                &TroopValueState::recountTotalTroopValue)
            recountTotalTroopValue;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051FA70,
                &TroopValueState::recomputeTotalTroopValueOfTroopsNearKeep)
            recomputeTotalTroopValueOfTroopsNearKeep;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(PackagedFileMagicNumInt, PackagedFileMagicNumInt), false,
                Address::SHC_3BB0A8C1_0x0051FB80, &TroopValueState::uselessFunction)
            uselessFunction;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051FB90,
                &TroopValueState::recountAttackTroopValue)
            recountAttackTroopValue;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x0051FF90,
                &TroopValueState::startAttackWave)
            startAttackWave;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005200A0,
                &TroopValueState::aiRecomputeAttacks2)
            aiRecomputeAttacks2;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(undefined4, int), false, Address::SHC_3BB0A8C1_0x005202B0,
                &TroopValueState::aiRecomputeAttacks)
            aiRecomputeAttacks;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00520450,
                &TroopValueState::processSiegeAttackWave)
            processSiegeAttackWave;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x005205A0,
                &TroopValueState::runAiAttackWaveLogic)
            runAiAttackWaveLogic;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(int), false, Address::SHC_3BB0A8C1_0x00520CD0,
                &TroopValueState::runAiAttackWaveLogicSimple)
            runAiAttackWaveLogicSimple;

            MACRO_FUNCTION_RESOLVER(void (TroopValueState::*)(), false, Address::SHC_3BB0A8C1_0x0051F950,
                &TroopValueState::aiControlNonSkirmishUnitMovement)
            aiControlNonSkirmishUnitMovement;

        } // namespace TroopValueState_Func
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
