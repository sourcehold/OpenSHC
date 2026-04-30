/**
  path: 'OpenSHC/Game/GameStateStructures.func.hpp'
*/

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Game/GameStateStructures.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Game {
    namespace GameStateStructures_Func {

        using OpenSHC::Commands::CommandBuildingTypeInt;
        using OpenSHC::Game::Resources::ResourceTypeInt;
        using OpenSHC::IO::PackagedFileMagicNumInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(bool (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x00401090,
            &GameStateStructures::isSameTeam)
        isSameTeam;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00455D40,
            &GameStateStructures::clearMapAndTimeAndPlayerData)
        clearMapAndTimeAndPlayerData;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00455D90,
            &GameStateStructures::meth_0x455d90)
        meth_0x455d90;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00455E10,
            &GameStateStructures::resetVariousCountsAndStatisticsAndStartGoodsAndResources)
        resetVariousCountsAndStatisticsAndStartGoodsAndResources;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x004560F0,
            &GameStateStructures::resetCountsAndStatistics)
        resetCountsAndStatistics;

        MACRO_FUNCTION_RESOLVER(bool (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x004563B0,
            &GameStateStructures::isFullIDEqualsToMinus1)
        isFullIDEqualsToMinus1;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x004563D0,
            &GameStateStructures::processUnitLossStatistic)
        processUnitLossStatistic;

        MACRO_FUNCTION_RESOLVER(uint (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x004565A0,
            &GameStateStructures::setLastEncounteredTroopUnit)
        setLastEncounteredTroopUnit;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(BOOLEnum, int), false, Address::SHC_3BB0A8C1_0x00456670,
            &GameStateStructures::updateDateAndTime)
        updateDateAndTime;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x00456750,
            &GameStateStructures::setMonthAndYear)
        setMonthAndYear;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x004567A0,
            &GameStateStructures::meth_0x4567a0)
        meth_0x4567a0;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00456810,
            &GameStateStructures::computeSignPostEntryData)
        computeSignPostEntryData;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00456870,
            &GameStateStructures::nof_fpoints_locationFinder)
        nof_fpoints_locationFinder;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x004568B0,
            &GameStateStructures::calculateAttackVectorsToCampFireOfPlayer)
        calculateAttackVectorsToCampFireOfPlayer;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x004568F0,
            &GameStateStructures::meth_0x4568f0)
        meth_0x4568f0;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x004569E0,
            &GameStateStructures::meth_0x4569e0)
        meth_0x4569e0;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00456AD0,
            &GameStateStructures::meth_0x456ad0)
        meth_0x456ad0;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00456C50,
            &GameStateStructures::clearDataAndSignpostDataIfNecessary)
        clearDataAndSignpostDataIfNecessary;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x00456EF0,
            &GameStateStructures::addSignpostToBuildingEntryData)
        addSignpostToBuildingEntryData;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(uint, int, int), false, Address::SHC_3BB0A8C1_0x00456FD0,
            &GameStateStructures::meth_0x456fd0)
        meth_0x456fd0;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x004572A0,
            &GameStateStructures::meth_0x4572a0)
        meth_0x4572a0;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x004574C0,
            &GameStateStructures::checkKeepEnclosed)
        checkKeepEnclosed;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x004576E0,
            &GameStateStructures::canNavigateFromKeepToKeep)
        canNavigateFromKeepToKeep;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x00457770,
            &GameStateStructures::canUnitsNavigateFromKeepToKeep)
        canUnitsNavigateFromKeepToKeep;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x00457800,
            &GameStateStructures::unitsCanMoveFromKeepOfPlayerToAnotherArea)
        unitsCanMoveFromKeepOfPlayerToAnotherArea;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (GameStateStructures::*)(int, int, int), false,
            Address::SHC_3BB0A8C1_0x00457870, &GameStateStructures::meth_0x457870)
        meth_0x457870;

        MACRO_FUNCTION_RESOLVER(bool (GameStateStructures::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004578F0,
            &GameStateStructures::meth_0x4578f0)
        meth_0x4578f0;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(uint), false, Address::SHC_3BB0A8C1_0x00457960,
            &GameStateStructures::updatePrimaryBuildingPlayerDataReferences)
        updatePrimaryBuildingPlayerDataReferences;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x00457A70,
            &GameStateStructures::changePlayerOwnership)
        changePlayerOwnership;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x00457AD0,
            &GameStateStructures::swapOwnership)
        swapOwnership;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x00457B40,
            &GameStateStructures::destroyPlayerCompletely)
        destroyPlayerCompletely;

        MACRO_FUNCTION_RESOLVER(undefined4 (GameStateStructures::*)(CommandBuildingTypeInt, int, BOOLEnum), false,
            Address::SHC_3BB0A8C1_0x00457B80, &GameStateStructures::checkRequiredResourcesForBuildingOrPlanToBuy)
        checkRequiredResourcesForBuildingOrPlanToBuy;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x00457E80,
            &GameStateStructures::getWallTilesThatCanBeBuilt)
        getWallTilesThatCanBeBuilt;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00457F20,
            &GameStateStructures::showPopAndGoldPopup)
        showPopAndGoldPopup;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00457FD0,
            &GameStateStructures::createStatsPopUpEntities)
        createStatsPopUpEntities;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int, int, int, undefined4), false,
            Address::SHC_3BB0A8C1_0x00458070, &GameStateStructures::displayPlayerTradeVisualEffect)
        displayPlayerTradeVisualEffect;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x004580C0,
            &GameStateStructures::spawnChicken)
        spawnChicken;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00458280,
            &GameStateStructures::spawnMotherOrChild)
        spawnMotherOrChild;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x004585B0,
            &GameStateStructures::playerHasACampground)
        playerHasACampground;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x004585F0,
            &GameStateStructures::moveUnitAroundCampfire)
        moveUnitAroundCampfire;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x004586D0,
            &GameStateStructures::meth_0x4586d0)
        meth_0x4586d0;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x004586F0,
            &GameStateStructures::meth_0x4586f0)
        meth_0x4586f0;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x00458700,
            &GameStateStructures::meth_0x458700)
        meth_0x458700;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (GameStateStructures::*)(ResourceTypeInt), false,
            Address::SHC_3BB0A8C1_0x00458740, &GameStateStructures::isResourceTypeTradeable)
        isResourceTypeTradeable;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00458760,
            &GameStateStructures::anyGoodsAreAllowedForSale)
        anyGoodsAreAllowedForSale;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(ResourceTypeInt), false, Address::SHC_3BB0A8C1_0x004587A0,
            &GameStateStructures::getNextGoodFilteringUnallowed)
        getNextGoodFilteringUnallowed;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(ResourceTypeInt), false, Address::SHC_3BB0A8C1_0x00458820,
            &GameStateStructures::getPreviousGoodsFilteringUnallowed)
        getPreviousGoodsFilteringUnallowed;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(undefined4, int), false, Address::SHC_3BB0A8C1_0x00458890,
            &GameStateStructures::getBatchBuyPrice)
        getBatchBuyPrice;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(undefined4, int, int), false,
            Address::SHC_3BB0A8C1_0x004588A0, &GameStateStructures::getBuyPrice)
        getBuyPrice;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x004588D0,
            &GameStateStructures::meth_0x4588d0)
        meth_0x4588d0;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(ResourceTypeInt), false, Address::SHC_3BB0A8C1_0x004588F0,
            &GameStateStructures::getSalePriceOfGood)
        getSalePriceOfGood;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00458910,
            &GameStateStructures::getSellPrice)
        getSellPrice;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x00458940,
            &GameStateStructures::getSellResourceAmount)
        getSellResourceAmount;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00458990,
            &GameStateStructures::setVariousGameStateToInitialValues)
        setVariousGameStateToInitialValues;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x004589E0,
            &GameStateStructures::processPeasantsForBuildings)
        processPeasantsForBuildings;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00458A70,
            &GameStateStructures::updateFoodTypesInStockForAllPlayers)
        updateFoodTypesInStockForAllPlayers;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00458AD0,
            &GameStateStructures::processFoodConsumption)
        processFoodConsumption;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00458D50,
            &GameStateStructures::updateAleRate)
        updateAleRate;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x00458E20,
            &GameStateStructures::computeAleCoverage)
        computeAleCoverage;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00458E60,
            &GameStateStructures::updateCrowding)
        updateCrowding;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00458EC0,
            &GameStateStructures::updateFearFactorProductivity)
        updateFearFactorProductivity;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00458F70,
            &GameStateStructures::recomputeReligionBonuses)
        recomputeReligionBonuses;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00459080,
            &GameStateStructures::calculateTaxIncomeForPlayer)
        calculateTaxIncomeForPlayer;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00459140,
            &GameStateStructures::calculateTaxBribeExpenseForPlayer)
        calculateTaxBribeExpenseForPlayer;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00459170,
            &GameStateStructures::getNumberToDisplayPlayerTaxIncome)
        getNumberToDisplayPlayerTaxIncome;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004591B0,
            &GameStateStructures::getNumberToDisplayBribeIncome)
        getNumberToDisplayBribeIncome;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x004591F0,
            &GameStateStructures::despawnPeasantOrWorker)
        despawnPeasantOrWorker;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x00459490,
            &GameStateStructures::spawnDrunkard)
        spawnDrunkard;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x004595D0,
            &GameStateStructures::singlePlayerHasKeepAndGranaryCheck)
        singlePlayerHasKeepAndGranaryCheck;

        MACRO_FUNCTION_RESOLVER(
            void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00459640, &GameStateStructures::resetTeams)
        resetTeams;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x004596D0,
            &GameStateStructures::getTeamsDifferent)
        getTeamsDifferent;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x00459700,
            &GameStateStructures::findAITeamMate)
        findAITeamMate;

        MACRO_FUNCTION_RESOLVER(uint (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x00459740,
            &GameStateStructures::TeamToBitFlagsUnk)
        TeamToBitFlagsUnk;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x004597D0,
            &GameStateStructures::meth_0x4597d0)
        meth_0x4597d0;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x004598B0,
            &GameStateStructures::recountStablesAndHorses)
        recountStablesAndHorses;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x00459930,
            &GameStateStructures::linkageBetweenHorseUnitAndStableUnk)
        linkageBetweenHorseUnitAndStableUnk;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x00459A20,
            &GameStateStructures::spawnPoisonCloudsAroundBuilding)
        spawnPoisonCloudsAroundBuilding;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x00459B50,
            &GameStateStructures::playSFXNoSpaceInTheStockPile)
        playSFXNoSpaceInTheStockPile;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x00459BB0,
            &GameStateStructures::FUN_00459bb0)
        FUN_00459bb0;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00459BE0,
            &GameStateStructures::fillWith0xFF)
        fillWith0xFF;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x00459C10,
            &GameStateStructures::assignSelectionToKey)
        assignSelectionToKey;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00459E40,
            &GameStateStructures::HandleActivateTacticalPowers)
        HandleActivateTacticalPowers;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x0045A060, &GameStateStructures::renderDebugDataCurrentPlayerData)
        renderDebugDataCurrentPlayerData;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x0045AE10,
            &GameStateStructures::addBuildingInRegistry)
        addBuildingInRegistry;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x0045AE70,
            &GameStateStructures::resetBuildingsCurrentIndexCounter)
        resetBuildingsCurrentIndexCounter;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x0045AEB0,
            &GameStateStructures::selectARandomBuildingOwnedByPlayer)
        selectARandomBuildingOwnedByPlayer;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x0045AF00,
            &GameStateStructures::resetSomethingBuildingRelatedForAllPlayers)
        resetSomethingBuildingRelatedForAllPlayers;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x0045AF30,
            &GameStateStructures::computePopulationStatistics)
        computePopulationStatistics;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x0045B1C0,
            &GameStateStructures::clearEnemyRelatedStructures)
        clearEnemyRelatedStructures;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x0045B3E0,
            &GameStateStructures::meth_0x45b3e0)
        meth_0x45b3e0;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int), false, Address::SHC_3BB0A8C1_0x0045B460,
            &GameStateStructures::switchPlayerOwnership)
        switchPlayerOwnership;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x0045B6B0,
            &GameStateStructures::updateTrader)
        updateTrader;

        MACRO_FUNCTION_RESOLVER(int (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x0045B7F0,
            &GameStateStructures::getSalesPrice)
        getSalesPrice;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x0045B830,
            &GameStateStructures::updatePopularity)
        updatePopularity;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x0045BF50,
            &GameStateStructures::updateTaxing)
        updateTaxing;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(int, int), false, Address::SHC_3BB0A8C1_0x0045C050,
            &GameStateStructures::spawnPoisonCloudsAtRandomStorageOrArmyBuilding)
        spawnPoisonCloudsAtRandomStorageOrArmyBuilding;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(PackagedFileMagicNumInt, PackagedFileMagicNumInt), false,
            Address::SHC_3BB0A8C1_0x0045C1C0, &GameStateStructures::meth_0x45c1c0)
        meth_0x45c1c0;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x0045B4A0,
            &GameStateStructures::processSingleTimeTick)
        processSingleTimeTick;

        MACRO_FUNCTION_RESOLVER(void (GameStateStructures::*)(), false, Address::SHC_3BB0A8C1_0x00459D80,
            &GameStateStructures::processGameTick)
        processGameTick;

    } // namespace GameStateStructures_Func
} // namespace Game
} // namespace OpenSHC
