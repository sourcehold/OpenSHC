/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/TroopValueState.hpp'
*/

#pragma once

#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
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
        using OpenSHC::Commands::MappersEnum;
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
            TroopValueState* Constructor_TroopValueState();

            void clearAttackInfo();

            void initializeAttackWaveSlot(int param_1, int param_2);

            BOOLEnum searchTribeWithProperties(int param_1);

            BOOLEnum isAttackWaveComplete();

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

            int findEnemyWalls(int unitID);

            void setScale3(BOOLEnum includeAll, int playerID);

            int findNearestAvailableScalePoint(int unitID);

            void setTown2(BOOLEnum includeAll, int playerID);

            int findEnemyBuildingsClosestToUnit(int unitID);

            void countAvailablePeopleValueSlots(BOOLEnum includeOccupied);

            void countAvailableLordValueSlots(BOOLEnum includeOccupied);

            int calculateTile2PeoplValueClosestToUnit(int unitID);

            int findEnemyLord(int unitID);

            void setGate2(BOOLEnum includeAll, int playerID);

            int findEnemyTowersOrGates(int unitID);

            void setWide3(BOOLEnum includeAll, int playerID);

            int getClosestWideValueBasedOnPlayer(int unitID);

            void setMoat3(BOOLEnum includeAll, int playerID);

            int calculateTile2MoatValueClosestToUnit(int unitID);

            int findNearestDiggableMoatPoint(int param_1);

            BOOLEnum findTribeWithMoatAttackBehavior();

            void countAvailableHighValueSlots(BOOLEnum includeOccupied);

            int calculateHigh2ClostestToTribeTargetUnit(int tribeID);

            void countAvailableArcherValueSlots(BOOLEnum includeOccupied);

            int calculateArch2ClosestToTribeTargetUnit(int tribeID);

            BOOLEnum attackInfoHasHigh2Building(int buildingID);

            BOOLEnum attackInfoHasArch2Building(int buildingID);

            void expandAIZoneLayerStage1();

            void expandAIZoneLayerStage2();

            void expandAIZoneLayerStage3();

            int findOrReserveArcherPointSlot(int param_1);

            void pruneStaleArcherPoints();

            int claimArcherAttackPoint(int param_1);

            int getSupportPointIndex(int tile);

            void pruneStaleSupportPoints();

            int assignTribeToSupportPoint(int x, int y, int tribeID);

            int getSiegeIndexForTile(int tile);

            void pruneStaleTentPoints();

            int placeSiegeTentAtAttackAngle(int tribeID, MappersEnum commandBuildingType);

            BOOLEnum placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers(
                int tribeID, MappersEnum commandBuildingType, uint strategicDistance, UnitInstructionType instruction);

            int placeTunnelEntrances(int tribeID);

            void clearAIInfoLayerOutsideStartZone();

            void playAttackAlarmSound();

            void placeSiegeTentsAndAssignEngineers(int param_1, BOOLEnum param_2);

            void placeTunnelForEveryTunneler(int attackWave);

            void addUnitToNewTribe(int unitID, int attackWave, AITribeType tribeType, int playerID);

            void exitSiegeEquipmentForWave(int wave);

            BOOLEnum getPlayerNot1AndHasKeep(int playerID);

            void registerSpottedEnemyTile(int param_1);

            BOOLEnum shouldLightPitchBasedOnTroopValue(int tile, int playerID, int param_3);

            BOOLEnum giveLightPitchInstructionToUnitClosestToPitch(int tile);

            void lightPitchIfNecessary(int unitID, int unitID2);

            void updateArcherBrazierProximityFlags();

            int getValueOfTroopType(UnitType unitType);

            void queueOilThrowForIdleArchers();

            BOOLEnum ifNecessaryThrowOilAutomatically(int param_1);

            void commandUnitsToMoveToKeep();

            void collectArcherUnitsByLocation();

            void redeployArchersToDefensivePositions();

            void assignMacemenAndKnightsNotFromPlayer1ToTribes();

            void trySendMacemenTribeToAttack();

            void trySendKnightTribeToAttack();

            void sendAttackingPatrolTribeToComputedDestination(int tribeID);

            void moveTribeToReachableNearbyTile(int param_1);

            void decideAndExecuteTribeAttackAction(int tribeID);

            BOOLEnum moveTribeToNearbyGatehouse(int param_1);

            void moveTowardsParticularUnits(int param_1);

            void decrementTileMap1104();

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

            void recountAttackTroopValue(BOOLEnum param_1);

            void updateAttackInfoTick();

            void initializeOrAdvanceAttackWave(int param_1);

            void aiRecomputeAttacks2(BOOLEnum param_1, int param_2);

            void aiRecomputeAttacks(int param_1, int param_2);

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
