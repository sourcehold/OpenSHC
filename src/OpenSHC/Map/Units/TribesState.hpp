/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/TribesState.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingType.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/Tribe.hpp"
#include "OpenSHC/Map/Units/UnitIDMovementDistancePair.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::CommandBuildingType;
        using OpenSHC::IO::PackagedFileMagicNum;
        using OpenSHC::Map::Units::SomeTribeBehaviorType;
        using OpenSHC::Map::Units::Tribe;
        using OpenSHC::Map::Units::UnitIDMovementDistancePair;
        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
        using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;
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
            undefined4 field6_0x18; // 0x00000018 length: 4
            BOOLEnum patrolButtonPressed; // 0x0000001C length: 4
            undefined4 rallyCount; // 0x00000020 length: 4
            undefined4 field9_0x24; // 0x00000024 length: 4
            Tribe tribes[1250]; // 0x00000028 length: 1025000
            UnitIDMovementDistancePair someUnitIDMovementDistancePair[1001]; // 0x000FA410 length: 4004
            int someUnitIDArrayCount; // 0x000FB3B4 length: 4
            int fcn_mtribe; // 0x000FB3B8 length: 4
            int tribeCopiedToSlot0; // 0x000FB3BC length: 4
            int unknownX_01; // 0x000FB3C0 length: 4
            int unknownY_01; // 0x000FB3C4 length: 4
            undefined1 padding_0xfb3c8[8]; // 0x000FB3C8 length: 8

        private:
            TribesState(TribesState const&);
            void operator=(TribesState const&);

        public:
            TribesState() {};
            ~TribesState() {};

            // Constructor
            TribesState* constructTribesState();

            void giveUnitSelectionMoveInstructionNoMatchedSpeed(
                undefined4 tribeID, undefined4 x, undefined4 y, undefined4 rallyBool, undefined4 doRally);

            int getSmallestPatrolTribe(int playerID, int tribeCount);

            void clearAllTribes();

            void reassignOwnerForTribesOfBehaviorType2(int param_1, int param_2);

            void swapTribeOwnership(int param_1, int param_2);

            undefined4 moveUnitToBehaviorTarget(int unitID, int param_2);

            void predictUnitInterceptPosition(int targetUnitID, int unitID, int* unitCurrentX, int* unitCurrentY);

            UnitType getMajoritySelectedUnitType(undefined4 tribeID, int* maximumCount);

            void playUnitSelectionSound(int param_1);

            void playUnitCombatSpeechForTarget(int selectionID, int unitID);

            void playUnitSelectSpeech(undefined4 param_1);

            void playUnitMoveSpeech(undefined4 param_1);

            void playAttackCommandFeedback(int param_1);

            void playPatrolCommandSpeech(undefined4 param_1);

            void playTunnelerCommandSpeech();

            void playWorkCommandSpeech(undefined4 param_1);

            void applyTribeBehaviorType(int attackWave, SomeTribeBehaviorType tribeBehaviorType);

            void updatePeasantSeatingAtBuilding(int param_1, int param_2, int param_3);

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

            void setUnitStance(int tribeID, UnitStanceEnum unitStance);

            void addRallyPoint(int section1016ID, short destinationX, short destinationY, int step);

            void snapshotSelectionTribeAndComputeStance(int playerID);

            void importStoredInfoFromSlot0(undefined4 param_1, int tribeID);

            void trimTribeToSize(undefined4 tribeID, int smallerSize);

            void spawnUnitsForAITribe(
                undefined4 param_1, int param_2, int param_3, int param_4, UnitType param_5, int param_6, int param_7);

            dword spawnUnitsIntoNewTribe(undefined4 counter, int tribeType, int x, int y, int playerID,
                UnitType unitType, UnitType unitType2, int unitType1Count, int unitType2Count);

            dword createTribeWithSpawnedUnit(
                short someIndex, undefined4 tribeType, int x, int y, int playerID, UnitType unitType, int count);

            dword spawnUnitsAroundLocation(
                undefined4 param_1, int aroundX, int aroundY, int playerID, UnitType unitType, int count);

            void storeDeerXAndYinMapInfo(undefined4 x, undefined4 y);

            void storeLionXAndYInMapInfo(undefined4 x, undefined4 y);

            void setRabbitSpawnXY(undefined4 x, undefined4 y);

            void setCamelSpawnXY(undefined4 x, undefined4 y);

            undefined4 findRecentOrSignpostSpawnLocation(uint* param_1, uint* param_2);

            undefined4 hasAvailableSpawnSlotForWildlifeOrMercs();

            void updateAnimalHerdBehaviorState(int tribeID);

            int getNonDyingUnit(int tribeID);

            void countDeerEfficiently();

            void markTribeAsAnimalTribe(int param_1);

            void flagTribesOfType(int param_1);

            void consumeFlaggedTribesOfType(int param_1, int param_2);

            void aiAssignNewUnitToTribe(int playerID, int unitType, int unitID);

            int scatterTribeUnitsRandomly(int param_1);

            void drawFlagsAndUnitDestinations(int tribeID);

            void upgradeTribeArrayLayoutForMapVersion(
                PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

            undefined4 updateTribeRallyFlags(int param_1);

            void unsetRallyRelatedFlagOnUnits(int tribeID);

            BOOLEnum isTribeAllAssassins(int tribeID);

            int getFirstUnitInTribeThatIsOnXTerrain(int selectionID);

            undefined4 tribeHasActiveLaddermanUnit(int param_1);

            undefined4 tribeContainsUnitThatCanClimb(int param_1);

            BOOLEnum selectionContainsHorses(int param_1);

            UnitType getMajorityArcherTypeEuropeanOrArabian(int selectionID);

            undefined4 applyMoveCommandOrRallyCommandToTribe(
                int tribeID, undefined4 x1, undefined4 y1, undefined4 isRallying, int storeAsRallyPoint);

            undefined4 assignAttackTargetsForTribe(int tribeID, SomeTribeBehaviorType targetType);

            undefined4 stopTribeMovementAndCheckIdle(int param_1);

            void sortTribePathDestinationsByCost(int tribeID, int horseAndRamCount);

            undefined4 isTribeUnitBlockedByOtherUnit(int param_1);

            int getTribeAliveStatus(int tribeID);

            undefined4 isTribePathToDestinationClear(
                int param_1, uint param_2, uint param_3, uint param_4, uint param_5);

            void applyLadderDestructionToTribeUnits(int param_1);

            void applyUnitTopSpeedDelayBasedOnTribeSize(int tribeID, BOOLEnum param_2);

            void playArcherCommandSpeech(int selectionID);

            BOOLEnum anyUnitsOfTribeAreOutsideCoverageOfPathFindingAlg(int tribeID, int algTileFlag);

            void applyMovementDistanceToUnitsInTribe(int param_1);

            void applyMovementDistanceToUnitsInTribeBasedOnUnitNumberInTribe(int param_1);

            undefined4 isTribeFreeOfTunnelingUnits(int param_1);

            void setTargetUnitForTribe(int tribeID);

            void setStateForAllTribeUnits(int param_1, undefined4 param_2);

            void standUpAllTribeUnits(int param_1);

            BOOLEnum allUnitsReachedTheirDestination(int tribeID);

            void removeAllTribeUnits(int param_1);

            BOOLEnum addUnitToNewTribe(uint unitID);

            void removeSelectedUnitsFromTheirCurrentTribes(int playerID);

            void clearTribesOfUnitType(int param_1, int param_2);

            void clearTribesNotOfUnitType(int playerID, int unitType);

            void removeUnitFromTribe(uint unitID, int tribeID);

            int popUnitFromTribe(int tribeID);

            dword createAnimal(CommandBuildingType animalType, uint x, uint y, int tile);

            BOOLEnum spawnDeerLionOrRabbit(int tribeID, int param_2, UnitType unitType);

            undefined4 trySpawnAdditionalWildlifeForTribe(int param_1, int param_2, int param_3, int param_4);

            void respawnDeer();

            void spawnWildlifeOrMercAtAvailableSlot();

            void upgradeMapTribesState(
                PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

            undefined4 giveTribeMoveInstruction(
                int tribeID, uint x1, uint y1, int rallyBool, int storeAsRallyPoint, UnitMatchSpeedEnum speedMatching);

            undefined4 commandUnitsToLocation(
                int tribeID, uint destinationX, uint destinationY, undefined4 matchUnitSpeeds);

            void computeTribePercentages(int tribeID);

            void updateTribeUnitAssignments();

            void spawnQueuedReinforcementWaves();

            undefined4 giveTribeAnInstruction(
                int tribeID, UnitInstructionType unitInstructionType, int id__x__tile, int unitUID__Y, int param_5);

            void moveTribeToNearbyClearTile(int param_1);

            int moveTribeToIndexedNearbyTile(int param_1);

            void updateTribeCombatStanceBehavior(int tribeID);

            void processDeerMoving(int tribeID);

            void updateLionWolfTribeBehavior(int param_1);

            void updateRabbitTribeBehavior(int param_1);

            void updateCamelTribeBehavior(int param_1);

            void updateTribes();
        };

        static_assert_cpp98_obj(sizeof(TribesState) == 1029072, TribesState);

#pragma pack(pop)

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
