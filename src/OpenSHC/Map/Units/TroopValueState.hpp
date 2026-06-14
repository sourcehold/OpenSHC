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
            TroopValueState();
            ~TroopValueState();

            // Constructor
            TroopValueState* Constructor_TroopValueState();

            void clearAttackInfo();

            void FUN_00518180(int param_1, int param_2);

            BOOLEnum searchTribeWithProperties(int param_1);

            undefined4 FUN_00518350();

            void sortAttackInfoTribeIDArrayBasedOn(
                int attackWave, int shrinkSize, int tribeSizeSumLimit, SomeTribeBehaviorType someTribeTypeIdentifier);

            void applyTribeBehaviorTypes(
                SomeTribeBehaviorType tribeBehaviorType, SomeTribeBehaviorType tribeBehaviorType2, int off1, int off2);

            void FUN_00518930(SomeTribeBehaviorType param_1, undefined4 param_2, short param_3, short param_4);

            void FUN_00518a10(
                int param_1, int param_2, SomeTribeBehaviorType param_3, undefined4 param_4, undefined4 param_5);

            BOOLEnum isLessThanPercentageOfTribesInAttackDying(int attackID, int leDyingPerc);

            void renderDebugDataZoneDataUnk(int x, int y, int width, int height);

            void FUN_00519310();

            void FUN_00519690(int tribeID);

            void FUN_00519790(int param_1);

            void FUN_00519850(int param_1);

            void recomputeTargetedBuildingTilesArray(int playerID);

            BOOLEnum getTileInTargetedBuildingTiles(int tile);

            void hack2related(int attackedPlayerID, int attackingPlayerID);

            undefined4 findEnemyWalls(int unitID);

            void setScale3(int one, int playerID);

            undefined4 meth_0x519e40(int unitID);

            void setTown2(int param_1, int playerID);

            undefined4 findEnemyBuildingsClosestToUnit(int unitID);

            void FUN_0051a0c0(int param_1);

            void FUN_0051a100(int param_1);

            undefined4 calculateTile2PeoplValueClosestToUnit(int unitID);

            int findEnemyLordUnk(undefined4 param_1);

            void setGate2(int param_1, int param_2);

            undefined4 findEnemyTowersOrGatesUnk(int unitID);

            void setWide3(int param_1, int param_2);

            undefined4 getClosestWideValueBasedOnPlayer(int playerID);

            void setMoat3(int checkAgainstNonZero, int playerID);

            undefined4 calculateTile2MoatValueClosestToUnit(int unitID);

            int meth_0x51a8a0(int param_1);

            undefined4 meth_0x51a920();

            void FUN_0051a9a0(int param_1);

            int calculateHigh2ClostestToTribeTargetUnit(int tribeID);

            void FUN_0051ab10(int param_1);

            int calculateArch2ClosestToTribeTargetUnit(int tribeID);

            void FUN_0051ace0();

            void FUN_0051ae00();

            void FUN_0051ae90();

            int unkArcherRelated1(int param_1);

            void FUN_0051af70();

            int FUN_0051aff0(int param_1);

            int getSupportPointIndex(int tile);

            void FUN_0051b110();

            int getSiegeIndexForTile(int tile);

            void FUN_0051b290();

            int placeSiegeTentAndAssignEngineersUnk(int tribeID, CommandBuildingType commandBuildingType);

            BOOLEnum placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers(int tribeID,
                CommandBuildingType commandBuildingType, uint strategicDistance, UnitInstructionType instruction);

            int placeTunnelEntrances(int tribeID);

            void FUN_0051b680();

            void FUN_0051b6c0();

            void placeSiegeTentsAndAssignEngineers(int param_1, int param_2);

            void placeTunnelForEveryTunneler(int attackWave);

            int addUnitToNewTribe(undefined4 unitID, int attackWave, AITribeType tribeType, undefined4 playerID);

            void exitSiegeEquipmentUnk(int wave);

            BOOLEnum getPlayerNot1AndHasKeep(int playerID);

            void FUN_0051be60(int param_1);

            BOOLEnum shouldLightPitchBecauseOfTroopValueUnk(int tile, int playerID);

            undefined4 giveLightPitchInstructionToUnitClosestToPitch(int tile);

            void lightPitchIfNecessary(int unitID, int unitID2);

            void meth_0x51c2d0();

            int getValueOfTroopType(UnitType unitType);

            void FUN_0051c470();

            undefined4 ifNecessaryThrowOilAutomatically(int param_1);

            void commandUnitsToMoveToKeep();

            void meth_0x51ca50();

            void FUN_0051cbd0();

            void assignMacemenAndKnightsNotFromPlayer1ToTribes();

            void FUN_0051cf90();

            void FUN_0051d020();

            void sendAttackingPatrolTribeToComputedDestination(int tribeID);

            void FUN_0051d1c0(int param_1);

            void FUN_0051d2b0(int tribeID);

            undefined4 moveUnitsToGateHouseUnk(int param_1);

            void moveTowardsParticularUnits(int param_1);

            void meth_0x51d690(int param_1);

            void meth_0x51d730(int attackWave);

            void updateTribeBehaviorBasedOnBehaviorType(int tribeID);

            void recomputeAttackInfo(int playerID, int attackedPlayerID);

            void FUN_0051f340();

            void FUN_0051f4b0();

            void FUN_0051f5c0();

            void recountTotalTroopValue();

            void recomputeTotalTroopValueOfTroopsNearKeep();

            void uselessFunction(PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

            void recountAttackTroopValue(int param_1);

            void meth_0x51ff90(int param_1);

            void aiRecomputeAttacks2(int param_1, int param_2);

            void aiRecomputeAttacks(undefined4 param_1, int param_2);

            void meth_0x520450(int attackID);

            void meth_0x5205a0(int param_1);

            void meth_0x520cd0(int param_1);

            void aiControlNonSkirmishUnitMovement();
        };

        static_assert_cpp98_obj(sizeof(TroopValueState) == 1062760, TroopValueState);

#pragma pack(pop)

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
