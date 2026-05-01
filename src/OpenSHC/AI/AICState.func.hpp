/**
  path: 'OpenSHC/AI/AICState.func.hpp'
*/

#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AINervousDestroyBuildingCategoryInt.hpp"
#include "OpenSHC/AI/AIUnitBehaviourTypeInt.hpp"
#include "OpenSHC/AI/AIVUnitTypeInt.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace AI {
    namespace AICState_Func {

        using OpenSHC::AI::AINervousDestroyBuildingCategoryInt;
        using OpenSHC::AI::AIUnitBehaviourTypeInt;
        using OpenSHC::AI::AIVUnitTypeInt;
        using OpenSHC::Commands::CommandBuildingTypeInt;
        using OpenSHC::Game::Player::PlayerID;
        using OpenSHC::Game::Resources::ResourceTypeInt;
        using OpenSHC::Map::Units::UnitTypeInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(), false, Address::SHC_3BB0A8C1_0x004C6D30, &AICState::wipeAICMemory)
        wipeAICMemory;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004C6D60, &AICState::setAICParameters_01)
        setAICParameters_01;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004C7120, &AICState::setAICParameters_02)
        setAICParameters_02;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004C7520, &AICState::setAICParameters_03)
        setAICParameters_03;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004C7910, &AICState::setAICParameters_04)
        setAICParameters_04;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004C7D20, &AICState::setAICParameters_05)
        setAICParameters_05;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004C8110, &AICState::setAICParameters_06)
        setAICParameters_06;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004C8530, &AICState::setAICParameters_07)
        setAICParameters_07;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004C8920, &AICState::setAICParameters_08)
        setAICParameters_08;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004C8D20, &AICState::setAICParameters_09)
        setAICParameters_09;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004C9120, &AICState::setAICParameters_10)
        setAICParameters_10;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004C94F0, &AICState::setAICParameters_11)
        setAICParameters_11;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004C9900, &AICState::setAICParameters_12)
        setAICParameters_12;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004C9CF0, &AICState::setAICParameters_13)
        setAICParameters_13;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CA0C0, &AICState::setAICParameters_14)
        setAICParameters_14;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CA4D0, &AICState::setAICParameters_15)
        setAICParameters_15;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CA8A0, &AICState::setAICParameters_16)
        setAICParameters_16;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(), false, Address::SHC_3BB0A8C1_0x004CAC70, &AICState::clearPlayerDataInformationChunk)
        clearPlayerDataInformationChunk;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004CACB0,
            &AICState::setTargetForTribeBasedOnTargetChoiceLogic)
        setTargetForTribeBasedOnTargetChoiceLogic;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CAEA0, &AICState::updateTaxesAndRationsForAI)
        updateTaxesAndRationsForAI;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CB060, &AICState::setFoodBuyPlan)
        setFoodBuyPlan;

        MACRO_FUNCTION_RESOLVER(
            int (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CB120, &AICState::getAIBuildInterval)
        getAIBuildInterval;

        MACRO_FUNCTION_RESOLVER(
            int (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CB150, &AICState::getResourceRebuildDelay)
        getResourceRebuildDelay;

        MACRO_FUNCTION_RESOLVER(
            int (AICState::*)(PlayerID), false, Address::SHC_3BB0A8C1_0x004CB180, &AICState::aiFarmChoice)
        aiFarmChoice;

        MACRO_FUNCTION_RESOLVER(
            int (AICState::*)(PlayerID), false, Address::SHC_3BB0A8C1_0x004CB1B0, &AICState::setNextFarmTypeToBuild)
        setNextFarmTypeToBuild;

        MACRO_FUNCTION_RESOLVER(
            uint (AICState::*)(PlayerID), false, Address::SHC_3BB0A8C1_0x004CB220, &AICState::aiShouldBuildFarm)
        aiShouldBuildFarm;

        MACRO_FUNCTION_RESOLVER(
            uint (AICState::*)(PlayerID), false, Address::SHC_3BB0A8C1_0x004CB290, &AICState::aiShouldBuildWoodcutter)
        aiShouldBuildWoodcutter;

        MACRO_FUNCTION_RESOLVER(
            uint (AICState::*)(PlayerID), false, Address::SHC_3BB0A8C1_0x004CB330, &AICState::aiShouldBuildQuarry)
        aiShouldBuildQuarry;

        MACRO_FUNCTION_RESOLVER(
            undefined4 (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CB3A0, &AICState::aiRequiresExtraOxtethers)
        aiRequiresExtraOxtethers;

        MACRO_FUNCTION_RESOLVER(
            uint (AICState::*)(PlayerID), false, Address::SHC_3BB0A8C1_0x004CB4D0, &AICState::aiShouldBuildIronMine)
        aiShouldBuildIronMine;

        MACRO_FUNCTION_RESOLVER(
            uint (AICState::*)(PlayerID), false, Address::SHC_3BB0A8C1_0x004CB540, &AICState::aiShouldBuildPitchrig)
        aiShouldBuildPitchrig;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(PlayerID, CommandBuildingTypeInt), false,
            Address::SHC_3BB0A8C1_0x004CB5B0, &AICState::shouldNotBeBuildingHovel)
        shouldNotBeBuildingHovel;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(int, CommandBuildingTypeInt), false,
            Address::SHC_3BB0A8C1_0x004CB610, &AICState::shouldWaitWithBuildingNegativeFearFactor)
        shouldWaitWithBuildingNegativeFearFactor;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(int, CommandBuildingTypeInt), false,
            Address::SHC_3BB0A8C1_0x004CB700, &AICState::shouldWaitWithBuildingAPositiveFearFactor)
        shouldWaitWithBuildingAPositiveFearFactor;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CB810, &AICState::destroyHouse)
        destroyHouse;

        MACRO_FUNCTION_RESOLVER(undefined4 (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CB890,
            &AICState::shouldDestroyWoodCutterUnk)
        shouldDestroyWoodCutterUnk;

        MACRO_FUNCTION_RESOLVER(undefined4 (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CB940,
            &AICState::destroyBuildingIfNoWorker)
        destroyBuildingIfNoWorker;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(int, CommandBuildingTypeInt), false,
            Address::SHC_3BB0A8C1_0x004CB9F0, &AICState::shouldNotBuildMarketArmoryGranaryBarracksMercenarypost)
        shouldNotBuildMarketArmoryGranaryBarracksMercenarypost;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CBA50,
            &AICState::planToBuyWhenLowOnResourceAndSnoozeBuildings)
        planToBuyWhenLowOnResourceAndSnoozeBuildings;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004CBE30,
            &AICState::setupWorkshopProductionType)
        setupWorkshopProductionType;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int, ResourceTypeInt, int), false, Address::SHC_3BB0A8C1_0x004CBFA0,
            &AICState::sellGoods)
        sellGoods;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(int, ResourceTypeInt, int), false,
            Address::SHC_3BB0A8C1_0x004CC000, &AICState::buyGoods)
        buyGoods;

        MACRO_FUNCTION_RESOLVER(AIUnitBehaviourTypeInt (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CC070,
            &AICState::randomlySelectAttackUnitTypeToRecruit)
        randomlySelectAttackUnitTypeToRecruit;

        MACRO_FUNCTION_RESOLVER(UnitTypeInt (AICState::*)(int, AIUnitBehaviourTypeInt), false,
            Address::SHC_3BB0A8C1_0x004CC250, &AICState::getUnitTypeForUnitBehaviourType)
        getUnitTypeForUnitBehaviourType;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004CC420,
            &AICState::generateSiegeCreationInformation)
        generateSiegeCreationInformation;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CC520, &AICState::recruitEngineers)
        recruitEngineers;

        MACRO_FUNCTION_RESOLVER(int (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004CC5A0,
            &AICState::assignRequiredIdleEngineersToNewTribe)
        assignRequiredIdleEngineersToNewTribe;

        MACRO_FUNCTION_RESOLVER(
            int (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004CC680, &AICState::addEngineersToSelection)
        addEngineersToSelection;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CC720, &AICState::addUnitsToTribe166)
        addUnitsToTribe166;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CC7B0, &AICState::syncBehaviourType7UnitTribes)
        syncBehaviourType7UnitTribes;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CC840,
            &AICState::addUnitToTribeType10_moatdiggersUnk)
        addUnitToTribeType10_moatdiggersUnk;

        MACRO_FUNCTION_RESOLVER(
            undefined4 (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CC8D0, &AICState::unitIDIsRangedOrArmored)
        unitIDIsRangedOrArmored;

        MACRO_FUNCTION_RESOLVER(
            int (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004CC910, &AICState::createTribeForUnitType)
        createTribeForUnitType;

        MACRO_FUNCTION_RESOLVER(
            int (AICState::*)(int, short*), false, Address::SHC_3BB0A8C1_0x004CC990, &AICState::smallestTribeOfUnitType)
        smallestTribeOfUnitType;

        MACRO_FUNCTION_RESOLVER(
            int (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004CCBE0, &AICState::getDefensiveTribeForUnit)
        getDefensiveTribeForUnit;

        MACRO_FUNCTION_RESOLVER(int (AICState::*)(short*, undefined, int), false, Address::SHC_3BB0A8C1_0x004CCD20,
            &AICState::addUnitToSmallestBehaviourTypeTribe)
        addUnitToSmallestBehaviourTypeTribe;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(undefined4, int), false, Address::SHC_3BB0A8C1_0x004CD0C0, &AICState::sendUnitsToKeep)
        sendUnitsToKeep;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004CD110, &AICState::sendUnitsToCampfire)
        sendUnitsToCampfire;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CD160, &AICState::digNearestMoat)
        digNearestMoat;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004CD250,
            &AICState::canNavigateUnitsFromTileToTargetTile)
        canNavigateUnitsFromTileToTargetTile;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CD2A0, &AICState::recruitHarrassingSiegeEngines)
        recruitHarrassingSiegeEngines;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CD560, &AICState::recruitSortieRangedUnits)
        recruitSortieRangedUnits;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CD690, &AICState::recruitSortieMeleeUnits)
        recruitSortieMeleeUnits;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CD7B0, &AICState::instructTribe166ToMove)
        instructTribe166ToMove;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CD8F0, &AICState::giveMoveCommandToSortieUnits)
        giveMoveCommandToSortieUnits;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CDA50,
            &AICState::addBuildingToSomePlayerStateArray)
        addBuildingToSomePlayerStateArray;

        MACRO_FUNCTION_RESOLVER(int (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CDAB0,
            &AICState::selectBuildingFromAListOfBuildingTypes)
        selectBuildingFromAListOfBuildingTypes;

        MACRO_FUNCTION_RESOLVER(int (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CDB20,
            &AICState::chooseRandomBuildingIDFromPlayersArrayOfBuildings)
        chooseRandomBuildingIDFromPlayersArrayOfBuildings;

        MACRO_FUNCTION_RESOLVER(int (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004CDBC0,
            &AICState::getTargetableBuildingForPlayerID)
        getTargetableBuildingForPlayerID;

        MACRO_FUNCTION_RESOLVER(int (AICState::*)(int, undefined4), false, Address::SHC_3BB0A8C1_0x004CDCA0,
            &AICState::selectRandomBuildingIDFromListOfBuildingTypes)
        selectRandomBuildingIDFromListOfBuildingTypes;

        MACRO_FUNCTION_RESOLVER(undefined4 (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CDCF0,
            &AICState::shouldWeAttackOrWaitForTeammates)
        shouldWeAttackOrWaitForTeammates;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CDE60, &AICState::setCurrentAttackStrength)
        setCurrentAttackStrength;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CDF10, &AICState::setCurrentAttackRaidParameter)
        setCurrentAttackRaidParameter;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004CDFD0, &AICState::setAttackPrimeInfo)
        setAttackPrimeInfo;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004CE040,
            &AICState::recomputeDistancesToAttackedKeepRelated)
        recomputeDistancesToAttackedKeepRelated;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(), false, Address::SHC_3BB0A8C1_0x004CE110, &AICState::recomputeAttackAIZone)
        recomputeAttackAIZone;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(), false, Address::SHC_3BB0A8C1_0x004CE1A0, &AICState::recomputeAIZonerLayer)
        recomputeAIZonerLayer;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CE200,
            &AICState::computeAndStoreShortestDistanceToKeepUnk)
        computeAndStoreShortestDistanceToKeepUnk;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CE3B0, &AICState::setNextMoveLocationForUnits)
        setNextMoveLocationForUnits;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CE430,
            &AICState::removeOrganismsAndSetMoveDestinationPairs)
        removeOrganismsAndSetMoveDestinationPairs;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(short*), false, Address::SHC_3BB0A8C1_0x004CE4D0, &AICState::aiRetreatUnits)
        aiRetreatUnits;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int, short*), false, Address::SHC_3BB0A8C1_0x004CE5F0,
            &AICState::sendUnitsToPlayerIDsKeepIfPossible)
        sendUnitsToPlayerIDsKeepIfPossible;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CE790,
            &AICState::setRallyRelatedFlagOnAllAIAttackTribes)
        setRallyRelatedFlagOnAllAIAttackTribes;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(short*), false, Address::SHC_3BB0A8C1_0x004CE830, &AICState::moveAttackTribesToLocations)
        moveAttackTribesToLocations;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CE930,
            &AICState::findAttackTribePositionAndPathToDefenses)
        findAttackTribePositionAndPathToDefenses;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CEA50,
            &AICState::makeUnitsGoDefensiveAndBackToSomeLocation)
        makeUnitsGoDefensiveAndBackToSomeLocation;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CEB50, &AICState::giveMoveCommandToAttackTribes)
        giveMoveCommandToAttackTribes;

        MACRO_FUNCTION_RESOLVER(uint (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CEC80,
            &AICState::aiChoiceAttForceRallyPercentage)
        aiChoiceAttForceRallyPercentage;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CED90,
            &AICState::percentageNonMovingTribesGTEAICSpecified)
        percentageNonMovingTribesGTEAICSpecified;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CEEA0,
            &AICState::processAttForceRallyPercentage)
        processAttForceRallyPercentage;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(CommandBuildingTypeInt), false, Address::SHC_3BB0A8C1_0x004CEFD0,
            &AICState::useAITribe_0x12_toPlaceSiegeTentsAndAssignEngineers)
        useAITribe_0x12_toPlaceSiegeTentsAndAssignEngineers;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CF180, &AICState::useAITribe_0xe_toPlaceTunnels)
        useAITribe_0xe_toPlaceTunnels;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CF270, &AICState::aiAttackWave_tribe13Unk)
        aiAttackWave_tribe13Unk;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CF2E0, &AICState::aiAttackWave_tribe12Unk)
        aiAttackWave_tribe12Unk;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CF400,
            &AICState::setTribe0xCtoAggressiveAndAttack)
        setTribe0xCtoAggressiveAndAttack;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CF470, &AICState::aiAttackWave_tribe11Unk)
        aiAttackWave_tribe11Unk;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CF4F0, &AICState::sendAITribe_0xf_toAttackPatrol)
        sendAITribe_0xf_toAttackPatrol;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CF560,
            &AICState::setTribe0x11ToAggressiveAndAttackIfConditionMet)
        setTribe0x11ToAggressiveAndAttackIfConditionMet;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CF5E0,
            &AICState::setEightTribe0xc0TribesToAggressiveAndAttack)
        setEightTribe0xc0TribesToAggressiveAndAttack;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CF660, &AICState::aiAttackWallsSmthUnk)
        aiAttackWallsSmthUnk;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CF6E0,
            &AICState::setTribe0xbToAggressiveAndAttack)
        setTribe0xbToAggressiveAndAttack;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CF750, &AICState::sendTribeToAttack)
        sendTribeToAttack;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CF7C0, &AICState::commandFourTribesToMove)
        commandFourTribesToMove;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CF870, &AICState::clearOutdatedAITribes)
        clearOutdatedAITribes;

        MACRO_FUNCTION_RESOLVER(
            undefined4 (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004CF920, &AICState::giveSomeRaidCommand)
        giveSomeRaidCommand;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CFA10, &AICState::addRallyPointForTribe)
        addRallyPointForTribe;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CFB20, &AICState::disbandAIPlayerSiegeUnits)
        disbandAIPlayerSiegeUnits;

        MACRO_FUNCTION_RESOLVER(
            int (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CFBC0, &AICState::countSiegeEngineUnits)
        countSiegeEngineUnits;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CFCD0, &AICState::aiAttackWaveSiegeUnitsUnk)
        aiAttackWaveSiegeUnitsUnk;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CFF60, &AICState::yieldCowThrow)
        yieldCowThrow;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004CFFD0, &AICState::hasNoTroopsOrAllAreDiggers)
        hasNoTroopsOrAllAreDiggers;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D00A0, &AICState::hasNotEnoughSupplies)
        hasNotEnoughSupplies;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D0110, &AICState::setAttackWillingnessUnk)
        setAttackWillingnessUnk;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(int, BOOLEnum), false, Address::SHC_3BB0A8C1_0x004D0190,
            &AICState::teamIsWeakRelativeToEnemy)
        teamIsWeakRelativeToEnemy;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int, AINervousDestroyBuildingCategoryInt), false,
            Address::SHC_3BB0A8C1_0x004D0280, &AICState::destroyAnyBuildingInCategory)
        destroyAnyBuildingInCategory;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(int, ResourceTypeInt, int), false,
            Address::SHC_3BB0A8C1_0x004D0520, &AICState::isResourceLargerOrEqualThanMinimumGoodsRequiredAfterTrade)
        isResourceLargerOrEqualThanMinimumGoodsRequiredAfterTrade;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D0580, &AICState::aiOfTypeInCurrentGame)
        aiOfTypeInCurrentGame;

        MACRO_FUNCTION_RESOLVER(
            int (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004D05D0, &AICState::shareGoldAmongTeamMembers)
        shareGoldAmongTeamMembers;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D0830, &AICState::PlayAnger1BikFromPlayer)
        PlayAnger1BikFromPlayer;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004D08B0,
            &AICState::PlayPlayerKilledBiksFromKilledAndKillerPlayer)
        PlayPlayerKilledBiksFromKilledAndKillerPlayer;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004D0A80,
            &AICState::playThanksBikFromPlayerToPlayer)
        playThanksBikFromPlayerToPlayer;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(), false, Address::SHC_3BB0A8C1_0x004D1090, &AICState::setSomeTimeToNowIfInIngameMenu)
        setSomeTimeToNowIfInIngameMenu;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(), false, Address::SHC_3BB0A8C1_0x004D10B0, &AICState::someChatMessageSelection)
        someChatMessageSelection;

        MACRO_FUNCTION_RESOLVER(int (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004D12A0,
            &AICState::getCurrentDesiredAttackRaidUnitCount)
        getCurrentDesiredAttackRaidUnitCount;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x004D1320,
            &AICState::renderDebugDataAiInfo)
        renderDebugDataAiInfo;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(), false, Address::SHC_3BB0A8C1_0x004D18B0, &AICState::setInitialAIC)
        setInitialAIC;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004D1950,
            &AICState::aiGiveCommandToOutpostTribesUnk)
        aiGiveCommandToOutpostTribesUnk;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(uint), false, Address::SHC_3BB0A8C1_0x004D1A00, &AICState::decideOnTribeAttackLocation)
        decideOnTribeAttackLocation;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int, ResourceTypeInt, undefined4), false,
            Address::SHC_3BB0A8C1_0x004D1F00, &AICState::requestGoods)
        requestGoods;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D2000, &AICState::aiCreateSiegeUnits)
        aiCreateSiegeUnits;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D2500, &AICState::aiRecruitEngineerForOilDuty)
        aiRecruitEngineerForOilDuty;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D2660, &AICState::assignUnitToATribe)
        assignUnitToATribe;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D2730, &AICState::addUnitToSmallestPatrolTribe)
        addUnitToSmallestPatrolTribe;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D2790,
            &AICState::addUnitToDefensiveTroopsTribeUnk)
        addUnitToDefensiveTroopsTribeUnk;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004D27E0, &AICState::addUnitToItsTribe)
        addUnitToItsTribe;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D2830, &AICState::ifHasTribe0SendUnitsToKeep)
        ifHasTribe0SendUnitsToKeep;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D2870, &AICState::sendTribeAtOffset1ToCampfire)
        sendTribeAtOffset1ToCampfire;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D28B0, &AICState::aiGiveOuterPatrolCommand)
        aiGiveOuterPatrolCommand;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D2A70, &AICState::aiGiveRaidInstructions)
        aiGiveRaidInstructions;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int, AIVUnitTypeInt, int), false, Address::SHC_3BB0A8C1_0x004D2E00,
            &AICState::sendTribeToAIVLocationSlot)
        sendTribeToAIVLocationSlot;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D2EC0, &AICState::computeAttackPossibilities)
        computeAttackPossibilities;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D2F80,
            &AICState::moveAttackingUnitsToNextRallyPoint)
        moveAttackingUnitsToNextRallyPoint;

        MACRO_FUNCTION_RESOLVER(undefined4 (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D30E0,
            &AICState::sendUnitsToAttackBreachedCastle)
        sendUnitsToAttackBreachedCastle;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004D3320, &AICState::updateAIStrengthState)
        updateAIStrengthState;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D3780, &AICState::computeNervousness)
        computeNervousness;

        MACRO_FUNCTION_RESOLVER(undefined4 (AICState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004D3850,
            &AICState::determineAIPlayerHelp)
        determineAIPlayerHelp;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(int, undefined4, int), false, Address::SHC_3BB0A8C1_0x004D38C0,
            &AICState::determineAIPlayerAttackRequestResponse)
        determineAIPlayerAttackRequestResponse;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(), false, Address::SHC_3BB0A8C1_0x004D3960, &AICState::makeOutpostTribesAttack)
        makeOutpostTribesAttack;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D3AE0, &AICState::aiRecruitUnits)
        aiRecruitUnits;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D3F20, &AICState::assignMoatDiggersUnk)
        assignMoatDiggersUnk;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D4040, &AICState::addEngineersToTribe)
        addEngineersToTribe;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D40B0, &AICState::redirectTunnelersUnk)
        redirectTunnelersUnk;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D4130,
            &AICState::sendRangedUnitTribesToAIVSlotsOrKeepIfNervous)
        sendRangedUnitTribesToAIVSlotsOrKeepIfNervous;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D4220,
            &AICState::sendCertainUnitTribesToAIVSlotsOrKeepIfNervousAndNotEnclosed)
        sendCertainUnitTribesToAIVSlotsOrKeepIfNervousAndNotEnclosed;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D4340,
            &AICState::sendWallPatrolUnitTribesToAIVLocations)
        sendWallPatrolUnitTribesToAIVLocations;

        MACRO_FUNCTION_RESOLVER(void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D44E0,
            &AICState::sendOilMenForOilPickupOrToAIVLocations)
        sendOilMenForOilPickupOrToAIVLocations;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D45E0, &AICState::abortAttackAndGoIdle)
        abortAttackAndGoIdle;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D4630, &AICState::recreateEngineersTribe)
        recreateEngineersTribe;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D4680, &AICState::selectAttackTarget)
        selectAttackTarget;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D1D60, &AICState::aiBuyAndSellGoods)
        aiBuyAndSellGoods;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D4940, &AICState::updateTribeLocations)
        updateTribeLocations;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(int), false, Address::SHC_3BB0A8C1_0x004D49E0, &AICState::updateAIPlayerState)
        updateAIPlayerState;

        MACRO_FUNCTION_RESOLVER(
            void (AICState::*)(), false, Address::SHC_3BB0A8C1_0x004D53E0, &AICState::updateAIBehaviour)
        updateAIBehaviour;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(int, CommandBuildingTypeInt), false,
            Address::SHC_3BB0A8C1_0x004ECA30, &AICState::shouldNotBeBuildingGranary)
        shouldNotBeBuildingGranary;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(PlayerID, CommandBuildingTypeInt), false,
            Address::SHC_3BB0A8C1_0x004ECA60, &AICState::shouldNotBeBuildingArmoury)
        shouldNotBeBuildingArmoury;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(int, CommandBuildingTypeInt), false,
            Address::SHC_3BB0A8C1_0x004ECA90, &AICState::shouldNotBuildKillingPits)
        shouldNotBuildKillingPits;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AICState::*)(undefined4, CommandBuildingTypeInt), false,
            Address::SHC_3BB0A8C1_0x004ECAB0, &AICState::woodCuttersHutWhileNoWoodAvailable)
        woodCuttersHutWhileNoWoodAvailable;

    } // namespace AICState_Func
} // namespace AI
} // namespace OpenSHC
