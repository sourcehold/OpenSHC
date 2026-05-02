/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/GameStateStructures.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Game/State/MapAndTimeState.hpp"
#include "OpenSHC/Game/State/UnitSelectionHotKeyEntry.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Commands::CommandBuildingTypeInt;
    using OpenSHC::Game::Player::PlayerData;
    using OpenSHC::Game::Resources::ResourceTypeInt;
    using OpenSHC::Game::State::MapAndTimeState;
    using OpenSHC::Game::State::UnitSelectionHotKeyEntry;
    using OpenSHC::IO::PackagedFileMagicNumInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00093BF4
    class GameStateStructures {
    public:
        UnitSelectionHotKeyEntry section1099Array[10]; // 0x00000000 length: 200000
        PlayerData playerDataArray[9]; // 0x00030D40 length: 133524
        MapAndTimeState mapAndTime; // 0x000516D4 length: 262608
        int gameTicksLoadBalancer; // 0x000918A4 length: 4
        short first500BuildingsPerPlayer[9][500]; // 0x000918A8 length: 9000
        int first500BuildingsCurrentIndexCounter[9]; // 0x00093BD0 length: 36

    private:
        GameStateStructures(GameStateStructures const&);
        void operator=(GameStateStructures const&);

        GameStateStructures();
        ~GameStateStructures();

    public:
        bool isSameTeam(int playerID1, int playerID2);

        void clearMapAndTimeAndPlayerData();

        void meth_0x455d90();

        void resetVariousCountsAndStatisticsAndStartGoodsAndResources();

        void resetCountsAndStatistics();

        bool isFullIDEqualsToMinus1(int param_1);

        void processUnitLossStatistic(int playerID, int unitID);

        uint setLastEncounteredTroopUnit(int playerID, int unitID);

        void updateDateAndTime(BOOLEnum startOfWeekAsCurrentTickIs0, int currentTick);

        void setMonthAndYear(int month, int year);

        void meth_0x4567a0();

        void computeSignPostEntryData();

        void nof_fpoints_locationFinder();

        void calculateAttackVectorsToCampFireOfPlayer(int playerID);

        int meth_0x4568f0();

        BOOLEnum meth_0x4569e0();

        int meth_0x456ad0();

        void clearDataAndSignpostDataIfNecessary();

        void addSignpostToBuildingEntryData(int buildingID);

        void meth_0x456fd0(uint param_1, int param_2, int param_3);

        void meth_0x4572a0(int playerID, int param_2);

        BOOLEnum checkKeepEnclosed(int playerID);

        BOOLEnum canNavigateFromKeepToKeep(int playerID1, int playerID2);

        BOOLEnum canUnitsNavigateFromKeepToKeep(int playerID, int targetPlayerID);

        BOOLEnum unitsCanMoveFromKeepOfPlayerToAnotherArea(int playerID);

        BOOLEnum meth_0x457870(int param_1, int param_2, int param_3);

        bool meth_0x4578f0(int param_1, int param_2, int param_3);

        void updatePrimaryBuildingPlayerDataReferences(uint buildingID);

        void changePlayerOwnership(int fromPlayer, int toPlayer);

        void swapOwnership(int playerID_1, int playerID_2);

        void destroyPlayerCompletely(int playerID);

        undefined4 checkRequiredResourcesForBuildingOrPlanToBuy(
            CommandBuildingTypeInt commandBuildingType, int playerID, BOOLEnum playResourceLackMsgUnk);

        int getWallTilesThatCanBeBuilt(int playerID, int wallMaterial);

        void showPopAndGoldPopup();

        void createStatsPopUpEntities();

        void displayPlayerTradeVisualEffect(int playerID, int param_2, int amount, undefined4 resourceType);

        void spawnChicken();

        void spawnMotherOrChild();

        BOOLEnum playerHasACampground(int playerID);

        int moveUnitAroundCampfire(int unitID, int availablePeasants);

        void meth_0x4586d0();

        void meth_0x4586f0();

        int meth_0x458700(int param_1);

        BOOLEnum isResourceTypeTradeable(ResourceTypeInt resourceType);

        BOOLEnum anyGoodsAreAllowedForSale();

        int getNextGoodFilteringUnallowed(ResourceTypeInt param_1);

        int getPreviousGoodsFilteringUnallowed(ResourceTypeInt param_1);

        int getBatchBuyPrice(undefined4 playerID, int resourceType);

        int getBuyPrice(undefined4 playerID, int resourceType, int amount);

        int meth_0x4588d0(int param_1);

        int getSalePriceOfGood(ResourceTypeInt param_1);

        int getSellPrice(int playerID, int resourceType, int amount);

        int getSellResourceAmount(int playerID, int resourceType);

        void setVariousGameStateToInitialValues();

        void processPeasantsForBuildings();

        void updateFoodTypesInStockForAllPlayers();

        void processFoodConsumption();

        void updateAleRate();

        int computeAleCoverage(int playerID);

        void updateCrowding();

        void updateFearFactorProductivity();

        void recomputeReligionBonuses();

        int calculateTaxIncomeForPlayer(int playerIndex, int taxStep, int currentPeasants);

        int calculateTaxBribeExpenseForPlayer(int playerIndex, int taxStep, int currentPopulation);

        int getNumberToDisplayPlayerTaxIncome(int playerIndex, int taxStep, int currentPopulation);

        int getNumberToDisplayBribeIncome(int playerIndex, int taxStep, int currentPopulation);

        void despawnPeasantOrWorker(int playerID);

        void spawnDrunkard(int param_1);

        int singlePlayerHasKeepAndGranaryCheck();

        void resetTeams();

        BOOLEnum getTeamsDifferent(int firstPlayerId, int secondPlayerId);

        int findAITeamMate(int playerID1);

        uint TeamToBitFlagsUnk(int unitID);

        BOOLEnum meth_0x4597d0();

        void recountStablesAndHorses();

        int linkageBetweenHorseUnitAndStableUnk(int playerID, int unitID);

        void spawnPoisonCloudsAroundBuilding(int buildingID);

        void playSFXNoSpaceInTheStockPile(int playerID);

        void FUN_00459bb0(int param_1);

        void fillWith0xFF();

        void assignSelectionToKey(int number, int tribeID);

        void HandleActivateTacticalPowers(int param_1, int powerType, int param_3);

        void renderDebugDataCurrentPlayerData(int x, int y, int width, int height);

        void addBuildingInRegistry(int buildingID);

        void resetBuildingsCurrentIndexCounter();

        int selectARandomBuildingOwnedByPlayer(int playerID);

        void resetSomethingBuildingRelatedForAllPlayers();

        void computePopulationStatistics();

        void clearEnemyRelatedStructures();

        void meth_0x45b3e0();

        void switchPlayerOwnership(int playerID);

        void updateTrader();

        int getSalesPrice(int playerID, int resourceType);

        void updatePopularity();

        void updateTaxing();

        void spawnPoisonCloudsAtRandomStorageOrArmyBuilding(int playerID, int count);

        void meth_0x45c1c0(PackagedFileMagicNumInt receivedMapVersion, PackagedFileMagicNumInt packagerMapVersion);

        void processSingleTimeTick();

        void processGameTick();
    };

    static_assert_cpp98_obj(sizeof(GameStateStructures) == 605172, GameStateStructures);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(GameStateStructures, false, Address::SHC_3BB0A8C1_0x0112B0B8) pDAT_GameStateStructures;

} // namespace Game
} // namespace OpenSHC
