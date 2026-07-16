/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/BuildingsState.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingType.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingCostStruct.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Commands::CommandBuildingType;
        using OpenSHC::Game::Player::PlayerID;
        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::IO::PackagedFileMagicNum;
        using OpenSHC::Map::Buildings::Building;
        using OpenSHC::Map::Buildings::BuildingCostStruct;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x0018E088
        class BuildingsState {
        public:
            int structCount; // 0x00000000 length: 4
            undefined4 field1_0x4; // 0x00000004 length: 4
            undefined4 maxBuildingsCount; // 0x00000008 length: 4
            undefined4 unknownCountdown01; // 0x0000000C length: 4
            undefined4 field4_0x10; // 0x00000010 length: 4
            Building buildings[2000]; // 0x00000014 length: 1624000
            BuildingCostStruct buildingCosts[110]; // 0x0018C7D4 length: 2200
            undefined4 pathLinkageKeepWasUpdatedUnk; // 0x0018D06C length: 4
            undefined4 counter; // 0x0018D070 length: 4
            undefined2 DAT_BuildingIDsNeedPeasantsQueue[2000]; // 0x0018D074 length: 4000
            undefined4 DAT_CountOfBuildingsNeedPeasants; // 0x0018E014 length: 4
            int campfireSpotX; // 0x0018E018 length: 4
            int campfireSpotY; // 0x0018E01C length: 4
            int campfireSpotOrientation; // 0x0018E020 length: 4
            undefined4 field14_0x18e024; // 0x0018E024 length: 4
            undefined4 DAT_TempXOffset; // 0x0018E028 length: 4
            undefined4 DAT_TempYOffset; // 0x0018E02C length: 4
            undefined4 farmerDestinationTile; // 0x0018E030 length: 4
            int hopFarmerDestinationOffsetX; // 0x0018E034 length: 4
            int hopFarmerDestinationOffsetY; // 0x0018E038 length: 4
            undefined4 menuSelectedBuildingID; // 0x0018E03C length: 4
            undefined4 newSelectedBuildingID; // 0x0018E040 length: 4
            undefined4 menuSelectedUnitID; // 0x0018E044 length: 4
            undefined4 newSelectedUnitID; // 0x0018E048 length: 4
            undefined4 field24_0x18e04c; // 0x0018E04C length: 4
            undefined4 field25_0x18e050; // 0x0018E050 length: 4
            char* DAT_CurrentlyPlayingBuildingBik; // 0x0018E054 length: 4
            BOOLEnum DAT_IsBuildingOrPeasantBinkPlaying; // 0x0018E058 length: 4
            int field28_0x18e05c; // 0x0018E05C length: 4
            undefined4 field29_0x18e060; // 0x0018E060 length: 4
            BOOLEnum isFirstTickInLoop; // 0x0018E064 length: 4
            undefined4 DAT_DraggedTileCountVerified; // 0x0018E068 length: 4
            int INT_SelectedBuildingStoneWoodCost; // 0x0018E06C length: 4
            int INT_SelectedBuildingStoneRepairCost; // 0x0018E070 length: 4
            undefined4 field34_0x18e074; // 0x0018E074 length: 4
            int siegeEngineCreationRelated01; // 0x0018E078 length: 4
            undefined4 unitID; // 0x0018E07C length: 4
            undefined4 field37_0x18e080; // 0x0018E080 length: 4
            int unused01; // 0x0018E084 length: 4

        private:
            BuildingsState(BuildingsState const&);
            void operator=(BuildingsState const&);

        public:
            BuildingsState() {};
            ~BuildingsState() {};

            // Constructor
            BuildingsState* constructBuildingsState();

            undefined4 getBuildingResourceAmountByUid(int buildingID, int param_2, ResourceType param_3);

            BuildingType convertCommandBuildingTypeToBuildingType(CommandBuildingType commandBuildingType);

            CommandBuildingType convertBuildingTypeToCommandBuildingType(BuildingType buildingType);

            undefined4 getBuildingHeightForBuildingID(int buildingID);

            undefined4 getBuildingHeightForBuildingID2(int buildingID);

            int getSpriteID(CommandBuildingType commandBuildingType);

            int getSpriteID2(CommandBuildingType commandBuildingType);

            void clearBuildings();

            void displayPopularityAndGoldPopups(int buildingID, int param_2, int param_3, undefined4 param_4);

            int spawnCrowForBuilding(int buildingID);

            uint isFearFactorBuilding(int buildingID);

            uint isReligiousBuilding(int buildingID);

            void copyPlayerDataArrayValues(int playerID, int playerID2);

            int chooseProductionItemType(int playerID, BuildingType buildingType);

            int getEmptyBuildingCount(int playerID, BuildingType buildingType);

            int countBuildingsForPlayer(PlayerID playerID, BuildingType buildingType, int includeBool);

            int countFarms(PlayerID playerID, int param_2);

            int findFirstBuildingOfType(int playerID, BuildingType buildingType);

            int findFirstBuildingIDForPlayerAndType(int playerID, BuildingType buildingType);

            int findNextBuildingForPlayerAndType(PlayerID playerID, BuildingType buildingType, int buildingID);

            int findNextBuildingIDForOwnerAndType(int param_1, int param_2, int param_3);

            int findNextBuildingForPlayerAndOneOfThreeTypes(
                int param_1, int param_2, int param_3, int param_4, int param_5);

            int canNavigateToDefensiveBuilding(
                int playerID, int buildingXPosition, int buildingYPosition, int buildingID);

            int findNextReachableDefensiveBuildingForPlayer(int param_1, int param_2, int param_3, int param_4);

            int pickARandomBuildingOfType(int playerID, BuildingType buildingType);

            int pickARandomBuildingIDOfTheseThreeTypes(
                int playerID, BuildingType buildingType1, BuildingType buildingType2, BuildingType buildingType3);

            int pickARandomPositiveFearFactorBuilding(int playerID);

            int findClosestInnBuildingID(int unitID);

            void recomputeAllFearFactors();

            undefined4 findBuildingOfTypeForPlayer(int playerID, BuildingType buildingType);

            void removeSiegeBuildings(int attackWave, int playerID);

            void setBuildingInitialEntryTileTry(int buildingID, undefined4 param_2);

            undefined4 prepareCampgroundCoords(int playerID);

            undefined4 hasBuildingEntranceFlagForOrientation(int buildingID);

            undefined4 hasBuildingExitFlagForOrientation(int buildingID);

            uint isBuildingPathBlockerOrDamageable(uint param_1, int param_2);

            BOOLEnum getBuildingHasHealthProperty(uint buildingID);

            BOOLEnum hasHumanPlayerUnitsOnBuilding(int buildingID);

            void setupBuildingEntrancesOffset(int buildingSize, int nudge, int try_, int offset);

            void setupNextCandidateLocationComputeOffsets2(int size, int nudge, int try_, int offset);

            BOOLEnum buildingHasSpaceForResource(int buildingID, ResourceType resourceType);

            void extendResourceCountdownForPlayerBuildingsOfType(
                BuildingType buildingType, int someCountdown, int playerID);

            int canBuildingStoreTheAmount(int buildingID, ResourceType resourceType, int storageLimit);

            int getResourceCountThatCanBeDeposited(int buildingID, undefined4 resourceType, int storageLimit);

            BuildingType getBuildingStorageTypeForResourceType(ResourceType resourceType);

            int getStorageBuildingForResourceTypeAndAmount(ResourceType resourceType, int amount, int owner);

            uint getArmoryIDIfSpaceLeft(uint buildingID, undefined4 resourceID, int playerID, int resourceCount);

            int computeArmoryRemainingCapacity(int buildingID);

            uint computeResourceSumForBuilding(int buildingID);

            uint hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters(int playerID, int param_2);

            int getResourceSpace(int param_1, int* resourceType);

            void countPlayerResources(int playerID);

            void recomputePlayerDataStocksBasedOnStorageBuildings();

            void getBuildingCost(CommandBuildingType commandBuildingType, int* pStone, int* pGold);

            void getPriceForDisbandedUnitType(UnitType unitType, int* outPrice);

            void resourceGainForKillingPitAndPitchDitch(
                BuildingType buildingType, int* ptrRequiredStone, int* ptrRequiredGold);

            void subtractPitchAndMoatFromStartingGoldInSiegeThatMode();

            uint hasEnoughGoldForMoat();

            int getFarmThatHasTile(int tile);

            undefined4 isFarmTileReadyForWheatStageChange(int param_1);

            void growWheat(int buildingID);

            void updateWheatFieldTileGraphics(int buildingID);

            void harmWheatFarmsOfPlayer(int playerID);

            void setupBarracksCampgroundPositions(int buildingID);

            void setupMercenaryPostCampgroundPositions(int playerID);

            undefined4 isSpaceAvailableAtUnitRallyPoint(int playerID, int value0to6, int unitID);

            undefined4 getKeepLocationForAIUnit(int playerID, int param_2, int unitID);

            void createEntityForAssemblyPointsForActiveTabType();

            void setupEngineersGuildParagroundPositions(int playerID);

            int findFreeEngineerAssemblyTile(int playerIndex, int param_2);

            void setupTunnelersGuildCampgroundPositions(int param_1);

            undefined4 findFreeTunnelerAssemblyTile(int param_1, int param_2);

            undefined4 findFreeCathedralAssemblyTile(int param_1, int param_2);

            void setTileRefsForOilSmelter(int buildingID);

            undefined4 isEngineerNotAtAssignedWorkTile(int param_1, int param_2, int param_3);

            uint getActiveEngineerForBuilding(int buildingID);

            undefined4 setNewOnFarmDestination(int buildingID);

            void growHops(int buildingID);

            void updateHopsFieldTileGraphics(int buildingID);

            void harmHopFarmsOfPlayer(int param_1);

            ushort* updateBuildingAreaTileGraphics(int param_1);

            void setDairyFarmCheeseCounter(int param_1);

            void harmAppleFarmTreesOfPlayer(int param_1);

            void setSignpostDataForBuildings();

            void destroySignpostData(int buildingID);

            int updateBuildingSignpostCounter(int param_1, int param_2);

            void setBuildingToAppleFarm(int buildingID);

            void clearBuildingValueWhenStateIsTwo();

            int getBuildingFlag3(int param_1);

            int getBuildingFlag1(int param_1);

            undefined4 determinePeasantSitPosition(int campfireID, int availablePeasants);

            void refreshAllBuildingTileDisplays();

            BOOLEnum hasWorker(int buildingID, int workerSlot);

            void assignWorkerToBuilding(int buildingID, int unitID, int workerIndex);

            void updateNeededEmployeeCount(int buildingID);

            int getBuildingPriority(int buildingType, int hasBurningBuilding);

            void updateAllBuildingsSnoozedState(int playerID, int buildingType);

            void applySnoozedStateBasedOnPlayerData();

            void processBuildingIDsNeedPeasantsQueue(undefined4 playerID);

            void updateLordLadyJesterAndGhostUnits(int playerID);

            undefined4 getRequiredEngineerCountForSiegeBuilding(int buildingID);

            void updateVisuallyActiveState(int buildingID);

            BOOLEnum updateRepairCostAndReturnIfDamaged(int buildingIndex);

            undefined4 canUnitReachBuildingPerimeter(int param_1, int param_2);

            undefined4 canUnitReachAdjacentTile(int param_1, int param_2);

            void processDamageToUnitsOnBuilding(int buildingID, int damageBonus);

            void spawnRandomFireEffectOnBuilding(int buildingID, undefined4 playerID);

            undefined4 getBuildingFlammabilityFactor(int buildingID);

            void extinguishBuildingFire(int buildingID);

            int findClosestReachableAlliedBuilding(int param_1);

            undefined4 playerHasBurningBuilding(int playerID);

            void validateBuildingTetheredUnits(int buildingID);

            void removeTetheredUnitFromBuilding(int buildingID, int unitID);

            int getRequiredEngineersCount(int buildingID);

            void initBuildingCosts();

            void updatePathLinkageLayerForAllBuildings();

            void processDamageFromKillingPit(int unitID);

            void updatePathLinkageTileMap(int param_1);

            void initializeGatePathfindingForOwner(int param_1);

            void rebuildTileLogicLayerForGatesAndWalls();

            void rebuildTileLogicLayerForKeeps();

            void updatePathLinkageForGatesKeepsSiegeTowers();

            void updateEnemyBuildings(int playerID);

            int aiFindBuildingToAttack(int param_1, int param_2, int param_3, int param_4);

            int findClosestEnemyBuildingWithinRadius(int param_1, int param_2, int param_3, int param_4);

            void destroyBuilding(int buildingID);

            void destroyBuildings(int playerID);

            void swapOwnersOfCastle(int param_1, int param_2);

            undefined4 determineBuildingEntranceFromKeepArea(int buildingID, int workerIndexPlus1, BOOLEnum flag);

            undefined4 determineBuildingEntranceFromCustomArea(int buildingID, int param_2, int param_3, int x, int y);

            void computeBuildingEntranceFlagsForOrientations(int param_1);

            void findQuarryPileLocation(undefined4 playerID, int x, int y, int buildingSize, int pileSize, int tryUnk,
                CommandBuildingType commandBuildingType);

            BOOLEnum hasBuildingAsNeighbour(int playerID, int x, int y, int size, BuildingType type);

            int findParticularBuilding(
                undefined4 param_1, int x, int y, int buildingSize, BuildingType buildingType, int buildingID);

            int findAccessibleAreaNearBuildingLocation(int x, int y, int buildingSize);

            undefined4 addResourceToStockpile(int buildingID, int buildingUID, ResourceType resourceType, int amount,
                int maxCapacity, int recomputeResources);

            void addResourceToGranary(ResourceType resourceType, int playerID, int amount);

            void addResourceToArmory(ResourceType resourceType, int playerID, int amount);

            void processResourceLoss(int playerID, ResourceType resourceType, int amount, int param_4);

            void subtractResourcesStoredInBuilding(int buildingID);

            void processPlacementResourceLossForBuildingType(int playerID, BuildingType buildingType, int param_3);

            void processWallBuildingLoss(int playerID, int highCount, int lowCount, int zero);

            void applyFoodLossPercentageToPlayer(int param_1, int param_2);

            BOOLEnum processResourceGain(int playerID, ResourceType resourceType, int amount);

            void applyGateOrDrawbridgeOpenCloseChange(int buildingID, BOOLEnum param_2, BOOLEnum param_3);

            void sortBuildingIDsNeedPeasantsQueue(int playerID);

            undefined4 lightUpBuilding(int buildingID, int burnerPlayerID, int spareGrounds);

            void upgradeBuildingsForMapVersion(
                PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

            int setupBuildingData(int playerID, uint x, uint y, undefined4 averageHeight, BuildingType buildingType,
                uint width, int playerID_dup, int variationIndex);

            void deleteBuilding(uint buildingID);

            void destroyBuildingAndLinkedDuplicates(uint param_1);

            int buildingIsAccessible(int buildingID, int amountUnk);

            char resolveBuildingEntryAccessibility(int buildingID, int param_2, int x, int y);

            void giveBackResourceForDestroyedBuilding(int buildingIDORIfNegResourceType, int playerID, int param_3);

            int getBuildingThatCanStoreThisResource(ResourceType resourceType, int amount, int playerID);

            uint getArmoryWithSpaceLeft(
                uint targetBuildingID, undefined4 producedItemTypeUnk, int playerID, int resourceToDeposit);

            int findQuarryPileThatIsCloseAndHasMostStone(int playerID, int x, int y, int unitID);

            void updateGateDrawBridgeOpenCloseLogic();

            void checkBuildingsNeedPeasants(int playerID);

            void spreadFireRandomlyToBuildings(int param_1, int param_2);

            void updateBuildings();

            void recomputeAccessibilityForAllBuildings();

            void updateHeatmapBasedOnBuildingAccessibility(int playerID);

            void applyVersionUpgradeAccessibilityRecompute(
                PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);
        };

        static_assert_cpp98_obj(sizeof(BuildingsState) == 1630344, BuildingsState);

#pragma pack(pop)

    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
