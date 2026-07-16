/**
  path: 'OpenSHC/Map/Units/UnitsState.func.hpp'
*/

#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/Instructions/MatchSpeedInstructionEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitsState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace UnitsState_Func {

            using OpenSHC::IO::PackagedFileMagicNum;
            using OpenSHC::IO::Graphics::GmID;
            using OpenSHC::Map::Entities::EntityType;
            using OpenSHC::Map::Units::UnitInstructionType;
            using OpenSHC::Map::Units::UnitType;
            using OpenSHC::Map::Units::Instructions::MatchSpeedInstructionEnum;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            // Constructor

            MACRO_FUNCTION_RESOLVER(UnitsState* (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x0053B8B0,
                &UnitsState::constructUnitsState)
            constructUnitsState;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x0052E7B0, &UnitsState::clearAllUnits)
            clearAllUnits;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(UnitType, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0052E830, &UnitsState::assignPeasantToBuilding)
            assignPeasantToBuilding;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, undefined4, int, int), false,
                Address::SHC_3BB0A8C1_0x0052E960, &UnitsState::euroRecruit)
            euroRecruit;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(UnitType, undefined4, int, int), false,
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

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052F4E0,
                &UnitsState::isUnitRegisteredOnItsOwnTile)
            isUnitRegisteredOnItsOwnTile;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052F550,
                &UnitsState::ifAnyUnitOnSameTileIsLadder)
            ifAnyUnitOnSameTileIsLadder;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052F5B0,
                &UnitsState::ifAnyUnitOnSameTileIsLadderInRightDirection)
            ifAnyUnitOnSameTileIsLadderInRightDirection;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052F680,
                &UnitsState::triggerDesyncIfTileUnitLinkageInvalid)
            triggerDesyncIfTileUnitLinkageInvalid;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x0052F730,
                &UnitsState::removeUnitsSameTileLinkageIfNoLongerApplicable)
            removeUnitsSameTileLinkageIfNoLongerApplicable;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052F7E0,
                &UnitsState::calculateUnitMovementSpeed)
            calculateUnitMovementSpeed;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052FBB0, &UnitsState::standUpIfSeated)
            standUpIfSeated;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0052FBF0,
                &UnitsState::sitDownIfStanding)
            sitDownIfStanding;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052FC30,
                &UnitsState::setFacingDirectionTowardUnit)
            setFacingDirectionTowardUnit;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052FCA0,
                &UnitsState::setFacingDirectionTowardCoords)
            setFacingDirectionTowardCoords;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052FD00,
                &UnitsState::setUnitFacingDirectionTowardsTarget)
            setUnitFacingDirectionTowardsTarget;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052FE00,
                &UnitsState::setFacingDirectionTowardUnitMicro)
            setFacingDirectionTowardUnitMicro;

            MACRO_FUNCTION_RESOLVER(bool (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052FE90,
                &UnitsState::setUnitFacingDirectionForTargetXandY)
            setUnitFacingDirectionForTargetXandY;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052FF80,
                &UnitsState::setUnitFacingDirectionBasedOnBuilding)
            setUnitFacingDirectionBasedOnBuilding;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00530080,
                &UnitsState::isComputerManagedNonPeasant)
            isComputerManagedNonPeasant;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005300B0, &UnitsState::playHurtSFXForUnit)
            playHurtSFXForUnit;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005301F0,
                &UnitsState::countLivingNondyingUnitsForPlayer)
            countLivingNondyingUnitsForPlayer;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00530240,
                &UnitsState::triggerStoneTowerDeathForPlayer)
            triggerStoneTowerDeathForPlayer;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005302B0, &UnitsState::killAllUnownedUnits)
            killAllUnownedUnits;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00530310,
                &UnitsState::triggerDeathAnimationForAllWildlife)
            triggerDeathAnimationForAllWildlife;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00530390, &UnitsState::killUnits)
            killUnits;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00530400,
                &UnitsState::transferNonCourtUnitsToPlayer)
            transferNonCourtUnitsToPlayer;

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
                &UnitsState::checkIfCitizenUnitIsAliveBasedOnState)
            checkIfCitizenUnitIsAliveBasedOnState;

            MACRO_FUNCTION_RESOLVER(bool (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00531000,
                &UnitsState::shouldUnitsEngageInMelee)
            shouldUnitsEngageInMelee;

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

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, EntityType, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00532700, &UnitsState::shootProjectile)
            shootProjectile;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00532BA0,
                &UnitsState::recomputeTroopValuesForPlayer)
            recomputeTroopValuesForPlayer;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00532F60, &UnitsState::getArmySize)
            getArmySize;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00532F80,
                &UnitsState::computeDistanceToNearestEnemyForLegacyMissions)
            computeDistanceToNearestEnemyForLegacyMissions;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00533090, &UnitsState::returnFalseStub)
            returnFalseStub;

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
                &UnitsState::findAndDestroyAdjacentEnemyLadder)
            findAndDestroyAdjacentEnemyLadder;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00533920,
                &UnitsState::getDestination2EqualsGivenCoordinates)
            getDestination2EqualsGivenCoordinates;

            MACRO_FUNCTION_RESOLVER(bool (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533960,
                &UnitsState::isAtSecondaryDestination)
            isAtSecondaryDestination;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005339A0,
                &UnitsState::hasUnitReachedDestination)
            hasUnitReachedDestination;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005339F0,
                &UnitsState::hasTunnelerNotFinishedDigging)
            hasTunnelerNotFinishedDigging;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, uint, int, int), false,
                Address::SHC_3BB0A8C1_0x00533A10, &UnitsState::computeLadderClimbPath)
            computeLadderClimbPath;

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
                &UnitsState::updateUnitFadeAndVisibilityNearStructures)
            updateUnitFadeAndVisibilityNearStructures;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533F90,
                &UnitsState::saveUnitStateBeforeInterruption)
            saveUnitStateBeforeInterruption;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00533FC0, &UnitsState::despawnUnreachableUnit)
            despawnUnreachableUnit;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534030, &UnitsState::updateMicroPosition)
            updateMicroPosition;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005340F0,
                &UnitsState::adjustUnitMapOrientationRelatedPositionBasedOnMapOrientationCorrectedFacingDirection)
            adjustUnitMapOrientationRelatedPositionBasedOnMapOrientationCorrectedFacingDirection;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(uint), false, Address::SHC_3BB0A8C1_0x00534130,
                &UnitsState::applyTunnelDamageAlongPathPlan)
            applyTunnelDamageAlongPathPlan;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534240, &UnitsState::stopUnitIfNextToTarget)
            stopUnitIfNextToTarget;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534380,
                &UnitsState::isWorkplaceBuildingOnAdjacentTile)
            isWorkplaceBuildingOnAdjacentTile;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005343F0,
                &UnitsState::setWorkplaceBuildingEntryAsTarget)
            setWorkplaceBuildingEntryAsTarget;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534460, &UnitsState::unitIsInMoat)
            unitIsInMoat;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00534490,
                &UnitsState::stampOccupancyFlagOnSurroundingTiles)
            stampOccupancyFlagOnSurroundingTiles;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, undefined4), false, Address::SHC_3BB0A8C1_0x00534520,
                &UnitsState::writeSixToTileMap1104InAllDirections)
            writeSixToTileMap1104InAllDirections;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x005345A0, &UnitsState::findEligibleUnitByTimeAndLocation)
            findEligibleUnitByTimeAndLocation;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005346D0, &UnitsState::selectNewBlessingTarget)
            selectNewBlessingTarget;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005347E0,
                &UnitsState::applyDragBoxSelectionByPriority)
            applyDragBoxSelectionByPriority;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00534D10,
                &UnitsState::selectUnitsInDragBoxForCurrentPlayer)
            selectUnitsInDragBoxForCurrentPlayer;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00534EE0,
                &UnitsState::selectFirstUnitInDragBoxAnyPlayer)
            selectFirstUnitInDragBoxAnyPlayer;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005350B0,
                &UnitsState::selectAllUnitsOfTypeForPlayer)
            selectAllUnitsOfTypeForPlayer;

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

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535520,
                &UnitsState::selectionContainsEngineersOnly)
            selectionContainsEngineersOnly;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535550, &UnitsState::selectionHasEngineers)
            selectionHasEngineers;

            MACRO_FUNCTION_RESOLVER(
                BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535560, &UnitsState::selectionHasArchers)
            selectionHasArchers;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535580,
                &UnitsState::selectionHasMobileAssaultUnits)
            selectionHasMobileAssaultUnits;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005355E0,
                &UnitsState::selectionHasMixedAssaultAndInfantry)
            selectionHasMixedAssaultAndInfantry;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535680,
                &UnitsState::getSelectedEngineerCarryingResource)
            getSelectedEngineerCarryingResource;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535700,
                &UnitsState::selectionContainsTunnelersOnly)
            selectionContainsTunnelersOnly;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535730,
                &UnitsState::selectionContainsRangedOnlyUnits)
            selectionContainsRangedOnlyUnits;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005357E0,
                &UnitsState::selectionContainsLadermenOnly)
            selectionContainsLadermenOnly;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535810,
                &UnitsState::selectionContainsOnlyArabAssassins)
            selectionContainsOnlyArabAssassins;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535840,
                &UnitsState::selectionContainsShieldmenOnly)
            selectionContainsShieldmenOnly;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535870,
                &UnitsState::selectionHasShieldOrSiegeMobileUnits)
            selectionHasShieldOrSiegeMobileUnits;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005358C0,
                &UnitsState::selectionHasShieldOrSiegeTower)
            selectionHasShieldOrSiegeTower;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535910,
                &UnitsState::selectionHasNoRangedUnits)
            selectionHasNoRangedUnits;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00535980,
                &UnitsState::selectionHasFootSoldiers)
            selectionHasFootSoldiers;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005359C0,
                &UnitsState::getSelectedLordIDIfOwnedByCurrentPlayer)
            getSelectedLordIDIfOwnedByCurrentPlayer;

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
                &UnitsState::getFirstSelectedUnitID)
            getFirstSelectedUnitID;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00535E20,
                &UnitsState::selectSiegeEngineAndPlayFeedback)
            selectSiegeEngineAndPlayFeedback;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00535FD0,
                &UnitsState::makeSelectionBasedOnShortcut)
            makeSelectionBasedOnShortcut;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005360A0,
                &UnitsState::isUnitShortcutAvailable)
            isUnitShortcutAvailable;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00536190,
                &UnitsState::selectTribeUnitsForPlayer)
            selectTribeUnitsForPlayer;

            MACRO_FUNCTION_RESOLVER(UnitType (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005361F0,
                &UnitsState::getUnitTypeOfFirstSelectedUnit)
            getUnitTypeOfFirstSelectedUnit;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536260,
                &UnitsState::selectionHasMovableNonSiegeUnit)
            selectionHasMovableNonSiegeUnit;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x005362F0,
                &UnitsState::getFirstSelectedUnitOfEitherType)
            getFirstSelectedUnitOfEitherType;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536370,
                &UnitsState::getMaxStoneAmmoInSelectedSiegeEngines)
            getMaxStoneAmmoInSelectedSiegeEngines;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536400,
                &UnitsState::countSelectedCatapultsAndTrebuchets)
            countSelectedCatapultsAndTrebuchets;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005364C0,
                &UnitsState::returnFirstSelectedEngineer)
            returnFirstSelectedEngineer;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536530,
                &UnitsState::getTunnelerIDOnlyIfFirstSelected)
            getTunnelerIDOnlyIfFirstSelected;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x005365A0,
                &UnitsState::getFirstSelectedLadderUnitID)
            getFirstSelectedLadderUnitID;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536610, &UnitsState::canAUnitClimb)
            canAUnitClimb;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536690,
                &UnitsState::getFirstSelectedSiegeEngineID)
            getFirstSelectedSiegeEngineID;

            MACRO_FUNCTION_RESOLVER(uint (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536710,
                &UnitsState::getFirstSelectedCatapultOrTrebuchetID)
            getFirstSelectedCatapultOrTrebuchetID;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00536780,
                &UnitsState::isTowerTileOvercrowdedByCurrentPlayer)
            isTowerTileOvercrowdedByCurrentPlayer;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536970,
                &UnitsState::checkAnySelectedUnitCannotClimb)
            checkAnySelectedUnitCannotClimb;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x005369F0,
                &UnitsState::selectionHasUnmannedSiegeEngine)
            selectionHasUnmannedSiegeEngine;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(uint), false, Address::SHC_3BB0A8C1_0x00536A60,
                &UnitsState::selectionContainsCombatUnit)
            selectionContainsCombatUnit;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536C70, &UnitsState::queueStopCommand)
            queueStopCommand;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00536C90,
                &UnitsState::queueUnitTypeCommand)
            queueUnitTypeCommand;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00536CC0,
                &UnitsState::queueClickNavigateMenuOrEscape)
            queueClickNavigateMenuOrEscape;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, uint, int), false, Address::SHC_3BB0A8C1_0x00536CF0,
                &UnitsState::clearOrDeselectUnitFromSelection)
            clearOrDeselectUnitFromSelection;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(), false, Address::SHC_3BB0A8C1_0x00536DE0,
                &UnitsState::clearSelectionCountsAndPlayerIDs)
            clearSelectionCountsAndPlayerIDs;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00536E30, &UnitsState::giveMoveCommand)
            giveMoveCommand;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, uint, uint, int, MatchSpeedInstructionEnum), false,
                Address::SHC_3BB0A8C1_0x00537070, &UnitsState::giveTribeMoveInstructionHumans)
            giveTribeMoveInstructionHumans;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x005370C0,
                &UnitsState::extendRallyPoint)
            extendRallyPoint;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x00537100, &UnitsState::queueDisbandAndAttackCommand2Params)
            queueDisbandAndAttackCommand2Params;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(undefined4, undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x00537130, &UnitsState::queueDisbandAndAttackCommand3Params)
            queueDisbandAndAttackCommand3Params;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(undefined4, undefined4, undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x00537160, &UnitsState::queueDisbandAndAttackCommand4Params)
            queueDisbandAndAttackCommand4Params;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(undefined4, UnitInstructionType, undefined4, undefined4, undefined4), false,
                Address::SHC_3BB0A8C1_0x005371A0, &UnitsState::queueDisbandAndAttackCommand5Params)
            queueDisbandAndAttackCommand5Params;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, UnitInstructionType, int, int, int), false,
                Address::SHC_3BB0A8C1_0x005371E0, &UnitsState::relayTribeInstruction)
            relayTribeInstruction;

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
                &UnitsState::findNearestShootableDeer)
            findNearestShootableDeer;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00537A00,
                &UnitsState::findNearestIdleCowForPlayer)
            findNearestIdleCowForPlayer;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, BOOLEnum, uint, uint), false,
                Address::SHC_3BB0A8C1_0x00537AA0, &UnitsState::findClosestAnimalStoreResult)
            findClosestAnimalStoreResult;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, uint, uint, int), false, Address::SHC_3BB0A8C1_0x00537C10,
                &UnitsState::findClosestEnemyByAreaAndRange)
            findClosestEnemyByAreaAndRange;

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
                &UnitsState::clearUnitPositionCommitState)
            clearUnitPositionCommitState;

            MACRO_FUNCTION_RESOLVER(
                GmID (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x00539BE0, &UnitsState::getPeasantGmID)
            getPeasantGmID;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int*, int*), false, Address::SHC_3BB0A8C1_0x00539DF0,
                &UnitsState::chooseHusbandAndWife)
            chooseHusbandAndWife;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053A070,
                &UnitsState::isWorkerAtProductionIdleState)
            isWorkerAtProductionIdleState;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053A150,
                &UnitsState::getWorkerBlockingStateIfStuck)
            getWorkerBlockingStateIfStuck;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053A4D0,
                &UnitsState::findActiveSiegeEngineForTribe)
            findActiveSiegeEngineForTribe;

            MACRO_FUNCTION_RESOLVER(
                int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053A560, &UnitsState::getLivingSelectableUnit)
            getLivingSelectableUnit;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x0053A5B0,
                &UnitsState::renderDebugDataUnitData)
            renderDebugDataUnitData;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int, UnitType), false, Address::SHC_3BB0A8C1_0x0053B8E0,
                &UnitsState::setUnitValues)
            setUnitValues;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053BB10,
                &UnitsState::commitPendingUnitPosition)
            commitPendingUnitPosition;

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
                &UnitsState::harassBuildingsWithSiegeAI)
            harassBuildingsWithSiegeAI;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(int, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x0053D3D0, &UnitsState::setDestinationForUnit)
            setDestinationForUnit;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053D850,
                &UnitsState::resumeMovementAfterInterruption)
            resumeMovementAfterInterruption;

            MACRO_FUNCTION_RESOLVER(
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053D900, &UnitsState::exitLadder)
            exitLadder;

            MACRO_FUNCTION_RESOLVER(
                uint (UnitsState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x0053D9C0, &UnitsState::getUnitInHitBox)
            getUnitInHitBox;

            MACRO_FUNCTION_RESOLVER(undefined4 (UnitsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0053DCC0,
                &UnitsState::setDestinationNearTargetedBuilding)
            setDestinationNearTargetedBuilding;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053DDD0,
                &UnitsState::selectWorkerSpeechOrMoraleStateID)
            selectWorkerSpeechOrMoraleStateID;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(PackagedFileMagicNum, PackagedFileMagicNum), false,
                Address::SHC_3BB0A8C1_0x0053E390, &UnitsState::upgradeMapFormatForUnits)
            upgradeMapFormatForUnits;

            MACRO_FUNCTION_RESOLVER(int (UnitsState::*)(int, int, int, int, int, UnitType), false,
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
                void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053E870, &UnitsState::resetUnitMovementState)
            resetUnitMovementState;

            MACRO_FUNCTION_RESOLVER(void (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0053E8D0,
                &UnitsState::clearHiddenFlagAndUpdatePosition)
            clearHiddenFlagAndUpdatePosition;

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
                &UnitsState::resumeMovementIfNoAttackTarget)
            resumeMovementIfNoAttackTarget;

            MACRO_FUNCTION_RESOLVER(dword (UnitsState::*)(int), false, Address::SHC_3BB0A8C1_0x0054A7B0,
                &UnitsState::findNearestEnemyAndHeadTowardsIt)
            findNearestEnemyAndHeadTowardsIt;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (UnitsState::*)(short*), false, Address::SHC_3BB0A8C1_0x0054B0D0,
                &UnitsState::acquireShootTarget)
            acquireShootTarget;

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
