/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
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
            undefined4 unknownInitially0_01; // 0x00000008 length: 4
            undefined4 DAT_LastSelectedUnitID; // 0x0000000C length: 4
            undefined4 unitControlsRelated; // 0x00000010 length: 4
            undefined4 field5_0x14; // 0x00000014 length: 4
            undefined4 DAT_LostChimps; // 0x00000018 length: 4
            undefined4 unitDistanceComputationResultUnk; // 0x0000001C length: 4
            undefined4 totalUnitsInSelection; // 0x00000020 length: 4
            int unitCountOfSelection[9]; // 0x00000024 length: 36
            byte unusedBytes01[44]; // 0x00000048 length: 44
            byte DAT_SelectedUnitsBitFlags[400]; // 0x00000074 length: 400
            byte unusedBytes02[852]; // 0x00000204 length: 852
            BOOLEnum hasEngineerSelected; // 0x00000558 length: 4
            undefined4 field14_0x55c; // 0x0000055C length: 4
            undefined4 field15_0x560; // 0x00000560 length: 4
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
            int field44_0x5f0; // 0x000005F0 length: 4
            undefined4 unknownX_01; // 0x000005F4 length: 4
            undefined4 unknownY_01; // 0x000005F8 length: 4
            byte unusedBytes03[8]; // 0x000005FC length: 8
            undefined4 field48_0x604; // 0x00000604 length: 4
            undefined4 field49_0x608; // 0x00000608 length: 4
            undefined4 DAT_EuroUnitAcquisitionFailReason; // 0x0000060C length: 4
            undefined4 DAT_EuroUnitRequiredResource; // 0x00000610 length: 4
            Unit units[2500]; // 0x00000614 length: 2920000
            short unusedUnitIDArray[2500]; // 0x002C9454 length: 5000
            int unusedUnitIDArrayIndex; // 0x002CA7DC length: 4
            DWORD creationTime; // 0x002CA7E0 length: 4

        private:
            UnitsState(UnitsState const&);
            void operator=(UnitsState const&);

            UnitsState();
            ~UnitsState();

        public:
            // Constructor
            UnitsState* Constructor_UnitsState();

            void clearAllUnits();

            int assignPeasantToBuilding(UnitTypeInt unitType, int buildingID, int playerID, int workerIndex);

            int euroRecruit(int unitType, undefined4 playersBarracksID, int playerID, int param_4);

            int nonEuroRecruit(UnitTypeInt unitType, undefined4 recruitmentBuilding, int playerID, int param_4);

            int disbandUnit(int unitID);

            void assignNameToUnit(int unitID);

            void removeUnitFromItsTribe(uint unitID, int unitUID);

            void makeUnitStopWalkingByClearingPathProgressState(int unitID);

            int checkUnitHasPropertyBasedOnUnitType(int unitID, int property);

            void recomputeUnitStandingHeight(int unitID);

            void setMoveDelayForUnitsOnSameTiles(int unitID, int unitIDCurrentTilePosition);

            void setupUnitSharingTileIDs(int unitID, int unitCurrentTilePosition);

            undefined4 meth_0x52f4e0(int unitID);

            BOOLEnum ifAnyUnitOnSameTileIsLadder(int unitID);

            undefined4 ifAnyUnitOnSameTileIsLadderInRightDirection(int tile, int y);

            void FUN_0052f680(int tile);

            void removeUnitsSameTileLinkageIfNoLongerApplicable();

            void calculateUnitMovementSpeed(int unitID);

            undefined4 meth_0x52fbb0(int param_1);

            undefined4 meth_0x52fbf0(int param_1);

            void meth_0x52fc30(int param_1, int param_2);

            void meth_0x52fca0(int param_1, int param_2, int param_3);

            undefined4 setUnitFacingDirectionTowardsTarget(int unitID, int targetUnitID);

            void FUN_0052fe00(int param_1, int param_2);

            bool setUnitFacingDirectionForTargetXandY(int unitID, int targetX, int targetY);

            uint setUnitFacingDirectionBasedOnBuilding(int unitID, int buildingID);

            BOOLEnum FUN_00530080(int param_1);

            void playHurtSFXForUnit(int unitID);

            int meth_0x5301f0(int param_1);

            void meth_0x530240(int param_1);

            void killAllUnownedUnits();

            void meth_0x530310();

            void killUnits(int playerID);

            void meth_0x530400(int fromPlayer, int toPlayer);

            void makeCourtMemberUnitsDisappearAndSwapAllOtherUnitsOwnership(int param_1, int param_2);

            void makeUnitsDisappearThatCannotReachTheKeep(int playerID);

            void setRandomNumberOnCows(int playerID);

            void setMissionNumberSpecificLord(int missionNumber);

            BOOLEnum checkIfCitizenUnitIsAliveBasedOnStateUnk(int param_1);

            bool meth_0x531000(int param_1, int param_2);

            int ComputeDamageFearFactorBonus(int damage, int playerID);

            undefined4 processUnitAttackOtherUnit(int unitID, int unit2ID);

            BOOLEnum processEntityDamageToUnit(int unitID, int entityID, int tileDistance);

            undefined4 processFireDamageToUnit(int unitID, int playerID, int halfTheDamage);

            void shootProjectile(int unitID, EntityTypeInt projectileType, int targetX, int targetY, int targetZUnk);

            void recomputeTroopValuesForPlayer(int playerID);

            int getArmySize(int playerID);

            int distanceComputationForSomeOldCodeForSomeMissions(int param_1);

            BOOLEnum FUN_00533090();

            void setRandomShootLocation(int unitID, int microX, int microY, int z);

            int getRemainingRequiredEngineers(int unitID);

            BOOLEnum checkTargetBuildingPossibilityOrState(int unitID);

            BOOLEnum findClosestLaddermanWithLadderPosition(int unitID);

            int meth_0x533810(int param_1, int param_2);

            BOOLEnum getDestination2EqualsGivenCoordinates(int unitID, int x, int y);

            bool meth_0x533960(int param_1);

            BOOLEnum unitReachedDestinationUnk(int unitID);

            BOOLEnum meth_0x5339f0(int param_1);

            undefined4 ladderClimbRelatedUnk(int unitID, uint param_2, int param_3, int param_4);

            void changeDestinationByAmount(int unitID, int leftover);

            void changeDestinationByLeftover(int unitID);

            void tracePathFromLadderExitSetDestination(int unitID);

            void FUN_00533d50(int unitID);

            void meth_0x533f90(int param_1);

            void meth_0x533fc0(int param_1);

            void updateMicroPosition(int unitID);

            void adjustUnitMapOrientationRelatedPositionBasedOnMapOrientationCorrectedFacingDirection(int param_1);

            void meth_0x534130(uint unitID);

            int stopUnitIfNextToTarget(int unitID);

            undefined4 meth_0x534380(int param_1);

            undefined4 setWorkplaceBuildingEntryAsTarget(int unitID, int entryAngleUnk);

            BOOLEnum unitIsInMoat(int unitID);

            void meth_0x534490(int param_1);

            void writeSixToTileMap1104InAllDirections(int unitID, undefined4 six);

            int getUnitThatFulfillsSomeTimebasedAndLocationBasedCriteria(
                int unitID, int playerID, int unitXPosition, int unitYPosition, int zero1, int zero2);

            int selectNewBlessingTarget(int unitID);

            void meth_0x5347e0();

            void meth_0x534d10();

            void meth_0x534ee0();

            void meth_0x5350b0(int param_1, int param_2);

            void deselectAllUnitsOneByOne();

            void deselectUnit(int unitID);

            void filterUnitSelectionExcludeUnitType(int unitType);

            void filterUnitSelectionForUnitType(int unitType);

            void recountUnitsInSelection();

            int meth_0x535520();

            BOOLEnum meth_0x535550();

            BOOLEnum meth_0x535560();

            undefined4 meth_0x535580();

            undefined4 meth_0x5355e0();

            uint meth_0x535680();

            int meth_0x535700();

            BOOLEnum selectionContainsRangedOnlyUnits();

            int meth_0x5357e0();

            BOOLEnum selectionContainsOnlyArabAssassins();

            int meth_0x535840();

            undefined4 meth_0x535870();

            undefined4 meth_0x5358c0();

            undefined4 meth_0x535910();

            undefined4 meth_0x535980();

            uint meth_0x5359c0();

            int createUnitSelection();

            int createTribeFromSelectedUnits();

            void playerMakeUnitSelection(int playerID, int tribeID);

            void FUN_00535df0(undefined4 param_1);

            void siegeEngineRelated(int playerID, int unitID, int tribeID);

            void makeSelectionBasedOnShortcut(int section1099ID);

            BOOLEnum isUnitShortcutAvailable(int unitHotKeyNumber);

            void tribeRelated1(int playerID, int tribeID);

            UnitTypeInt getUnitTypeOfFirstSelectedUnit();

            undefined4 meth_0x536260();

            uint meth_0x5362f0(int param_1, int param_2);

            int meth_0x536370();

            undefined4 meth_0x536400();

            uint returnFirstSelectedEngineer();

            uint getTunnelerIDOnlyIfFirstSelected();

            uint meth_0x5365a0();

            undefined4 canAUnitClimb();

            uint meth_0x536690();

            uint meth_0x536710();

            BOOLEnum meth_0x536780(int param_1);

            undefined4 checkAnySelectedUnitCannotClimb();

            BOOLEnum meth_0x5369f0(int param_1);

            int selectionContainsCombatUnit(uint unitID);

            void FUN_00536c70();

            void queueCommand0xF(undefined4 unitType);

            void queueClickNavigateMenuOrEscape(undefined4 param_1);

            void tribeRelated2(int playerID, uint unitID, int unitType);

            void meth_0x536de0();

            void giveMoveCommand(int tribeID, int x, int y, int patrol, int matchUnitSpeeds);

            void giveTribeMoveInstructionHumans(
                int tribeID, uint x, uint y, int rallyBool, MatchSpeedInstructionEnumInt speedMatching);

            void extendRallyPoint(int tribeID, int mouseX, int mouseY, int rallyCount);

            void FUN_00537100(undefined4 param_1, undefined4 param_2);

            void FUN_00537130(undefined4 param_1, undefined4 param_2, undefined4 param_3);

            void queueCommand_36d(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4);

            void queueCommand_36_variation2(undefined4 param_1, UnitInstructionTypeInt instruction, undefined4 param_3,
                undefined4 param_4, undefined4 param_5);

            void giveTribeAnInstruction2(
                int tribeID, UnitInstructionTypeInt instructionType, int targetID_1, int targetID_2, int param_5);

            uint findFreeTileNearby(uint unitID, uint tile);

            BOOLEnum findTunnelTarget(int originBuildingID, int targetPlayer);

            int getAliveLordForPlayer(int playerID);

            int getRawDeerCount();

            void meth_0x537880(int param_1);

            int meth_0x537a00(int param_1, int param_2, int param_3);

            int findClosestAnimalStoreResult(int maxDistance, BOOLEnum excludeCows, uint x, uint y);

            int getClosestUnitIDUnk(int param_1, uint param_2, uint param_3, int param_4);

            undefined4 tryAttackUnitID(int unitID_1, int unitID_2);

            void setTowerSiegeEngineToIdle(int buildingID);

            void setAIControlStatusTo100000();

            int FUN_00537f60(int unitIndex, int* param_2);

            GmIDInt getPeasantGmID(int unitID);

            undefined4 chooseHusbandAndWife(int* husbandID, int* wifeID);

            undefined4 meth_0x53a070(int param_1);

            int meth_0x53a150(int param_1);

            int meth_0x53a4d0(int param_1);

            int getLivingSelectableUnit(int playerID);

            void renderDebugDataUnitData(int x, int y, int width, int height);

            void setUnitValues(int unitID, UnitTypeInt unitType);

            void updateUnitPositionUnk(int unitID);

            void setupUnitSharingCurrentTilePosition(int unitID);

            void teleportUnitToUnitXAndY(int unitID);

            int getEnemyUnitIDNearby(int unitID, int tileUnk, int unitHeight);

            int prepareProjectileTarget(int shooterID, int targetID, int param_3);

            undefined4 harassBuildingsAIUnk(int unitID);

            BOOLEnum setDestinationForUnit(int unitID, uint x, uint y, int reusePathingInfo);

            void meth_0x53d850(int unitID);

            void exitLadder(int unitID);

            uint getUnitInHitBox(undefined4 param_1);

            undefined4 setTargetedBuildingDestinationUnk(int unitID, int param_2);

            int meth_0x53ddd0(int unitID);

            void upgradeMapFormatForUnits(
                PackagedFileMagicNumInt receivedMapVersion, PackagedFileMagicNumInt packagerMapVersion);

            int spawnUnit(int playerID, int displayColor, int microXPosition, int microYPosition, int terrainHeight,
                UnitTypeInt unitType);

            int changeUnitType(int unitID);

            void deleteUnit(uint unitID);

            void commitUnitLocation(int unitID);

            void someUnitMoveFunction(int unitID);

            void meth_0x53e8d0(int unitID);

            void setPositionOfUnit(int unitID, uint x, uint y, undefined4 height);

            void commitMimmicLocation(int unitID);

            BOOLEnum ifOnADefensiveStructureSetDestinationInDirectionOfTarget(int unitID);

            void processMeleeInitiation(int unitID);

            void meth_0x54a770(int param_1);

            dword findNearestEnemyAndHeadTowardsItUnk(int unitID);

            BOOLEnum canShootTargetUnk(short* unitID);

            BOOLEnum updateClimbing(int unitID);

            void unitClimbing(int param_1);

            int handleUnitMovementWhenTargetingBuildings(int unitID);

            BOOLEnum moveToFreeTileNearby(int unitID);

            undefined4 processUnitMove(int unitID, int speedCategory);

            void updateUnits();
        };

        static_assert_cpp98_obj(sizeof(UnitsState) == 2926564, UnitsState);

#pragma pack(pop)

        MACRO_STRUCT_RESOLVER(UnitsState, false, Address::SHC_3BB0A8C1_0x01387F38) pDAT_UnitsState;

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
