/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/RenderingDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Game/Skirmish/StartingResourceStructureInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/UI/MenuIDMenuElementAddressPair.hpp"
#include "OpenSHC/UI/MenuItem.hpp"
#include "OpenSHC/UI/Position.hpp"
#include "OpenSHC/UI/TextMessageBLLookupStruct.hpp"
#include "OpenSHC/UI/UC.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::Resources::ResourceTypeInt;
    using OpenSHC::Game::Skirmish::StartingResourceStructureInt;
    using OpenSHC::Map::Units::UnitTypeInt;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::UI::MenuIDMenuElementAddressPair;
    using OpenSHC::UI::MenuItem;
    using OpenSHC::UI::Position;
    using OpenSHC::UI::TextMessageBLLookupStruct;
    using OpenSHC::UI::UC;

#pragma pack(push, 1)
    // SIZE: 0x000557E4
    typedef struct RenderingDefinedData {

        int DAT_StartGold[3]; // 0x00000000 length: 12
        char ARRAY_MalePeasantSFXNames[128][32]; // 0x0000000C length: 4096
        char ARRAY_FemalePeasantSFXNames[128][32]; // 0x0000100C length: 4096
        UC ARRAY_UCArray[292]; // 0x0000200C length: 144832
        MenuItem MenuItems_Unknown_ManyThings[1]; // 0x000255CC length: 80
        MenuItem MenuItems_IntroLogos[2]; // 0x0002561C length: 160
        MenuItem MenuItems_IntroVideo[1]; // 0x000256BC length: 80
        MenuItem MenuItems_StartEnterName[1]; // 0x0002570C length: 80
        MenuItem MenuItems_MainMenu[13]; // 0x0002575C length: 1040
        MenuItem MenuItems_HistoricCampaignSelect[9]; // 0x00025B6C length: 720
        MenuItem MenuItems_UnusedEconomicGametypeSelect[8]; // 0x00025E3C length: 640
        MenuItem MenuItems_CustomScenarios[8]; // 0x000260BC length: 640
        MenuItem MenuItems_UnusedSomeMissionStartUnk[4]; // 0x0002633C length: 320
        MenuItem MenuItems_HistoricMissionSelect[10]; // 0x0002647C length: 800
        MenuItem MenuItems_UnusedEconomicMissionSelect[11]; // 0x0002679C length: 880
        MenuItem MenuItems_UnusedSetName[5]; // 0x00026B0C length: 400
        MenuItem MenuItems_UnusedOldTitleMenu[4]; // 0x00026C9C length: 320
        MenuItem MenuItems_LobbyMenu[93]; // 0x00026DDC length: 7440
        MenuItem MenuItems_SkirmishConnectionOptions[5]; // 0x00028AEC length: 400
        MenuItem MenuItems_SkirmishPlayOptions[9]; // 0x00028C7C length: 720
        MenuItem MenuItems_SendMapTo[4]; // 0x00028F4C length: 320
        MenuItem MenuItems_ReceiveMapFrom[3]; // 0x0002908C length: 240
        MenuItem MenuItems_UnusedSelectRandomNumberOfEnemies[9]; // 0x0002917C length: 720
        MenuItem MenuItems_ChooseRandomNumberOfEnemies[11]; // 0x0002944C length: 880
        MenuItem MenuItems_SelectCrusade[6]; // 0x000297BC length: 480
        MenuItem MenuItems_BasicAiLordSelect[11]; // 0x0002999C length: 880
        MenuItem MenuItems_ExtendedAiLordSelect[19]; // 0x00029D0C length: 1520
        MenuItem MenuItems_Roundtable[25]; // 0x0002A2FC length: 2000
        MenuItem MenuItems_OverlaySlider[3]; // 0x0002AACC length: 240
        MenuItem MenuItems_UnusedWinCondition[13]; // 0x0002ABBC length: 1040
        MenuItem MenuItems_SingleplayerMapChoice[46]; // 0x0002AFCC length: 3680
        MenuItem MenuItems_MapEditorProperties[16]; // 0x0002BE2C length: 1280
        MenuItem MenuItems_NewMapMaptype[8]; // 0x0002C32C length: 640
        MenuItem MenuItems_NewMapMapsize[7]; // 0x0002C5AC length: 560
        MenuItem MenuItems_UnusedChooseAvailableKeeps[14]; // 0x0002C7DC length: 1120
        MenuItem MenuItems_UnusedChooseGameType[9]; // 0x0002CC3C length: 720
        MenuItem MenuItems_UnusedCreateSiege[10]; // 0x0002CF0C length: 800
        MenuItem MenuItems_Unknown26CampaignRelatedUnk[1]; // 0x0002D22C length: 80
        MenuItem MenuItems_Unknown27CampaignUnk[3]; // 0x0002D27C length: 240
        MenuItem MenuItems_UnusedExtremeAd[1]; // 0x0002D36C length: 80
        MenuItem MenuItems_HistoricCampaignIntroAndMissionPicture[1]; // 0x0002D3BC length: 80
        MenuItem MenuItems_HistoricCampaignOutroAndMissionIntro[1]; // 0x0002D40C length: 80
        MenuItem MenuItems_ScenarioDescription[12]; // 0x0002D45C length: 960
        MenuItem MenuItems_CrusadeMissionIntro[4]; // 0x0002D81C length: 320
        MenuItem MenuItems_CrusadeMap[7]; // 0x0002D95C length: 560
        MenuItem MenuItems_RankingGames[28]; // 0x0002DB8C length: 2240
        MenuItem MenuItems_CrusadeEndscreen[3]; // 0x0002E44C length: 240
        MenuItem MenuItems_MissionFinishedTransition[61]; // 0x0002E53C length: 4880
        MenuItem MenuItems_GameLostUnk[61]; // 0x0002F84C length: 4880
        MenuItem MenuItems_ChooseNetworkServiceProvider[37]; // 0x00030B5C length: 2960
        MenuItem MenuItems_FindingNetworkSessions[20]; // 0x000316EC length: 1600
        MenuItem MenuItems_WaitingForHost[4]; // 0x00031D2C length: 320
        MenuItem MenuItems_BuildMenu[297]; // 0x00031E6C length: 23760
        MenuItem MenuItems_BuildingAndStatusMenu[295]; // 0x00037B3C length: 23600
        MenuItem MenuItems_PauseMenu[10]; // 0x0003D76C length: 800
        MenuItem MenuItems_PauseMenuOptions[6]; // 0x0003DA8C length: 480
        MenuItem MenuItems_MainMenuOptions[10]; // 0x0003DC6C length: 800
        MenuItem MenuItems_GameplayOptions[8]; // 0x0003DF8C length: 640
        MenuItem MenuItems_VideoOptions[10]; // 0x0003E20C length: 800
        MenuItem MenuItems_SoundOptions[16]; // 0x0003E52C length: 1280
        MenuItem MenuItems_IdentityOptions[11]; // 0x0003EA2C length: 880
        MenuItem MenuItems_EnterTitleOnGameStart[5]; // 0x0003ED9C length: 400
        MenuItem MenuItems_NetworkOptions[3]; // 0x0003EF2C length: 240
        MenuItem MenuItems_LoadMap[27]; // 0x0003F01C length: 2160
        MenuItem MenuItems_SaveMap[29]; // 0x0003F88C length: 2320
        MenuItem MenuItem_YesNoDialog[4]; // 0x0004019C length: 320
        MenuItem MenuItems_QuitDialog[4]; // 0x000402DC length: 320
        MenuItem MenuItems_DeleteGameRecord[4]; // 0x0004041C length: 320
        MenuItem MenuItems_TacticalPowerBar[2]; // 0x0004055C length: 160
        MenuItem MenuItems_ProgressBarBox[2]; // 0x000405FC length: 160
        MenuItem MenuItems_Chat[45]; // 0x0004069C length: 3600
        MenuItem MenuItems_Allies[17]; // 0x000414AC length: 1360
        MenuItem MenuItem_AlliesOrder[12]; // 0x000419FC length: 960
        MenuItem MenuItems_AlliesRequestGoods[32]; // 0x00041DBC length: 2560
        MenuItem MenuItems_AlliesSendGoods[32]; // 0x000427BC length: 2560
        MenuItem MenuItems_GreatestLord[7]; // 0x000431BC length: 560
        MenuItem MenuItems_OnlineQuitGame[5]; // 0x000433EC length: 400
        MenuItem MenuItems_OnlineVoteQuitGame[4]; // 0x0004357C length: 320
        MenuItem MenuItems_DebugModals[2]; // 0x000436BC length: 160
        MenuItem MenuItems_DisplayAiLordMessage[1]; // 0x0004375C length: 80
        MenuItem MenuItems_TutorialBox[4]; // 0x000437AC length: 320
        MenuItem MenuItems_TutorialBoxWithLeave[5]; // 0x000438EC length: 400
        MenuItem MenuItems_UnusedHelpTextEditor[33]; // 0x00043A7C length: 2640
        MenuItem MenuItems_BuildingHelpText[9]; // 0x000444CC length: 720
        MenuItem MenuItems_InGameHelpText[9]; // 0x0004479C length: 720
        MenuItem MenuItems_DisplayScenarioHelpText[8]; // 0x00044A6C length: 640
        MenuItem MenuItems_Credits[1]; // 0x00044CEC length: 80
        MenuItem MenuItems_MapDescriptionEditor[12]; // 0x00044D3C length: 960
        MenuItem MenuItems_UnusedDemoBuyItScreen[6]; // 0x000450FC length: 480
        MenuItem MenuItems_EditorMapTypeQuickChange[8]; // 0x000452DC length: 640
        MenuItem MenuItems_Empty10[1]; // 0x0004555C length: 80
        MenuItem MenuItems_Empty11[1]; // 0x000455AC length: 80
        MenuItem MenuItems_Menu_MapEditorLandscaping[100]; // 0x000455FC length: 8000
        MenuItem MenuItems_EditScenario[44]; // 0x0004753C length: 3520
        MenuItem MenuItems_UnusedChooseMessageBox[21]; // 0x000482FC length: 1680
        MenuItem MenuItems_TraderSettings[23]; // 0x0004898C length: 1840
        MenuItem MenuItems_StartGoods[23]; // 0x000490BC length: 1840
        MenuItem MenuItems_UnusedSiegeAttackingForceUnk[21]; // 0x000497EC length: 1680
        MenuItem MenuItems_NewInvasion[37]; // 0x00049E7C length: 2960
        MenuItem MenuItems_UnusedCreateTimedMessageEvent[36]; // 0x0004AA0C length: 2880
        MenuItem MenuItems_NewEvent[9]; // 0x0004B54C length: 720
        MenuItem MenuItems_NewEventCondition[50]; // 0x0004B81C length: 4000
        MenuItem MenuItems_NewEventAction[28]; // 0x0004C7BC length: 2240
        MenuItem MenuItems_UnusedCreateMessageEvent[32]; // 0x0004D07C length: 2560
        MenuItem MenuItems_BuildingAvailability[66]; // 0x0004DA7C length: 5280
        MenuItem MenuItems_DisableEuroTroops[10]; // 0x0004EF1C length: 800
        MenuItem MenuItems_DisableArabTroops[10]; // 0x0004F23C length: 800
        MenuItem MenuItems_DisableWeapon[9]; // 0x0004F55C length: 720
        MenuItem MenuItems_TriggerInvasion[33]; // 0x0004F82C length: 2640
        MenuItem MenuItems_TriggerEventOrInvasion[5]; // 0x0005027C length: 400
        MenuItem MenuItems_TriggerEvent[13]; // 0x0005040C length: 1040
        MenuItem MenuItems_TriggerEventSlider[5]; // 0x0005081C length: 400
        MenuIDMenuElementAddressPair DAT_MenuViewIDMenuMapping[51]; // 0x000509AC length: 408
        TextMessageBLLookupStruct DAT_TextMessageLookupTable[422]; // 0x00050B44 length: 6752
        int field114_0x525a4[27]; // 0x000525A4 length: 108
        uint DAT_ColorTable1[9]; // 0x00052610 length: 36
        undefined1 padding_0x52634[100]; // 0x00052634 length: 100
        BGR24 DAT_ColorArray[9]; // 0x00052698 length: 36
        undefined1 padding_0x526bc[208]; // 0x000526BC length: 208
        StartingResourceStructureInt DAT_StartGoods[3]; // 0x0005278C length: 300
        int DAT_HumanAdvantageArray; // 0x000528B8 length: 4
        int field427_0x528bc; // 0x000528BC length: 4
        int field428_0x528c0; // 0x000528C0 length: 4
        int field429_0x528c4; // 0x000528C4 length: 4
        int field430_0x528c8; // 0x000528C8 length: 4
        int field431_0x528cc; // 0x000528CC length: 4
        int DAT_AIAdvantageArray; // 0x000528D0 length: 4
        int field433_0x528d4; // 0x000528D4 length: 4
        int field434_0x528d8; // 0x000528D8 length: 4
        int field435_0x528dc; // 0x000528DC length: 4
        int field436_0x528e0; // 0x000528E0 length: 4
        int field437_0x528e4; // 0x000528E4 length: 4
        undefined1 padding_0x528e8[4]; // 0x000528E8 length: 4
        int DAT_StartingTroops[20][3][20]; // 0x000528EC length: 4800
        undefined1 padding_0x53bac[8]; // 0x00053BAC length: 8
        int field451_0x53bb4[24]; // 0x00053BB4 length: 96
        int DAT_StartGoldPerFairnessLevel[3][5][2]; // 0x00053C14 length: 120
        int field453_0x53c8c[20][20]; // 0x00053C8C length: 1600
        undefined1 padding_0x542cc[440]; // 0x000542CC length: 440
        int field894_0x54484[18][10]; // 0x00054484 length: 720
        int DAT_BuyPricePerResource[26]; // 0x00054754 length: 104
        int DAT_SalesPricePerResource[25]; // 0x000547BC length: 100
        int DAT_NoRushTicks[5]; // 0x00054820 length: 20
        int DAT_TroopTypeValuesPart; // 0x00054834 length: 4
        undefined1 padding_0x54838[84]; // 0x00054838 length: 84
        int TROOP_VALUE_ARCHER; // 0x0005488C length: 4
        int TROOP_VALUE_CROSSBOW; // 0x00054890 length: 4
        int TROOP_VALUE_SPEARMAN; // 0x00054894 length: 4
        int TROOP_VALUE_PIKEMAN; // 0x00054898 length: 4
        int TROOP_VALUE_MACEMAN; // 0x0005489C length: 4
        int TROOP_VALUE_SWORDSMAN; // 0x000548A0 length: 4
        int TROOP_VALUE_KNIGHT; // 0x000548A4 length: 4
        int TROOP_VALUE_LADDERMAN; // 0x000548A8 length: 4
        int TROOP_VALUE_ENGINEER; // 0x000548AC length: 4
        int TROOP_VALUE_MONK; // 0x000548B0 length: 4
        int TROOP_VALUE_TUNNELER; // 0x000548B4 length: 4
        int TROOP_VALUE_A_ARCHER; // 0x000548B8 length: 4
        int TROOP_VALUE_SLAVE; // 0x000548BC length: 4
        int TROOP_VALUE_SLINGER; // 0x000548C0 length: 4
        int TROOP_VALUE_ASSASSIN; // 0x000548C4 length: 4
        int TROOP_VALUE_HARCHER; // 0x000548C8 length: 4
        int TROOP_VALUE_A_SWORDSMAN; // 0x000548CC length: 4
        int TROOP_VALUE_FIRETHROWER; // 0x000548D0 length: 4
        int TROOP_VALUE_S_FBALLISTA; // 0x000548D4 length: 4
        int TROOP_VALUE_CATAPULT; // 0x000548D8 length: 4
        int field1003_0x548dc; // 0x000548DC length: 4
        int field1004_0x548e0; // 0x000548E0 length: 4
        int field1005_0x548e4; // 0x000548E4 length: 4
        int field1006_0x548e8; // 0x000548E8 length: 4
        int field1007_0x548ec; // 0x000548EC length: 4
        int field1008_0x548f0; // 0x000548F0 length: 4
        int field1009_0x548f4; // 0x000548F4 length: 4
        int field1010_0x548f8; // 0x000548F8 length: 4
        int field1011_0x548fc; // 0x000548FC length: 4
        int field1012_0x54900; // 0x00054900 length: 4
        int field1013_0x54904; // 0x00054904 length: 4
        int field1014_0x54908; // 0x00054908 length: 4
        int field1015_0x5490c; // 0x0005490C length: 4
        int field1016_0x54910; // 0x00054910 length: 4
        int field1017_0x54914; // 0x00054914 length: 4
        int field1018_0x54918; // 0x00054918 length: 4
        int field1019_0x5491c; // 0x0005491C length: 4
        int field1020_0x54920; // 0x00054920 length: 4
        int field1021_0x54924; // 0x00054924 length: 4
        int field1022_0x54928; // 0x00054928 length: 4
        int field1023_0x5492c; // 0x0005492C length: 4
        int field1024_0x54930; // 0x00054930 length: 4
        int field1025_0x54934; // 0x00054934 length: 4
        int field1026_0x54938; // 0x00054938 length: 4
        int field1027_0x5493c[24]; // 0x0005493C length: 96
        int field1028_0x5499c[24]; // 0x0005499C length: 96
        int field1029_0x549fc[24]; // 0x000549FC length: 96
        UnitTypeInt field1030_0x54a5c[28]; // 0x00054A5C length: 112
        char* DAT_ChimpTgxArray[70]; // 0x00054ACC length: 280
        char* DAT_ChimpTgxSketchArray[80]; // 0x00054BE4 length: 320
        char* DAT_ChimpHelpArray[70]; // 0x00054D24 length: 280
        char* DAT_ChimpBikArray[70]; // 0x00054E3C length: 280
        char* DAT_BuildingHelpArray[108]; // 0x00054F54 length: 432
        char* DAT_BuildingBikArray[108]; // 0x00055104 length: 432
        char* DAT_BuildingTgxSketchArray[108]; // 0x000552B4 length: 432
        ResourceTypeInt field1038_0x55464[8]; // 0x00055464 length: 32
        int field1039_0x55484[8]; // 0x00055484 length: 32
        Position DAT_StockpileIconsPositionNudges[8]; // 0x000554A4 length: 64
        int field1041_0x554e4[8]; // 0x000554E4 length: 32
        int field1042_0x55504[8]; // 0x00055504 length: 32
        Position field1043_0x55524[8]; // 0x00055524 length: 64
        int DAT_MarketStonksOrder[20]; // 0x00055564 length: 80
        ResourceTypeInt DAT_FoodTypes[8]; // 0x000555B4 length: 32
        int DAT_RawResourceTypes[4]; // 0x000555D4 length: 16
        int field1047_0x555e4[8]; // 0x000555E4 length: 32
        Position field1048_0x55604[25]; // 0x00055604 length: 200
        int field1049_0x556cc[7][3]; // 0x000556CC length: 84
        int field1050_0x55720[4]; // 0x00055720 length: 16
        undefined1 padding_0x55730[68]; // 0x00055730 length: 68
        UnitTypeInt DAT_UnitTypeGroups[3][9]; // 0x00055774 length: 108
        int field1120_0x557e0; // 0x000557E0 length: 4

    } RenderingDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(RenderingDefinedData) == 350180, RenderingDefinedData);
} // namespace Game
} // namespace OpenSHC
