/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/MapPropertiesState.hpp'
*/

#pragma once

#include "OpenSHC/AI/Siege/SiegeInformation.hpp"
#include "OpenSHC/DE/SHCDE/eMappersInt.hpp"
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

    using OpenSHC::AI::Siege::SiegeInformation;
    using OpenSHC::DE::SHCDE::eMappersInt;
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
        SiegeInformation SEC_SiegeInformation; // 0x000000EC length: 80
        SiegeGameModeRelatedSection SEC_Section1067; // 0x0000013C length: 28
        int SEC_StartingPopularity; // 0x00000158 length: 4
        short SEC_BuildingAvailability[100]; // 0x0000015C length: 200
        undefined4 field8_0x224; // 0x00000224 length: 4
        short buildingAvailabilityRelatedFlags[380]; // 0x00000228 length: 760
        short field10_0x520; // 0x00000520 length: 2
        short field11_0x522; // 0x00000522 length: 2
        short field12_0x524; // 0x00000524 length: 2
        short field13_0x526; // 0x00000526 length: 2
        short field14_0x528; // 0x00000528 length: 2
        short field15_0x52a; // 0x0000052A length: 2
        short field16_0x52c; // 0x0000052C length: 2
        short field17_0x52e; // 0x0000052E length: 2
        short field18_0x530; // 0x00000530 length: 2
        short field19_0x532; // 0x00000532 length: 2
        short field20_0x534; // 0x00000534 length: 2
        short field21_0x536; // 0x00000536 length: 2
        short field22_0x538; // 0x00000538 length: 2
        short field23_0x53a; // 0x0000053A length: 2
        short field24_0x53c; // 0x0000053C length: 2
        short field25_0x53e; // 0x0000053E length: 2
        short field26_0x540; // 0x00000540 length: 2
        short field27_0x542; // 0x00000542 length: 2
        short field28_0x544; // 0x00000544 length: 2
        short field29_0x546; // 0x00000546 length: 2
        short field30_0x548; // 0x00000548 length: 2
        short field31_0x54a; // 0x0000054A length: 2
        short field32_0x54c; // 0x0000054C length: 2
        short field33_0x54e; // 0x0000054E length: 2
        short field34_0x550; // 0x00000550 length: 2
        short field35_0x552; // 0x00000552 length: 2
        short field36_0x554; // 0x00000554 length: 2
        short field37_0x556; // 0x00000556 length: 2
        short field38_0x558; // 0x00000558 length: 2
        short field39_0x55a; // 0x0000055A length: 2
        short field40_0x55c; // 0x0000055C length: 2
        short field41_0x55e; // 0x0000055E length: 2
        short field42_0x560; // 0x00000560 length: 2
        short field43_0x562; // 0x00000562 length: 2
        short field44_0x564; // 0x00000564 length: 2
        short field45_0x566; // 0x00000566 length: 2
        short field46_0x568; // 0x00000568 length: 2
        short field47_0x56a; // 0x0000056A length: 2
        short field48_0x56c; // 0x0000056C length: 2
        short field49_0x56e; // 0x0000056E length: 2
        short field50_0x570; // 0x00000570 length: 2
        short field51_0x572; // 0x00000572 length: 2
        short field52_0x574; // 0x00000574 length: 2
        short field53_0x576; // 0x00000576 length: 2
        short field54_0x578; // 0x00000578 length: 2
        short field55_0x57a; // 0x0000057A length: 2
        short field56_0x57c; // 0x0000057C length: 2
        short field57_0x57e; // 0x0000057E length: 2
        undefined1 padding_0x580[2]; // 0x00000580 length: 2
        BarracksRecruitabilityShort barracksRecruitability; // 0x00000582 length: 14
        short SEC_MercRecruitable[7]; // 0x00000590 length: 14
        short SEC_XbowProducible_save; // 0x0000059E length: 2
        short SEC_BowProducible_save; // 0x000005A0 length: 2
        short SEC_PikeProducible_save; // 0x000005A2 length: 2
        short SEC_SpearProducible_save; // 0x000005A4 length: 2
        short SEC_SwordProducible_save; // 0x000005A6 length: 2
        short SEC_MaceProducible_save; // 0x000005A8 length: 2
        undefined1 padding_0x5aa[2]; // 0x000005AA length: 2
        int SEC_EventsCount; // 0x000005AC length: 4
        InGameEventUnionVersion SEC_Events[200]; // 0x000005B0 length: 45600
        InGameEventExtra SEC_EventsExtra[200]; // 0x0000B7D0 length: 32000
        TradeableResourcesSection SEC_Section1065; // 0x000134D0 length: 100
        int scenarionMissionType; // 0x00013534 length: 4
        MapType2Int SEC_U3_MapType2_1; // 0x00013538 length: 4
        MapType2Int scenarioMissionSiegeOrInvasion; // 0x0001353C length: 4
        undefined4 SEC_Section1090; // 0x00013540 length: 4
        undefined4 SEC_Section1080; // 0x00013544 length: 4
        undefined4 SEC_Section1081; // 0x00013548 length: 4
        undefined1 padding_0x1354c[16]; // 0x0001354C length: 16
        undefined4 field96_0x1355c; // 0x0001355C length: 4
        int field97_0x13560; // 0x00013560 length: 4
        undefined4 DAT_CurrentEventID; // 0x00013564 length: 4
        undefined4 field99_0x13568; // 0x00013568 length: 4
        undefined1 padding_0x1356c[4]; // 0x0001356C length: 4
        undefined4 invasionTroopIndex; // 0x00013570 length: 4
        int DAT_BuildingAvailabilityScrollbarOffset; // 0x00013574 length: 4
        undefined4 flag; // 0x00013578 length: 4
        undefined4 offset; // 0x0001357C length: 4
        undefined4 indexStored; // 0x00013580 length: 4
        undefined1 padding_0x13584[8]; // 0x00013584 length: 8
        undefined4 value; // 0x0001358C length: 4
        undefined4 field118_0x13590; // 0x00013590 length: 4
        undefined1 padding_0x13594[8]; // 0x00013594 length: 8
        undefined4 total; // 0x0001359C length: 4
        int unknownArray_01[1000]; // 0x000135A0 length: 4000
        undefined4 year_copy; // 0x00014540 length: 4
        undefined4 DAT_MapEditorUnitPointsSum; // 0x00014544 length: 4
        undefined4 DAT_InvasionEventItemUnitCountSum; // 0x00014548 length: 4
        undefined1 padding_0x1454c[8]; // 0x0001454C length: 8
        undefined4 field140_0x14554; // 0x00014554 length: 4
        undefined4 field141_0x14558; // 0x00014558 length: 4
        undefined4 field142_0x1455c; // 0x0001455C length: 4
        undefined4 field143_0x14560; // 0x00014560 length: 4
        undefined4 field144_0x14564; // 0x00014564 length: 4
        undefined4 field145_0x14568; // 0x00014568 length: 4
        undefined4 field146_0x1456c; // 0x0001456C length: 4
        undefined4 field147_0x14570; // 0x00014570 length: 4
        undefined4 field148_0x14574; // 0x00014574 length: 4
        undefined4 field149_0x14578; // 0x00014578 length: 4
        undefined4 field150_0x1457c; // 0x0001457C length: 4
        undefined4 field151_0x14580; // 0x00014580 length: 4
        undefined4 field152_0x14584; // 0x00014584 length: 4
        undefined4 field153_0x14588; // 0x00014588 length: 4
        undefined4 field154_0x1458c; // 0x0001458C length: 4
        undefined4 field155_0x14590; // 0x00014590 length: 4
        undefined4 field156_0x14594; // 0x00014594 length: 4
        undefined1 padding_0x14598[4]; // 0x00014598 length: 4
        undefined4 field161_0x1459c; // 0x0001459C length: 4
        undefined4 field162_0x145a0; // 0x000145A0 length: 4
        undefined4 field163_0x145a4; // 0x000145A4 length: 4
        undefined4 field164_0x145a8; // 0x000145A8 length: 4
        undefined4 field165_0x145ac; // 0x000145AC length: 4
        undefined4 field166_0x145b0; // 0x000145B0 length: 4
        undefined1 padding_0x145b4[4]; // 0x000145B4 length: 4
        undefined4 field171_0x145b8; // 0x000145B8 length: 4
        undefined4 field172_0x145bc; // 0x000145BC length: 4
        undefined4 field173_0x145c0; // 0x000145C0 length: 4
        undefined4 field174_0x145c4; // 0x000145C4 length: 4
        undefined4 field175_0x145c8; // 0x000145C8 length: 4
        undefined1 padding_0x145cc[4]; // 0x000145CC length: 4
        undefined4 field180_0x145d0; // 0x000145D0 length: 4
        undefined4 field181_0x145d4; // 0x000145D4 length: 4
        undefined1 padding_0x145d8[4]; // 0x000145D8 length: 4
        undefined4 eventType; // 0x000145DC length: 4
        IngameEventHeader invasionEvent; // 0x000145E0 length: 16
        IngameInvasionEventItemContent invasionEventContent; // 0x000145F0 length: 176

    private:
        MapPropertiesState(MapPropertiesState const&);
        void operator=(MapPropertiesState const&);

        MapPropertiesState();
        ~MapPropertiesState();

    public:
        BOOLEnum isParam1LessThan21(int param_1);

        void importTradingCosts();

        undefined4 mapHasCertainEvent();

        int getEventIDForTimeUntilDefeatEventType();

        void FUN_004b7930();

        void meth_0x4b7980();

        void sumUnitPoints();

        void sumUnitCounts();

        void meth_0x4ba7d0();

        void meth_0x4ba8b0(int param_1);

        void commitBuildingAvailability();

        BOOLEnum isMapperAvailable(eMappersInt param_1);

        int FUN_004bb0b0(int param_1);

        void resetEuroUnitRestrictions();

        void meth_0x4bb990();

        void openEventTriggerMenu(undefined4 eventType);

        void sumInvasionEventUnitCount();

        void tweakMonthAndYearBasedOnSection1047();

        void FUN_004bc1c0(int param_1, int param_2, int param_3, int param_4, int param_5, undefined4 param_6);

        void meth_0x4bd980();

        void meth_0x4bda80(int param_1);

        void computeSomeKindOfMissionCompletionScore();

        void setStartingYearAndStartingResources();

        void meth_0x4beb20();

        void meth_0x4c1320();

        void meth_0x4c13f0();

        void FUN_004c2280();

        void processSingleplayerEvents();

        void loadMap(char* mapName);

        void FUN_004c6820(char* param_1);

        void FUN_004c6880(int missionNumber);
    };

    static_assert_cpp98_obj(sizeof(MapPropertiesState) == 83616, MapPropertiesState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(MapPropertiesState, false, Address::SHC_3BB0A8C1_0x01653858) pDAT_MapPropertiesState;

} // namespace Map
} // namespace OpenSHC
