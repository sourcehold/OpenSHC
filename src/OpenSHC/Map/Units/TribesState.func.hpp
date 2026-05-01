/**
  path: 'OpenSHC/Map/Units/TribesState.func.hpp'
*/

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnumShort.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnumInt.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorTypeInt.hpp"
#include "OpenSHC/Map/Units/TribesState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace TribesState_Func {

            using OpenSHC::Commands::CommandBuildingTypeInt;
            using OpenSHC::IO::PackagedFileMagicNumInt;
            using OpenSHC::Map::Units::SomeTribeBehaviorTypeInt;
            using OpenSHC::Map::Units::UnitInstructionTypeInt;
            using OpenSHC::Map::Units::UnitTypeInt;
            using OpenSHC::Map::Units::Behavior::UnitStanceEnumShort;
            using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnumInt;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4, undefined4, undefined4, undefined4, undefined4),
                false, Address::SHC_3BB0A8C1_0x004B7700, &TribesState::giveUnitSelectionMoveInstructionNoMatchedSpeed)
            giveUnitSelectionMoveInstructionNoMatchedSpeed;

            MACRO_FUNCTION_RESOLVER(int (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004CCAF0,
                &TribesState::getSmallestPatrolTribe)
            getSmallestPatrolTribe;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x005211B0, &TribesState::clearAllTribes)
            clearAllTribes;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00521210, &TribesState::FUN_00521210)
            FUN_00521210;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00521240,
                &TribesState::swapTribeOwnership)
            swapTribeOwnership;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00521280,
                &TribesState::meth_0x521280)
            meth_0x521280;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int, int*, int*), false,
                Address::SHC_3BB0A8C1_0x00521500, &TribesState::calculatePathPlanToUnitUnk)
            calculatePathPlanToUnitUnk;

            MACRO_FUNCTION_RESOLVER(UnitTypeInt (TribesState::*)(undefined4, int*), false,
                Address::SHC_3BB0A8C1_0x00521720, &TribesState::FUN_00521720)
            FUN_00521720;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005217E0, &TribesState::meth_0x5217e0)
            meth_0x5217e0;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00521A90,
                &TribesState::somethingTargetUnitSoundRelated)
            somethingTargetUnitSoundRelated;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00521EB0, &TribesState::meth_0x521eb0)
            meth_0x521eb0;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00521EF0, &TribesState::meth_0x521ef0)
            meth_0x521ef0;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00522090, &TribesState::meth_0x522090)
            meth_0x522090;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00522110, &TribesState::FUN_00522110)
            FUN_00522110;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x00522150, &TribesState::FUN_00522150)
            FUN_00522150;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00522160, &TribesState::meth_0x522160)
            meth_0x522160;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, SomeTribeBehaviorTypeInt), false,
                Address::SHC_3BB0A8C1_0x005221A0, &TribesState::applyTribeBehaviorType)
            applyTribeBehaviorType;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00522210,
                &TribesState::FUN_00522210)
            FUN_00522210;

            MACRO_FUNCTION_RESOLVER(uint (TribesState::*)(int, uint), false, Address::SHC_3BB0A8C1_0x00522360,
                &TribesState::tribeCorrespondsWithUID)
            tribeCorrespondsWithUID;

            MACRO_FUNCTION_RESOLVER(int (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00522390,
                &TribesState::getUnitIDForIndexInTribe)
            getUnitIDForIndexInTribe;

            MACRO_FUNCTION_RESOLVER(int (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00522410,
                &TribesState::getSpecificUnitFromTribe)
            getSpecificUnitFromTribe;

            MACRO_FUNCTION_RESOLVER(int (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005224E0,
                &TribesState::setWhetherTribeContainsAnyUnits)
            setWhetherTribeContainsAnyUnits;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(uint), false, Address::SHC_3BB0A8C1_0x00522520, &TribesState::addUnitToSelected)
            addUnitToSelected;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TribesState::*)(uint), false, Address::SHC_3BB0A8C1_0x00522550,
                &TribesState::unitIsSelectedByPlayer)
            unitIsSelectedByPlayer;

            MACRO_FUNCTION_RESOLVER(
                int (TribesState::*)(uint, int), false, Address::SHC_3BB0A8C1_0x00522590, &TribesState::addUnitToTribe)
            addUnitToTribe;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(uint, int), false, Address::SHC_3BB0A8C1_0x00522630,
                &TribesState::removeUnitFromThisTribeIfInTribe)
            removeUnitFromThisTribeIfInTribe;

            MACRO_FUNCTION_RESOLVER(
                int (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00522720, &TribesState::getAvailableTribeID)
            getAvailableTribeID;

            MACRO_FUNCTION_RESOLVER(
                int (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005227E0, &TribesState::createTribeForPlayer)
            createTribeForPlayer;

            MACRO_FUNCTION_RESOLVER(
                int (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00522890, &TribesState::createTribe)
            createTribe;

            MACRO_FUNCTION_RESOLVER(int (TribesState::*)(int, undefined4, int), false, Address::SHC_3BB0A8C1_0x00522950,
                &TribesState::createPlayerTribe)
            createPlayerTribe;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005229C0,
                &TribesState::addUnitsToTribeAndComputeMovementSpeed)
            addUnitsToTribeAndComputeMovementSpeed;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, uint, int), false, Address::SHC_3BB0A8C1_0x00522B00,
                &TribesState::addUnitToTribeAndUpdateTribeMovementSpeed)
            addUnitToTribeAndUpdateTribeMovementSpeed;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00522BC0, &TribesState::clearTribe)
            clearTribe;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x00522BF0, &TribesState::queueUnitStance)
            queueUnitStance;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, UnitStanceEnumShort), false,
                Address::SHC_3BB0A8C1_0x00522C20, &TribesState::setUnitStance)
            setUnitStance;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, short, short, int), false,
                Address::SHC_3BB0A8C1_0x00522C50, &TribesState::addRallyPoint)
            addRallyPoint;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00522CA0,
                &TribesState::temporarilyStoreTribeIfAllNewlySelectedUnitsPartOfThisTribe_And_AlwaysRememberStance)
            temporarilyStoreTribeIfAllNewlySelectedUnitsPartOfThisTribe_And_AlwaysRememberStance;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4, int), false, Address::SHC_3BB0A8C1_0x00522DD0,
                &TribesState::importStoredInfoFromSlot0)
            importStoredInfoFromSlot0;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4, int), false, Address::SHC_3BB0A8C1_0x00522EF0,
                &TribesState::meth_0x522ef0)
            meth_0x522ef0;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4, int, int, int, UnitTypeInt, int, int), false,
                Address::SHC_3BB0A8C1_0x00522F70, &TribesState::FUN_00522f70)
            FUN_00522f70;

            MACRO_FUNCTION_RESOLVER(
                dword (TribesState::*)(undefined4, int, int, int, int, UnitTypeInt, UnitTypeInt, int, int), false,
                Address::SHC_3BB0A8C1_0x00523030, &TribesState::spawnUnitsIntoNewTribe)
            spawnUnitsIntoNewTribe;

            MACRO_FUNCTION_RESOLVER(dword (TribesState::*)(short, undefined4, int, int, int, UnitTypeInt, int), false,
                Address::SHC_3BB0A8C1_0x00523190, &TribesState::meth_0x523190)
            meth_0x523190;

            MACRO_FUNCTION_RESOLVER(dword (TribesState::*)(undefined4, int, int, int, UnitTypeInt, int), false,
                Address::SHC_3BB0A8C1_0x00523240, &TribesState::spawnUnitsAroundLocation)
            spawnUnitsAroundLocation;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x00523340, &TribesState::storeDeerXAndYinMapInfo)
            storeDeerXAndYinMapInfo;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x00523370, &TribesState::storeLionXAndYInMapInfo)
            storeLionXAndYInMapInfo;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x005233A0, &TribesState::setRabbitSpawnXY)
            setRabbitSpawnXY;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x005233E0, &TribesState::setCamelSpawnXY)
            setCamelSpawnXY;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(uint*, uint*), false, Address::SHC_3BB0A8C1_0x00523410,
                &TribesState::FUN_00523410)
            FUN_00523410;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x00523520, &TribesState::FUN_00523520)
            FUN_00523520;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523590, &TribesState::meth_0x523590)
            meth_0x523590;

            MACRO_FUNCTION_RESOLVER(
                int (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523630, &TribesState::getNonDyingUnit)
            getNonDyingUnit;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x005236A0, &TribesState::countDeerEfficiently)
            countDeerEfficiently;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523730, &TribesState::meth_0x523730)
            meth_0x523730;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523750, &TribesState::meth_0x523750)
            meth_0x523750;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00523790, &TribesState::meth_0x523790)
            meth_0x523790;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x005237F0,
                &TribesState::aiAssignNewUnitToTribe)
            aiAssignNewUnitToTribe;

            MACRO_FUNCTION_RESOLVER(
                int (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523920, &TribesState::meth_0x523920)
            meth_0x523920;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523A30,
                &TribesState::drawFlagsAndUnitDestinations)
            drawFlagsAndUnitDestinations;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(PackagedFileMagicNumInt, PackagedFileMagicNumInt), false,
                Address::SHC_3BB0A8C1_0x00523EF0, &TribesState::meth_0x523ef0)
            meth_0x523ef0;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523F70, &TribesState::meth_0x523f70)
            meth_0x523f70;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524000,
                &TribesState::unsetRallyRelatedFlagOnUnits)
            unsetRallyRelatedFlagOnUnits;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524060,
                &TribesState::isTribeAllAssassins)
            isTribeAllAssassins;

            MACRO_FUNCTION_RESOLVER(int (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005240D0,
                &TribesState::getFirstUnitInTribeThatIsOnXTerrain)
            getFirstUnitInTribeThatIsOnXTerrain;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524140, &TribesState::meth_0x524140)
            meth_0x524140;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005241C0,
                &TribesState::tribeContainsUnitThatCanClimb)
            tribeContainsUnitThatCanClimb;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524230,
                &TribesState::selectionContainsHorses)
            selectionContainsHorses;

            MACRO_FUNCTION_RESOLVER(UnitTypeInt (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005242B0,
                &TribesState::getMajorityArcherTypeEuropeanOrArabian)
            getMajorityArcherTypeEuropeanOrArabian;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, undefined4, undefined4, undefined4, int), false,
                Address::SHC_3BB0A8C1_0x00524340, &TribesState::applyMoveCommandOrRallyCommandToTribe)
            applyMoveCommandOrRallyCommandToTribe;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, SomeTribeBehaviorTypeInt), false,
                Address::SHC_3BB0A8C1_0x005244D0, &TribesState::aiAttackWaveUnk)
            aiAttackWaveUnk;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524890, &TribesState::meth_0x524890)
            meth_0x524890;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00524930, &TribesState::meth_0x524930)
            meth_0x524930;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524B30, &TribesState::meth_0x524b30)
            meth_0x524b30;

            MACRO_FUNCTION_RESOLVER(undefined (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524BF0,
                &TribesState::getTribeAliveStatus)
            getTribeAliveStatus;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, uint, uint, uint, uint), false,
                Address::SHC_3BB0A8C1_0x00524CA0, &TribesState::meth_0x524ca0)
            meth_0x524ca0;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524E20, &TribesState::meth_0x524e20)
            meth_0x524e20;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, BOOLEnum), false, Address::SHC_3BB0A8C1_0x00524EF0,
                &TribesState::applyUnitTopSpeedDelayBasedOnTribeSize)
            applyUnitTopSpeedDelayBasedOnTribeSize;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525090, &TribesState::FUN_00525090)
            FUN_00525090;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005250B0,
                &TribesState::anyUnitsOfTribeAreOutsideCoverageOfPathFindingAlg)
            anyUnitsOfTribeAreOutsideCoverageOfPathFindingAlg;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525130,
                &TribesState::applyMovementDistanceToUnitsInTribe)
            applyMovementDistanceToUnitsInTribe;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005251A0,
                &TribesState::applyMovementDistanceToUnitsInTribeBasedOnUnitNumberInTribe)
            applyMovementDistanceToUnitsInTribeBasedOnUnitNumberInTribe;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525210, &TribesState::meth_0x525210)
            meth_0x525210;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525280,
                &TribesState::setTargetUnitForTribe)
            setTargetUnitForTribe;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, undefined4), false, Address::SHC_3BB0A8C1_0x00525300,
                &TribesState::meth_0x525300)
            meth_0x525300;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525370, &TribesState::meth_0x525370)
            meth_0x525370;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005253F0,
                &TribesState::allUnitsReachedTheirDestination)
            allUnitsReachedTheirDestination;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525470,
                &TribesState::makeUnitsDisappearUnk)
            makeUnitsDisappearUnk;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TribesState::*)(uint), false, Address::SHC_3BB0A8C1_0x005254C0,
                &TribesState::addUnitToNewTribe)
            addUnitToNewTribe;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525790,
                &TribesState::removeSelectedUnitsFromTheirCurrentTribes)
            removeSelectedUnitsFromTheirCurrentTribes;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00525870,
                &TribesState::clearTribesOfUnitType)
            clearTribesOfUnitType;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00525970,
                &TribesState::clearTribesNotOfUnitType)
            clearTribesNotOfUnitType;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(uint, int), false, Address::SHC_3BB0A8C1_0x00525A70,
                &TribesState::removeUnitFromTribe)
            removeUnitFromTribe;

            MACRO_FUNCTION_RESOLVER(
                int (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525B70, &TribesState::popUnitFromTribe)
            popUnitFromTribe;

            MACRO_FUNCTION_RESOLVER(dword (TribesState::*)(CommandBuildingTypeInt, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x00525BA0, &TribesState::createAnimal)
            createAnimal;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TribesState::*)(int, int, UnitTypeInt), false,
                Address::SHC_3BB0A8C1_0x00525F20, &TribesState::spawnDeerLionOrRabbit)
            spawnDeerLionOrRabbit;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x005260B0, &TribesState::meth_0x5260b0)
            meth_0x5260b0;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x005261B0, &TribesState::respawnDeer)
            respawnDeer;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x005262A0, &TribesState::meth_0x5262a0)
            meth_0x5262a0;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(PackagedFileMagicNumInt, PackagedFileMagicNumInt), false,
                Address::SHC_3BB0A8C1_0x00526370, &TribesState::upgradeMapTribesState)
            upgradeMapTribesState;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, uint, uint, int, int, UnitMatchSpeedEnumInt),
                false, Address::SHC_3BB0A8C1_0x005263A0, &TribesState::giveTribeMoveInstruction)
            giveTribeMoveInstruction;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, uint, uint, undefined4), false,
                Address::SHC_3BB0A8C1_0x00526F00, &TribesState::commandUnitsToLocation)
            commandUnitsToLocation;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005270F0,
                &TribesState::computeTribePercentages)
            computeTribePercentages;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x00527330,
                &TribesState::updateTribeUnitAssignments)
            updateTribeUnitAssignments;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x00527440, &TribesState::siegeThatRelatedUnk)
            siegeThatRelatedUnk;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, UnitInstructionTypeInt, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00527C80, &TribesState::giveTribeAnInstruction)
            giveTribeAnInstruction;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052A640, &TribesState::meth_0x52a640)
            meth_0x52a640;

            MACRO_FUNCTION_RESOLVER(
                int (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052A700, &TribesState::meth_0x52a700)
            meth_0x52a700;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052A7D0,
                &TribesState::unitAttackBuildingOrOtherUnitBasedOnStanceUnk)
            unitAttackBuildingOrOtherUnitBasedOnStanceUnk;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052AD50, &TribesState::processDeerMoving)
            processDeerMoving;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052B110, &TribesState::meth_0x52b110)
            meth_0x52b110;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052B390, &TribesState::meth_0x52b390)
            meth_0x52b390;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052B630, &TribesState::meth_0x52b630)
            meth_0x52b630;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x0052B860, &TribesState::updateTribes)
            updateTribes;

        } // namespace TribesState_Func
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
