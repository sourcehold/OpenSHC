/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AICState.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIC/AICSpecification.hpp"
#include "OpenSHC/AI/AINervousDestroyBuildingCategoryInt.hpp"
#include "OpenSHC/AI/AIUnitBehaviourTypeInt.hpp"
#include "OpenSHC/AI/AIVUnitTypeInt.hpp"
#include "OpenSHC/AI/TileDistancePair.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AINervousDestroyBuildingCategoryInt;
    using OpenSHC::AI::AIUnitBehaviourTypeInt;
    using OpenSHC::AI::AIVUnitTypeInt;
    using OpenSHC::AI::TileDistancePair;
    using OpenSHC::AI::AIC::AICSpecification;
    using OpenSHC::Commands::CommandBuildingTypeInt;
    using OpenSHC::Game::Player::PlayerID;
    using OpenSHC::Game::Resources::ResourceTypeInt;
    using OpenSHC::Map::Units::UnitTypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00006D90
    class AICState {
    public:
        AICSpecification DAT_AICArray[20]; // 0x00000000 length: 13520
        undefined4 aiBorderTilesIndex; // 0x000034D0 length: 4
        TileDistancePair aiBorderTiles[1000]; // 0x000034D4 length: 8000
        byte unused01[512]; // 0x00005414 length: 512
        short tribeIDArray[1000]; // 0x00005614 length: 2000
        int tribeUIDArray[1000]; // 0x00005DE4 length: 4000
        undefined4 DAT_SomeTime; // 0x00006D84 length: 4
        byte unused02[8]; // 0x00006D88 length: 8

    private:
        AICState(AICState const&);
        void operator=(AICState const&);

        AICState();
        ~AICState();

    public:
        // Constructor
        AICState* Constructor_AICState();

        void wipeAICMemory();

        void setAICParameters_01(int aicID);

        void setAICParameters_02(int param_1);

        void setAICParameters_03(int param_1);

        void setAICParameters_04(int param_1);

        void setAICParameters_05(int param_1);

        void setAICParameters_06(int param_1);

        void setAICParameters_07(int param_1);

        void setAICParameters_08(int param_1);

        void setAICParameters_09(int param_1);

        void setAICParameters_10(int param_1);

        void setAICParameters_11(int param_1);

        void setAICParameters_12(int param_1);

        void setAICParameters_13(int param_1);

        void setAICParameters_14(int param_1);

        void setAICParameters_15(int param_1);

        void setAICParameters_16(int param_1);

        void clearPlayerDataInformationChunk();

        void setTargetForTribeBasedOnTargetChoiceLogic(int owner, int tribe);

        void updateTaxesAndRationsForAI(int playerID);

        void setFoodBuyPlan(int playerID);

        int getAIBuildInterval(int playerID);

        int getResourceRebuildDelay(int param_1);

        int aiFarmChoice(PlayerID playerID);

        int setNextFarmTypeToBuild(PlayerID playerID);

        uint aiShouldBuildFarm(PlayerID playerID);

        uint aiShouldBuildWoodcutter(PlayerID playerID);

        uint aiShouldBuildQuarry(PlayerID playerID);

        undefined4 aiRequiresExtraOxtethers(int playerID);

        uint aiShouldBuildIronMine(PlayerID playerID);

        uint aiShouldBuildPitchrig(PlayerID param_1);

        BOOLEnum shouldNotBeBuildingHovel(PlayerID playerID, CommandBuildingTypeInt param_2);

        BOOLEnum shouldWaitWithBuildingNegativeFearFactor(int param_1, CommandBuildingTypeInt param_2);

        BOOLEnum shouldWaitWithBuildingAPositiveFearFactor(int playerID, CommandBuildingTypeInt param_2);

        BOOLEnum destroyHouse(int playerID);

        undefined4 shouldDestroyWoodCutterUnk(int playerID);

        undefined4 destroyBuildingIfNoWorker(int buildingID);

        BOOLEnum shouldNotBuildMarketArmoryGranaryBarracksMercenarypost(int playerID, CommandBuildingTypeInt param_2);

        void planToBuyWhenLowOnResourceAndSnoozeBuildings(int playerID);

        void setupWorkshopProductionType(int playerID, int buildingID);

        void sellGoods(int playerID, ResourceTypeInt resourceType, int amount);

        BOOLEnum buyGoods(int playerID, ResourceTypeInt resourceType, int amount);

        AIUnitBehaviourTypeInt randomlySelectAttackUnitTypeToRecruit(int playerID);

        UnitTypeInt getUnitTypeForUnitBehaviourType(int playerID, AIUnitBehaviourTypeInt unitBehaviourType);

        void generateSiegeCreationInformation(int playerID, int buildingID, int unitID);

        void recruitEngineers(int playerID);

        int assignRequiredIdleEngineersToNewTribe(int playerID, int count);

        int addEngineersToSelection(int playerID, int unitCount);

        void addUnitsToTribe166(int playerID);

        void syncBehaviourType7UnitTribes(int param_1);

        void addUnitToTribeType10_moatdiggersUnk(int unitID);

        undefined4 unitIDIsRangedOrArmored(int unitID);

        int createTribeForUnitType(int playerID, int unitSelectionTypeIndex);

        int smallestTribeOfUnitType(int playerID, short* unitType);

        int getDefensiveTribeForUnit(int playerID, int unitID);

        int addUnitToSmallestBehaviourTypeTribe(short* playerID, undefined unitID, int aiUnitBehaviourType);

        void sendUnitsToKeep(undefined4 tribeID, int playerID);

        void sendUnitsToCampfire(int tribeID, int playerID);

        void digNearestMoat(int playerID);

        BOOLEnum canNavigateUnitsFromTileToTargetTile(int tribeID, int tile);

        void recruitHarrassingSiegeEngines(int playerID);

        void recruitSortieRangedUnits(int playerID);

        void recruitSortieMeleeUnits(int playerID);

        void instructTribe166ToMove(int playerID);

        void giveMoveCommandToSortieUnits(int playerID);

        void addBuildingToSomePlayerStateArray(int buildingID);

        int selectBuildingFromAListOfBuildingTypes(int playerID);

        int chooseRandomBuildingIDFromPlayersArrayOfBuildings(int playerID);

        int getTargetableBuildingForPlayerID(int playerID, int param_2);

        int selectRandomBuildingIDFromListOfBuildingTypes(int playerID, undefined4 param_2);

        undefined4 shouldWeAttackOrWaitForTeammates(int playerID);

        void setCurrentAttackStrength(int playerID);

        void setCurrentAttackRaidParameter(int playerID);

        void setAttackPrimeInfo(int playerID, int attackedPlayerID);

        void recomputeDistancesToAttackedKeepRelated(int playerID, int useBorderDistance);

        void recomputeAttackAIZone();

        void recomputeAIZonerLayer();

        void computeAndStoreShortestDistanceToKeepUnk(int playerID);

        void setNextMoveLocationForUnits(int playerID);

        void removeOrganismsAndSetMoveDestinationPairs(int playerID);

        void aiRetreatUnits(short* playerID);

        void sendUnitsToPlayerIDsKeepIfPossible(int playerID1, short* playerID2);

        void setRallyRelatedFlagOnAllAIAttackTribes(int param_1);

        void moveAttackTribesToLocations(short* playerID);

        void findAttackTribePositionAndPathToDefenses(int playerID);

        void makeUnitsGoDefensiveAndBackToSomeLocation(int param_1);

        void giveMoveCommandToAttackTribes(int playerID);

        uint aiChoiceAttForceRallyPercentage(int param_1);

        BOOLEnum percentageNonMovingTribesGTEAICSpecified(int playerID);

        BOOLEnum processAttForceRallyPercentage(int playerID);

        void useAITribe_0x12_toPlaceSiegeTentsAndAssignEngineers(CommandBuildingTypeInt playerID);

        void useAITribe_0xe_toPlaceTunnels(int playerID);

        void aiAttackWave_tribe13Unk(int param_1);

        void aiAttackWave_tribe12Unk(int param_1);

        void setTribe0xCtoAggressiveAndAttack(int playerID);

        void aiAttackWave_tribe11Unk(int playerID);

        void sendAITribe_0xf_toAttackPatrol(int playerID);

        void setTribe0x11ToAggressiveAndAttackIfConditionMet(int param_1);

        void setEightTribe0xc0TribesToAggressiveAndAttack(int playerID);

        void aiAttackWallsSmthUnk(int param_1);

        void setTribe0xbToAggressiveAndAttack(int playerID);

        void sendTribeToAttack(int playerID);

        void commandFourTribesToMove(int playerID);

        void clearOutdatedAITribes(int playerID);

        undefined4 giveSomeRaidCommand(int tribeIndex, int tribeType);

        void addRallyPointForTribe(int tribeID);

        void disbandAIPlayerSiegeUnits(int playerID);

        int countSiegeEngineUnits(int playerID);

        void aiAttackWaveSiegeUnitsUnk(int playerID);

        BOOLEnum yieldCowThrow(int playerID);

        BOOLEnum hasNoTroopsOrAllAreDiggers(int playerID);

        BOOLEnum hasNotEnoughSupplies(int playerID);

        void setAttackWillingnessUnk(int param_1);

        BOOLEnum teamIsWeakRelativeToEnemy(int playerID, BOOLEnum param_2);

        void destroyAnyBuildingInCategory(int playerID, AINervousDestroyBuildingCategoryInt buildingCategory);

        BOOLEnum isResourceLargerOrEqualThanMinimumGoodsRequiredAfterTrade(
            int playerID, ResourceTypeInt resourceType, int buffer);

        BOOLEnum aiOfTypeInCurrentGame(int param_1);

        int shareGoldAmongTeamMembers(int playerID, int gold);

        void PlayAnger1BikFromPlayer(int playerID);

        void PlayPlayerKilledBiksFromKilledAndKillerPlayer(int killerPlayerID, int killedPlayerID);

        void playThanksBikFromPlayerToPlayer(int playerID, int targetPlayerID);

        void setSomeTimeToNowIfInIngameMenu();

        void someChatMessageSelection();

        int getCurrentDesiredAttackRaidUnitCount(int aiType, int playerID);

        void renderDebugDataAiInfo(int x, int y, int width, int height);

        void setInitialAIC();

        void aiGiveCommandToOutpostTribesUnk(int tribeID, int tribeUID);

        void decideOnTribeAttackLocation(uint tribeID__moatWasHit);

        void requestGoods(int playerID, ResourceTypeInt resourceType, undefined4 amount);

        void aiCreateSiegeUnits(int playerID);

        void aiRecruitEngineerForOilDuty(int playerID);

        void assignUnitToATribe(int unitID);

        void addUnitToSmallestPatrolTribe(int unitID);

        void addUnitToDefensiveTroopsTribeUnk(int unitID);

        void addUnitToItsTribe(int unitID, int aiUnitBehaviourType);

        void ifHasTribe0SendUnitsToKeep(int playerID);

        void sendTribeAtOffset1ToCampfire(int playerID);

        void aiGiveOuterPatrolCommand(int playerID);

        void aiGiveRaidInstructions(int playerID);

        void sendTribeToAIVLocationSlot(int tribeID, AIVUnitTypeInt aivUnitType, int slotIndex);

        void computeAttackPossibilities(int playerID);

        void moveAttackingUnitsToNextRallyPoint(int playerID);

        undefined4 sendUnitsToAttackBreachedCastle(int attackingPlayerIndex);

        void updateAIStrengthState(int playerID, int aiRecruitUnitChoicePreference);

        void computeNervousness(int playerID);

        undefined4 determineAIPlayerHelp(int playerID, int requestedByPlayerID);

        BOOLEnum determineAIPlayerAttackRequestResponse(int playerID, undefined4 param_2, int requestedByPlayerID);

        void makeOutpostTribesAttack();

        void aiRecruitUnits(int playerID);

        void assignMoatDiggersUnk(int playerID);

        void addEngineersToTribe(int playerID);

        void redirectTunnelersUnk(int param_1);

        void sendRangedUnitTribesToAIVSlotsOrKeepIfNervous(int playerID);

        void sendCertainUnitTribesToAIVSlotsOrKeepIfNervousAndNotEnclosed(int playerID);

        void sendWallPatrolUnitTribesToAIVLocations(int playerID);

        void sendOilMenForOilPickupOrToAIVLocations(int playerID);

        void abortAttackAndGoIdle(int playerID);

        void recreateEngineersTribe(int playerID);

        void selectAttackTarget(int playerID);

        void aiBuyAndSellGoods(int playerID);

        void updateTribeLocations(int playerID);

        void updateAIPlayerState(int playerID);

        void updateAIBehaviour();

        BOOLEnum shouldNotBeBuildingGranary(int playerID, CommandBuildingTypeInt param_2);

        BOOLEnum shouldNotBeBuildingArmoury(PlayerID playerID, CommandBuildingTypeInt param_2);

        BOOLEnum shouldNotBuildKillingPits(int playerID, CommandBuildingTypeInt commandBuildingType);

        BOOLEnum woodCuttersHutWhileNoWoodAvailable(undefined4 playerID, CommandBuildingTypeInt param_2);
    };

    static_assert_cpp98_obj(sizeof(AICState) == 28048, AICState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(AICState, false, Address::SHC_3BB0A8C1_0x023FC8E8) pDAT_AICState;

} // namespace AI
} // namespace OpenSHC
