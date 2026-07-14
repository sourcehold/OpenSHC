/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/UnitsState.hpp'
*/

#pragma once

#include "OpenSHC/IO/Graphics/GmIDInt.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/Entities/EntityTypeInt.hpp"
#include "OpenSHC/Map/Units/Instructions/MatchSpeedInstructionEnumInt.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitInstructionTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::IO::PackagedFileMagicNumInt;
        using OpenSHC::IO::Graphics::GmIDInt;
        using OpenSHC::Map::Entities::EntityTypeInt;
        using OpenSHC::Map::Units::Unit;
        using OpenSHC::Map::Units::UnitInstructionTypeInt;
        using OpenSHC::Map::Units::UnitTypeInt;
        using OpenSHC::Map::Units::Instructions::MatchSpeedInstructionEnumInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x002CA7E4
        class UnitsState {
        public:
            uint maxUnitCount; // 0x00000000 length: 4
            uint DAT_UnitCount; // 0x00000004 length: 4
            undefined4 dwUnitMoveProcessCounter; // 0x00000008 length: 4
            undefined4 DAT_LastSelectedUnitID; // 0x0000000C length: 4
            undefined4 unitControlsRelated; // 0x00000010 length: 4
            undefined4 dwUnitCommandUIState; // 0x00000014 length: 4
            undefined4 DAT_LostChimps; // 0x00000018 length: 4
            undefined4 dwNearestEnemyDistanceResult; // 0x0000001C length: 4
            undefined4 totalUnitsInSelection; // 0x00000020 length: 4
            int unitCountOfSelection[9]; // 0x00000024 length: 36
            byte unusedBytes01[44]; // 0x00000048 length: 44
            byte DAT_SelectedUnitsBitFlags[400]; // 0x00000074 length: 400
            byte unusedBytes02[852]; // 0x00000204 length: 852
            BOOLEnum hasEngineerSelected; // 0x00000558 length: 4
            undefined4 dwSelectionEnemyOwnerID; // 0x0000055C length: 4
            undefined4 dwLastSelectedStoneThrowerID; // 0x00000560 length: 4
            undefined4 selectionEuropeanArchers; // 0x00000564 length: 4
            undefined4 selectionSpearmen; // 0x00000568 length: 4
            undefined4 selectionMacemen; // 0x0000056C length: 4
            undefined4 selectionCrossbowmen; // 0x00000570 length: 4
            undefined4 selectionPikemen; // 0x00000574 length: 4
            undefined4 selectionSwordsmen; // 0x00000578 length: 4
            undefined4 selectionKnights; // 0x0000057C length: 4
            undefined4 selectionEngineers; // 0x00000580 length: 4
            int selectionLaddermen; // 0x00000584 length: 4
            int selectionTunnelers; // 0x00000588 length: 4
            int selectionMonks; // 0x0000058C length: 4
            int selectionCatapults; // 0x00000590 length: 4
            int selectionTrebuchets; // 0x00000594 length: 4
            int selectionBatteringRam; // 0x00000598 length: 4
            int selectionSiegeTower; // 0x0000059C length: 4
            int selectionShield; // 0x000005A0 length: 4
            int selectionMangonel; // 0x000005A4 length: 4
            int selectionBallista; // 0x000005A8 length: 4
            int field34_0x5ac; // 0x000005AC length: 4
            int selectionArabArcher; // 0x000005B0 length: 4
            int selectionArabSlave; // 0x000005B4 length: 4
            int selectionArabSlinger; // 0x000005B8 length: 4
            int selectionArabAssassin; // 0x000005BC length: 4
            int selectionArabHorseArchers; // 0x000005C0 length: 4
            int selectionArabSwordsman; // 0x000005C4 length: 4
            int selectionArabFireThrower; // 0x000005C8 length: 4
            int selectionFireBallista; // 0x000005CC length: 4
            int selectionSlots[8]; // 0x000005D0 length: 32
            int nSelectionChangedFlag; // 0x000005F0 length: 4
            undefined4 dwLadderClimbTargetX; // 0x000005F4 length: 4
            undefined4 dwLadderClimbTargetY; // 0x000005F8 length: 4
            byte unusedBytes03[8]; // 0x000005FC length: 8
            undefined4 dwLastSelectionClickTimeMs; // 0x00000604 length: 4
            undefined4 dwDoubleClickSelectedUnitID; // 0x00000608 length: 4
            undefined4 DAT_EuroUnitAcquisitionFailReason; // 0x0000060C length: 4
            undefined4 DAT_EuroUnitRequiredResource; // 0x00000610 length: 4
            Unit units[2500]; // 0x00000614 length: 2920000
            short unusedUnitIDArray[2500]; // 0x002C9454 length: 5000
            int unusedUnitIDArrayIndex; // 0x002CA7DC length: 4
            DWORD creationTime; // 0x002CA7E0 length: 4

        private:
            UnitsState(UnitsState const&);
            void operator=(UnitsState const&);

        public:
            UnitsState() {};
            ~UnitsState() {};

            // Constructor
            UnitsState* Constructor_UnitsState();

            void clearAllUnits();

            int assignPeasantToBuilding(UnitTypeInt unitType, int buildingID, int playerID, int workerIndex);

            int euroRecruit(int unitType, undefined4 playersBarracksID, int playerID, int param_4);

            int nonEuroRecruit(UnitTypeInt unitType, undefined4 recruitmentBuilding, int playerID, int param_4);

            int disbandUnit(int unitID);

            void assignNameToUnit(int unitID);

            void removeUnitFromItsTribe(uint unitID, int unitUID);

            undefined makeUnitStopWalkingByClearingPathProgressState();

            int checkUnitHasPropertyBasedOnUnitType(int unitID, int property);

            void recomputeUnitStandingHeight(int unitID);

            void setMoveDelayForUnitsOnSameTiles(int unitID, int unitIDCurrentTilePosition);

            void setupUnitSharingTileIDs(int unitID, int unitCurrentTilePosition);

            undefined4 isUnitLinkedOnTile(int unitID);

            undefined ifAnyUnitOnSameTileIsLadder();

            undefined4 ifAnyUnitOnSameTileIsLadderInRightDirection(int tile, int y);

            void detectTileUnitDesync(int tile);

            void removeUnitsSameTileLinkageIfNoLongerApplicable();

            void calculateUnitMovementSpeed(int unitID);

            undefined4 makeSeatedUnitStand(int param_1);

            undefined4 makeUnitSit(int param_1);

            void setUnitFacingTowardUnit(int param_1, int param_2);

            void setUnitFacingTowardPoint(int param_1, int param_2, int param_3);

            undefined4 setUnitFacingDirectionTowardsTarget(int unitID, int targetUnitID);

            void orientUnitTowardUnit(int param_1, int param_2);

            bool setUnitFacingDirectionForTargetXandY(int unitID, int targetX, int targetY);

            uint setUnitFacingDirectionBasedOnBuilding(int unitID, int buildingID);

            BOOLEnum isUnitComputerManaged(int param_1);

            void playHurtSFXForUnit(int unitID);

            int countAlivePlayerUnits(int param_1);

            void killPlayerTowerUnits(int param_1);

            void killAllUnownedUnits();

            void removeWildlifeAnimals();

            void killUnits(int playerID);

            void reassignFarmAnimals(int fromPlayer, int toPlayer);

            void makeCourtMemberUnitsDisappearAndSwapAllOtherUnitsOwnership(int param_1, int param_2);

            void makeUnitsDisappearThatCannotReachTheKeep(int playerID);

            void setRandomNumberOnCows(int playerID);

            void setMissionNumberSpecificLord(int missionNumber);

            undefined checkIfCitizenUnitIsAliveBasedOnState();

            bool canUnitsEngageEachOther(int param_1, int param_2);

            int ComputeDamageFearFactorBonus(int damage, int playerID);

            undefined4 processUnitAttackOtherUnit(int unitID, int unit2ID);

            BOOLEnum processEntityDamageToUnit(int unitID, int entityID, int tileDistance);

            undefined4 processFireDamageToUnit(int unitID, int playerID, int halfTheDamage);

            void shootProjectile(int unitID, EntityTypeInt projectileType, int targetX, int targetY, int targetZUnk);

            void recomputeTroopValuesForPlayer(int playerID);

            int getArmySize(int playerID);

            int distanceComputationForSomeOldCodeForSomeMissions(int param_1);

            BOOLEnum returnFalse();

            void setRandomShootLocation(int unitID, int microX, int microY, int z);

            int getRemainingRequiredEngineers(int unitID);

            BOOLEnum checkTargetBuildingPossibilityOrState(int unitID);

            BOOLEnum findClosestLaddermanWithLadderPosition(int unitID);

            int findAndDestroyAdjacentLadder(int param_1, int param_2);

            BOOLEnum getDestination2EqualsGivenCoordinates(int unitID, int x, int y);

            bool isUnitAtDestination(int param_1);

            BOOLEnum unitReachedDestination(int unitID);

            BOOLEnum isTunnelerNotFinished(int param_1);

            undefined4 commitUnitLadderClimbPath(int unitID, uint param_2, int param_3, int param_4);

            void changeDestinationByAmount(int unitID, int leftover);

            void changeDestinationByLeftover(int unitID);

            void tracePathFromLadderExitSetDestination(int unitID);

            void updateUnitFadeBehindStructures(int unitID);

            undefined markTunnelerFinishedDigging();

            void removeTrappedWallUnit(int param_1);

            void updateMicroPosition(int unitID);

            void adjustUnitMapOrientationRelatedPositionBasedOnMapOrientationCorrectedFacingDirection(int param_1);

            void digTunnelAlongPath(uint unitID);

            int stopUnitIfNextToTarget(int unitID);

            undefined4 isUnitAdjacentToWorkplace(int param_1);

            undefined4 setWorkplaceBuildingEntryAsTarget(int unitID, int entryAngleUnk);

            BOOLEnum unitIsInMoat(int unitID);

            void markUnitTileOccupancy(int param_1);

            void writeSixToTileMap1104InAllDirections(int unitID, undefined4 six);

            int getUnitThatFulfillsSomeTimebasedAndLocationBasedCriteria(
                int unitID, int playerID, int unitXPosition, int unitYPosition, int zero1, int zero2);

            int selectNewBlessingTarget(int unitID);

            void selectUnitsInDragBox();

            void selectOwnUnitsInDragBox();

            void selectSingleUnitInDragBox();

            void selectAllUnitsOfType(int param_1, int param_2);

            void deselectAllUnitsOneByOne();

            undefined deselectUnit();

            void filterUnitSelectionExcludeUnitType(int unitType);

            void filterUnitSelectionForUnitType(int unitType);

            void recountUnitsInSelection();

            int isSelectionOnlyEngineers();

            BOOLEnum selectionHasEngineers();

            BOOLEnum selectionHasArchers();

            undefined4 selectionHasAdvancedUnit();

            undefined4 selectionHasSiegeAndOther();

            uint findEngineerAtOilSmelter();

            int isSelectionOnlyTunnelers();

            BOOLEnum selectionContainsRangedOnlyUnits();

            int isSelectionOnlyLaddermen();

            BOOLEnum selectionContainsOnlyArabAssassins();

            int isSelectionOnlyShields();

            undefined4 selectionHasSiegeCoverAndOther();

            undefined4 selectionHasShieldOrTowerAndOther();

            undefined4 selectionHasNoRangedUnits();

            undefined4 selectionCanDigMoat();

            uint getSelectedLordUnit();

            int createUnitSelection();

            int createTribeFromSelectedUnits();

            void playerMakeUnitSelection(int playerID, int tribeID);

            void queueTribeCommand(undefined4 param_1);

            void assignUnitToTribeWithSiegeSpeech(int playerID, int unitID, int tribeID);

            void makeSelectionBasedOnShortcut(int section1099ID);

            BOOLEnum isUnitShortcutAvailable(int unitHotKeyNumber);

            void selectAllTribeUnitsForPlayer(int playerID, int tribeID);

            UnitTypeInt getUnitTypeOfFirstSelectedUnit();

            undefined4 selectionHasFieldUnit();

            uint findSelectedUnitOfTypes(int param_1, int param_2);

            int getMaxSelectedCatapultAmmo();

            undefined4 countSelectedStoneThrowers();

            uint returnFirstSelectedEngineer();

            uint getTunnelerIDOnlyIfFirstSelected();

            uint getSelectedLadderUnit();

            undefined4 canAUnitClimb();

            uint getSelectedSiegeEngine();

            uint getSelectedStoneThrower();

            BOOLEnum canCaptureTowerAtTile(int param_1);

            undefined4 checkAnySelectedUnitCannotClimb();

            BOOLEnum canManSiegeEngine(int param_1);

            int selectionContainsCombatUnit(uint unitID);

            void queueUnitCommand0F();

            void queueCommand0xF(undefined4 unitType);

            void queueClickNavigateMenuOrEscape(undefined4 param_1);

            void clearUnitSelectionAndTribe(int playerID, uint unitID, int unitType);

            void clearSelectionCounts();

            void giveMoveCommand(int tribeID, int x, int y, int patrol, int matchUnitSpeeds);

            void giveTribeMoveInstructionHumans(
                int tribeID, uint x, uint y, int rallyBool, MatchSpeedInstructionEnumInt speedMatching);

            void extendRallyPoint(int tribeID, int mouseX, int mouseY, int rallyCount);

            void queueDisbandAndAttackCommand(undefined4 param_1, undefined4 param_2);

            void queueDisbandAndAttackUnitsCommand(undefined4 param_1, undefined4 param_2, undefined4 param_3);

            void queueCommand_36d(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4);

            void queueCommand_36_variation2(undefined4 param_1, UnitInstructionTypeInt instruction, undefined4 param_3,
                undefined4 param_4, undefined4 param_5);

            void giveTribeAnInstruction2(
                int tribeID, UnitInstructionTypeInt instructionType, int targetID_1, int targetID_2, int param_5);

            uint findFreeTileNearby(uint unitID, uint tile);

            BOOLEnum findTunnelTarget(int originBuildingID, int targetPlayer);

            int getAliveLordForPlayer(int playerID);

            int getRawDeerCount();

            void findNearestHuntableDeer(int param_1);

            int findNearestIdleCow(int param_1, int param_2, int param_3);

            int findClosestAnimalStoreResult(int maxDistance, BOOLEnum excludeCows, uint x, uint y);

            int findClosestEnemyUnitInArea(int param_1, uint param_2, uint param_3, int param_4);

            undefined4 tryAttackUnitID(int unitID_1, int unitID_2);

            void setTowerSiegeEngineToIdle(int buildingID);

            void setAIControlStatusTo100000();

            int getUnitAnimationIndex(int unitIndex, int* param_2);

            GmIDInt getPeasantGmID(int unitID);

            undefined4 chooseHusbandAndWife(int* husbandID, int* wifeID);

            undefined isWorkerInProductionState();

            int computeWorkerNextAction(int param_1);

            int findPlayerOperationalSiegeEngine(int param_1);

            int getLivingSelectableUnit(int playerID);

            void renderDebugDataUnitData(int x, int y, int width, int height);

            void setUnitValues(int unitID, UnitTypeInt unitType);

            void commitUnitPositionUpdate(int unitID);

            void setupUnitSharingCurrentTilePosition(int unitID);

            void teleportUnitToUnitXAndY(int unitID);

            int getEnemyUnitIDNearby(int unitID, int tileUnk, int unitHeight);

            int prepareProjectileTarget(int shooterID, int targetID, int param_3);

            undefined4 aiSiegeUnitPickTargetAndShoot(int unitID);

            BOOLEnum setDestinationForUnit(int unitID, uint x, uint y, int reusePathingInfo);

            void resumeUnitMovement(int unitID);

            void exitLadder(int unitID);

            uint getUnitInHitBox(undefined4 param_1);

            undefined4 setUnitDestinationNextToTargetBuilding(int unitID, int param_2);

            int computePeasantThoughtBubble(int unitID);

            void upgradeMapFormatForUnits(
                PackagedFileMagicNumInt receivedMapVersion, PackagedFileMagicNumInt packagerMapVersion);

            int spawnUnit(int playerID, int displayColor, int microXPosition, int microYPosition, int terrainHeight,
                UnitTypeInt unitType);

            int changeUnitType(int unitID);

            void deleteUnit(uint unitID);

            void commitUnitLocation(int unitID);

            void someUnitMoveFunction(int unitID);

            void revealHiddenUnit(int unitID);

            void setPositionOfUnit(int unitID, uint x, uint y, undefined4 height);

            void commitMimmicLocation(int unitID);

            BOOLEnum ifOnADefensiveStructureSetDestinationInDirectionOfTarget(int unitID);

            void processMeleeInitiation(int unitID);

            void resumeUnitIfNotAttacking(int param_1);

            dword unitAcquireBestEnemyTargetAndPursue(int unitID);

            BOOLEnum acquireAndSetShootTarget(short* unitID);

            BOOLEnum updateClimbing(int unitID);

            void unitClimbing(int param_1);

            int handleUnitMovementWhenTargetingBuildings(int unitID);

            BOOLEnum moveToFreeTileNearby(int unitID);

            undefined4 processUnitMove(int unitID, int speedCategory);

            void updateUnits();
        };

        static_assert_cpp98_obj(sizeof(UnitsState) == 2926564, UnitsState);

#pragma pack(pop)

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
