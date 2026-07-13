/**
  path: 'OpenSHC/Map/Units/UnitsState.func.hpp'
*/

#include "OpenSHC/IO/Graphics/GmIDInt.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/Entities/EntityTypeInt.hpp"
#include "OpenSHC/Map/Units/Instructions/MatchSpeedInstructionEnumInt.hpp"
#include "OpenSHC/Map/Units/UnitInstructionTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitsState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace UnitsState_Func {

            using OpenSHC::IO::PackagedFileMagicNumInt;
            using OpenSHC::IO::Graphics::GmIDInt;
            using OpenSHC::Map::Entities::EntityTypeInt;
            using OpenSHC::Map::Units::UnitInstructionTypeInt;
            using OpenSHC::Map::Units::UnitTypeInt;
            using OpenSHC::Map::Units::Instructions::MatchSpeedInstructionEnumInt;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x0052E7B0, &UnitsState::clearAllUnits)
            clearAllUnits;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(UnitTypeInt, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0052E830, &UnitsState::assignPeasantToBuilding)
            assignPeasantToBuilding;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, undefined4, int, int), false,
                Address::SHC_3BB0A8C1_0x0052E960, &UnitsState::euroRecruit)
            euroRecruit;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(UnitTypeInt, undefined4, int, int), false,
                Address::SHC_3BB0A8C1_0x0052EC10, &UnitsState::nonEuroRecruit)
            nonEuroRecruit;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052EDC0, &UnitsState::disbandUnit)
            disbandUnit;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052EED0, &UnitsState::assignNameToUnit)
            assignNameToUnit;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(uint, int), false, Address::SHC_3BB0A8C1_0x0052F010,
                &UnitsState::removeUnitFromItsTribe)
            removeUnitFromItsTribe;

            MACRO_FUNCTION_RESOLVER(undefined (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x0052F070,
                &UnitsState::makeUnitStopWalkingByClearingPathProgressState)
            makeUnitStopWalkingByClearingPathProgressState;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052F0A0,
                &UnitsState::checkUnitHasPropertyBasedOnUnitType)
            checkUnitHasPropertyBasedOnUnitType;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052F0D0,
                &UnitsState::recomputeUnitStandingHeight)
            recomputeUnitStandingHeight;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052F260,
                &UnitsState::setMoveDelayForUnitsOnSameTiles)
            setMoveDelayForUnitsOnSameTiles;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052F440,
                &UnitsState::setupUnitSharingTileIDs)
            setupUnitSharingTileIDs;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052F4E0,
                &UnitsState::isUnitLinkedOnTile)
            isUnitLinkedOnTile;

            MACRO_FUNCTION_RESOLVER(undefined (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x0052F550,
                &UnitsState::ifAnyUnitOnSameTileIsLadder)
            ifAnyUnitOnSameTileIsLadder;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052F5B0,
                &UnitsState::ifAnyUnitOnSameTileIsLadderInRightDirection)
            ifAnyUnitOnSameTileIsLadderInRightDirection;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052F680, &UnitsState::detectTileUnitDesync)
            detectTileUnitDesync;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x0052F730,
                &UnitsState::removeUnitsSameTileLinkageIfNoLongerApplicable)
            removeUnitsSameTileLinkageIfNoLongerApplicable;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052F7E0,
                &UnitsState::calculateUnitMovementSpeed)
            calculateUnitMovementSpeed;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052FBB0,
                &UnitsState::makeSeatedUnitStand)
            makeSeatedUnitStand;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052FBF0, &UnitsState::makeUnitSit)
            makeUnitSit;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052FC30,
                &UnitsState::setUnitFacingTowardUnit)
            setUnitFacingTowardUnit;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052FCA0,
                &UnitsState::setUnitFacingTowardPoint)
            setUnitFacingTowardPoint;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052FD00,
                &UnitsState::setUnitFacingDirectionTowardsTarget)
            setUnitFacingDirectionTowardsTarget;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052FE00,
                &UnitsState::orientUnitTowardUnit)
            orientUnitTowardUnit;

            MACRO_FUNCTION_RESOLVER(bool (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052FE90,
                &UnitsState::setUnitFacingDirectionForTargetXandY)
            setUnitFacingDirectionForTargetXandY;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052FF80,
                &UnitsState::setUnitFacingDirectionBasedOnBuilding)
            setUnitFacingDirectionBasedOnBuilding;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00530080,
                &UnitsState::isUnitComputerManaged)
            isUnitComputerManaged;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005300B0, &UnitsState::playHurtSFXForUnit)
            playHurtSFXForUnit;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005301F0, &UnitsState::countAlivePlayerUnits)
            countAlivePlayerUnits;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00530240, &UnitsState::killPlayerTowerUnits)
            killPlayerTowerUnits;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005302B0, &UnitsState::killAllUnownedUnits)
            killAllUnownedUnits;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00530310, &UnitsState::removeWildlifeAnimals)
            removeWildlifeAnimals;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00530390, &UnitsState::killUnits)
            killUnits;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00530400,
                &UnitsState::reassignFarmAnimals)
            reassignFarmAnimals;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00530500,
                &UnitsState::makeCourtMemberUnitsDisappearAndSwapAllOtherUnitsOwnership)
            makeCourtMemberUnitsDisappearAndSwapAllOtherUnitsOwnership;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00530650,
                &UnitsState::makeUnitsDisappearThatCannotReachTheKeep)
            makeUnitsDisappearThatCannotReachTheKeep;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00530880, &UnitsState::setRandomNumberOnCows)
            setRandomNumberOnCows;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005308F0,
                &UnitsState::setMissionNumberSpecificLord)
            setMissionNumberSpecificLord;

            MACRO_FUNCTION_RESOLVER(undefined (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00530FD0,
                &UnitsState::checkIfCitizenUnitIsAliveBasedOnState)
            checkIfCitizenUnitIsAliveBasedOnState;

            MACRO_FUNCTION_RESOLVER(bool (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00531000,
                &UnitsState::canUnitsEngageEachOther)
            canUnitsEngageEachOther;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005311F0,
                &UnitsState::ComputeDamageFearFactorBonus)
            ComputeDamageFearFactorBonus;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00531220,
                &UnitsState::processUnitAttackOtherUnit)
            processUnitAttackOtherUnit;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00531920,
                &UnitsState::processEntityDamageToUnit)
            processEntityDamageToUnit;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00532460,
                &UnitsState::processFireDamageToUnit)
            processFireDamageToUnit;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, EntityTypeInt, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00532700, &UnitsState::shootProjectile)
            shootProjectile;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00532BA0,
                &UnitsState::recomputeTroopValuesForPlayer)
            recomputeTroopValuesForPlayer;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00532F60, &UnitsState::getArmySize)
            getArmySize;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00532F80,
                &UnitsState::distanceComputationForSomeOldCodeForSomeMissions)
            distanceComputationForSomeOldCodeForSomeMissions;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00533090, &UnitsState::returnFalse)
            returnFalse;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x005330A0,
                &UnitsState::setRandomShootLocation)
            setRandomShootLocation;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005334A0,
                &UnitsState::getRemainingRequiredEngineers)
            getRemainingRequiredEngineers;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533580,
                &UnitsState::checkTargetBuildingPossibilityOrState)
            checkTargetBuildingPossibilityOrState;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533630,
                &UnitsState::findClosestLaddermanWithLadderPosition)
            findClosestLaddermanWithLadderPosition;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00533810,
                &UnitsState::findAndDestroyAdjacentLadder)
            findAndDestroyAdjacentLadder;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00533920,
                &UnitsState::getDestination2EqualsGivenCoordinates)
            getDestination2EqualsGivenCoordinates;

            MACRO_FUNCTION_RESOLVER(
                bool (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533960, &UnitsState::isUnitAtDestination)
            isUnitAtDestination;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005339A0,
                &UnitsState::unitReachedDestination)
            unitReachedDestination;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005339F0,
                &UnitsState::isTunnelerNotFinished)
            isTunnelerNotFinished;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, uint, int, int), false,
                Address::SHC_3BB0A8C1_0x00533A10, &UnitsState::commitUnitLadderClimbPath)
            commitUnitLadderClimbPath;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00533B30,
                &UnitsState::changeDestinationByAmount)
            changeDestinationByAmount;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533C70,
                &UnitsState::changeDestinationByLeftover)
            changeDestinationByLeftover;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533CA0,
                &UnitsState::tracePathFromLadderExitSetDestination)
            tracePathFromLadderExitSetDestination;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533D50,
                &UnitsState::updateUnitFadeBehindStructures)
            updateUnitFadeBehindStructures;

            MACRO_FUNCTION_RESOLVER(undefined (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00533F90,
                &UnitsState::markTunnelerFinishedDigging)
            markTunnelerFinishedDigging;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533FC0, &UnitsState::removeTrappedWallUnit)
            removeTrappedWallUnit;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534030, &UnitsState::updateMicroPosition)
            updateMicroPosition;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005340F0,
                &UnitsState::adjustUnitMapOrientationRelatedPositionBasedOnMapOrientationCorrectedFacingDirection)
            adjustUnitMapOrientationRelatedPositionBasedOnMapOrientationCorrectedFacingDirection;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(uint), false, Address::SHC_3BB0A8C1_0x00534130, &UnitsState::digTunnelAlongPath)
            digTunnelAlongPath;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534240, &UnitsState::stopUnitIfNextToTarget)
            stopUnitIfNextToTarget;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534380,
                &UnitsState::isUnitAdjacentToWorkplace)
            isUnitAdjacentToWorkplace;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005343F0,
                &UnitsState::setWorkplaceBuildingEntryAsTarget)
            setWorkplaceBuildingEntryAsTarget;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534460, &UnitsState::unitIsInMoat)
            unitIsInMoat;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534490, &UnitsState::markUnitTileOccupancy)
            markUnitTileOccupancy;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, undefined4), false, Address::SHC_3BB0A8C1_0x00534520,
                &UnitsState::writeSixToTileMap1104InAllDirections)
            writeSixToTileMap1104InAllDirections;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x005345A0, &UnitsState::getUnitThatFulfillsSomeTimebasedAndLocationBasedCriteria)
            getUnitThatFulfillsSomeTimebasedAndLocationBasedCriteria;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005346D0, &UnitsState::selectNewBlessingTarget)
            selectNewBlessingTarget;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005347E0, &UnitsState::selectUnitsInDragBox)
            selectUnitsInDragBox;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00534D10, &UnitsState::selectOwnUnitsInDragBox)
            selectOwnUnitsInDragBox;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00534EE0, &UnitsState::selectSingleUnitInDragBox)
            selectSingleUnitInDragBox;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005350B0,
                &UnitsState::selectAllUnitsOfType)
            selectAllUnitsOfType;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535150, &UnitsState::deselectAllUnitsOneByOne)
            deselectAllUnitsOneByOne;

            MACRO_FUNCTION_RESOLVER(
                undefined (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535190, &UnitsState::deselectUnit)
            deselectUnit;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005351C0,
                &UnitsState::filterUnitSelectionExcludeUnitType)
            filterUnitSelectionExcludeUnitType;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00535200,
                &UnitsState::filterUnitSelectionForUnitType)
            filterUnitSelectionForUnitType;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535240, &UnitsState::recountUnitsInSelection)
            recountUnitsInSelection;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535520, &UnitsState::isSelectionOnlyEngineers)
            isSelectionOnlyEngineers;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535550, &UnitsState::selectionHasEngineers)
            selectionHasEngineers;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535560, &UnitsState::selectionHasArchers)
            selectionHasArchers;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535580,
                &UnitsState::selectionHasAdvancedUnit)
            selectionHasAdvancedUnit;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005355E0,
                &UnitsState::selectionHasSiegeAndOther)
            selectionHasSiegeAndOther;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535680, &UnitsState::findEngineerAtOilSmelter)
            findEngineerAtOilSmelter;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535700, &UnitsState::isSelectionOnlyTunnelers)
            isSelectionOnlyTunnelers;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535730,
                &UnitsState::selectionContainsRangedOnlyUnits)
            selectionContainsRangedOnlyUnits;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005357E0, &UnitsState::isSelectionOnlyLaddermen)
            isSelectionOnlyLaddermen;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535810,
                &UnitsState::selectionContainsOnlyArabAssassins)
            selectionContainsOnlyArabAssassins;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535840, &UnitsState::isSelectionOnlyShields)
            isSelectionOnlyShields;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535870,
                &UnitsState::selectionHasSiegeCoverAndOther)
            selectionHasSiegeCoverAndOther;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005358C0,
                &UnitsState::selectionHasShieldOrTowerAndOther)
            selectionHasShieldOrTowerAndOther;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535910,
                &UnitsState::selectionHasNoRangedUnits)
            selectionHasNoRangedUnits;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535980, &UnitsState::selectionCanDigMoat)
            selectionCanDigMoat;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005359C0, &UnitsState::getSelectedLordUnit)
            getSelectedLordUnit;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535A30, &UnitsState::createUnitSelection)
            createUnitSelection;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535B00,
                &UnitsState::createTribeFromSelectedUnits)
            createTribeFromSelectedUnits;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00535BC0,
                &UnitsState::playerMakeUnitSelection)
            playerMakeUnitSelection;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00535DF0,
                &UnitsState::queueTribeCommand)
            queueTribeCommand;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00535E20,
                &UnitsState::assignUnitToTribeWithSiegeSpeech)
            assignUnitToTribeWithSiegeSpeech;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00535FD0,
                &UnitsState::makeSelectionBasedOnShortcut)
            makeSelectionBasedOnShortcut;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005360A0,
                &UnitsState::isUnitShortcutAvailable)
            isUnitShortcutAvailable;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00536190,
                &UnitsState::selectAllTribeUnitsForPlayer)
            selectAllTribeUnitsForPlayer;

            MACRO_FUNCTION_RESOLVER(UnitTypeInt (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005361F0,
                &UnitsState::getUnitTypeOfFirstSelectedUnit)
            getUnitTypeOfFirstSelectedUnit;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536260,
                &UnitsState::selectionHasFieldUnit)
            selectionHasFieldUnit;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005362F0,
                &UnitsState::findSelectedUnitOfTypes)
            findSelectedUnitOfTypes;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536370, &UnitsState::getMaxSelectedCatapultAmmo)
            getMaxSelectedCatapultAmmo;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536400,
                &UnitsState::countSelectedStoneThrowers)
            countSelectedStoneThrowers;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005364C0,
                &UnitsState::returnFirstSelectedEngineer)
            returnFirstSelectedEngineer;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536530,
                &UnitsState::getTunnelerIDOnlyIfFirstSelected)
            getTunnelerIDOnlyIfFirstSelected;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005365A0, &UnitsState::getSelectedLadderUnit)
            getSelectedLadderUnit;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536610, &UnitsState::canAUnitClimb)
            canAUnitClimb;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536690, &UnitsState::getSelectedSiegeEngine)
            getSelectedSiegeEngine;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536710, &UnitsState::getSelectedStoneThrower)
            getSelectedStoneThrower;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00536780,
                &UnitsState::canCaptureTowerAtTile)
            canCaptureTowerAtTile;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536970,
                &UnitsState::checkAnySelectedUnitCannotClimb)
            checkAnySelectedUnitCannotClimb;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005369F0, &UnitsState::canManSiegeEngine)
            canManSiegeEngine;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(uint), false, Address::SHC_3BB0A8C1_0x00536A60,
                &UnitsState::selectionContainsCombatUnit)
            selectionContainsCombatUnit;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536C70, &UnitsState::queueUnitCommand0F)
            queueUnitCommand0F;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00536C90, &UnitsState::queueCommand0xF)
            queueCommand0xF;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00536CC0,
                &UnitsState::queueClickNavigateMenuOrEscape)
            queueClickNavigateMenuOrEscape;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, uint, int), false, Address::SHC_3BB0A8C1_0x00536CF0,
                &UnitsState::clearUnitSelectionAndTribe)
            clearUnitSelectionAndTribe;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536DE0, &UnitsState::clearSelectionCounts)
            clearSelectionCounts;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00536E30, &UnitsState::giveMoveCommand)
            giveMoveCommand;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, uint, uint, int, MatchSpeedInstructionEnumInt), false,
                Address::SHC_3BB0A8C1_0x00537070, &UnitsState::giveTribeMoveInstructionHumans)
            giveTribeMoveInstructionHumans;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x005370C0,
                &UnitsState::extendRallyPoint)
            extendRallyPoint;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x00537100, &UnitsState::queueDisbandAndAttackCommand)
            queueDisbandAndAttackCommand;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(undefined4, undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x00537130, &UnitsState::queueDisbandAndAttackUnitsCommand)
            queueDisbandAndAttackUnitsCommand;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(undefined4, undefined4, undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x00537160, &UnitsState::queueCommand_36d)
            queueCommand_36d;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(undefined4, UnitInstructionTypeInt, undefined4, undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x005371A0, &UnitsState::queueCommand_36_variation2)
            queueCommand_36_variation2;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, UnitInstructionTypeInt, int, int, int), false,
                Address::SHC_3BB0A8C1_0x005371E0, &UnitsState::giveTribeAnInstruction2)
            giveTribeAnInstruction2;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(uint, uint), false, Address::SHC_3BB0A8C1_0x005371F0,
                &UnitsState::findFreeTileNearby)
            findFreeTileNearby;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00537700,
                &UnitsState::findTunnelTarget)
            findTunnelTarget;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005377F0, &UnitsState::getAliveLordForPlayer)
            getAliveLordForPlayer;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00537840, &UnitsState::getRawDeerCount)
            getRawDeerCount;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00537880,
                &UnitsState::findNearestHuntableDeer)
            findNearestHuntableDeer;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00537A00,
                &UnitsState::findNearestIdleCow)
            findNearestIdleCow;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, BOOLEnum, uint, uint), false,
                Address::SHC_3BB0A8C1_0x00537AA0, &UnitsState::findClosestAnimalStoreResult)
            findClosestAnimalStoreResult;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, uint, uint, int), false, Address::SHC_3BB0A8C1_0x00537C10,
                &UnitsState::findClosestEnemyUnitInArea)
            findClosestEnemyUnitInArea;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00537D60,
                &UnitsState::tryAttackUnitID)
            tryAttackUnitID;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00537E00,
                &UnitsState::setTowerSiegeEngineToIdle)
            setTowerSiegeEngineToIdle;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00537EE0,
                &UnitsState::setAIControlStatusTo100000)
            setAIControlStatusTo100000;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, int*), false, Address::SHC_3BB0A8C1_0x00537F60,
                &UnitsState::getUnitAnimationIndex)
            getUnitAnimationIndex;

            MACRO_FUNCTION_RESOLVER(
                GmIDInt (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00539BE0, &UnitsState::getPeasantGmID)
            getPeasantGmID;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int*, int*), false, Address::SHC_3BB0A8C1_0x00539DF0,
                &UnitsState::chooseHusbandAndWife)
            chooseHusbandAndWife;

            MACRO_FUNCTION_RESOLVER(undefined (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x0053A070,
                &UnitsState::isWorkerInProductionState)
            isWorkerInProductionState;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053A150, &UnitsState::computeWorkerNextAction)
            computeWorkerNextAction;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053A4D0,
                &UnitsState::findPlayerOperationalSiegeEngine)
            findPlayerOperationalSiegeEngine;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053A560, &UnitsState::getLivingSelectableUnit)
            getLivingSelectableUnit;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x0053A5B0,
                &UnitsState::renderDebugDataUnitData)
            renderDebugDataUnitData;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, UnitTypeInt), false, Address::SHC_3BB0A8C1_0x0053B8E0,
                &UnitsState::setUnitValues)
            setUnitValues;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053BB10,
                &UnitsState::commitUnitPositionUpdate)
            commitUnitPositionUpdate;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053BB70,
                &UnitsState::setupUnitSharingCurrentTilePosition)
            setupUnitSharingCurrentTilePosition;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053BB90,
                &UnitsState::teleportUnitToUnitXAndY)
            teleportUnitToUnitXAndY;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0053CAE0,
                &UnitsState::getEnemyUnitIDNearby)
            getEnemyUnitIDNearby;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0053CBD0,
                &UnitsState::prepareProjectileTarget)
            prepareProjectileTarget;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053D030,
                &UnitsState::aiSiegeUnitPickTargetAndShoot)
            aiSiegeUnitPickTargetAndShoot;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x0053D3D0, &UnitsState::setDestinationForUnit)
            setDestinationForUnit;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053D850, &UnitsState::resumeUnitMovement)
            resumeUnitMovement;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053D900, &UnitsState::exitLadder)
            exitLadder;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x0053D9C0, &UnitsState::getUnitInHitBox)
            getUnitInHitBox;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0053DCC0,
                &UnitsState::setUnitDestinationNextToTargetBuilding)
            setUnitDestinationNextToTargetBuilding;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053DDD0,
                &UnitsState::computePeasantThoughtBubble)
            computePeasantThoughtBubble;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(PackagedFileMagicNumInt, PackagedFileMagicNumInt), false,
                Address::SHC_3BB0A8C1_0x0053E390, &UnitsState::upgradeMapFormatForUnits)
            upgradeMapFormatForUnits;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, int, int, int, int, UnitTypeInt), false,
                Address::SHC_3BB0A8C1_0x0053E440, &UnitsState::spawnUnit)
            spawnUnit;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053E6C0, &UnitsState::changeUnitType)
            changeUnitType;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(uint), false, Address::SHC_3BB0A8C1_0x0053E790, &UnitsState::deleteUnit)
            deleteUnit;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053E820, &UnitsState::commitUnitLocation)
            commitUnitLocation;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053E870, &UnitsState::someUnitMoveFunction)
            someUnitMoveFunction;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053E8D0, &UnitsState::revealHiddenUnit)
            revealHiddenUnit;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, uint, uint, undefined4), false,
                Address::SHC_3BB0A8C1_0x0053E900, &UnitsState::setPositionOfUnit)
            setPositionOfUnit;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053E9F0, &UnitsState::commitMimmicLocation)
            commitMimmicLocation;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00540040,
                &UnitsState::ifOnADefensiveStructureSetDestinationInDirectionOfTarget)
            ifOnADefensiveStructureSetDestinationInDirectionOfTarget;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00549C70, &UnitsState::processMeleeInitiation)
            processMeleeInitiation;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0054A770,
                &UnitsState::resumeUnitIfNotAttacking)
            resumeUnitIfNotAttacking;

            MACRO_FUNCTION_RESOLVER(dword (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0054A7B0,
                &UnitsState::unitAcquireBestEnemyTargetAndPursue)
            unitAcquireBestEnemyTargetAndPursue;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(short*), false, Address::SHC_3BB0A8C1_0x0054B0D0,
                &UnitsState::acquireAndSetShootTarget)
            acquireAndSetShootTarget;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0054BFC0, &UnitsState::updateClimbing)
            updateClimbing;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0054C1C0, &UnitsState::unitClimbing)
            unitClimbing;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0054C4F0,
                &UnitsState::handleUnitMovementWhenTargetingBuildings)
            handleUnitMovementWhenTargetingBuildings;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0054C610,
                &UnitsState::moveToFreeTileNearby)
            moveToFreeTileNearby;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00578C40,
                &UnitsState::processUnitMove)
            processUnitMove;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00579300, &UnitsState::updateUnits)
            updateUnits;

        } // namespace UnitsState_Func
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
