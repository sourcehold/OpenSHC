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

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052F070,
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

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052F4E0, &UnitsState::meth_0x52f4e0)
            meth_0x52f4e0;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052F550,
                &UnitsState::ifAnyUnitOnSameTileIsLadder)
            ifAnyUnitOnSameTileIsLadder;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052F5B0,
                &UnitsState::ifAnyUnitOnSameTileIsLadderInRightDirection)
            ifAnyUnitOnSameTileIsLadderInRightDirection;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052F680, &UnitsState::FUN_0052f680)
            FUN_0052f680;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x0052F730,
                &UnitsState::removeUnitsSameTileLinkageIfNoLongerApplicable)
            removeUnitsSameTileLinkageIfNoLongerApplicable;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052F7E0,
                &UnitsState::calculateUnitMovementSpeed)
            calculateUnitMovementSpeed;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052FBB0, &UnitsState::meth_0x52fbb0)
            meth_0x52fbb0;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052FBF0, &UnitsState::meth_0x52fbf0)
            meth_0x52fbf0;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052FC30, &UnitsState::meth_0x52fc30)
            meth_0x52fc30;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052FCA0,
                &UnitsState::meth_0x52fca0)
            meth_0x52fca0;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052FD00,
                &UnitsState::setUnitFacingDirectionTowardsTarget)
            setUnitFacingDirectionTowardsTarget;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052FE00, &UnitsState::FUN_0052fe00)
            FUN_0052fe00;

            MACRO_FUNCTION_RESOLVER(bool (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052FE90,
                &UnitsState::setUnitFacingDirectionForTargetXandY)
            setUnitFacingDirectionForTargetXandY;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052FF80,
                &UnitsState::setUnitFacingDirectionBasedOnBuilding)
            setUnitFacingDirectionBasedOnBuilding;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00530080, &UnitsState::FUN_00530080)
            FUN_00530080;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005300B0, &UnitsState::playHurtSFXForUnit)
            playHurtSFXForUnit;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005301F0, &UnitsState::meth_0x5301f0)
            meth_0x5301f0;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00530240, &UnitsState::meth_0x530240)
            meth_0x530240;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005302B0, &UnitsState::killAllUnownedUnits)
            killAllUnownedUnits;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00530310, &UnitsState::meth_0x530310)
            meth_0x530310;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00530390, &UnitsState::killUnits)
            killUnits;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00530400, &UnitsState::meth_0x530400)
            meth_0x530400;

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

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00530FD0,
                &UnitsState::checkIfCitizenUnitIsAliveBasedOnStateUnk)
            checkIfCitizenUnitIsAliveBasedOnStateUnk;

            MACRO_FUNCTION_RESOLVER(
                bool (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00531000, &UnitsState::meth_0x531000)
            meth_0x531000;

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
                BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00533090, &UnitsState::FUN_00533090)
            FUN_00533090;

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

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00533810, &UnitsState::meth_0x533810)
            meth_0x533810;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00533920,
                &UnitsState::getDestination2EqualsGivenCoordinates)
            getDestination2EqualsGivenCoordinates;

            MACRO_FUNCTION_RESOLVER(
                bool (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533960, &UnitsState::meth_0x533960)
            meth_0x533960;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005339A0,
                &UnitsState::unitReachedDestinationUnk)
            unitReachedDestinationUnk;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005339F0, &UnitsState::meth_0x5339f0)
            meth_0x5339f0;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, uint, int, int), false,
                Address::SHC_3BB0A8C1_0x00533A10, &UnitsState::ladderClimbRelatedUnk)
            ladderClimbRelatedUnk;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00533B30,
                &UnitsState::changeDestinationByAmount)
            changeDestinationByAmount;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533C70,
                &UnitsState::changeDestinationByLeftover)
            changeDestinationByLeftover;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533CA0,
                &UnitsState::tracePathFromLadderExitSetDestination)
            tracePathFromLadderExitSetDestination;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533D50, &UnitsState::FUN_00533d50)
            FUN_00533d50;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533F90, &UnitsState::meth_0x533f90)
            meth_0x533f90;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533FC0, &UnitsState::meth_0x533fc0)
            meth_0x533fc0;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534030, &UnitsState::updateMicroPosition)
            updateMicroPosition;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005340F0,
                &UnitsState::adjustUnitMapOrientationRelatedPositionBasedOnMapOrientationCorrectedFacingDirection)
            adjustUnitMapOrientationRelatedPositionBasedOnMapOrientationCorrectedFacingDirection;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(uint), false, Address::SHC_3BB0A8C1_0x00534130, &UnitsState::meth_0x534130)
            meth_0x534130;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534240, &UnitsState::stopUnitIfNextToTarget)
            stopUnitIfNextToTarget;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534380, &UnitsState::meth_0x534380)
            meth_0x534380;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005343F0,
                &UnitsState::setWorkplaceBuildingEntryAsTarget)
            setWorkplaceBuildingEntryAsTarget;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534460, &UnitsState::unitIsInMoat)
            unitIsInMoat;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534490, &UnitsState::meth_0x534490)
            meth_0x534490;

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
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005347E0, &UnitsState::meth_0x5347e0)
            meth_0x5347e0;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00534D10, &UnitsState::meth_0x534d10)
            meth_0x534d10;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00534EE0, &UnitsState::meth_0x534ee0)
            meth_0x534ee0;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005350B0, &UnitsState::meth_0x5350b0)
            meth_0x5350b0;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535150, &UnitsState::deselectAllUnitsOneByOne)
            deselectAllUnitsOneByOne;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00535190, &UnitsState::deselectUnit)
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
                int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535520, &UnitsState::meth_0x535520)
            meth_0x535520;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535550, &UnitsState::meth_0x535550)
            meth_0x535550;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535560, &UnitsState::meth_0x535560)
            meth_0x535560;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535580, &UnitsState::meth_0x535580)
            meth_0x535580;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005355E0, &UnitsState::meth_0x5355e0)
            meth_0x5355e0;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535680, &UnitsState::meth_0x535680)
            meth_0x535680;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535700, &UnitsState::meth_0x535700)
            meth_0x535700;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535730,
                &UnitsState::selectionContainsRangedOnlyUnits)
            selectionContainsRangedOnlyUnits;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005357E0, &UnitsState::meth_0x5357e0)
            meth_0x5357e0;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535810,
                &UnitsState::selectionContainsOnlyArabAssassins)
            selectionContainsOnlyArabAssassins;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535840, &UnitsState::meth_0x535840)
            meth_0x535840;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535870, &UnitsState::meth_0x535870)
            meth_0x535870;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005358C0, &UnitsState::meth_0x5358c0)
            meth_0x5358c0;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535910, &UnitsState::meth_0x535910)
            meth_0x535910;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535980, &UnitsState::meth_0x535980)
            meth_0x535980;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005359C0, &UnitsState::meth_0x5359c0)
            meth_0x5359c0;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535A30, &UnitsState::createUnitSelection)
            createUnitSelection;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535B00,
                &UnitsState::createTribeFromSelectedUnits)
            createTribeFromSelectedUnits;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00535BC0,
                &UnitsState::playerMakeUnitSelection)
            playerMakeUnitSelection;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00535DF0, &UnitsState::FUN_00535df0)
            FUN_00535df0;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00535E20,
                &UnitsState::siegeEngineRelated)
            siegeEngineRelated;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00535FD0,
                &UnitsState::makeSelectionBasedOnShortcut)
            makeSelectionBasedOnShortcut;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005360A0,
                &UnitsState::isUnitShortcutAvailable)
            isUnitShortcutAvailable;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00536190, &UnitsState::tribeRelated1)
            tribeRelated1;

            MACRO_FUNCTION_RESOLVER(UnitTypeInt (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005361F0,
                &UnitsState::getUnitTypeOfFirstSelectedUnit)
            getUnitTypeOfFirstSelectedUnit;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536260, &UnitsState::meth_0x536260)
            meth_0x536260;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005362F0, &UnitsState::meth_0x5362f0)
            meth_0x5362f0;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536370, &UnitsState::meth_0x536370)
            meth_0x536370;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536400, &UnitsState::meth_0x536400)
            meth_0x536400;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005364C0,
                &UnitsState::returnFirstSelectedEngineer)
            returnFirstSelectedEngineer;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536530,
                &UnitsState::getTunnelerIDOnlyIfFirstSelected)
            getTunnelerIDOnlyIfFirstSelected;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005365A0, &UnitsState::meth_0x5365a0)
            meth_0x5365a0;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536610, &UnitsState::canAUnitClimb)
            canAUnitClimb;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536690, &UnitsState::meth_0x536690)
            meth_0x536690;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536710, &UnitsState::meth_0x536710)
            meth_0x536710;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00536780, &UnitsState::meth_0x536780)
            meth_0x536780;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536970,
                &UnitsState::checkAnySelectedUnitCannotClimb)
            checkAnySelectedUnitCannotClimb;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005369F0, &UnitsState::meth_0x5369f0)
            meth_0x5369f0;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(uint), false, Address::SHC_3BB0A8C1_0x00536A60,
                &UnitsState::selectionContainsCombatUnit)
            selectionContainsCombatUnit;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536C70, &UnitsState::FUN_00536c70)
            FUN_00536c70;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00536C90, &UnitsState::queueCommand0xF)
            queueCommand0xF;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00536CC0,
                &UnitsState::queueClickNavigateMenuOrEscape)
            queueClickNavigateMenuOrEscape;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, uint, int), false, Address::SHC_3BB0A8C1_0x00536CF0,
                &UnitsState::tribeRelated2)
            tribeRelated2;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536DE0, &UnitsState::meth_0x536de0)
            meth_0x536de0;

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
                Address::SHC_3BB0A8C1_0x00537100, &UnitsState::FUN_00537100)
            FUN_00537100;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(undefined4, undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x00537130, &UnitsState::FUN_00537130)
            FUN_00537130;

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

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00537880, &UnitsState::meth_0x537880)
            meth_0x537880;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00537A00, &UnitsState::meth_0x537a00)
            meth_0x537a00;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, BOOLEnum, uint, uint), false,
                Address::SHC_3BB0A8C1_0x00537AA0, &UnitsState::findClosestAnimalStoreResult)
            findClosestAnimalStoreResult;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, uint, uint, int), false, Address::SHC_3BB0A8C1_0x00537C10,
                &UnitsState::getClosestUnitIDUnk)
            getClosestUnitIDUnk;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00537D60,
                &UnitsState::tryAttackUnitID)
            tryAttackUnitID;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00537E00,
                &UnitsState::setTowerSiegeEngineToIdle)
            setTowerSiegeEngineToIdle;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00537EE0,
                &UnitsState::setAIControlStatusTo100000)
            setAIControlStatusTo100000;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int, int*), false, Address::SHC_3BB0A8C1_0x00537F60, &UnitsState::FUN_00537f60)
            FUN_00537f60;

            MACRO_FUNCTION_RESOLVER(
                GmIDInt (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00539BE0, &UnitsState::getPeasantGmID)
            getPeasantGmID;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int*, int*), false, Address::SHC_3BB0A8C1_0x00539DF0,
                &UnitsState::chooseHusbandAndWife)
            chooseHusbandAndWife;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053A070, &UnitsState::meth_0x53a070)
            meth_0x53a070;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053A150, &UnitsState::meth_0x53a150)
            meth_0x53a150;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053A4D0, &UnitsState::meth_0x53a4d0)
            meth_0x53a4d0;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053A560, &UnitsState::getLivingSelectableUnit)
            getLivingSelectableUnit;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x0053A5B0,
                &UnitsState::renderDebugDataUnitData)
            renderDebugDataUnitData;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, UnitTypeInt), false, Address::SHC_3BB0A8C1_0x0053B8E0,
                &UnitsState::setUnitValues)
            setUnitValues;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053BB10, &UnitsState::updateUnitPositionUnk)
            updateUnitPositionUnk;

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
                &UnitsState::harassBuildingsAIUnk)
            harassBuildingsAIUnk;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x0053D3D0, &UnitsState::setDestinationForUnit)
            setDestinationForUnit;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053D850, &UnitsState::meth_0x53d850)
            meth_0x53d850;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053D900, &UnitsState::exitLadder)
            exitLadder;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x0053D9C0, &UnitsState::getUnitInHitBox)
            getUnitInHitBox;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0053DCC0,
                &UnitsState::setTargetedBuildingDestinationUnk)
            setTargetedBuildingDestinationUnk;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053DDD0, &UnitsState::meth_0x53ddd0)
            meth_0x53ddd0;

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
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053E8D0, &UnitsState::meth_0x53e8d0)
            meth_0x53e8d0;

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

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0054A770, &UnitsState::meth_0x54a770)
            meth_0x54a770;

            MACRO_FUNCTION_RESOLVER(dword (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0054A7B0,
                &UnitsState::findNearestEnemyAndHeadTowardsItUnk)
            findNearestEnemyAndHeadTowardsItUnk;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(short*), false, Address::SHC_3BB0A8C1_0x0054B0D0,
                &UnitsState::canShootTargetUnk)
            canShootTargetUnk;

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
