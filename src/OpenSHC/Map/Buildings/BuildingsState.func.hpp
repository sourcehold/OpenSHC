/**
  path: 'OpenSHC/Map/Buildings/BuildingsState.func.hpp'
*/

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace Buildings {
        namespace BuildingsState_Func {

            using OpenSHC::Commands::CommandBuildingTypeInt;
            using OpenSHC::Game::Player::PlayerID;
            using OpenSHC::Game::Resources::ResourceTypeInt;
            using OpenSHC::IO::PackagedFileMagicNumInt;
            using OpenSHC::Map::Buildings::BuildingTypeInt;
            using OpenSHC::Map::Units::UnitTypeInt;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, int, ResourceTypeInt), false,
                Address::SHC_3BB0A8C1_0x00409330, &BuildingsState::someArrayIndexingOnBuildingField0x120)
            someArrayIndexingOnBuildingField0x120;

            MACRO_FUNCTION_RESOLVER(undefined (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x00409370,
                &BuildingsState::convertCommandBuildingTypeToBuildingType)
            convertCommandBuildingTypeToBuildingType;

            MACRO_FUNCTION_RESOLVER(CommandBuildingTypeInt (BuildingsState::*)(BuildingTypeInt), false,
                Address::SHC_3BB0A8C1_0x00409930, &BuildingsState::convertBuildingTypeToCommandBuildingType)
            convertBuildingTypeToCommandBuildingType;

            MACRO_FUNCTION_RESOLVER(undefined (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x00409DB0,
                &BuildingsState::getBuildingHeightForBuildingID)
            getBuildingHeightForBuildingID;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x00409E80,
                &BuildingsState::GetBuildingHeightForBuildingID_type2)
            GetBuildingHeightForBuildingID_type2;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(CommandBuildingTypeInt), false,
                Address::SHC_3BB0A8C1_0x00409F50, &BuildingsState::getSpriteID)
            getSpriteID;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(CommandBuildingTypeInt), false,
                Address::SHC_3BB0A8C1_0x00409FF0, &BuildingsState::getSpriteID2)
            getSpriteID2;

            MACRO_FUNCTION_RESOLVER(
                void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040A020, &BuildingsState::clearBuildings)
            clearBuildings;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, int, int, undefined4), false,
                Address::SHC_3BB0A8C1_0x0040A060, &BuildingsState::displayPopularityAndGoldPopups)
            displayPopularityAndGoldPopups;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040A260,
                &BuildingsState::spawnCrowForBuilding)
            spawnCrowForBuilding;

            MACRO_FUNCTION_RESOLVER(uint (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040A400,
                &BuildingsState::isFearFactorBuilding)
            isFearFactorBuilding;

            MACRO_FUNCTION_RESOLVER(uint (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040A4A0,
                &BuildingsState::isReligiousBuilding)
            isReligiousBuilding;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0040A4E0,
                &BuildingsState::copyPlayerDataArrayValues)
            copyPlayerDataArrayValues;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, BuildingTypeInt), false,
                Address::SHC_3BB0A8C1_0x0040A8A0, &BuildingsState::chooseProductionItemType)
            chooseProductionItemType;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, BuildingTypeInt), false,
                Address::SHC_3BB0A8C1_0x0040A950, &BuildingsState::getEmptyBuildingCount)
            getEmptyBuildingCount;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(PlayerID, BuildingTypeInt, int), false,
                Address::SHC_3BB0A8C1_0x0040A9B0, &BuildingsState::countBuildingsForPlayer)
            countBuildingsForPlayer;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(PlayerID, int), false, Address::SHC_3BB0A8C1_0x0040AA10,
                &BuildingsState::countFarms)
            countFarms;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, BuildingTypeInt), false,
                Address::SHC_3BB0A8C1_0x0040AA80, &BuildingsState::findFirstBuildingOfType)
            findFirstBuildingOfType;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, BuildingTypeInt), false,
                Address::SHC_3BB0A8C1_0x0040AAD0, &BuildingsState::findFirstBuildingIDForPlayerAndType)
            findFirstBuildingIDForPlayerAndType;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(PlayerID, BuildingTypeInt, int), false,
                Address::SHC_3BB0A8C1_0x0040AB30, &BuildingsState::findNextBuildingForPlayerAndType)
            findNextBuildingForPlayerAndType;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0040AB90,
                &BuildingsState::findNextOwnedBuildingOfType)
            findNextOwnedBuildingOfType;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0040AC00, &BuildingsState::findNextOwnedBuildingOfTypes)
            findNextOwnedBuildingOfTypes;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0040AC80, &BuildingsState::canNavigateToDefensiveBuilding)
            canNavigateToDefensiveBuilding;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0040ADB0, &BuildingsState::findNextReachableDefensiveBuilding)
            findNextReachableDefensiveBuilding;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, BuildingTypeInt), false,
                Address::SHC_3BB0A8C1_0x0040AEF0, &BuildingsState::pickARandomBuildingOfType)
            pickARandomBuildingOfType;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, BuildingTypeInt, BuildingTypeInt, BuildingTypeInt),
                false, Address::SHC_3BB0A8C1_0x0040AFB0, &BuildingsState::pickARandomBuildingIDOfTheseThreeTypes)
            pickARandomBuildingIDOfTheseThreeTypes;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040B090,
                &BuildingsState::pickARandomPositiveFearFactorBuilding)
            pickARandomPositiveFearFactorBuilding;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040B1A0,
                &BuildingsState::closestInnBuildingID)
            closestInnBuildingID;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040B260,
                &BuildingsState::recomputeAllFearFactors)
            recomputeAllFearFactors;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, BuildingTypeInt), false,
                Address::SHC_3BB0A8C1_0x0040B4E0, &BuildingsState::findBuildingOfTypeForPlayer)
            findBuildingOfTypeForPlayer;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0040B540,
                &BuildingsState::removeSiegeBuildings)
            removeSiegeBuildings;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, undefined4), false, Address::SHC_3BB0A8C1_0x0040B5D0,
                &BuildingsState::setBuildingInitialEntryTileTry)
            setBuildingInitialEntryTileTry;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040B660,
                &BuildingsState::prepareCampgroundCoords)
            prepareCampgroundCoords;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040B720,
                &BuildingsState::getBuildingOrientationFlag)
            getBuildingOrientationFlag;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040B7B0,
                &BuildingsState::getBuildingOrientationFlag2)
            getBuildingOrientationFlag2;

            MACRO_FUNCTION_RESOLVER(uint (BuildingsState::*)(uint, int), false, Address::SHC_3BB0A8C1_0x0040B840,
                &BuildingsState::isBuildingBlockingOrDestructible)
            isBuildingBlockingOrDestructible;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (BuildingsState::*)(uint), false, Address::SHC_3BB0A8C1_0x0040B900,
                &BuildingsState::getBuildingHasHealthProperty)
            getBuildingHasHealthProperty;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040B980,
                &BuildingsState::trueIfAnyUnitsOnBuildingAreFromHumanPlayer)
            trueIfAnyUnitsOnBuildingAreFromHumanPlayer;

            MACRO_FUNCTION_RESOLVER(undefined (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040BA10,
                &BuildingsState::setupBuildingEntrancesOffset)
            setupBuildingEntrancesOffset;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0040BC40, &BuildingsState::setupNextCandidateLocationComputeOffsets2)
            setupNextCandidateLocationComputeOffsets2;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (BuildingsState::*)(int, ResourceTypeInt), false,
                Address::SHC_3BB0A8C1_0x0040BE70, &BuildingsState::buildingHasSpaceForResource)
            buildingHasSpaceForResource;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(BuildingTypeInt, int, int), false,
                Address::SHC_3BB0A8C1_0x0040BEE0, &BuildingsState::raiseBuildingCountdownForType)
            raiseBuildingCountdownForType;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, ResourceTypeInt, int), false,
                Address::SHC_3BB0A8C1_0x0040BF40, &BuildingsState::canBuildingStoreTheAmount)
            canBuildingStoreTheAmount;

            MACRO_FUNCTION_RESOLVER(undefined (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040BFA0,
                &BuildingsState::getResourceCountThatCanBeDeposited)
            getResourceCountThatCanBeDeposited;

            MACRO_FUNCTION_RESOLVER(undefined (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040BFD0,
                &BuildingsState::getBuildingStorageTypeForResourceType)
            getBuildingStorageTypeForResourceType;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(ResourceTypeInt, int, int), false,
                Address::SHC_3BB0A8C1_0x0040BFE0, &BuildingsState::getStorageBuildingForResourceTypeAndAmount)
            getStorageBuildingForResourceTypeAndAmount;

            MACRO_FUNCTION_RESOLVER(uint (BuildingsState::*)(uint, undefined4, int, int), false,
                Address::SHC_3BB0A8C1_0x0040C060, &BuildingsState::ifArmoryReturnIDIfSpaceLeft)
            ifArmoryReturnIDIfSpaceLeft;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040C0D0,
                &BuildingsState::getArmoryFreeCapacity)
            getArmoryFreeCapacity;

            MACRO_FUNCTION_RESOLVER(uint (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040C130,
                &BuildingsState::computeResourceSumForBuilding)
            computeResourceSumForBuilding;

            MACRO_FUNCTION_RESOLVER(uint (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0040C1A0,
                &BuildingsState::hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters)
            hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int*), false, Address::SHC_3BB0A8C1_0x0040C1F0,
                &BuildingsState::getResourceSpace)
            getResourceSpace;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040C300,
                &BuildingsState::countPlayerResources)
            countPlayerResources;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040C4B0,
                &BuildingsState::recomputePlayerDataStocksBasedOnStorageBuildings)
            recomputePlayerDataStocksBasedOnStorageBuildings;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(CommandBuildingTypeInt, int*, int*), false,
                Address::SHC_3BB0A8C1_0x0040C5F0, &BuildingsState::getBuildingCost)
            getBuildingCost;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(UnitTypeInt, int*), false,
                Address::SHC_3BB0A8C1_0x0040C800, &BuildingsState::getPriceForDisbandedUnitType)
            getPriceForDisbandedUnitType;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(BuildingTypeInt, int*, int*), false,
                Address::SHC_3BB0A8C1_0x0040C9B0, &BuildingsState::resourceGainForKillingPitAndPitchDitch)
            resourceGainForKillingPitAndPitchDitch;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040C9F0,
                &BuildingsState::subtractPitchAndMoatFromStartingGoldInSiegeThatMode)
            subtractPitchAndMoatFromStartingGoldInSiegeThatMode;

            MACRO_FUNCTION_RESOLVER(uint (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040CAC0,
                &BuildingsState::hasEnoughGoldForMoat)
            hasEnoughGoldForMoat;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040CB10,
                &BuildingsState::getFarmThatHasTile)
            getFarmThatHasTile;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040CB90,
                &BuildingsState::hasFarmTileReadyToHarvest)
            hasFarmTileReadyToHarvest;

            MACRO_FUNCTION_RESOLVER(
                void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040CC30, &BuildingsState::growWheat)
            growWheat;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040CF20,
                &BuildingsState::updateWheatFieldCropGraphics)
            updateWheatFieldCropGraphics;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040D090,
                &BuildingsState::harmWheatFarmsOfPlayer)
            harmWheatFarmsOfPlayer;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040D120,
                &BuildingsState::computeBarracksParadePositions)
            computeBarracksParadePositions;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040D400,
                &BuildingsState::computeMercenaryParadePositions)
            computeMercenaryParadePositions;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, int, int), false,
                Address::SHC_3BB0A8C1_0x0040D6E0, &BuildingsState::getIsAnySpaceAvailableAtUnitRallyPoint)
            getIsAnySpaceAvailableAtUnitRallyPoint;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, int, int), false,
                Address::SHC_3BB0A8C1_0x0040D9C0, &BuildingsState::ifAIUnitReturnKeepLocation)
            ifAIUnitReturnKeepLocation;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040DC70,
                &BuildingsState::createEntityForAssemblyPointsForActiveTabType)
            createEntityForAssemblyPointsForActiveTabType;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040E040,
                &BuildingsState::computeEngineersCampgroundPositions)
            computeEngineersCampgroundPositions;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0040E120,
                &BuildingsState::someLaddermanFunction1)
            someLaddermanFunction1;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040E330,
                &BuildingsState::computeTunnelersCampgroundPositions)
            computeTunnelersCampgroundPositions;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0040E410,
                &BuildingsState::findTunnelerMusterTile)
            findTunnelerMusterTile;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0040E610,
                &BuildingsState::findCathedralMusterTile)
            findCathedralMusterTile;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040E740,
                &BuildingsState::setTileRefsForOilSmelter)
            setTileRefsForOilSmelter;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, int, int), false,
                Address::SHC_3BB0A8C1_0x0040E900, &BuildingsState::getWorkerSlotDestinationTile)
            getWorkerSlotDestinationTile;

            MACRO_FUNCTION_RESOLVER(uint (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040E990,
                &BuildingsState::getActiveEngineerWorker)
            getActiveEngineerWorker;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040EA00,
                &BuildingsState::setNewOnFarmDestination)
            setNewOnFarmDestination;

            MACRO_FUNCTION_RESOLVER(
                void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040EBF0, &BuildingsState::growHops)
            growHops;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040EDF0,
                &BuildingsState::updateFarmCropTileGraphics)
            updateFarmCropTileGraphics;

            MACRO_FUNCTION_RESOLVER(
                void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040EF40, &BuildingsState::harvestHopFarm)
            harvestHopFarm;

            MACRO_FUNCTION_RESOLVER(ushort* (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040EFD0,
                &BuildingsState::updateFarmFieldTileGraphics)
            updateFarmFieldTileGraphics;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040F040,
                &BuildingsState::setDairyFarmCheeseCounter)
            setDairyFarmCheeseCounter;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040F090,
                &BuildingsState::regrowAppleFarmOrchard)
            regrowAppleFarmOrchard;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040F1E0,
                &BuildingsState::setSignpostDataForBuildings)
            setSignpostDataForBuildings;

            MACRO_FUNCTION_RESOLVER(undefined (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040F240,
                &BuildingsState::destroySignpostData)
            destroySignpostData;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0040F360,
                &BuildingsState::setBuildingDisplayState)
            setBuildingDisplayState;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040F3D0,
                &BuildingsState::setBuildingToAppleFarm)
            setBuildingToAppleFarm;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040F3F0,
                &BuildingsState::setBuildingValueBasedOnBuildingStateBeing2)
            setBuildingValueBasedOnBuildingStateBeing2;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040F420,
                &BuildingsState::getBuildingFlag3)
            getBuildingFlag3;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040F440,
                &BuildingsState::getBuildingFlag1)
            getBuildingFlag1;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0040F460,
                &BuildingsState::determinePeasantSitPosition)
            determinePeasantSitPosition;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040F4F0,
                &BuildingsState::refreshAllBuildingDisplayLayers)
            refreshAllBuildingDisplayLayers;

            MACRO_FUNCTION_RESOLVER(
                undefined (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040F540, &BuildingsState::hasWorker)
            hasWorker;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0040F5C0,
                &BuildingsState::assignWorkerToBuilding)
            assignWorkerToBuilding;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040F620,
                &BuildingsState::updateNeededEmployeeCount)
            updateNeededEmployeeCount;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0040F700,
                &BuildingsState::getBuildingPriority)
            getBuildingPriority;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0040F750,
                &BuildingsState::updateAllBuildingsSnoozedState)
            updateAllBuildingsSnoozedState;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x0040F8A0,
                &BuildingsState::applySnoozedStateBasedOnPlayerData)
            applySnoozedStateBasedOnPlayerData;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x0040F9D0,
                &BuildingsState::processBuildingIDsNeedPeasantsQueue)
            processBuildingIDsNeedPeasantsQueue;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0040FC40,
                &BuildingsState::updatePlayerCourtUnits)
            updatePlayerCourtUnits;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x00410200,
                &BuildingsState::getRequiredEngineerCountForSiegeBuilding)
            getRequiredEngineerCountForSiegeBuilding;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x00410290,
                &BuildingsState::updateVisuallyActiveState)
            updateVisuallyActiveState;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x00410320,
                &BuildingsState::updateRepairCostAndReturnIfDamaged)
            updateRepairCostAndReturnIfDamaged;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00410440,
                &BuildingsState::canUnitReachBuilding)
            canUnitReachBuilding;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004105F0,
                &BuildingsState::canUnitReachTileNeighbor)
            canUnitReachTileNeighbor;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004106D0,
                &BuildingsState::processDamageToUnitsOnBuilding)
            processDamageToUnitsOnBuilding;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, undefined4), false, Address::SHC_3BB0A8C1_0x00410800,
                &BuildingsState::spawnBuildingFirePops)
            spawnBuildingFirePops;

            MACRO_FUNCTION_RESOLVER(undefined (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x00410920,
                &BuildingsState::getBuildingFireClass)
            getBuildingFireClass;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x004109F0,
                &BuildingsState::extinguishBuildingFire)
            extinguishBuildingFire;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x00410B10,
                &BuildingsState::findNearestReachableTeamBuilding)
            findNearestReachableTeamBuilding;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x00410C40,
                &BuildingsState::playerHasBurningBuilding)
            playerHasBurningBuilding;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x004173D0,
                &BuildingsState::revalidateBuildingOccupants)
            revalidateBuildingOccupants;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00417450,
                &BuildingsState::removeOccupantFromBuilding)
            removeOccupantFromBuilding;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x00418EC0,
                &BuildingsState::requiredEngineersCount)
            requiredEngineersCount;

            MACRO_FUNCTION_RESOLVER(
                void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x00419780, &BuildingsState::initBuildingCosts)
            initBuildingCosts;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x004197C0,
                &BuildingsState::updatePathLinkageLayerForAllBuildings)
            updatePathLinkageLayerForAllBuildings;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x00419800,
                &BuildingsState::processDamageFromKillingPit)
            processDamageFromKillingPit;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x00419960,
                &BuildingsState::unkUpdatePathLinkageTileMap)
            unkUpdatePathLinkageTileMap;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x00419A30,
                &BuildingsState::initPlayerGatehousePathLinks)
            initPlayerGatehousePathLinks;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x00419AC0,
                &BuildingsState::applyWallMoatTilesToMap)
            applyWallMoatTilesToMap;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x00419BE0,
                &BuildingsState::markKeepTilesInLogicLayer)
            markKeepTilesInLogicLayer;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x00419C70,
                &BuildingsState::updatePathLinkageForGatesKeepsSiegeTowers)
            updatePathLinkageForGatesKeepsSiegeTowers;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x00419D70,
                &BuildingsState::updateEnemyBuildings)
            updateEnemyBuildings;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00419EB0, &BuildingsState::AIfindBuildingToAttack)
            AIfindBuildingToAttack;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00419FA0, &BuildingsState::findNearestEnemyBuildingInRadius)
            findNearestEnemyBuildingInRadius;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0041A7A0,
                &BuildingsState::destroyBuilding)
            destroyBuilding;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0041A860,
                &BuildingsState::destroyBuildings)
            destroyBuildings;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0041A8D0,
                &BuildingsState::swapOwnersOfCastle)
            swapOwnersOfCastle;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, int, BOOLEnum), false,
                Address::SHC_3BB0A8C1_0x0041ADE0, &BuildingsState::determineBuildingEntranceFromKeepArea)
            determineBuildingEntranceFromKeepArea;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0041B2B0, &BuildingsState::determineBuildingEntranceFromCustomArea)
            determineBuildingEntranceFromCustomArea;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0041B7C0,
                &BuildingsState::updateBuildingBlockedAccessTiles)
            updateBuildingBlockedAccessTiles;

            MACRO_FUNCTION_RESOLVER(
                void (BuildingsState::*)(undefined4, int, int, int, int, int, CommandBuildingTypeInt), false,
                Address::SHC_3BB0A8C1_0x0041B890, &BuildingsState::findQuarryPileLocation)
            findQuarryPileLocation;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (BuildingsState::*)(int, int, int, int, BuildingTypeInt), false,
                Address::SHC_3BB0A8C1_0x0041B940, &BuildingsState::hasBuildingAsNeighbour)
            hasBuildingAsNeighbour;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(undefined4, int, int, int, BuildingTypeInt, int), false,
                Address::SHC_3BB0A8C1_0x0041BA00, &BuildingsState::findParticularBuilding)
            findParticularBuilding;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0041BAB0,
                &BuildingsState::getBuildingEntranceAreaID)
            getBuildingEntranceAreaID;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, int, ResourceTypeInt, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0041BB30, &BuildingsState::addResourceToStockpile)
            addResourceToStockpile;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(ResourceTypeInt, int, int), false,
                Address::SHC_3BB0A8C1_0x0041BC10, &BuildingsState::addResourceToGranary)
            addResourceToGranary;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(ResourceTypeInt, int, int), false,
                Address::SHC_3BB0A8C1_0x0041BCA0, &BuildingsState::addResourceToArmory)
            addResourceToArmory;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, ResourceTypeInt, int, int), false,
                Address::SHC_3BB0A8C1_0x0041BD70, &BuildingsState::processResourceLoss)
            processResourceLoss;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0041BF50,
                &BuildingsState::subtractResourcesStoredInBuilding)
            subtractResourcesStoredInBuilding;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, BuildingTypeInt, int), false,
                Address::SHC_3BB0A8C1_0x0041BFD0, &BuildingsState::processPlacementResourceLossForBuildingType)
            processPlacementResourceLossForBuildingType;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0041C190, &BuildingsState::processWallBuildingLoss)
            processWallBuildingLoss;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0041C240,
                &BuildingsState::removeFoodResourcesByPercent)
            removeFoodResourcesByPercent;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (BuildingsState::*)(int, ResourceTypeInt, int), false,
                Address::SHC_3BB0A8C1_0x0041C310, &BuildingsState::processResourceGain)
            processResourceGain;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, BOOLEnum, BOOLEnum), false,
                Address::SHC_3BB0A8C1_0x0041C570, &BuildingsState::ApplyGateOrDrawbridgeOpenCloseChange)
            ApplyGateOrDrawbridgeOpenCloseChange;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x0041C6F0,
                &BuildingsState::sortBuildingIDsNeedPeasantsQueue)
            sortBuildingIDsNeedPeasantsQueue;

            MACRO_FUNCTION_RESOLVER(undefined4 (BuildingsState::*)(int, int, int), false,
                Address::SHC_3BB0A8C1_0x0041C810, &BuildingsState::lightUpBuilding)
            lightUpBuilding;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(PackagedFileMagicNumInt, PackagedFileMagicNumInt), false,
                Address::SHC_3BB0A8C1_0x00420BF0, &BuildingsState::migrateBuildingsForMapVersion)
            migrateBuildingsForMapVersion;

            MACRO_FUNCTION_RESOLVER(
                int (BuildingsState::*)(int, uint, uint, undefined4, BuildingTypeInt, uint, int, int), false,
                Address::SHC_3BB0A8C1_0x00420D20, &BuildingsState::setupBuildingData)
            setupBuildingData;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(uint), false, Address::SHC_3BB0A8C1_0x00421890,
                &BuildingsState::deleteBuilding)
            deleteBuilding;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(uint), false, Address::SHC_3BB0A8C1_0x00421990,
                &BuildingsState::someBuildingDestroyFunction)
            someBuildingDestroyFunction;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00421A40,
                &BuildingsState::buildingIsAccessible)
            buildingIsAccessible;

            MACRO_FUNCTION_RESOLVER(char (BuildingsState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00421BE0, &BuildingsState::checkBuildingAccessFromArea)
            checkBuildingAccessFromArea;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00421D70,
                &BuildingsState::giveBackResourceForDestroyedBuilding)
            giveBackResourceForDestroyedBuilding;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(ResourceTypeInt, int, int), false,
                Address::SHC_3BB0A8C1_0x00422230, &BuildingsState::getBuildingThatCanStoreThisResource)
            getBuildingThatCanStoreThisResource;

            MACRO_FUNCTION_RESOLVER(uint (BuildingsState::*)(uint, undefined4, int, int), false,
                Address::SHC_3BB0A8C1_0x00422370, &BuildingsState::getArmoryWithSpaceLeft)
            getArmoryWithSpaceLeft;

            MACRO_FUNCTION_RESOLVER(int (BuildingsState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00422400, &BuildingsState::findQuarryPileThatIsCloseAndHasMostStone)
            findQuarryPileThatIsCloseAndHasMostStone;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x004224F0,
                &BuildingsState::UpdateGateDrawBridgeOpenCloseLogic)
            UpdateGateDrawBridgeOpenCloseLogic;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x00422B80,
                &BuildingsState::checkBuildingsNeedPeasants)
            checkBuildingsNeedPeasants;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00422C60,
                &BuildingsState::igniteRandomPlayerBuildings)
            igniteRandomPlayerBuildings;

            MACRO_FUNCTION_RESOLVER(
                void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x00422E20, &BuildingsState::updateBuildings)
            updateBuildings;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(), false, Address::SHC_3BB0A8C1_0x00424220,
                &BuildingsState::recomputeAllBuildingAccessibility)
            recomputeAllBuildingAccessibility;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(int), false, Address::SHC_3BB0A8C1_0x00424270,
                &BuildingsState::updateHeatmapBasedOnBuildingAccessibility)
            updateHeatmapBasedOnBuildingAccessibility;

            MACRO_FUNCTION_RESOLVER(void (BuildingsState::*)(PackagedFileMagicNumInt, PackagedFileMagicNumInt), false,
                Address::SHC_3BB0A8C1_0x00424310, &BuildingsState::recomputeBuildingAccessibilityOnLoad)
            recomputeBuildingAccessibilityOnLoad;

        } // namespace BuildingsState_Func
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
