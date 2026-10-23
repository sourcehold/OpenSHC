/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/MapPropertiesState.hpp'
*/

#pragma once

#include "OpenSHC/AI/Siege/SiegeUnitCounts.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/Scenario/BarracksRecruitabilityShort.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventExtra.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.hpp"
#include "OpenSHC/Game/ScenarioEvents/IngameEventHeader.hpp"
#include "OpenSHC/Game/ScenarioEvents/IngameInvasionEventItemContent.hpp"
#include "OpenSHC/Game/Siege/SiegeGameModeRelatedSection.hpp"
#include "OpenSHC/Game/TradeableResourcesSection.hpp"
#include "OpenSHC/Map/MapType2Int.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::AI::Siege::SiegeUnitCounts;
    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::TradeableResourcesSection;
    using OpenSHC::Game::Scenario::BarracksRecruitabilityShort;
    using OpenSHC::Game::ScenarioEvents::InGameEventExtra;
    using OpenSHC::Game::ScenarioEvents::IngameEventHeader;
    using OpenSHC::Game::ScenarioEvents::InGameEventUnionVersion;
    using OpenSHC::Game::ScenarioEvents::IngameInvasionEventItemContent;
    using OpenSHC::Game::Siege::SiegeGameModeRelatedSection;
    using OpenSHC::Map::MapType2Int;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x000146A0
    class MapPropertiesState {
    public:
        uchar SEC_Section1089[128]; // 0x00000000 length: 128
        int SEC_StartingYear; // 0x00000080 length: 4
        int SEC_StartingMonth; // 0x00000084 length: 4
        int SEC_StartingResources[25]; // 0x00000088 length: 100
        SiegeUnitCounts SEC_SiegeInformation; // 0x000000EC length: 80
        SiegeGameModeRelatedSection SEC_Section1067; // 0x0000013C length: 28
        int SEC_StartingPopularity; // 0x00000158 length: 4
        short buildingAvailability[100]; // 0x0000015C length: 200
        undefined4 buildingAvailabilityRowCount; // 0x00000224 length: 4
        short buildingAvailabilityRelatedFlags[380]; // 0x00000228 length: 760
        short buildingAvailabilityArray2[49]; // 0x00000520 length: 98
        BarracksRecruitabilityShort barracksRecruitability; // 0x00000582 length: 14
        short SEC_MercRecruitable[7]; // 0x00000590 length: 14
        short SEC_XbowProducible_save; // 0x0000059E length: 2
        short SEC_BowProducible_save; // 0x000005A0 length: 2
        short SEC_PikeProducible_save; // 0x000005A2 length: 2
        short SEC_SpearProducible_save; // 0x000005A4 length: 2
        short SEC_SwordProducible_save; // 0x000005A6 length: 2
        short SEC_MaceProducible_save; // 0x000005A8 length: 2
        undefined1 padding_0x5aa[2]; // 0x000005AA length: 2
        int eventsCount; // 0x000005AC length: 4
        InGameEventUnionVersion scenarioEvents[200]; // 0x000005B0 length: 45600
        InGameEventExtra SEC_EventsExtra[200]; // 0x0000B7D0 length: 32000
        TradeableResourcesSection SEC_Section1065; // 0x000134D0 length: 100
        int scenarionMissionType; // 0x00013534 length: 4
        MapType2Int SEC_U3_MapType2_1; // 0x00013538 length: 4
        MapType2Int scenarioMissionSiegeOrInvasion; // 0x0001353C length: 4
        undefined4 SEC_Section1090; // 0x00013540 length: 4
        undefined4 SEC_Section1080; // 0x00013544 length: 4
        undefined4 SEC_Section1081; // 0x00013548 length: 4
        undefined1 padding_0x1354c[4]; // 0x0001354C length: 4
        int visibleRowCount; // 0x00013550 length: 4
        undefined1 padding_0x13554[8]; // 0x00013554 length: 8
        int eventListScrollOffset; // 0x0001355C length: 4
        int eventListSelection; // 0x00013560 length: 4
        undefined4 currentEventID; // 0x00013564 length: 4
        undefined4 editedEventType; // 0x00013568 length: 4
        int field_0x1356c; // 0x0001356C length: 4
        undefined4 invasionTroopIndex; // 0x00013570 length: 4
        int DAT_BuildingAvailabilityScrollbarOffset; // 0x00013574 length: 4
        undefined4 flag; // 0x00013578 length: 4
        undefined4 offset; // 0x0001357C length: 4
        undefined4 indexStored; // 0x00013580 length: 4
        int selectedAbsoluteIndex; // 0x00013584 length: 4
        dword selectionTime; // 0x00013588 length: 4
        undefined4 value; // 0x0001358C length: 4
        undefined4 field57_0x13590; // 0x00013590 length: 4
        undefined1 padding_0x13594[8]; // 0x00013594 length: 8
        undefined4 total; // 0x0001359C length: 4
        int unknownArray_01[1000]; // 0x000135A0 length: 4000
        undefined4 year_copy; // 0x00014540 length: 4
        undefined4 DAT_MapEditorUnitPointsSum; // 0x00014544 length: 4
        undefined4 DAT_InvasionEventItemUnitCountSum; // 0x00014548 length: 4
        undefined1 padding_0x1454c[8]; // 0x0001454C length: 8
        undefined4 missionScore; // 0x00014554 length: 4
        undefined4 monthsRemaining; // 0x00014558 length: 4
        undefined4 timeBonusScore; // 0x0001455C length: 4
        int objectiveGoodsCount; // 0x00014560 length: 4
        int objectiveGoodsSurplus[7]; // 0x00014564 length: 28
        int objectiveGoodsScore[7]; // 0x00014580 length: 28
        int objectiveGoodsType[7]; // 0x0001459C length: 28
        int troopSurvivalScore; // 0x000145B8 length: 4
        int troopLossPercent; // 0x000145BC length: 4
        int enemyTroopValueTotal; // 0x000145C0 length: 4
        int enemyTroopValueSurviving; // 0x000145C4 length: 4
        int enemyTroopValueLost; // 0x000145C8 length: 4
        int sliderPopupDelay; // 0x000145CC length: 4
        int sliderPopupX; // 0x000145D0 length: 4
        int sliderPopupY; // 0x000145D4 length: 4
        undefined4 field133_0x145d8; // 0x000145D8 length: 4
        undefined4 eventType; // 0x000145DC length: 4
        IngameEventHeader invasionEvent; // 0x000145E0 length: 16
        IngameInvasionEventItemContent invasionEventContent; // 0x000145F0 length: 176

    private:
        MapPropertiesState(MapPropertiesState const&);
        void operator=(MapPropertiesState const&);

    public:
        MapPropertiesState() {};
        ~MapPropertiesState() {};

        BOOLEnum isValueInRangeOneToTwenty(int param_1);

        void importTradingCosts();

        BOOLEnum mapHasCertainEvent();

        int getEventIDForTimeUntilDefeatEventType();

        void activateScenarioTypeEvents();

        void determineScenarioMissionTypeAndResetEvents();

        int getDifficultyMultipliedValue(int param_1);

        int sumUnitPoints();

        void sumUnitCounts();

        void sortEventsByDate();

        void removeEventAtIndex(int param_1);

        void commitBuildingAvailability();

        BOOLEnum isMapperAvailable(MappersEnum param_1);

        int isMercRecruitableForBuildingType(int param_1);

        void resetEuroUnitRestrictions();

        void pruneInvalidEventTriggerLinks();

        void openEventTriggerMenu(undefined4 eventType);

        int sumInvasionEventUnitCount();

        void adjustEventMonthAndYearForSection1047();

        void spawnAttackWaveForPlayer(
            int param_1, int param_2, int param_3, int param_4, int param_5, undefined4 param_6);

        void createScenarioEventForNextMonth();

        void createChainedMissionOutcomeEvents(int param_1);

        void computeMissionCompletionScore();

        void setStartingYearAndStartingResources();

        void updateEventYearsAndCommitBuildingAvailability();

        void removeProcessedInvasionEvents();

        void spawnInvasionEventAttackWave();

        void updateMilitaryCampaignMissionState();

        void loadMapSiegeHeaderSections(char* param_1);

        void processSingleplayerEvents();

        void loadMap(char* mapName);

        void loadMapSiegeHeaderForMissionIndex(char* param_1);

        void loadMissionMapAndSetLord(int missionNumber);
    };

    static_assert_cpp98_obj(sizeof(MapPropertiesState) == 83616, MapPropertiesState);

#pragma pack(pop)

} // namespace Map
} // namespace OpenSHC
