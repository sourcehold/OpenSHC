/**
  path: 'OpenSHC/Map/Units/TribesState.func.hpp'
*/

#include "OpenSHC/Commands/CommandBuildingType.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/TribesState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace TribesState_Func {

            using OpenSHC::Commands::CommandBuildingType;
            using OpenSHC::IO::PackagedFileMagicNum;
            using OpenSHC::Map::Units::SomeTribeBehaviorType;
            using OpenSHC::Map::Units::UnitInstructionType;
            using OpenSHC::Map::Units::UnitType;
            using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
            using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;
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

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00521210,
                &TribesState::reassignOwnerForTribesOfBehaviorType2)
            reassignOwnerForTribesOfBehaviorType2;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00521240,
                &TribesState::swapTribeOwnership)
            swapTribeOwnership;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00521280,
                &TribesState::moveUnitToBehaviorTarget)
            moveUnitToBehaviorTarget;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int, int*, int*), false,
                Address::SHC_3BB0A8C1_0x00521500, &TribesState::predictUnitInterceptPosition)
            predictUnitInterceptPosition;

            MACRO_FUNCTION_RESOLVER(UnitType (TribesState::*)(undefined4, int*), false,
                Address::SHC_3BB0A8C1_0x00521720, &TribesState::getMajoritySelectedUnitType)
            getMajoritySelectedUnitType;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005217E0,
                &TribesState::playUnitSelectionSound)
            playUnitSelectionSound;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00521A90,
                &TribesState::playUnitCombatSpeechForTarget)
            playUnitCombatSpeechForTarget;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00521EB0,
                &TribesState::playUnitSelectSpeech)
            playUnitSelectSpeech;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00521EF0,
                &TribesState::playUnitMoveSpeech)
            playUnitMoveSpeech;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00522090,
                &TribesState::playAttackCommandFeedback)
            playAttackCommandFeedback;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00522110,
                &TribesState::playPatrolCommandSpeech)
            playPatrolCommandSpeech;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x00522150,
                &TribesState::playTunnelerCommandSpeech)
            playTunnelerCommandSpeech;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00522160,
                &TribesState::playWorkCommandSpeech)
            playWorkCommandSpeech;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, SomeTribeBehaviorType), false,
                Address::SHC_3BB0A8C1_0x005221A0, &TribesState::applyTribeBehaviorType)
            applyTribeBehaviorType;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00522210,
                &TribesState::updatePeasantSeatingAtBuilding)
            updatePeasantSeatingAtBuilding;

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

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, UnitStanceEnum), false, Address::SHC_3BB0A8C1_0x00522C20,
                &TribesState::setUnitStance)
            setUnitStance;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, short, short, int), false,
                Address::SHC_3BB0A8C1_0x00522C50, &TribesState::addRallyPoint)
            addRallyPoint;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00522CA0,
                &TribesState::snapshotSelectionTribeAndComputeStance)
            snapshotSelectionTribeAndComputeStance;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4, int), false, Address::SHC_3BB0A8C1_0x00522DD0,
                &TribesState::importStoredInfoFromSlot0)
            importStoredInfoFromSlot0;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4, int), false, Address::SHC_3BB0A8C1_0x00522EF0,
                &TribesState::trimTribeToSize)
            trimTribeToSize;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(undefined4, int, int, int, UnitType, int, int), false,
                Address::SHC_3BB0A8C1_0x00522F70, &TribesState::spawnUnitsForAITribe)
            spawnUnitsForAITribe;

            MACRO_FUNCTION_RESOLVER(
                dword (TribesState::*)(undefined4, int, int, int, int, UnitType, UnitType, int, int), false,
                Address::SHC_3BB0A8C1_0x00523030, &TribesState::spawnUnitsIntoNewTribe)
            spawnUnitsIntoNewTribe;

            MACRO_FUNCTION_RESOLVER(dword (TribesState::*)(short, undefined4, int, int, int, UnitType, int), false,
                Address::SHC_3BB0A8C1_0x00523190, &TribesState::createTribeWithSpawnedUnit)
            createTribeWithSpawnedUnit;

            MACRO_FUNCTION_RESOLVER(dword (TribesState::*)(undefined4, int, int, int, UnitType, int), false,
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
                &TribesState::findRecentOrSignpostSpawnLocation)
            findRecentOrSignpostSpawnLocation;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x00523520,
                &TribesState::hasAvailableSpawnSlotForWildlifeOrMercs)
            hasAvailableSpawnSlotForWildlifeOrMercs;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523590,
                &TribesState::updateAnimalHerdBehaviorState)
            updateAnimalHerdBehaviorState;

            MACRO_FUNCTION_RESOLVER(
                int (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523630, &TribesState::getNonDyingUnit)
            getNonDyingUnit;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x005236A0, &TribesState::countDeerEfficiently)
            countDeerEfficiently;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523730,
                &TribesState::markTribeAsAnimalTribe)
            markTribeAsAnimalTribe;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523750, &TribesState::flagTribesOfType)
            flagTribesOfType;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00523790,
                &TribesState::consumeFlaggedTribesOfType)
            consumeFlaggedTribesOfType;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x005237F0,
                &TribesState::aiAssignNewUnitToTribe)
            aiAssignNewUnitToTribe;

            MACRO_FUNCTION_RESOLVER(int (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523920,
                &TribesState::scatterTribeUnitsRandomly)
            scatterTribeUnitsRandomly;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523A30,
                &TribesState::drawFlagsAndUnitDestinations)
            drawFlagsAndUnitDestinations;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(PackagedFileMagicNum, PackagedFileMagicNum), false,
                Address::SHC_3BB0A8C1_0x00523EF0, &TribesState::upgradeTribeArrayLayoutForMapVersion)
            upgradeTribeArrayLayoutForMapVersion;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00523F70,
                &TribesState::updateTribeRallyFlags)
            updateTribeRallyFlags;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524000,
                &TribesState::unsetRallyRelatedFlagOnUnits)
            unsetRallyRelatedFlagOnUnits;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524060,
                &TribesState::isTribeAllAssassins)
            isTribeAllAssassins;

            MACRO_FUNCTION_RESOLVER(int (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005240D0,
                &TribesState::getFirstUnitInTribeThatIsOnXTerrain)
            getFirstUnitInTribeThatIsOnXTerrain;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524140,
                &TribesState::tribeHasActiveLaddermanUnit)
            tribeHasActiveLaddermanUnit;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005241C0,
                &TribesState::tribeContainsUnitThatCanClimb)
            tribeContainsUnitThatCanClimb;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524230,
                &TribesState::selectionContainsHorses)
            selectionContainsHorses;

            MACRO_FUNCTION_RESOLVER(UnitType (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005242B0,
                &TribesState::getMajorityArcherTypeEuropeanOrArabian)
            getMajorityArcherTypeEuropeanOrArabian;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, undefined4, undefined4, undefined4, int), false,
                Address::SHC_3BB0A8C1_0x00524340, &TribesState::applyMoveCommandOrRallyCommandToTribe)
            applyMoveCommandOrRallyCommandToTribe;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, SomeTribeBehaviorType), false,
                Address::SHC_3BB0A8C1_0x005244D0, &TribesState::assignAttackTargetsForTribe)
            assignAttackTargetsForTribe;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524890,
                &TribesState::stopTribeMovementAndCheckIdle)
            stopTribeMovementAndCheckIdle;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00524930,
                &TribesState::sortTribePathDestinationsByCost)
            sortTribePathDestinationsByCost;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524B30,
                &TribesState::isTribeUnitBlockedByOtherUnit)
            isTribeUnitBlockedByOtherUnit;

            MACRO_FUNCTION_RESOLVER(
                int (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524BF0, &TribesState::getTribeAliveStatus)
            getTribeAliveStatus;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, uint, uint, uint, uint), false,
                Address::SHC_3BB0A8C1_0x00524CA0, &TribesState::isTribePathToDestinationClear)
            isTribePathToDestinationClear;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00524E20,
                &TribesState::applyLadderDestructionToTribeUnits)
            applyLadderDestructionToTribeUnits;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, BOOLEnum), false, Address::SHC_3BB0A8C1_0x00524EF0,
                &TribesState::applyUnitTopSpeedDelayBasedOnTribeSize)
            applyUnitTopSpeedDelayBasedOnTribeSize;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525090,
                &TribesState::playArcherCommandSpeech)
            playArcherCommandSpeech;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TribesState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005250B0,
                &TribesState::anyUnitsOfTribeAreOutsideCoverageOfPathFindingAlg)
            anyUnitsOfTribeAreOutsideCoverageOfPathFindingAlg;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525130,
                &TribesState::applyMovementDistanceToUnitsInTribe)
            applyMovementDistanceToUnitsInTribe;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005251A0,
                &TribesState::applyMovementDistanceToUnitsInTribeBasedOnUnitNumberInTribe)
            applyMovementDistanceToUnitsInTribeBasedOnUnitNumberInTribe;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525210,
                &TribesState::isTribeFreeOfTunnelingUnits)
            isTribeFreeOfTunnelingUnits;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525280,
                &TribesState::setTargetUnitForTribe)
            setTargetUnitForTribe;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int, undefined4), false, Address::SHC_3BB0A8C1_0x00525300,
                &TribesState::setStateForAllTribeUnits)
            setStateForAllTribeUnits;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525370, &TribesState::standUpAllTribeUnits)
            standUpAllTribeUnits;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x005253F0,
                &TribesState::allUnitsReachedTheirDestination)
            allUnitsReachedTheirDestination;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x00525470, &TribesState::removeAllTribeUnits)
            removeAllTribeUnits;

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

            MACRO_FUNCTION_RESOLVER(dword (TribesState::*)(CommandBuildingType, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x00525BA0, &TribesState::createAnimal)
            createAnimal;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TribesState::*)(int, int, UnitType), false,
                Address::SHC_3BB0A8C1_0x00525F20, &TribesState::spawnDeerLionOrRabbit)
            spawnDeerLionOrRabbit;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x005260B0, &TribesState::trySpawnAdditionalWildlifeForTribe)
            trySpawnAdditionalWildlifeForTribe;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x005261B0, &TribesState::respawnDeer)
            respawnDeer;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x005262A0,
                &TribesState::spawnWildlifeOrMercAtAvailableSlot)
            spawnWildlifeOrMercAtAvailableSlot;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(PackagedFileMagicNum, PackagedFileMagicNum), false,
                Address::SHC_3BB0A8C1_0x00526370, &TribesState::upgradeMapTribesState)
            upgradeMapTribesState;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, uint, uint, int, int, UnitMatchSpeedEnum), false,
                Address::SHC_3BB0A8C1_0x005263A0, &TribesState::giveTribeMoveInstruction)
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

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x00527440,
                &TribesState::spawnQueuedReinforcementWaves)
            spawnQueuedReinforcementWaves;

            MACRO_FUNCTION_RESOLVER(undefined4 (TribesState::*)(int, UnitInstructionType, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00527C80, &TribesState::giveTribeAnInstruction)
            giveTribeAnInstruction;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052A640,
                &TribesState::moveTribeToNearbyClearTile)
            moveTribeToNearbyClearTile;

            MACRO_FUNCTION_RESOLVER(int (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052A700,
                &TribesState::moveTribeToIndexedNearbyTile)
            moveTribeToIndexedNearbyTile;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052A7D0,
                &TribesState::updateTribeCombatStanceBehavior)
            updateTribeCombatStanceBehavior;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052AD50, &TribesState::processDeerMoving)
            processDeerMoving;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052B110,
                &TribesState::updateLionWolfTribeBehavior)
            updateLionWolfTribeBehavior;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052B390,
                &TribesState::updateRabbitTribeBehavior)
            updateRabbitTribeBehavior;

            MACRO_FUNCTION_RESOLVER(void (TribesState::*)(int), false, Address::SHC_3BB0A8C1_0x0052B630,
                &TribesState::updateCamelTribeBehavior)
            updateCamelTribeBehavior;

            MACRO_FUNCTION_RESOLVER(
                void (TribesState::*)(), false, Address::SHC_3BB0A8C1_0x0052B860, &TribesState::updateTribes)
            updateTribes;

        } // namespace TribesState_Func
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
