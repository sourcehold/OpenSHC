/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/BuildingsState.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingCostStruct.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Commands::CommandBuildingTypeInt;
        using OpenSHC::Game::Player::PlayerID;
        using OpenSHC::Game::Resources::ResourceTypeInt;
        using OpenSHC::IO::PackagedFileMagicNumInt;
        using OpenSHC::Map::Buildings::Building;
        using OpenSHC::Map::Buildings::BuildingCostStruct;
        using OpenSHC::Map::Buildings::BuildingTypeInt;
        using OpenSHC::Map::Units::UnitTypeInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x0018E088
        class BuildingsState {
        public:
            int structCount; // 0x00000000 length: 4
            undefined4 field1_0x4; // 0x00000004 length: 4
            undefined4 maxBuildingsCount; // 0x00000008 length: 4
            undefined4 dwBuildingCapacityRemaining; // 0x0000000C length: 4
            undefined4 dwBuildingSlowUpdateCountdown; // 0x00000010 length: 4
            Building buildings[2000]; // 0x00000014 length: 1624000
            BuildingCostStruct buildingCosts[110]; // 0x0018C7D4 length: 2200
            undefined4 dwPathLinkageNeedsUpdate; // 0x0018D06C length: 4
            undefined4 counter; // 0x0018D070 length: 4
            undefined2 DAT_BuildingIDsNeedPeasantsQueue[2000]; // 0x0018D074 length: 4000
            undefined4 DAT_CountOfBuildingsNeedPeasants; // 0x0018E014 length: 4
            int campfireSpotX; // 0x0018E018 length: 4
            int campfireSpotY; // 0x0018E01C length: 4
            int campfireSpotOrientation; // 0x0018E020 length: 4
            undefined4 dwFarmCropGraphicsFlag; // 0x0018E024 length: 4
            undefined4 DAT_TempXOffset; // 0x0018E028 length: 4
            undefined4 DAT_TempYOffset; // 0x0018E02C length: 4
            undefined4 farmerDestinationTile; // 0x0018E030 length: 4
            int hopFarmerDestinationOffsetX; // 0x0018E034 length: 4
            int hopFarmerDestinationOffsetY; // 0x0018E038 length: 4
            undefined4 menuSelectedBuildingID; // 0x0018E03C length: 4
            undefined4 newSelectedBuildingID; // 0x0018E040 length: 4
            undefined4 menuSelectedUnitID; // 0x0018E044 length: 4
            undefined4 newSelectedUnitID; // 0x0018E048 length: 4
            undefined4 dwBuildingHelpTextActive; // 0x0018E04C length: 4
            undefined4 dwBuildingHelpTextID; // 0x0018E050 length: 4
            char* DAT_CurrentlyPlayingBuildingBik; // 0x0018E054 length: 4
            BOOLEnum DAT_IsBuildingOrPeasantBinkPlaying; // 0x0018E058 length: 4
            int nStatusMenuBuildingID; // 0x0018E05C length: 4
            undefined4 dwStatusMenuBuildingUID; // 0x0018E060 length: 4
            BOOLEnum isFirstTickInLoop; // 0x0018E064 length: 4
            undefined4 DAT_DraggedTileCountVerified; // 0x0018E068 length: 4
            int INT_SelectedBuildingStoneWoodCost; // 0x0018E06C length: 4
            int INT_SelectedBuildingStoneRepairCost; // 0x0018E070 length: 4
            undefined4 dwTowerUpdateFlag; // 0x0018E074 length: 4
            int siegeEngineCreationRelated01; // 0x0018E078 length: 4
            undefined4 unitID; // 0x0018E07C length: 4
            undefined4 dwBuildingsStateInitTimeMs; // 0x0018E080 length: 4
            int unused01; // 0x0018E084 length: 4

        private:
            BuildingsState(BuildingsState const&);
            void operator=(BuildingsState const&);

        public:
            BuildingsState() {};
            ~BuildingsState() {};

            // Constructor
            BuildingsState* Constructor_BuildingsState();

            undefined4 someArrayIndexingOnBuildingField0x120(int buildingID, int param_2, ResourceTypeInt param_3);

            undefined convertCommandBuildingTypeToBuildingType();

            CommandBuildingTypeInt convertBuildingTypeToCommandBuildingType(BuildingTypeInt buildingType);

            undefined getBuildingHeightForBuildingID();

            undefined4 GetBuildingHeightForBuildingID_type2(int buildingID);

            int getSpriteID(CommandBuildingTypeInt commandBuildingType);

            int getSpriteID2(CommandBuildingTypeInt commandBuildingType);

            void clearBuildings();

            void displayPopularityAndGoldPopups(int buildingID, int param_2, int param_3, undefined4 param_4);

            int spawnCrowForBuilding(int buildingID);

            uint isFearFactorBuilding(int buildingID);

            uint isReligiousBuilding(int buildingID);

            void copyPlayerDataArrayValues(int playerID, int playerID2);

            int chooseProductionItemType(int playerID, BuildingTypeInt buildingType);

            int getEmptyBuildingCount(int playerID, BuildingTypeInt buildingType);

            int countBuildingsForPlayer(PlayerID playerID, BuildingTypeInt buildingType, int includeBool);

            int countFarms(PlayerID playerID, int param_2);

            int findFirstBuildingOfType(int playerID, BuildingTypeInt buildingType);

            int findFirstBuildingIDForPlayerAndType(int playerID, BuildingTypeInt buildingType);

            int findNextBuildingForPlayerAndType(PlayerID playerID, BuildingTypeInt buildingType, int buildingID);

            int findNextOwnedBuildingOfType(int param_1, int param_2, int param_3);

            int findNextOwnedBuildingOfTypes(int param_1, int param_2, int param_3, int param_4, int param_5);

            int canNavigateToDefensiveBuilding(
                int playerID, int buildingXPosition, int buildingYPosition, int buildingID);

            int findNextReachableDefensiveBuilding(int param_1, int param_2, int param_3, int param_4);

            int pickARandomBuildingOfType(int playerID, BuildingTypeInt buildingType);

            int pickARandomBuildingIDOfTheseThreeTypes(int playerID, BuildingTypeInt buildingType1,
                BuildingTypeInt buildingType2, BuildingTypeInt buildingType3);

            int pickARandomPositiveFearFactorBuilding(int playerID);

            int closestInnBuildingID(int unitID);

            void recomputeAllFearFactors();

            undefined4 findBuildingOfTypeForPlayer(int playerID, BuildingTypeInt buildingType);

            void removeSiegeBuildings(int attackWave, int playerID);

            void setBuildingInitialEntryTileTry(int buildingID, undefined4 param_2);

            undefined4 prepareCampgroundCoords(int playerID);

            undefined4 getBuildingOrientationFlag(int buildingID);

            undefined4 getBuildingOrientationFlag2(int buildingID);

            uint isBuildingBlockingOrDestructible(uint param_1, int param_2);

            BOOLEnum getBuildingHasHealthProperty(uint buildingID);

            BOOLEnum trueIfAnyUnitsOnBuildingAreFromHumanPlayer(int buildingID);

            undefined setupBuildingEntrancesOffset();

            void setupNextCandidateLocationComputeOffsets2(int size, int nudge, int try_, int offset);

            BOOLEnum buildingHasSpaceForResource(int buildingID, ResourceTypeInt resourceType);

            void raiseBuildingCountdownForType(BuildingTypeInt buildingType, int someCountdown, int playerID);

            int canBuildingStoreTheAmount(int buildingID, ResourceTypeInt resourceType, int storageLimit);

            undefined getResourceCountThatCanBeDeposited();

            undefined getBuildingStorageTypeForResourceType();

            int getStorageBuildingForResourceTypeAndAmount(ResourceTypeInt resourceType, int amount, int owner);

            uint ifArmoryReturnIDIfSpaceLeft(uint buildingID, undefined4 resourceID, int playerID, int resourceCount);

            int getArmoryFreeCapacity(int buildingID);

            uint computeResourceSumForBuilding(int buildingID);

            uint hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters(int playerID, int param_2);

            int getResourceSpace(int param_1, int* resourceType);

            void countPlayerResources(int playerID);

            void recomputePlayerDataStocksBasedOnStorageBuildings();

            void getBuildingCost(CommandBuildingTypeInt commandBuildingType, int* pStone, int* pGold);

            void getPriceForDisbandedUnitType(UnitTypeInt unitType, int* outPrice);

            void resourceGainForKillingPitAndPitchDitch(
                BuildingTypeInt buildingType, int* ptrRequiredStone, int* ptrRequiredGold);

            void subtractPitchAndMoatFromStartingGoldInSiegeThatMode();

            uint hasEnoughGoldForMoat();

            int getFarmThatHasTile(int tile);

            undefined4 hasFarmTileReadyToHarvest(int param_1);

            void growWheat(int buildingID);

            void updateWheatFieldCropGraphics(int buildingID);

            void harmWheatFarmsOfPlayer(int playerID);

            void computeBarracksParadePositions(int buildingID);

            void computeMercenaryParadePositions(int playerID);

            undefined4 getIsAnySpaceAvailableAtUnitRallyPoint(int playerID, int value0to6, int unitID);

            undefined4 ifAIUnitReturnKeepLocation(int playerID, int param_2, int unitID);

            void createEntityForAssemblyPointsForActiveTabType();

            void computeEngineersCampgroundPositions(int param_1);

            int someLaddermanFunction1(int playerIndex, int param_2);

            void computeTunnelersCampgroundPositions(int param_1);

            undefined4 findTunnelerMusterTile(int param_1, int param_2);

            undefined4 findCathedralMusterTile(int param_1, int param_2);

            void setTileRefsForOilSmelter(int buildingID);

            undefined4 getWorkerSlotDestinationTile(int param_1, int param_2, int param_3);

            uint getActiveEngineerWorker(int buildingID);

            undefined4 setNewOnFarmDestination(int buildingID);

            void growHops(int buildingID);

            void updateFarmCropTileGraphics(int buildingID);

            void harvestHopFarm(int param_1);

            ushort* updateFarmFieldTileGraphics(int param_1);

            void setDairyFarmCheeseCounter(int param_1);

            void regrowAppleFarmOrchard(int param_1);

            void setSignpostDataForBuildings();

            undefined destroySignpostData();

            int setBuildingDisplayState(int param_1, int param_2);

            void setBuildingToAppleFarm(int buildingID);

            void setBuildingValueBasedOnBuildingStateBeing2();

            int getBuildingFlag3(int param_1);

            int getBuildingFlag1(int param_1);

            undefined4 determinePeasantSitPosition(int campfireID, int availablePeasants);

            void refreshAllBuildingDisplayLayers();

            undefined hasWorker();

            void assignWorkerToBuilding(int buildingID, int unitID, int workerIndex);

            void updateNeededEmployeeCount(int buildingID);

            int getBuildingPriority(int buildingType, int hasBurningBuilding);

            void updateAllBuildingsSnoozedState(int playerID, int buildingType);

            void applySnoozedStateBasedOnPlayerData();

            void processBuildingIDsNeedPeasantsQueue(undefined4 playerID);

            void updatePlayerCourtUnits(int playerID);

            undefined4 getRequiredEngineerCountForSiegeBuilding(int buildingID);

            void updateVisuallyActiveState(int buildingID);

            BOOLEnum updateRepairCostAndReturnIfDamaged(int buildingIndex);

            undefined4 canUnitReachBuilding(int param_1, int param_2);

            undefined4 canUnitReachTileNeighbor(int param_1, int param_2);

            void processDamageToUnitsOnBuilding(int buildingID, int damageBonus);

            void spawnBuildingFirePops(int buildingID, undefined4 playerID);

            undefined getBuildingFireClass();

            void extinguishBuildingFire(int buildingID);

            int findNearestReachableTeamBuilding(int param_1);

            undefined4 playerHasBurningBuilding(int playerID);

            void revalidateBuildingOccupants(int buildingID);

            void removeOccupantFromBuilding(int buildingID, int unitID);

            int requiredEngineersCount(int buildingID);

            void initBuildingCosts();

            void updatePathLinkageLayerForAllBuildings();

            void processDamageFromKillingPit(int unitID);

            void unkUpdatePathLinkageTileMap(int param_1);

            void initPlayerGatehousePathLinks(int param_1);

            void applyWallMoatTilesToMap();

            void markKeepTilesInLogicLayer();

            void updatePathLinkageForGatesKeepsSiegeTowers();

            void updateEnemyBuildings(int playerID);

            int AIfindBuildingToAttack(int param_1, int param_2, int param_3, int param_4);

            int findNearestEnemyBuildingInRadius(int param_1, int param_2, int param_3, int param_4);

            void destroyBuilding(int buildingID);

            void destroyBuildings(int playerID);

            void swapOwnersOfCastle(int param_1, int param_2);

            undefined4 determineBuildingEntranceFromKeepArea(int buildingID, int workerIndexPlus1, BOOLEnum flag);

            undefined4 determineBuildingEntranceFromCustomArea(int buildingID, int param_2, int param_3, int x, int y);

            void updateBuildingBlockedAccessTiles(int param_1);

            void findQuarryPileLocation(undefined4 playerID, int x, int y, int buildingSize, int pileSize, int tryUnk,
                CommandBuildingTypeInt commandBuildingType);

            BOOLEnum hasBuildingAsNeighbour(int playerID, int x, int y, int size, BuildingTypeInt type);

            int findParticularBuilding(
                undefined4 param_1, int x, int y, int buildingSize, BuildingTypeInt buildingType, int buildingID);

            int getBuildingEntranceAreaID(int x, int y, int buildingSize);

            undefined4 addResourceToStockpile(int buildingID, int buildingUID, ResourceTypeInt resourceType, int amount,
                int maxCapacity, int recomputeResources);

            void addResourceToGranary(ResourceTypeInt resourceType, int playerID, int amount);

            void addResourceToArmory(ResourceTypeInt resourceType, int playerID, int amount);

            void processResourceLoss(int playerID, ResourceTypeInt resourceType, int amount, int param_4);

            void subtractResourcesStoredInBuilding(int buildingID);

            void processPlacementResourceLossForBuildingType(int playerID, BuildingTypeInt buildingType, int param_3);

            void processWallBuildingLoss(int playerID, int highCount, int lowCount, int zero);

            void removeFoodResourcesByPercent(int param_1, int param_2);

            BOOLEnum processResourceGain(int playerID, ResourceTypeInt resourceType, int amount);

            void ApplyGateOrDrawbridgeOpenCloseChange(int buildingID, BOOLEnum param_2, BOOLEnum param_3);

            void sortBuildingIDsNeedPeasantsQueue(int playerID);

            undefined4 lightUpBuilding(int buildingID, int burnerPlayerID, int spareGrounds);

            void migrateBuildingsForMapVersion(
                PackagedFileMagicNumInt receivedMapVersion, PackagedFileMagicNumInt packagerMapVersion);

            int setupBuildingData(int playerID, uint x, uint y, undefined4 averageHeight, BuildingTypeInt buildingType,
                uint width, int playerID_dup, int variationIndex);

            void deleteBuilding(uint buildingID);

            void someBuildingDestroyFunction(uint param_1);

            int buildingIsAccessible(int buildingID, int amountUnk);

            char checkBuildingAccessFromArea(int buildingID, int param_2, int x, int y);

            int giveBackResourceForDestroyedBuilding(int buildingID__negResourceType, int playerID, int param_3);

            int getBuildingThatCanStoreThisResource(ResourceTypeInt resourceType, int amount, int playerID);

            uint getArmoryWithSpaceLeft(
                uint targetBuildingID, undefined4 producedItemTypeUnk, int playerID, int resourceToDeposit);

            int findQuarryPileThatIsCloseAndHasMostStone(int playerID, int x, int y, int unitID);

            void UpdateGateDrawBridgeOpenCloseLogic();

            void checkBuildingsNeedPeasants(int playerID);

            void igniteRandomPlayerBuildings(int param_1, int param_2);

            void updateBuildings();

            void recomputeAllBuildingAccessibility();

            void updateHeatmapBasedOnBuildingAccessibility(int playerID);

            void recomputeBuildingAccessibilityOnLoad(
                PackagedFileMagicNumInt receivedMapVersion, PackagedFileMagicNumInt packagerMapVersion);
        };

        static_assert_cpp98_obj(sizeof(BuildingsState) == 1630344, BuildingsState);

#pragma pack(pop)

    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
