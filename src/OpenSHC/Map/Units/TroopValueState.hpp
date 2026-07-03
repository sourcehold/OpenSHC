/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/TroopValueState.hpp'
*/

#pragma once

#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/AttackInfo.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::AI::Tribes::AITribeType;
        using OpenSHC::Commands::CommandBuildingType;
        using OpenSHC::IO::PackagedFileMagicNum;
        using OpenSHC::Map::AttackInfo;
        using OpenSHC::Map::Units::SomeTribeBehaviorType;
        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x00103768
        class TroopValueState {
        public:
            undefined4 x; // 0x00000000 length: 4
            undefined4 y; // 0x00000004 length: 4
            undefined4 tile; // 0x00000008 length: 4
            AttackInfo attackInfo; // 0x0000000C length: 1062748

        private:
            TroopValueState(TroopValueState const&);
            void operator=(TroopValueState const&);

        public:
            TroopValueState() {};
            ~TroopValueState() {};

            // Constructor
            TroopValueState* constructTroopValueState();

            void clearAttackInfo();

            void initializeAttackWaveSlot(int param_1, int param_2);

            BOOLEnum searchTribeWithProperties(int param_1);

            undefined4 isAttackWaveComplete();

            void sortAttackInfoTribeIDArrayBasedOn(
                int attackWave, int shrinkSize, int tribeSizeSumLimit, SomeTribeBehaviorType someTribeTypeIdentifier);

            void applyTribeBehaviorTypes(
                SomeTribeBehaviorType tribeBehaviorType, SomeTribeBehaviorType tribeBehaviorType2, int off1, int off2);

            void assignBehaviorTypeToNearbyTribes(
                SomeTribeBehaviorType param_1, undefined4 param_2, short param_3, short param_4);

            void assignBehaviorTypeAndLinkSupportTribe(
                int param_1, int param_2, SomeTribeBehaviorType param_3, undefined4 param_4, undefined4 param_5);

            BOOLEnum isLessThanPercentageOfTribesInAttackDying(int attackID, int leDyingPerc);

            void renderAttackInfoDebugOverlay(int x, int y, int width, int height);

            void computeAttackWaveTroopComposition();

            void buildRallyPointsFromSiegeUnits(int tribeID);

            void setRallyPointForLaddermenTribe(int param_1);

            void initializeAttackZoneSearch(int param_1);

            void recomputeTargetedBuildingTilesArray(int playerID);

            BOOLEnum getTileInTargetedBuildingTiles(int tile);

            void computeSiegeSpotScores(int attackedPlayerID, int attackingPlayerID);

            undefined4 findEnemyWalls(int unitID);

            void setScale3(int one, int playerID);

            undefined4 findNearestAvailableScalePoint(int unitID);

            void setTown2(int param_1, int playerID);

            undefined4 findEnemyBuildingsClosestToUnit(int unitID);

            void countAvailablePeopleValueSlots(int param_1);

            void countAvailableLordValueSlots(int param_1);

            undefined4 calculateTile2PeoplValueClosestToUnit(int unitID);

            int findEnemyLord(undefined4 param_1);

            void setGate2(int param_1, int param_2);

            undefined4 findEnemyTowersOrGates(int unitID);

            void setWide3(int param_1, int param_2);

            undefined4 getClosestWideValueBasedOnPlayer(int playerID);

            void setMoat3(int checkAgainstNonZero, int playerID);

            undefined4 calculateTile2MoatValueClosestToUnit(int unitID);

            int findNearestDiggableMoatPoint(int param_1);

            undefined4 findTribeWithMoatAttackBehavior();

            void countAvailableHighValueSlots(int param_1);

            int calculateHigh2ClostestToTribeTargetUnit(int tribeID);

            void countAvailableArcherValueSlots(int param_1);

            int calculateArch2ClosestToTribeTargetUnit(int tribeID);

            void expandAIZoneLayerStage1();

            void expandAIZoneLayerStage2();

            void expandAIZoneLayerStage3();

            int findOrReserveArcherPointSlot(int param_1);

            void pruneStaleArcherPoints();

            int claimArcherAttackPoint(int param_1);

            int getSupportPointIndex(int tile);

            void pruneStaleSupportPoints();

            int getSiegeIndexForTile(int tile);

            void pruneStaleTentPoints();

            int placeSiegeTentAtAttackAngle(int tribeID, CommandBuildingType commandBuildingType);

            BOOLEnum placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers(int tribeID,
                CommandBuildingType commandBuildingType, uint strategicDistance, UnitInstructionType instruction);

            int placeTunnelEntrances(int tribeID);

            void clearAIInfoLayerOutsideStartZone();

            void playAttackAlarmSound();

            void placeSiegeTentsAndAssignEngineers(int param_1, int param_2);

            void placeTunnelForEveryTunneler(int attackWave);

            int addUnitToNewTribe(undefined4 unitID, int attackWave, AITribeType tribeType, undefined4 playerID);

            void exitSiegeEquipmentForWave(int wave);

            BOOLEnum getPlayerNot1AndHasKeep(int playerID);

            void registerSpottedEnemyTile(int param_1);

            BOOLEnum shouldLightPitchBasedOnTroopValue(int tile, int playerID);

            undefined4 giveLightPitchInstructionToUnitClosestToPitch(int tile);

            void lightPitchIfNecessary(int unitID, int unitID2);

            void updateArcherBrazierProximityFlags();

            int getValueOfTroopType(UnitType unitType);

            void queueOilThrowForIdleArchers();

            undefined4 ifNecessaryThrowOilAutomatically(int param_1);

            void commandUnitsToMoveToKeep();

            void collectArcherUnitsByLocation();

            void redeployArchersToDefensivePositions();

            void assignMacemenAndKnightsNotFromPlayer1ToTribes();

            void trySendMacemenTribeToAttack();

            void trySendKnightTribeToAttack();

            void sendAttackingPatrolTribeToComputedDestination(int tribeID);

            void moveTribeToReachableNearbyTile(int param_1);

            void decideAndExecuteTribeAttackAction(int tribeID);

            undefined4 moveTribeToNearbyGatehouse(int param_1);

            void moveTowardsParticularUnits(int param_1);

            void advanceAttackWaveStaging(int param_1);

            void updateActiveAttackWaveState(int attackWave);

            void updateTribeBehaviorBasedOnBehaviorType(int tribeID);

            void recomputeAttackInfo(int playerID, int attackedPlayerID);

            void scanForArcherPoints();

            void scanForSupportPoints();

            void scanForSiegeTentPoints();

            void processSpottedEnemyTiles();

            void recountTotalTroopValue();

            void recomputeTotalTroopValueOfTroopsNearKeep();

            void uselessFunction(PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

            void recountAttackTroopValue(int param_1);

            void updateAttackInfoTick();

            void initializeOrAdvanceAttackWave(int param_1);

            void aiRecomputeAttacks2(int param_1, int param_2);

            void aiRecomputeAttacks(undefined4 param_1, int param_2);

            void updateInProgressAttackWave(int attackID);

            void executeAttackWaveTargetAssignment(int param_1);

            void executeDelayedAttackWaveTargetAssignment(int param_1);

            void aiControlNonSkirmishUnitMovement();
        };

        static_assert_cpp98_obj(sizeof(TroopValueState) == 1062760, TroopValueState);

#pragma pack(pop)

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
