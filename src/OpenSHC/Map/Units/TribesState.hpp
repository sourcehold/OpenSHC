/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/TribesState.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnumShort.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnumInt.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorTypeInt.hpp"
#include "OpenSHC/Map/Units/Tribe.hpp"
#include "OpenSHC/Map/Units/UnitIDMovementDistancePair.hpp"
#include "OpenSHC/Map/Units/UnitInstructionTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::CommandBuildingTypeInt;
        using OpenSHC::IO::PackagedFileMagicNumInt;
        using OpenSHC::Map::Units::SomeTribeBehaviorTypeInt;
        using OpenSHC::Map::Units::Tribe;
        using OpenSHC::Map::Units::UnitIDMovementDistancePair;
        using OpenSHC::Map::Units::UnitInstructionTypeInt;
        using OpenSHC::Map::Units::UnitTypeInt;
        using OpenSHC::Map::Units::Behavior::UnitStanceEnumShort;
        using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnumInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x000FB3D0
        class TribesState {
        public:
            undefined4 DAT_CurrentTribeID; // 0x00000000 length: 4
            int clans; // 0x00000004 length: 4
            undefined4 field2_0x8; // 0x00000008 length: 4
            undefined4 ALG_ResultX; // 0x0000000C length: 4
            undefined4 ALG_ResultY; // 0x00000010 length: 4
            undefined4 ALG_ResultTileIndex; // 0x00000014 length: 4
            undefined4 dwTribeMoveInstructionCounter; // 0x00000018 length: 4
            BOOLEnum patrolButtonPressed; // 0x0000001C length: 4
            undefined4 rallyCount; // 0x00000020 length: 4
            undefined4 field9_0x24; // 0x00000024 length: 4
            Tribe tribes[1250]; // 0x00000028 length: 1025000
            UnitIDMovementDistancePair someUnitIDMovementDistancePair[1001]; // 0x000FA410 length: 4004
            int someUnitIDArrayCount; // 0x000FB3B4 length: 4
            int fcn_mtribe; // 0x000FB3B8 length: 4
            int tribeCopiedToSlot0; // 0x000FB3BC length: 4
            int nEventMinimapTargetX; // 0x000FB3C0 length: 4
            int nEventMinimapTargetY; // 0x000FB3C4 length: 4
            undefined1 padding_0xfb3c8[8]; // 0x000FB3C8 length: 8

        private:
            TribesState(TribesState const&);
            void operator=(TribesState const&);

        public:
            TribesState() {};
            ~TribesState() {};

            // Constructor
            TribesState* Constructor_TribesState();

            void giveUnitSelectionMoveInstructionNoMatchedSpeed(
                undefined4 tribeID, undefined4 x, undefined4 y, undefined4 rallyBool, undefined4 doRally);

            int getSmallestPatrolTribe(int playerID, int tribeCount);

            void clearAllTribes();

            void reassignTribeOwnership(int param_1, int param_2);

            void swapTribeOwnership(int param_1, int param_2);

            undefined4 assignTribeUnitTarget(int unitID, int param_2);

            void projectPursuitInterceptAlongPathPlan(
                int targetUnitID, int unitID, int* unitCurrentX, int* unitCurrentY);

            UnitTypeInt getMostCommonSelectedUnitType(undefined4 tribeID, int* maximumCount);

            void playSelectedUnitOrderSpeech(int param_1);

            void playTribeSelectionSpeech(int selectionID, int unitID);

            void playUnitOrderSpeech0B(undefined4 param_1);

            void playAttackOrderSpeech(undefined4 param_1);

            void playSiegeOrEngineerOrderSpeech(int param_1);

            void playUnitOrderSpeech29(undefined4 param_1);

            void playTunnelerDigSpeech();

            void playUnitOrderSpeech24(undefined4 param_1);

            void applyTribeBehaviorType(int attackWave, SomeTribeBehaviorTypeInt tribeBehaviorType);

            void selectPeasantsAtBuilding(int param_1, int param_2, int param_3);

            uint tribeCorrespondsWithUID(int tribeID, uint tribeUID);

            int getUnitIDForIndexInTribe(int tribeID, int unitSelectionIndex);

            int getSpecificUnitFromTribe(int tribeID, int param_2);

            int setWhetherTribeContainsAnyUnits(int tribeID);

            void addUnitToSelected(uint unitID);

            BOOLEnum unitIsSelectedByPlayer(uint tribeID);

            int addUnitToTribe(uint unitID, int tribeID);

            void removeUnitFromThisTribeIfInTribe(uint unitID, int tribeID);

            int getAvailableTribeID(int playerID);

            int createTribeForPlayer(int playerID);

            int createTribe(int playerID, int setAsCurrentTribeID);

            int createPlayerTribe(int playerID, undefined4 one, int tribeID);

            void addUnitsToTribeAndComputeMovementSpeed(int playerID, int tribeID);

            void addUnitToTribeAndUpdateTribeMovementSpeed(int param_1, uint unitID, int tribeID);

            void clearTribe(int param_1);

            void queueUnitStance(undefined4 stanceID, undefined4 param_2);

            void setUnitStance(int tribeID, UnitStanceEnumShort unitStance);

            void addRallyPoint(int section1016ID, short destinationX, short destinationY, int step);

            void temporarilyStoreTribeIfAllNewlySelectedUnitsPartOfThisTribe_And_AlwaysRememberStance(int playerID);

            void importStoredInfoFromSlot0(undefined4 param_1, int tribeID);

            void shrinkTribeToSize(undefined4 tribeID, int smallerSize);

            void spawnUnitsForTribe(undefined4 param_1, int param_2, int param_3, int param_4, UnitTypeInt param_5,
                int param_6, int param_7);

            dword spawnUnitsIntoNewTribe(undefined4 counter, int tribeType, int x, int y, int playerID,
                UnitTypeInt unitType, UnitTypeInt unitType2, int unitType1Count, int unitType2Count);

            dword createTribeWithSpawn(short param_1, undefined4 param_2, int param_3, int param_4, int param_5,
                UnitTypeInt param_6, int param_7);

            dword spawnUnitsAroundLocation(
                undefined4 param_1, int aroundX, int aroundY, int playerID, UnitTypeInt unitType, int count);

            void storeDeerXAndYinMapInfo(undefined4 x, undefined4 y);

            void storeLionXAndYInMapInfo(undefined4 x, undefined4 y);

            void setRabbitSpawnXY(undefined4 x, undefined4 y);

            void setCamelSpawnXY(undefined4 x, undefined4 y);

            undefined4 findAiSpawnPoint(uint* param_1, uint* param_2);

            undefined4 hasRabbitOrMercSpawnAvailable();

            void updateTribeAnimalScatter(int tribeID);

            int getNonDyingUnit(int tribeID);

            void countDeerEfficiently();

            void markTribeAsAnimal(int param_1);

            void flagTribesOfType(int param_1);

            void updateNTribesOfType(int param_1, int param_2);

            void aiAssignNewUnitToTribe(int playerID, int unitType, int unitID);

            int disperseTribeToArea(int param_1);

            void drawFlagsAndUnitDestinations(int tribeID);

            void migrateTribesForMapVersion(
                PackagedFileMagicNumInt receivedMapVersion, PackagedFileMagicNumInt packagerMapVersion);

            undefined4 updateTribeRallyFlags(int param_1);

            void unsetRallyRelatedFlagOnUnits(int tribeID);

            BOOLEnum isTribeAllAssassins(int tribeID);

            int getFirstUnitInTribeThatIsOnXTerrain(int selectionID);

            undefined4 tribeHasDeployedLadder(int param_1);

            undefined4 tribeContainsUnitThatCanClimb(int param_1);

            BOOLEnum selectionContainsHorses(int param_1);

            UnitTypeInt getMajorityArcherTypeEuropeanOrArabian(int selectionID);

            undefined4 applyMoveCommandOrRallyCommandToTribe(
                int tribeID, undefined4 x1, undefined4 y1, undefined4 isRallying, int storeAsRallyPoint);

            undefined4 commandTribeAttackWave(int tribeID, SomeTribeBehaviorTypeInt targetType);

            undefined4 stopTribeUnitsMoving(int param_1);

            void buildTribeDestinationQueue(int tribeID, int horseAndRamCount);

            undefined4 isTribeUnitBlocked(int param_1);

            int getTribeAliveStatus(int tribeID);

            undefined4 canTribeReachAreaUnobstructed(
                int param_1, uint param_2, uint param_3, uint param_4, uint param_5);

            void commandTribeClimbLadders(int param_1);

            void applyUnitTopSpeedDelayBasedOnTribeSize(int tribeID, BOOLEnum param_2);

            void playArcherOrderSpeech(int selectionID);

            BOOLEnum anyUnitsOfTribeAreOutsideCoverageOfPathFindingAlg(int tribeID, int algTileFlag);

            void applyMovementDistanceToUnitsInTribe(int param_1);

            void applyMovementDistanceToUnitsInTribeBasedOnUnitNumberInTribe(int param_1);

            undefined4 tribeHasNoFinishedTunneler(int param_1);

            void setTargetUnitForTribe(int tribeID);

            void setTribeUnitsState(int param_1, undefined4 param_2);

            void resetTribeUnitsToIdle(int param_1);

            BOOLEnum allUnitsReachedTheirDestination(int tribeID);

            void makeTribeUnitsDisappear(int param_1);

            BOOLEnum addUnitToNewTribe(uint unitID);

            void removeSelectedUnitsFromTheirCurrentTribes(int playerID);

            void clearTribesOfUnitType(int param_1, int param_2);

            void clearTribesNotOfUnitType(int playerID, int unitType);

            void removeUnitFromTribe(uint unitID, int tribeID);

            int popUnitFromTribe(int tribeID);

            dword createAnimal(CommandBuildingTypeInt animalType, uint x, uint y, int tile);

            BOOLEnum spawnDeerLionOrRabbit(int tribeID, int param_2, UnitTypeInt unitType);

            undefined4 maybeSpawnTribeAnimal(int param_1, int param_2, int param_3, int param_4);

            void respawnDeer();

            void spawnRabbitAtValidPoint();

            void upgradeMapTribesState(
                PackagedFileMagicNumInt receivedMapVersion, PackagedFileMagicNumInt packagerMapVersion);

            undefined4 giveTribeMoveInstruction(int tribeID, uint x1, uint y1, int rallyBool, int storeAsRallyPoint,
                UnitMatchSpeedEnumInt speedMatching);

            undefined4 commandUnitsToLocation(
                int tribeID, uint destinationX, uint destinationY, undefined4 matchUnitSpeeds);

            void computeTribePercentages(int tribeID);

            void updateTribeUnitAssignments();

            void spawnScenarioAttackWaves();

            undefined4 giveTribeAnInstruction(
                int tribeID, UnitInstructionTypeInt unitInstructionType, int id__x__tile, int unitUID__Y, int param_5);

            void scatterTribeToReachableSpot(int param_1);

            int moveTribeToScatterSpot(int param_1);

            void updateTribeAttackBehaviour(int tribeID);

            void processDeerMoving(int tribeID);

            void updatePredatorTribeAI(int param_1);

            void updateRabbitTribeAI(int param_1);

            void updateCamelTribeAI(int param_1);

            void updateTribes();
        };

        static_assert_cpp98_obj(sizeof(TribesState) == 1029072, TribesState);

#pragma pack(pop)

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
