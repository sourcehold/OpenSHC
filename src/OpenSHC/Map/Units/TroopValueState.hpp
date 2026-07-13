/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/TroopValueState.hpp'
*/

#pragma once

#include "OpenSHC/AI/Tribes/AITribeTypeShort.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/AttackInfo.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorTypeInt.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitInstructionTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::AI::Tribes::AITribeTypeShort;
        using OpenSHC::Commands::CommandBuildingTypeInt;
        using OpenSHC::IO::PackagedFileMagicNumInt;
        using OpenSHC::Map::AttackInfo;
        using OpenSHC::Map::Units::SomeTribeBehaviorTypeInt;
        using OpenSHC::Map::Units::SomeTribeBehaviorTypeShort;
        using OpenSHC::Map::Units::UnitInstructionTypeInt;
        using OpenSHC::Map::Units::UnitTypeInt;
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

            void resetAttackAndAssignSignpost(int param_1, int param_2);

            BOOLEnum searchTribeWithProperties(int param_1);

            undefined4 areAllAttacksFinished();

            void sortAttackInfoTribeIDArrayBasedOn(int attackWave, int shrinkSize, int tribeSizeSumLimit,
                SomeTribeBehaviorTypeInt someTribeTypeIdentifier);

            void applyTribeBehaviorTypes(SomeTribeBehaviorTypeInt tribeBehaviorType,
                SomeTribeBehaviorTypeInt tribeBehaviorType2, int off1, int off2);

            void assignBehaviorToReachableTribes(
                SomeTribeBehaviorTypeShort param_1, undefined4 param_2, short param_3, short param_4);

            void assignTribeBehaviorAndPairArchers(
                int param_1, int param_2, SomeTribeBehaviorTypeShort param_3, undefined4 param_4, undefined4 param_5);

            BOOLEnum isLessThanPercentageOfTribesInAttackDying(int attackID, int leDyingPerc);

            void renderAIAttackDebugOverlay(int x, int y, int width, int height);

            void computeAttackWaveScaling();

            void buildSiegeRallyPoints(int tribeID);

            void setLaddermanRallyPoint(int param_1);

            void initAttackInfoStartZone(int param_1);

            void recomputeTargetedBuildingTilesArray(int playerID);

            BOOLEnum getTileInTargetedBuildingTiles(int tile);

            void hack2related(int attackedPlayerID, int attackingPlayerID);

            undefined4 findEnemyWalls(int unitID);

            void setScale3(int one, int playerID);

            undefined4 findAttackInfoScaleTarget(int unitID);

            void setTown2(int param_1, int playerID);

            undefined4 findEnemyBuildingsClosestToUnit(int unitID);

            void countAvailablePeopleTargets(int param_1);

            void countAvailableLordTargets(int param_1);

            undefined4 calculateTile2PeoplValueClosestToUnit(int unitID);

            int assignUnitToEnemyLordTarget(undefined4 param_1);

            void setGate2(int param_1, int param_2);

            undefined4 assignUnitToNearestEnemyGateTarget(int unitID);

            void setWide3(int param_1, int param_2);

            undefined4 getClosestWideValueBasedOnPlayer(int playerID);

            void setMoat3(int checkAgainstNonZero, int playerID);

            undefined4 calculateTile2MoatValueClosestToUnit(int unitID);

            int findMoatTileToDig(int param_1);

            undefined4 findMoatDiggingTribeTarget();

            void countAvailableHighTargets(int param_1);

            int calculateHigh2ClostestToTribeTargetUnit(int tribeID);

            void countAvailableArcherTargets(int param_1);

            int calculateArch2ClosestToTribeTargetUnit(int tribeID);

            void recomputeAIApproachLayer1();

            void recomputeAIApproachLayer2();

            void recomputeAIApproachLayer4();

            int findArcherPointIndexForTile(int param_1);

            void validateAttackInfoEntries();

            int assignTribeArcherAttackPosition(int param_1);

            int getSupportPointIndex(int tile);

            void validateSupportPointEntries();

            int getSiegeIndexForTile(int tile);

            void validateTentPointEntries();

            int placeSiegeTentAndOrderConstruction(int tribeID, CommandBuildingTypeInt commandBuildingType);

            BOOLEnum placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers(int tribeID,
                CommandBuildingTypeInt commandBuildingType, uint strategicDistance, UnitInstructionTypeInt instruction);

            int placeTunnelEntrances(int tribeID);

            void clearAIInfoLayerOutsideStartZone();

            void playAttackStartHorn();

            void placeSiegeTentsAndAssignEngineers(int param_1, int param_2);

            void placeTunnelForEveryTunneler(int attackWave);

            int addUnitToNewTribe(undefined4 unitID, int attackWave, AITribeTypeShort tribeType, undefined4 playerID);

            void commandSiegeCrewsExitEquipment(int wave);

            undefined getPlayerNot1AndHasKeep();

            void addAttackTargetTile(int param_1);

            BOOLEnum shouldLightPitchBecauseOfTroopValue(int tile, int playerID);

            undefined4 giveLightPitchInstructionToUnitClosestToPitch(int tile);

            void lightPitchIfNecessary(int unitID, int unitID2);

            void updateArcherBrazierFlags();

            int getValueOfTroopType(UnitTypeInt unitType);

            void aiEngineersThrowOil();

            undefined4 ifNecessaryThrowOilAutomatically(int param_1);

            void commandUnitsToMoveToKeep();

            void collectAIArchersForRepositioning();

            void refillWallArcherPositions();

            void assignMacemenAndKnightsNotFromPlayer1ToTribes();

            void dispatchAggressiveMacemenTribe();

            void dispatchAggressiveKnightTribe();

            void sendAttackingPatrolTribeToComputedDestination(int tribeID);

            void sendTribeAlongAttackPath(int param_1);

            void decideTribeAttackTarget(int tribeID);

            undefined4 commandTribeMoveToNearestEnemyGatehouse(int param_1);

            void moveTowardsParticularUnits(int param_1);

            void dispatchAttackWavePeopleAssault(int param_1);

            void processSiegeRetreatWave(int attackWave);

            void updateTribeBehaviorBasedOnBehaviorType(int tribeID);

            void recomputeAttackInfo(int playerID, int attackedPlayerID);

            void computeAIArcherAttackPoints();

            void computeAISupportPoints();

            void computeAISiegeTentPoints();

            void recountTotalTroopValue();

            void recomputeTotalTroopValueOfTroopsNearKeep();

            void uselessFunction(
                PackagedFileMagicNumInt receivedMapVersion, PackagedFileMagicNumInt packagerMapVersion);

            void recountAttackTroopValue(int param_1);

            void startAttackWave(int param_1);

            void aiRecomputeAttacks2(int param_1, int param_2);

            void aiRecomputeAttacks(undefined4 param_1, int param_2);

            void processSiegeAttackWave(int attackID);

            void runAiAttackWaveLogic(int param_1);

            void runAiAttackWaveLogicSimple(int param_1);

            void aiControlNonSkirmishUnitMovement();
        };

        static_assert_cpp98_obj(sizeof(TroopValueState) == 1062760, TroopValueState);

#pragma pack(pop)

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
