/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI.func.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/UI.hpp"
#include "OpenSHC/UI/ChooseNetworkServiceProvider/ChooseNetworkServiceProviderButtonActionsInt.hpp"
#include "OpenSHC/UI/Enums/SoundMenuClickTypeInt.hpp"
#include "OpenSHC/UI/Multiplayer/FindingNetworkSessions_ButtonParametersInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"
namespace OpenSHC {
namespace UI_Func {

    using OpenSHC::Commands::CommandBuildingTypeInt;
    using OpenSHC::Game::Resources::ResourceTypeInt;
    using OpenSHC::UI::ChooseNetworkServiceProvider::ChooseNetworkServiceProviderButtonActionsInt;
    using OpenSHC::UI::Enums::SoundMenuClickTypeInt;
    using OpenSHC::UI::Multiplayer::FindingNetworkSessions_ButtonParametersInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00424720, &OpenSHC::UI::MenuView_IntroLogos_Prepare)
    MenuView_IntroLogos_Prepare;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00424770, &OpenSHC::UI::MenuView_IntroLogos_DoInitial)
    MenuView_IntroLogos_DoInitial;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004247A0, &OpenSHC::UI::MenuView_IntroLogos_DoEveryFrame)
    MenuView_IntroLogos_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int unused), false, Address::SHC_3BB0A8C1_0x00424990,
        &OpenSHC::UI::MenuItemActionHandler_IntroLogos_General)
    MenuItemActionHandler_IntroLogos_General;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00424A50, &OpenSHC::UI::MenuView_IntroVideo_Prepare)
    MenuView_IntroVideo_Prepare;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00424AD0, &OpenSHC::UI::MenuView_IntroVideo_DoEveryFrame)
    MenuView_IntroVideo_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00424B10,
        &OpenSHC::UI::MenuView_GameStartEnterName_DoEveryFrame)
    MenuView_GameStartEnterName_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00424C40, &OpenSHC::UI::MenuView_MainMenu_Prepare)
    MenuView_MainMenu_Prepare;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00424CD0, &OpenSHC::UI::MenuView_MainMenu_DoInitial)
    MenuView_MainMenu_DoInitial;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00424DA0, &OpenSHC::UI::MenuView_MainMenu_DoEveryFrame)
    MenuView_MainMenu_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00424F50,
        &OpenSHC::UI::MenuItemRenderFunction_MainMenu_Main)
    MenuItemRenderFunction_MainMenu_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004251A0,
        &OpenSHC::UI::MenuItemActionHandler_MainMenu_Main)
    MenuItemActionHandler_MainMenu_Main;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00425500,
        &OpenSHC::UI::MenuView_HistoricCampaignSelect_Prepare)
    MenuView_HistoricCampaignSelect_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00425580,
        &OpenSHC::UI::MenuView_HistoricCampaignSelect_DoEveryFrame)
    MenuView_HistoricCampaignSelect_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004255D0,
        &OpenSHC::UI::MenuItemRenderFunction_HistoricCampaignSelect_Main)
    MenuItemRenderFunction_HistoricCampaignSelect_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00425720,
        &OpenSHC::UI::MenuItemActionHandler_HistoricCampaignSelect_Main)
    MenuItemActionHandler_HistoricCampaignSelect_Main;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004259D0,
        &OpenSHC::UI::MenuView_UnusedEconomicGametypeSelect_Prepare)
    MenuView_UnusedEconomicGametypeSelect_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00425A40,
        &OpenSHC::UI::MenuView_UnusedEconomicGametypeSelect_DoInitial)
    MenuView_UnusedEconomicGametypeSelect_DoInitial;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00425AD0,
        &OpenSHC::UI::MenuItemRenderFunction_UnusedEconomicGametypeSelect_Main)
    MenuItemRenderFunction_UnusedEconomicGametypeSelect_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00425C20,
        &OpenSHC::UI::MenuItemActionHandler_UnusedEconomicGametypeSelect_Main)
    MenuItemActionHandler_UnusedEconomicGametypeSelect_Main;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00425EA0, &OpenSHC::UI::MenuView_CustomScenarios_Prepare)
    MenuView_CustomScenarios_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00425F60,
        &OpenSHC::UI::MenuView_General_DoInitial_BlackBoxDefaultBorderAndPicture)
    MenuView_General_DoInitial_BlackBoxDefaultBorderAndPicture;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00425FF0,
        &OpenSHC::UI::MenuView_CustomScenarios_DoEveryFrame)
    MenuView_CustomScenarios_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00426060,
        &OpenSHC::UI::MenuItemRenderFunction_CustomScenarios_Main)
    MenuItemRenderFunction_CustomScenarios_Main;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004261E0, &OpenSHC::UI::MenuView_Credits_Prepare)
    MenuView_Credits_Prepare;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004262B0, &OpenSHC::UI::MenuView_Credits_DoInitial)
    MenuView_Credits_DoInitial;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00426340, &OpenSHC::UI::MenuView_Credits_DoEveryFrame)
    MenuView_Credits_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00426570,
        &OpenSHC::UI::MenuView_UnusedDemoBuyItScreen_Prepare)
    MenuView_UnusedDemoBuyItScreen_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00426600,
        &OpenSHC::UI::MenuView_UnusedDemoBuyItScreen_DoInitial)
    MenuView_UnusedDemoBuyItScreen_DoInitial;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004266A0,
        &OpenSHC::UI::MenuView_UnusedDemoBuyItScreen_DoEveryFrame)
    MenuView_UnusedDemoBuyItScreen_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004266E0, &OpenSHC::UI::MenuModalRenderFunction_UnusedSetName)
    MenuModalRenderFunction_UnusedSetName;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00426750,
        &OpenSHC::UI::MenuItemRenderFunction_UnusedSetName_ButtonsUnk)
    MenuItemRenderFunction_UnusedSetName_ButtonsUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004267F0,
        &OpenSHC::UI::MenuItemActionHandler_UnusedSetName_ButtonsUnk)
    MenuItemActionHandler_UnusedSetName_ButtonsUnk;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00426830,
        &OpenSHC::UI::MenuView_HistoricMissionSelect_Prepare)
    MenuView_HistoricMissionSelect_Prepare;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004268C0, &OpenSHC::UI::MenuView_MissionSelect_DoEveryFrame)
    MenuView_MissionSelect_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004269E0,
        &OpenSHC::UI::MenuItemRenderFunction_HistoricMissionSelect_MissionRows)
    MenuItemRenderFunction_HistoricMissionSelect_MissionRows;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00426B80,
        &OpenSHC::UI::MenuItemActionHandler_HistoricMissionSelect_General)
    MenuItemActionHandler_HistoricMissionSelect_General;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00426C50,
        &OpenSHC::UI::MenuView_UnusedEconomicMissionSelect_Prepare)
    MenuView_UnusedEconomicMissionSelect_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00426CA0,
        &OpenSHC::UI::MenuItemRenderFunction_HistoricAndEconomicMissionSelect_NextAndBackHands)
    MenuItemRenderFunction_HistoricAndEconomicMissionSelect_NextAndBackHands;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00426D30,
        &OpenSHC::UI::MenuItemRenderFunction_UnusedEconomicMissionSelect_MissionSelect)
    MenuItemRenderFunction_UnusedEconomicMissionSelect_MissionSelect;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00426ED0,
        &OpenSHC::UI::MenuItemActionHandler_UnusedEconomicMissionSelect_General)
    MenuItemActionHandler_UnusedEconomicMissionSelect_General;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00426F80,
        &OpenSHC::UI::MenuView_UnusedSomeMissionStartUnk_Prepare)
    MenuView_UnusedSomeMissionStartUnk_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00426FB0,
        &OpenSHC::UI::MenuItemRenderFunction_UnusedSomeMissionStartUnk_General)
    MenuItemRenderFunction_UnusedSomeMissionStartUnk_General;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00427080,
        &OpenSHC::UI::MenuItemActionHandler_UnusedSomeMissionStartUnk_General)
    MenuItemActionHandler_UnusedSomeMissionStartUnk_General;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00427110, &OpenSHC::UI::MenuView_MpConnection_Prepare)
    MenuView_MpConnection_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004271E0,
        &OpenSHC::UI::MenuView_General_DoEveryFrame_FirstGfxCentered)
    MenuView_General_DoEveryFrame_FirstGfxCentered;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00427240,
        &OpenSHC::UI::MenuView_Unknown61ReturnToSkrimishMenuUnk_DoInitial)
    MenuView_Unknown61ReturnToSkrimishMenuUnk_DoInitial;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004272C0,
        &OpenSHC::UI::MenuView_Unknown61ReturnToSkrimishMenuUnk_DoEveryFrame)
    MenuView_Unknown61ReturnToSkrimishMenuUnk_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00427320, &OpenSHC::UI::MenuView_LobbyMenu_Prepare)
    MenuView_LobbyMenu_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004276F0,
        &OpenSHC::UI::MenuView_General_DoInitial_DefaultMainMenuStructure)
    MenuView_General_DoInitial_DefaultMainMenuStructure;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00427740,
        &OpenSHC::UI::MenuItemRenderFunction_LobbyMenu_MapSelectHeader)
    MenuItemRenderFunction_LobbyMenu_MapSelectHeader;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00427810,
        &OpenSHC::UI::MenuItemRenderFunction_LobbyMenu_PlayerListAndNpcButtons)
    MenuItemRenderFunction_LobbyMenu_PlayerListAndNpcButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00428150,
        &OpenSHC::UI::MenuItemRenderFunction_General_MenuMiniMap)
    MenuItemRenderFunction_General_MenuMiniMap;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004285F0,
        &OpenSHC::UI::MenuItemRenderFunction_LobbyMenu_MapDesc)
    MenuItemRenderFunction_LobbyMenu_MapDesc;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x00428980, &OpenSHC::UI::MenuItemActionHandler_LobbyMenu_MapDescScrollbar)
    MenuItemActionHandler_LobbyMenu_MapDescScrollbar;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
        Address::SHC_3BB0A8C1_0x00428A60, &OpenSHC::UI::MenuItemRenderFunction_LobbyMenu_MapDescScrollbar)
    MenuItemRenderFunction_LobbyMenu_MapDescScrollbar;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00428AC0,
        &OpenSHC::UI::MenuItemRenderFunction_General_AdvancedGameOptions)
    MenuItemRenderFunction_General_AdvancedGameOptions;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00429A40,
        &OpenSHC::UI::MenuItemActionHandler_General_AdvancedGameOptions)
    MenuItemActionHandler_General_AdvancedGameOptions;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042A480,
        &OpenSHC::UI::MenuItemRenderFunction_LobbyMenu_SkirmishTypeAndBalance)
    MenuItemRenderFunction_LobbyMenu_SkirmishTypeAndBalance;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042A840,
        &OpenSHC::UI::MenuItemActionHandler_LobbyMenu_SkirmishTypeAndBalance)
    MenuItemActionHandler_LobbyMenu_SkirmishTypeAndBalance;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042AC40,
        &OpenSHC::UI::MenuItemRenderFunction_LobbyMenu_Unknown)
    MenuItemRenderFunction_LobbyMenu_Unknown;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042AC90,
        &OpenSHC::UI::MenuItemRenderFunction_LobbyMenu_ChatBox)
    MenuItemRenderFunction_LobbyMenu_ChatBox;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042AE90,
        &OpenSHC::UI::MenuItemRenderFunction_LobbyMenu_NonBoxedButtons)
    MenuItemRenderFunction_LobbyMenu_NonBoxedButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042B470,
        &OpenSHC::UI::MenuItemActionHandler_LobbyMenu_MapSelectTable)
    MenuItemActionHandler_LobbyMenu_MapSelectTable;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042B4C0,
        &OpenSHC::UI::MenuItemRenderFunction_LobbyMenu_MapSelectTable)
    MenuItemRenderFunction_LobbyMenu_MapSelectTable;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x0042B7B0, &OpenSHC::UI::MenuItemActionHandler_LobbyMenu_MapSelectScrollbar)
    MenuItemActionHandler_LobbyMenu_MapSelectScrollbar;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
        Address::SHC_3BB0A8C1_0x0042B8F0, &OpenSHC::UI::MenuItemRenderFunction_LobbyMenu_MapSelectScrollbar)
    MenuItemRenderFunction_LobbyMenu_MapSelectScrollbar;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042B960,
        &OpenSHC::UI::MenuView_UnusedSelectRandomNumberOfEnemies_DoEveryFrame)
    MenuView_UnusedSelectRandomNumberOfEnemies_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042BA50,
        &OpenSHC::UI::MenuItemActionHandler_UnusedSelectRandomNumberOfEnemies_Main)
    MenuItemActionHandler_UnusedSelectRandomNumberOfEnemies_Main;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042BB70,
        &OpenSHC::UI::MenuView_General_Prepare_SwordShieldAndBorder)
    MenuView_General_Prepare_SwordShieldAndBorder;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042BB90, &OpenSHC::UI::MenuView_SelectCrusade_DoInitial)
    MenuView_SelectCrusade_DoInitial;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042BBF0, &OpenSHC::UI::MenuView_SelectCrusade_DoEveryFrame)
    MenuView_SelectCrusade_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042BF00,
        &OpenSHC::UI::MenuItemActionHandler_SelectCrusade_Main)
    MenuItemActionHandler_SelectCrusade_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042C060,
        &OpenSHC::UI::MenuItemRenderFunction_SelectCrusade_Main)
    MenuItemRenderFunction_SelectCrusade_Main;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042C090, &OpenSHC::UI::MenuView_Unknown33_DoEveryFrame)
    MenuView_Unknown33_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042D140,
        &OpenSHC::UI::MenuItemRenderFunction_SingleplayerMapChoice_ButtonsAndHands)
    MenuItemRenderFunction_SingleplayerMapChoice_ButtonsAndHands;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042D640,
        &OpenSHC::UI::MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands)
    MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042D9A0,
        &OpenSHC::UI::MenuItemRenderFunction_SingleplayerMapChoice_MapTable)
    MenuItemRenderFunction_SingleplayerMapChoice_MapTable;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042DBB0,
        &OpenSHC::UI::MenuItemRenderFunction_SingleplayerMapChoice_MapTableHeader)
    MenuItemRenderFunction_SingleplayerMapChoice_MapTableHeader;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
        Address::SHC_3BB0A8C1_0x0042DC60, &OpenSHC::UI::MenuItemRenderFunction_SingleplayerMapChoice_Scrollbar)
    MenuItemRenderFunction_SingleplayerMapChoice_Scrollbar;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042DCB0, &OpenSHC::UI::MenuView_UnusedOldTitleMenu_Prepare)
    MenuView_UnusedOldTitleMenu_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042DD00,
        &OpenSHC::UI::MenuView_UnusedOldTitleMenu_DoInitial)
    MenuView_UnusedOldTitleMenu_DoInitial;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042DE20,
        &OpenSHC::UI::MenuItemRenderFunction_UnusedOldTitleMenu_ExitButton)
    MenuItemRenderFunction_UnusedOldTitleMenu_ExitButton;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042DEB0,
        &OpenSHC::UI::MenuItemRenderFunction_UnusedOldTitleMenu_ContinueButton)
    MenuItemRenderFunction_UnusedOldTitleMenu_ContinueButton;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042DF40,
        &OpenSHC::UI::MenuItemRenderFunction_UnusedOldTitleMenu_TestMapButton)
    MenuItemRenderFunction_UnusedOldTitleMenu_TestMapButton;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042DFD0, &OpenSHC::UI::MenuView_MapEditorProperties_Prepare)
    MenuView_MapEditorProperties_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042E0D0,
        &OpenSHC::UI::MenuView_MapEditorProperties_DoEveryFrame)
    MenuView_MapEditorProperties_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042E900,
        &OpenSHC::UI::MenuItemRenderFunction_MapEditorProperties_MainButtons)
    MenuItemRenderFunction_MapEditorProperties_MainButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042EBC0,
        &OpenSHC::UI::MenuItemRenderFunction_MapEditorProperties_MapDescriptionBox)
    MenuItemRenderFunction_MapEditorProperties_MapDescriptionBox;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0042EDF0,
        &OpenSHC::UI::MenuItemActionHandler_MapEditorProperties_MapDescriptionBox)
    MenuItemActionHandler_MapEditorProperties_MapDescriptionBox;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x0042EE80,
        &OpenSHC::UI::MenuItemActionHandler_MapEditorProperties_MapDescriptionScrollbar)
    MenuItemActionHandler_MapEditorProperties_MapDescriptionScrollbar;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
        Address::SHC_3BB0A8C1_0x0042EF80,
        &OpenSHC::UI::MenuItemRenderFunction_MapEditorProperties_MapDescriptionScrollbar)
    MenuItemRenderFunction_MapEditorProperties_MapDescriptionScrollbar;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042EFE0, &OpenSHC::UI::MenuView_NewMapMaptype_Prepare)
    MenuView_NewMapMaptype_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042F140,
        &OpenSHC::UI::MenuItemRenderFunction_NewMapMaptype_Buttons)
    MenuItemRenderFunction_NewMapMaptype_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042F2B0,
        &OpenSHC::UI::MenuItemActionHandler_NewMapMaptype_Buttons)
    MenuItemActionHandler_NewMapMaptype_Buttons;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042F3D0, &OpenSHC::UI::MenuView_NewMapMapsize_Prepare)
    MenuView_NewMapMapsize_Prepare;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042F3F0, &OpenSHC::UI::MenuView_NewMapMapsize_DoEveryFrame)
    MenuView_NewMapMapsize_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042F7F0,
        &OpenSHC::UI::MenuItemRenderFunction_NewMapMapsize_Buttons)
    MenuItemRenderFunction_NewMapMapsize_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042F940,
        &OpenSHC::UI::MenuItemActionHandler_NewMapMapsize_Buttons)
    MenuItemActionHandler_NewMapMapsize_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042FAA0,
        &OpenSHC::UI::MenuView_UnusedChooseAvailableKeeps_Prepare)
    MenuView_UnusedChooseAvailableKeeps_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0042FAC0,
        &OpenSHC::UI::MenuView_UnusedChooseAvailableKeeps_DoEveryFrame)
    MenuView_UnusedChooseAvailableKeeps_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042FEC0,
        &OpenSHC::UI::MenuItemRenderFunction_UnusedChooseAvailableKeeps_Main)
    MenuItemRenderFunction_UnusedChooseAvailableKeeps_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00430050,
        &OpenSHC::UI::MenuItemActionHandler_UnusedChooseAvailableKeeps_Main)
    MenuItemActionHandler_UnusedChooseAvailableKeeps_Main;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00430100,
        &OpenSHC::UI::MenuView_General_DoInitial_ScreenToBlack)
    MenuView_General_DoInitial_ScreenToBlack;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00430150,
        &OpenSHC::UI::MenuView_UnusedChooseGameType_DoEveryFrame)
    MenuView_UnusedChooseGameType_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00430550,
        &OpenSHC::UI::MenuItemRenderFunctio_UnusedChooseGameType_Mainn)
    MenuItemRenderFunctio_UnusedChooseGameType_Mainn;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004305D0,
        &OpenSHC::UI::MenuItemActionHandler_UnusedChooseGameType_Main)
    MenuItemActionHandler_UnusedChooseGameType_Main;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00430690, &OpenSHC::UI::MenuView_UnusedCreateSiege_Prepare)
    MenuView_UnusedCreateSiege_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004306D0,
        &OpenSHC::UI::MenuView_UnusedCreateSiege_DoEveryFrame)
    MenuView_UnusedCreateSiege_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00430BF0,
        &OpenSHC::UI::MenuItemRenderFunction_UnusedCreateSiege_SiegeThat)
    MenuItemRenderFunction_UnusedCreateSiege_SiegeThat;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00430CC0,
        &OpenSHC::UI::MenuView_MapEditorLandscaping_Prepare)
    MenuView_MapEditorLandscaping_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00430CE0,
        &OpenSHC::UI::MenuView_MapEditorLandscaping_DoInitial)
    MenuView_MapEditorLandscaping_DoInitial;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004313C0,
        &OpenSHC::UI::MenuView_MapEditorLandscaping_DoEveryFrame)
    MenuView_MapEditorLandscaping_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00431460,
        &OpenSHC::UI::MenuItemActionHandler_MapEditorLandscaping_CategoryButtons)
    MenuItemActionHandler_MapEditorLandscaping_CategoryButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(CommandBuildingTypeInt param_1), false, Address::SHC_3BB0A8C1_0x004314E0,
        &OpenSHC::UI::MenuItemActionHandler_MapEditorLandscaping_GeneralButtons)
    MenuItemActionHandler_MapEditorLandscaping_GeneralButtons;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00431A90, &OpenSHC::UI::MenuView_BuildMenu_Prepare)
    MenuView_BuildMenu_Prepare;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00431B60, &OpenSHC::UI::MenuView_BuildMenu_DoInitial)
    MenuView_BuildMenu_DoInitial;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00433030, &OpenSHC::UI::MenuView_BuildMenu_DoEveryFrame)
    MenuView_BuildMenu_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00433200,
        &OpenSHC::UI::MenuItemActionHandler_BuildMenu_SomeKeepAndGranaryCheckUnk)
    MenuItemActionHandler_BuildMenu_SomeKeepAndGranaryCheckUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00433230,
        &OpenSHC::UI::MenuItemActionHandler_InGameMenu_UnknownBinkRelated)
    MenuItemActionHandler_InGameMenu_UnknownBinkRelated;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00433260, &OpenSHC::UI::RenderScribeFrame)
    RenderScribeFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00433370,
        &OpenSHC::UI::MenuItemActionHandler_InGameMenu_ProcessScribeAnimationChange)
    MenuItemActionHandler_InGameMenu_ProcessScribeAnimationChange;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004335A0,
        &OpenSHC::UI::MenuItemActionHandler_InGameMenu_ViewToKeeps)
    MenuItemActionHandler_InGameMenu_ViewToKeeps;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00433780, &OpenSHC::UI::RenderGoldValue)
    RenderGoldValue;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00434120,
        &OpenSHC::UI::MenuItemActionHandler_InGameMenu_Scrolling)
    MenuItemActionHandler_InGameMenu_Scrolling;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00434230,
        &OpenSHC::UI::MenuItemRenderFunction_BuildMenu_BuildingKeepSubcategoryButton)
    MenuItemRenderFunction_BuildMenu_BuildingKeepSubcategoryButton;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00434260,
        &OpenSHC::UI::MenuItemActionHandler_General_Unknown2)
    MenuItemActionHandler_General_Unknown2;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00434270,
        &OpenSHC::UI::MenuItemActionHandler_InGameMenu_MiniMapInteraction)
    MenuItemActionHandler_InGameMenu_MiniMapInteraction;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00434300,
        &OpenSHC::UI::MenuItemRenderFunction_BuildMenu_MiniMapInteraction)
    MenuItemRenderFunction_BuildMenu_MiniMapInteraction;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00434350,
        &OpenSHC::UI::MenuItemActionHandler_InGameMenu_PeasantBuildAndRightClickMenuSelection)
    MenuItemActionHandler_InGameMenu_PeasantBuildAndRightClickMenuSelection;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004348D0,
        &OpenSHC::UI::MenuItemActionHandler_InGameMenu_UnitSelectionAndControlsUnk)
    MenuItemActionHandler_InGameMenu_UnitSelectionAndControlsUnk;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00437ED0,
        &OpenSHC::UI::MenuItemActionHandler_InGameMenu_TriggerPlaceWallCommand)
    MenuItemActionHandler_InGameMenu_TriggerPlaceWallCommand;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004387D0,
        &OpenSHC::UI::MenuItemActionHandler_BuildMenu_DeleteAction)
    MenuItemActionHandler_BuildMenu_DeleteAction;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00438B60,
        &OpenSHC::UI::MenuItemActionHandler_InGameMenu_RightClickMenuAndMaybeResets)
    MenuItemActionHandler_InGameMenu_RightClickMenuAndMaybeResets;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int mapperValue), false, Address::SHC_3BB0A8C1_0x00438BE0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildMenu_UnitActionButtons)
    MenuItemRenderFunction_BuildMenu_UnitActionButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00439160,
        &OpenSHC::UI::MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroops)
    MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroops;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00439390,
        &OpenSHC::UI::MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroopsDeselectHelper)
    MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroopsDeselectHelper;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int slotID), false, Address::SHC_3BB0A8C1_0x004393C0,
        &OpenSHC::UI::MenuItemActionHandler_BuildMenu_CurrentlySelectedTroops)
    MenuItemActionHandler_BuildMenu_CurrentlySelectedTroops;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00439890,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_StopBuildingOrPeasantBinkPlayback)
    MenuItemActionHandler_BuildingAndStatusMenu_StopBuildingOrPeasantBinkPlayback;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004398B0,
        &OpenSHC::UI::MenuView_BuildingAndStatusMenu_DoInitial)
    MenuView_BuildingAndStatusMenu_DoInitial;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0043A850,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_Unknown_Countdown)
    MenuItemActionHandler_BuildingAndStatusMenu_Unknown_Countdown;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0043A860,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_BuildingHelpTextButton)
    MenuItemActionHandler_BuildingAndStatusMenu_BuildingHelpTextButton;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0043A880,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_BuildingHelpTextButton)
    MenuItemRenderFunction_BuildingAndStatusMenu_BuildingHelpTextButton;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0043A8C0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_BarracksAndMercenaryPostHelpText)
    MenuItemRenderFunction_BuildingAndStatusMenu_BarracksAndMercenaryPostHelpText;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0043A8E0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_AvailablePeasantsTextUpperRight)
    MenuItemRenderFunction_BuildingAndStatusMenu_AvailablePeasantsTextUpperRight;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0043A960,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_AvailablePeasantsTextDownRight)
    MenuItemRenderFunction_BuildingAndStatusMenu_AvailablePeasantsTextDownRight;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0043E490,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_StatusMenuButtons)
    MenuItemActionHandler_BuildingAndStatusMenu_StatusMenuButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0043E4E0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_StatusMainMenuButtons)
    MenuItemRenderFunction_BuildingAndStatusMenu_StatusMainMenuButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0043F2B0,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_PopularityMenuSwitchButtonUnk)
    MenuItemActionHandler_BuildingAndStatusMenu_PopularityMenuSwitchButtonUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0043F2C0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_PopularityMenuSwitchButton)
    MenuItemRenderFunction_BuildingAndStatusMenu_PopularityMenuSwitchButton;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0043FBB0,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_DisableFoodType)
    MenuItemActionHandler_BuildingAndStatusMenu_DisableFoodType;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int foodType), false, Address::SHC_3BB0A8C1_0x0043FBF0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_DisableFoodType)
    MenuItemRenderFunction_BuildingAndStatusMenu_DisableFoodType;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0043FC80,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_ArmySwitchButton)
    MenuItemActionHandler_BuildingAndStatusMenu_ArmySwitchButton;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0043FCA0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_ArmyStatusSwitchButton)
    MenuItemRenderFunction_BuildingAndStatusMenu_ArmyStatusSwitchButton;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0043FCB0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_ArmyStatusReturn)
    MenuItemRenderFunction_BuildingAndStatusMenu_ArmyStatusReturn;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00440280,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_ReturnToBuildMenu)
    MenuItemActionHandler_BuildingAndStatusMenu_ReturnToBuildMenu;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00440360, &OpenSHC::UI::FUN_00440360)
    FUN_00440360;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004403D0,
        &OpenSHC::UI::MenuView_UnusedHelpTextEditor_Prepare)
    MenuView_UnusedHelpTextEditor_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00440400,
        &OpenSHC::UI::MenuView_UnusedHelpTextEditor_DoEveryFrame)
    MenuView_UnusedHelpTextEditor_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00440410,
        &OpenSHC::UI::MenuItemFunction_General_Unknown)
    MenuItemFunction_General_Unknown;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00440420,
        &OpenSHC::UI::MenuItemActionHandler_UnusedOldTitleMenu_General)
    MenuItemActionHandler_UnusedOldTitleMenu_General;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(void* param_1), false, Address::SHC_3BB0A8C1_0x00440560,
        &OpenSHC::UI::MenuView_GameStartEnterName_Prepare)
    MenuView_GameStartEnterName_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004406F0,
        &OpenSHC::UI::MenuView_GameStartEnterName_DoInitial)
    MenuView_GameStartEnterName_DoInitial;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00440770,
        &OpenSHC::UI::MenuItemActionHandler_CustomScenarios_Main)
    MenuItemActionHandler_CustomScenarios_Main;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004409C0,
        &OpenSHC::UI::MenuView_Unknown61ReturnToSkrimishMenuUnk_Prepare)
    MenuView_Unknown61ReturnToSkrimishMenuUnk_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00440A50,
        &OpenSHC::UI::MenuItemActionHandler_LobbyMenu_MapSelectHeader)
    MenuItemActionHandler_LobbyMenu_MapSelectHeader;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00440E50,
        &OpenSHC::UI::MenuItemActionHandler_LobbyMenu_PlayerListAndNpcButtons)
    MenuItemActionHandler_LobbyMenu_PlayerListAndNpcButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00442640,
        &OpenSHC::UI::MenuItemActionHandler_LobbyMenu_LobbyscreenStartButtonClick)
    MenuItemActionHandler_LobbyMenu_LobbyscreenStartButtonClick;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00442C30,
        &OpenSHC::UI::MenuItemActionHandler_SingleplayerMapChoice_MapTable)
    MenuItemActionHandler_SingleplayerMapChoice_MapTable;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x00442F40, &OpenSHC::UI::MenuItemActionHandler_SingleplayerMapChoice_Scrollbar)
    MenuItemActionHandler_SingleplayerMapChoice_Scrollbar;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00443070,
        &OpenSHC::UI::MenuItemActionHandler_MapEditorProperties_MainButtons)
    MenuItemActionHandler_MapEditorProperties_MainButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004437E0,
        &OpenSHC::UI::MenuItemActionHandler_UnusedCreateSiege_SiegeThat)
    MenuItemActionHandler_UnusedCreateSiege_SiegeThat;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00437CC0,
        &OpenSHC::UI::MenuItemActionHandler_MapEditorLandscaping_QueueCommandCallback)
    MenuItemActionHandler_MapEditorLandscaping_QueueCommandCallback;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(CommandBuildingTypeInt buttonID), false, Address::SHC_3BB0A8C1_0x00444410,
        &OpenSHC::UI::MenuItemActionHandler_General_ToolbarButtonPressed)
    MenuItemActionHandler_General_ToolbarButtonPressed;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00444B80,
        &OpenSHC::UI::MenuItemActionHandler_InGameMenu_MainButtons)
    MenuItemActionHandler_InGameMenu_MainButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004451C0,
        &OpenSHC::UI::MenuItemActionHandler_InGameMenu_TriggerPlaceBuildingCommand)
    MenuItemActionHandler_InGameMenu_TriggerPlaceBuildingCommand;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00446920,
        &OpenSHC::UI::MenuItemActionHandler_BuildMenu_UnitActionButtons)
    MenuItemActionHandler_BuildMenu_UnitActionButtons;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00446C00,
        &OpenSHC::UI::MenuView_BuildingAndStatusMenu_Prepare)
    MenuView_BuildingAndStatusMenu_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004476B0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_BuildingWorkStatus)
    MenuItemRenderFunction_BuildingAndStatusMenu_BuildingWorkStatus;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004482F0, &OpenSHC::UI::MenuView_LobbyMenu_DoEveryFrame)
    MenuView_LobbyMenu_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00448D40,
        &OpenSHC::UI::MenuView_SingleplayerMapChoice_Prepare)
    MenuView_SingleplayerMapChoice_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00448E90,
        &OpenSHC::UI::MenuView_SingleplayerMapChoice_DoEveryFrame)
    MenuView_SingleplayerMapChoice_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00449290,
        &OpenSHC::UI::MenuItemActionHandler_SingleplayerMapChoice_MapTableHeader)
    MenuItemActionHandler_SingleplayerMapChoice_MapTableHeader;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004494E0,
        &OpenSHC::UI::MenuView_BuildingAndStatusMenu_DoEveryFrame)
    MenuView_BuildingAndStatusMenu_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0045DE40,
        &OpenSHC::UI::MenuItemRenderFunction_TextEditor_Buttons)
    MenuItemRenderFunction_TextEditor_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x0045EDF0, &OpenSHC::UI::MenuItemActionHandler_TextEditor_Scrollbar)
    MenuItemActionHandler_TextEditor_Scrollbar;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
        Address::SHC_3BB0A8C1_0x0045EF90, &OpenSHC::UI::MenuItemRenderFunction_TextEditor_Scrollbar)
    MenuItemRenderFunction_TextEditor_Scrollbar;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0045F120,
        &OpenSHC::UI::MenuItemRenderFunction_DisplayScenarioHelpText_AnotherButtonUnk)
    MenuItemRenderFunction_DisplayScenarioHelpText_AnotherButtonUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00461570,
        &OpenSHC::UI::MenuItemActionHandler_TextEditor_TextInputRelatedUnk)
    MenuItemActionHandler_TextEditor_TextInputRelatedUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0045DB40,
        &OpenSHC::UI::MenuItemActionHandler_TextEditor_Buttons)
    MenuItemActionHandler_TextEditor_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00463FF0,
        &OpenSHC::UI::MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)
    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00464260,
        &OpenSHC::UI::MenuItemRenderFunction_ChooseRandomNumberOfEnemies_Main)
    MenuItemRenderFunction_ChooseRandomNumberOfEnemies_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004643F0,
        &OpenSHC::UI::MenuItemRenderFunction_InGameMenu_MainButtons)
    MenuItemRenderFunction_InGameMenu_MainButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00464860,
        &OpenSHC::UI::MenuItemRenderFunction_MapEditorLandscaping_GeneralButtons)
    MenuItemRenderFunction_MapEditorLandscaping_GeneralButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004649C0,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_Unknown_Min1)
    MenuItemActionHandler_BuildingAndStatusMenu_Unknown_Min1;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004649D0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_BarracksWeaponAvailability)
    MenuItemRenderFunction_BuildingAndStatusMenu_BarracksWeaponAvailability;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00464D90,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_UnknownMin1Unk)
    MenuItemActionHandler_BuildingAndStatusMenu_UnknownMin1Unk;

    MACRO_FUNCTION_RESOLVER(
        BOOLEnum(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00465040, &OpenSHC::UI::HasEnoughGold)
    HasEnoughGold;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(ResourceTypeInt _weapon), false, Address::SHC_3BB0A8C1_0x00465110,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_WorkshopWeaponSelection)
    MenuItemRenderFunction_BuildingAndStatusMenu_WorkshopWeaponSelection;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(ResourceTypeInt weapon), false, Address::SHC_3BB0A8C1_0x00465200,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_WorkshopWeaponSelection)
    MenuItemActionHandler_BuildingAndStatusMenu_WorkshopWeaponSelection;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004652D0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_DrawbridgeOpenClose)
    MenuItemRenderFunction_BuildingAndStatusMenu_DrawbridgeOpenClose;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00465360,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_DrawbridgeOpenClose)
    MenuItemActionHandler_BuildingAndStatusMenu_DrawbridgeOpenClose;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004653F0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_GatehouseOpenClose)
    MenuItemRenderFunction_BuildingAndStatusMenu_GatehouseOpenClose;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00465480,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_GatehouseOpenClose)
    MenuItemActionHandler_BuildingAndStatusMenu_GatehouseOpenClose;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x00465560, &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_TaxSlider)
    MenuItemActionHandler_BuildingAndStatusMenu_TaxSlider;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged),
        false, Address::SHC_3BB0A8C1_0x00465630,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_HorizontalSlider)
    MenuItemRenderFunction_BuildingAndStatusMenu_HorizontalSlider;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004656A0,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_TaxArrowButtons)
    MenuItemActionHandler_BuildingAndStatusMenu_TaxArrowButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004657B0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_TaxArrowButtons)
    MenuItemRenderFunction_BuildingAndStatusMenu_TaxArrowButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00465820,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_ChangeRations)
    MenuItemActionHandler_BuildingAndStatusMenu_ChangeRations;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004658B0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_GeneralButtonRender)
    MenuItemRenderFunction_BuildingAndStatusMenu_GeneralButtonRender;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00465920,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_MarketMenuChangeButtons)
    MenuItemActionHandler_BuildingAndStatusMenu_MarketMenuChangeButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00465950,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_SelectBuySellGoods)
    MenuItemRenderFunction_BuildingAndStatusMenu_SelectBuySellGoods;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004659E0,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_SelectBuySellGoods)
    MenuItemActionHandler_BuildingAndStatusMenu_SelectBuySellGoods;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00465A20,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_BuySellMenuButtonsAndHands)
    MenuItemRenderFunction_BuildingAndStatusMenu_BuySellMenuButtonsAndHands;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004660B0,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_BuildingSleep)
    MenuItemActionHandler_BuildingAndStatusMenu_BuildingSleep;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00466160,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_RepairBuildingButton)
    MenuItemActionHandler_BuildingAndStatusMenu_RepairBuildingButton;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00466320,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_RepairBuildingButton)
    MenuItemRenderFunction_BuildingAndStatusMenu_RepairBuildingButton;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00466620,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_OutpostUnitSelection)
    MenuItemRenderFunction_BuildingAndStatusMenu_OutpostUnitSelection;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00466710,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_OutpostUnitSelection)
    MenuItemActionHandler_BuildingAndStatusMenu_OutpostUnitSelection;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x00466730,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_OutpostSliderSize)
    MenuItemActionHandler_BuildingAndStatusMenu_OutpostSliderSize;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x00466810,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_OutpostSliderDelay)
    MenuItemActionHandler_BuildingAndStatusMenu_OutpostSliderDelay;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004668F0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildMenu_BuildingIcons)
    MenuItemRenderFunction_BuildMenu_BuildingIcons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00466920,
        &OpenSHC::UI::MenuItemRenderFunction_BuildMenu_BuildingSubcategoryButton)
    MenuItemRenderFunction_BuildMenu_BuildingSubcategoryButton;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00466950,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_BarrackUnitPortraits)
    MenuItemActionHandler_BuildingAndStatusMenu_BarrackUnitPortraits;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00466AB0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_MercenaryPostPortraits)
    MenuItemRenderFunction_BuildingAndStatusMenu_MercenaryPostPortraits;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00466C20,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_EngineerAndMonkPortraits)
    MenuItemRenderFunction_BuildingAndStatusMenu_EngineerAndMonkPortraits;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00466D10,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAndStatusMenu_TunnelerPortrait)
    MenuItemRenderFunction_BuildingAndStatusMenu_TunnelerPortrait;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00466E10, &OpenSHC::UI::DisableMercPostPortraits)
    DisableMercPostPortraits;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00466E20,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_EngineerAndMonkPortraits)
    MenuItemActionHandler_BuildingAndStatusMenu_EngineerAndMonkPortraits;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00466F60,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_TunnelerPortrait)
    MenuItemActionHandler_BuildingAndStatusMenu_TunnelerPortrait;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00467040,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_BuySellMenuButtonsAndHands)
    MenuItemActionHandler_BuildingAndStatusMenu_BuySellMenuButtonsAndHands;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int barrackUnitIdUnk), false, Address::SHC_3BB0A8C1_0x004672F0,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_BarrackMenuClick)
    MenuItemActionHandler_BuildingAndStatusMenu_BarrackMenuClick;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004674C0,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAndStatusMenu_MercenaryPostPortraits)
    MenuItemActionHandler_BuildingAndStatusMenu_MercenaryPostPortraits;

    MACRO_FUNCTION_RESOLVER(
        undefined4(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0046CF90, &OpenSHC::UI::TicksSinceCounterStart)
    TicksSinceCounterStart;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00471A80, &OpenSHC::UI::FUN_00471a80)
    FUN_00471a80;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047C670,
        &OpenSHC::UI::MenuItemRenderFunction_NetworkSessions_Buttons)
    MenuItemRenderFunction_NetworkSessions_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x0047C860, &OpenSHC::UI::MenuModalRenderFunction_ChooseNetworkServiceProvider)
    MenuModalRenderFunction_ChooseNetworkServiceProvider;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x0047CA80,
        &OpenSHC::UI::MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderScrollbarUnk)
    MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderScrollbarUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047CB30,
        &OpenSHC::UI::MenuItemRenderFunction_ChooseNetworkServiceProvider_ProviderTableRows)
    MenuItemRenderFunction_ChooseNetworkServiceProvider_ProviderTableRows;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047CC10,
        &OpenSHC::UI::MenuItemActionHandler_General_TextInputDisplay)
    MenuItemActionHandler_General_TextInputDisplay;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047CCA0,
        &OpenSHC::UI::MenuItemRenderFunction_General_TextInputDisplay)
    MenuItemRenderFunction_General_TextInputDisplay;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047CEE0,
        &OpenSHC::UI::MenuItemRenderFunction_ChooseNetworkServiceProvider_InputLabels)
    MenuItemRenderFunction_ChooseNetworkServiceProvider_InputLabels;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047CF50,
        &OpenSHC::UI::MenuItemRenderFunction_ChooseNetworkServiceProvider_YourIpDisplay)
    MenuItemRenderFunction_ChooseNetworkServiceProvider_YourIpDisplay;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x0047D070,
        &OpenSHC::UI::MenuItemActionHandler_ChooseNetworkServiceProvider_ModemScrollbarUnk)
    MenuItemActionHandler_ChooseNetworkServiceProvider_ModemScrollbarUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047D0E0,
        &OpenSHC::UI::MenuItemActionHandler_ChooseNetworkServiceProvider_ModemTableRows)
    MenuItemActionHandler_ChooseNetworkServiceProvider_ModemTableRows;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047D100,
        &OpenSHC::UI::MenuItemRenderFunction_ChooseNetworkServiceProvider_ModemTableRows)
    MenuItemRenderFunction_ChooseNetworkServiceProvider_ModemTableRows;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x0047D190, &OpenSHC::UI::MenuModalRenderFunction_FindingNetworkSessions)
    MenuModalRenderFunction_FindingNetworkSessions;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x0047D330, &OpenSHC::UI::MenuItemActionHandler_FindingNetworkSessions_Scrollbar)
    MenuItemActionHandler_FindingNetworkSessions_Scrollbar;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047D3F0,
        &OpenSHC::UI::MenuItemActionHandler_FindingNetworkSessions_TableRows)
    MenuItemActionHandler_FindingNetworkSessions_TableRows;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047D410,
        &OpenSHC::UI::MenuItemRenderFunction_FindingNetworkSessions_TableRows)
    MenuItemRenderFunction_FindingNetworkSessions_TableRows;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x0047E3A0, &OpenSHC::UI::MenuModalRenderFunction_WaitingForHost)
    MenuModalRenderFunction_WaitingForHost;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047E3E0,
        &OpenSHC::UI::MenuItemActionHandler_WaitingForHost_Button)
    MenuItemActionHandler_WaitingForHost_Button;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047E420,
        &OpenSHC::UI::MenuItemRenderFunction_WaitingForHost_Button)
    MenuItemRenderFunction_WaitingForHost_Button;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047FD50,
        &OpenSHC::UI::MenuItemRenderFunction_Chat_MostButtons)
    MenuItemRenderFunction_Chat_MostButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047FFA0,
        &OpenSHC::UI::MenuItemActionHandler_Chat_SendMessageToPlayer)
    MenuItemActionHandler_Chat_SendMessageToPlayer;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0047FFE0,
        &OpenSHC::UI::MenuItemRenderFunction_Chat_TauntButtons)
    MenuItemRenderFunction_Chat_TauntButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00487200,
        &OpenSHC::UI::MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderTableRows)
    MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderTableRows;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0048BF70,
        &OpenSHC::UI::MenuItemActionHandler_FindingNetworkSessions_EnumerateDPlaySessions)
    MenuItemActionHandler_FindingNetworkSessions_EnumerateDPlaySessions;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0048F590,
        &OpenSHC::UI::MenuItemActionHandler_Chat_MostButtons)
    MenuItemActionHandler_Chat_MostButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0048F850,
        &OpenSHC::UI::MenuItemActionHandler_Chat_TauntButtons)
    MenuItemActionHandler_Chat_TauntButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(ChooseNetworkServiceProviderButtonActionsInt param_1), false,
        Address::SHC_3BB0A8C1_0x004909E0, &OpenSHC::UI::MenuItemActionHandler_ChooseNetworkServiceProvider_Buttons)
    MenuItemActionHandler_ChooseNetworkServiceProvider_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(FindingNetworkSessions_ButtonParametersInt param_1), false,
        Address::SHC_3BB0A8C1_0x00490D90, &OpenSHC::UI::MenuItemActionHandler_FindingNetworkSessions_Buttons)
    MenuItemActionHandler_FindingNetworkSessions_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004914D0,
        &OpenSHC::UI::MenuItemActionHandler_WaitingForHost_ConnectToLobby)
    MenuItemActionHandler_WaitingForHost_ConnectToLobby;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x00491810, &OpenSHC::UI::MenuModalRenderFunction_OptionsMenu)
    MenuModalRenderFunction_OptionsMenu;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00491840,
        &OpenSHC::UI::MenuItemRenderFunction_OptionsMenu_Buttons)
    MenuItemRenderFunction_OptionsMenu_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00491A30,
        &OpenSHC::UI::MenuItemRenderFunction_OptionsMenu_SubOptionsButtons)
    MenuItemRenderFunction_OptionsMenu_SubOptionsButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x00491AC0, &OpenSHC::UI::MenuModalRenderFunction_IdentityOptions)
    MenuModalRenderFunction_IdentityOptions;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x00491BF0, &OpenSHC::UI::MenuModalRenderFunction_EnterTitleOnGameStart)
    MenuModalRenderFunction_EnterTitleOnGameStart;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00491C20,
        &OpenSHC::UI::MenuItemActionHandler_EnterTitleOnGameStart_Button)
    MenuItemActionHandler_EnterTitleOnGameStart_Button;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00491C50,
        &OpenSHC::UI::MenuItemRenderFunction_EnterTitleOnGameStart_Button)
    MenuItemRenderFunction_EnterTitleOnGameStart_Button;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00491CE0,
        &OpenSHC::UI::MenuItemActionHandler_IdentityOptions_LordIcons)
    MenuItemActionHandler_IdentityOptions_LordIcons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00491D70,
        &OpenSHC::UI::MenuItemRenderFunction_IdentityOptions_LordIcons)
    MenuItemRenderFunction_IdentityOptions_LordIcons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x00491E80, &OpenSHC::UI::MenuModalRenderFunction_GameplayOptions)
    MenuModalRenderFunction_GameplayOptions;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00491EB0,
        &OpenSHC::UI::MenuItemRenderFunction_GameplayOptions_Buttons)
    MenuItemRenderFunction_GameplayOptions_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x00491FD0, &OpenSHC::UI::MenuItemActionHandler_GameplayOptions_SpeedSlider)
    MenuItemActionHandler_GameplayOptions_SpeedSlider;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged),
        false, Address::SHC_3BB0A8C1_0x00492080, &OpenSHC::UI::MenuItemRenderFunction_GameplayOptions_SpeedSlider)
    MenuItemRenderFunction_GameplayOptions_SpeedSlider;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x00492120, &OpenSHC::UI::MenuModalRenderFunction_VideoOptions)
    MenuModalRenderFunction_VideoOptions;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00492170,
        &OpenSHC::UI::MenuItemRenderFunction_VideoOptions_Main)
    MenuItemRenderFunction_VideoOptions_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x00492660, &OpenSHC::UI::MenuModalRenderFunction_SoundOptions)
    MenuModalRenderFunction_SoundOptions;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00492690,
        &OpenSHC::UI::MenuItemRenderFunction_SoundOptions_Buttons)
    MenuItemRenderFunction_SoundOptions_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x00492890, &OpenSHC::UI::MenuItemActionHandler_SoundOptions_VolumeSlider)
    MenuItemActionHandler_SoundOptions_VolumeSlider;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged),
        false, Address::SHC_3BB0A8C1_0x004929C0, &OpenSHC::UI::MenuItemRenderFunction_SoundOptions_VolumeSlider)
    MenuItemRenderFunction_SoundOptions_VolumeSlider;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x00492A60, &OpenSHC::UI::MenuModalRenderFunction_NetworkOptions)
    MenuModalRenderFunction_NetworkOptions;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00492A90,
        &OpenSHC::UI::MenuItemRenderFunction_SaveLoadMap_Buttons)
    MenuItemRenderFunction_SaveLoadMap_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x00492BA0, &OpenSHC::UI::MenuItemActionHandler_SaveLoadMap_Scrollbar)
    MenuItemActionHandler_SaveLoadMap_Scrollbar;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
        Address::SHC_3BB0A8C1_0x00492C60, &OpenSHC::UI::MenuItemRenderFunction_SaveLoadMap_Scrollbar)
    MenuItemRenderFunction_SaveLoadMap_Scrollbar;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00492C90,
        &OpenSHC::UI::MenuItemRenderFunction_SaveLoadMap_TableContent)
    MenuItemRenderFunction_SaveLoadMap_TableContent;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00492DE0,
        &OpenSHC::UI::MenuItemActionHandler_SaveLoadMap_TableHeader)
    MenuItemActionHandler_SaveLoadMap_TableHeader;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00492FD0,
        &OpenSHC::UI::MenuItemRenderFunction_SaveLoadMap_TableHeader)
    MenuItemRenderFunction_SaveLoadMap_TableHeader;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004931A0, &OpenSHC::UI::MenuModalRenderFunction_SaveMap)
    MenuModalRenderFunction_SaveMap;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004932A0,
        &OpenSHC::UI::MenuItemActionHandler_SaveMap_TableContent)
    MenuItemActionHandler_SaveMap_TableContent;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004932E0,
        &OpenSHC::UI::MenuItemRenderFunction_SaveMap_InputTextDisplay)
    MenuItemRenderFunction_SaveMap_InputTextDisplay;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x00493390, &OpenSHC::UI::MenuModalRenderFunction_YesNoDialog)
    MenuModalRenderFunction_YesNoDialog;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004934F0,
        &OpenSHC::UI::MenuItemRenderFunction_General_GameOptionsTextButton)
    MenuItemRenderFunction_General_GameOptionsTextButton;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x00493560, &OpenSHC::UI::MenuModalRenderFunction_ProgressBarBox)
    MenuModalRenderFunction_ProgressBarBox;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004937B0, &OpenSHC::UI::MenuModalRenderFunction_OnlineQuitGame)
    MenuModalRenderFunction_OnlineQuitGame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004937E0, &OpenSHC::UI::MenuModalRenderFunction_OnlineVoteQuitGame)
    MenuModalRenderFunction_OnlineVoteQuitGame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00493850,
        &OpenSHC::UI::MenuItemRenderFunction_OnlineVoteQuitAndQuitGame_Main)
    MenuItemRenderFunction_OnlineVoteQuitAndQuitGame_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00493BD0,
        &OpenSHC::UI::MenuItemActionHandler_OptionsMenu_SubOptionsButtons)
    MenuItemActionHandler_OptionsMenu_SubOptionsButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00493D30,
        &OpenSHC::UI::MenuItemActionHandler_IdentityOptions_Confirm)
    MenuItemActionHandler_IdentityOptions_Confirm;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00493D80,
        &OpenSHC::UI::MenuItemActionHandler_GameplayOptions_Buttons)
    MenuItemActionHandler_GameplayOptions_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00493E20,
        &OpenSHC::UI::MenuItemActionHandler_VideoOptions_Main)
    MenuItemActionHandler_VideoOptions_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(SoundMenuClickTypeInt param_1), false, Address::SHC_3BB0A8C1_0x004940B0,
        &OpenSHC::UI::MenuItemActionHandler_SoundOptions_Buttons)
    MenuItemActionHandler_SoundOptions_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004941F0,
        &OpenSHC::UI::MenuItemActionHandler_NetworkOptions_LeaveButtonUnk)
    MenuItemActionHandler_NetworkOptions_LeaveButtonUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x00494210, &OpenSHC::UI::MenuModalRenderFunction_LoadMap)
    MenuModalRenderFunction_LoadMap;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004943B0,
        &OpenSHC::UI::MenuItemActionHandler_SaveLoadMap_Buttons)
    MenuItemActionHandler_SaveLoadMap_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004948C0,
        &OpenSHC::UI::MenuItemActionHandler_LoadMap_TableContent)
    MenuItemActionHandler_LoadMap_TableContent;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00494920,
        &OpenSHC::UI::MenuItemActionHandler_SaveMap_ReturnKeySave)
    MenuItemActionHandler_SaveMap_ReturnKeySave;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0048C230,
        &OpenSHC::UI::MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)
    MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004950B0,
        &OpenSHC::UI::MenuItemActionHandler_ProgressBarBox_LoadAndSaveGameButtonLogic)
    MenuItemActionHandler_ProgressBarBox_LoadAndSaveGameButtonLogic;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00495800, &OpenSHC::UI::FUN_00495800)
    FUN_00495800;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00495860,
        &OpenSHC::UI::MenuItemActionHandler_OnlineVoteQuitAndQuitGame_Main)
    MenuItemActionHandler_OnlineVoteQuitAndQuitGame_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00496B80,
        &OpenSHC::UI::MenuItemActionHandler_OptionsMenu_Buttons)
    MenuItemActionHandler_OptionsMenu_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AA440, &OpenSHC::UI::MenuModalRenderFunction_OverlaySlider)
    MenuModalRenderFunction_OverlaySlider;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x004AA600, &OpenSHC::UI::MenuItemActionHandler_OverlaySlider_Slider)
    MenuItemActionHandler_OverlaySlider_Slider;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged),
        false, Address::SHC_3BB0A8C1_0x004AA800, &OpenSHC::UI::MenuItemRenderFunction_OverlaySlider_Slider)
    MenuItemRenderFunction_OverlaySlider_Slider;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004AA970,
        &OpenSHC::UI::MenuItemRenderFunction_UnusedWinCondition_Options)
    MenuItemRenderFunction_UnusedWinCondition_Options;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AAA40, &OpenSHC::UI::MenuModalRenderFunction_DebugDataCurrentPlayerData)
    MenuModalRenderFunction_DebugDataCurrentPlayerData;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AAA60, &OpenSHC::UI::MenuModalRenderFunction_DebugDataAiInfo)
    MenuModalRenderFunction_DebugDataAiInfo;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AAA80, &OpenSHC::UI::MenuModalRenderFunction_DebugDataUnitData)
    MenuModalRenderFunction_DebugDataUnitData;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AAAA0, &OpenSHC::UI::MenuModalRenderFunction_DebugDataZoneDataUnk)
    MenuModalRenderFunction_DebugDataZoneDataUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AAAC0, &OpenSHC::UI::MenuModalRenderFunction_DebugDataMousePointing)
    MenuModalRenderFunction_DebugDataMousePointing;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AAAE0, &OpenSHC::UI::MenuModalRenderFunction_DebugDataNetwork)
    MenuModalRenderFunction_DebugDataNetwork;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AAB00, &OpenSHC::UI::MenuModalRenderFunction_DebugDataSplitInfo)
    MenuModalRenderFunction_DebugDataSplitInfo;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AAB20, &OpenSHC::UI::MenuModalRenderFunction_DebugDataMapData)
    MenuModalRenderFunction_DebugDataMapData;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AAB40, &OpenSHC::UI::MenuModalRenderFunction_TextEditor)
    MenuModalRenderFunction_TextEditor;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AAB50, &OpenSHC::UI::MenuModalRenderFunction_CreditsScroll)
    MenuModalRenderFunction_CreditsScroll;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AB440, &OpenSHC::UI::MenuModalRenderFunction_DisplayAiLordMessage)
    MenuModalRenderFunction_DisplayAiLordMessage;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AB460, &OpenSHC::UI::MenuModalRenderFunction_UnusedChooseMessageBox)
    MenuModalRenderFunction_UnusedChooseMessageBox;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AB4B0, &OpenSHC::UI::MenuModalRenderFunction_TraderSettings)
    MenuModalRenderFunction_TraderSettings;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AB4E0, &OpenSHC::UI::MenuModalRenderFunction_StartGoods)
    MenuModalRenderFunction_StartGoods;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AB510, &OpenSHC::UI::MenuModalRenderFunction_UnusedSiegeAttackingForceUnk)
    MenuModalRenderFunction_UnusedSiegeAttackingForceUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AB540, &OpenSHC::UI::MenuModalRenderFunction_CreateOrTriggerInvasion)
    MenuModalRenderFunction_CreateOrTriggerInvasion;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AB570, &OpenSHC::UI::MenuModalRenderFunction_UnusedCreateTimedMessageEvent)
    MenuModalRenderFunction_UnusedCreateTimedMessageEvent;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AB680, &OpenSHC::UI::MenuModalRenderFunction_UnusedCreateMessageEvent)
    MenuModalRenderFunction_UnusedCreateMessageEvent;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AB790, &OpenSHC::UI::MenuModalRenderFunction_NewEvent)
    MenuModalRenderFunction_NewEvent;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004ABA20, &OpenSHC::UI::MenuModalRenderFunction_NewEventCondition)
    MenuModalRenderFunction_NewEventCondition;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004ABAB0, &OpenSHC::UI::MenuModalRenderFunction_NewEventAction)
    MenuModalRenderFunction_NewEventAction;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004ABBA0, &OpenSHC::UI::MenuModalRenderFunction_BuildingAvailability)
    MenuModalRenderFunction_BuildingAvailability;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004ABCB0, &OpenSHC::UI::MenuModalRenderFunction_DisableTroops)
    MenuModalRenderFunction_DisableTroops;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004ABCE0, &OpenSHC::UI::MenuModalRenderFunction_DisableWeapon)
    MenuModalRenderFunction_DisableWeapon;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004ABD10, &OpenSHC::UI::MenuModalRenderFunction_TutorialBox_Thunk)
    MenuModalRenderFunction_TutorialBox_Thunk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004ABD20, &OpenSHC::UI::MenuModalRenderFunction_Chat)
    MenuModalRenderFunction_Chat;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004ABE50, &OpenSHC::UI::MenuModalRenderFunction_SkirmishConnectionOptions)
    MenuModalRenderFunction_SkirmishConnectionOptions;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004ABE80, &OpenSHC::UI::MenuModalRenderFunction_SkirmishPlayOptions)
    MenuModalRenderFunction_SkirmishPlayOptions;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004ABEB0,
        &OpenSHC::UI::MenuItemActionHandler_EditorMapTypeQuickChange_Main)
    MenuItemActionHandler_EditorMapTypeQuickChange_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004AC040,
        &OpenSHC::UI::MenuItemRenderFunction_EditorMapTypeQuickChange_Main)
    MenuItemRenderFunction_EditorMapTypeQuickChange_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AC250, &OpenSHC::UI::MenuModalRenderFunction_TriggerEvent)
    MenuModalRenderFunction_TriggerEvent;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AC280, &OpenSHC::UI::MenuModalRenderFunction_TriggerEventSlider)
    MenuModalRenderFunction_TriggerEventSlider;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AC310, &OpenSHC::UI::MenuModalRenderFunction_SendMapTo)
    MenuModalRenderFunction_SendMapTo;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004AC440,
        &OpenSHC::UI::MenuItemRenderFunction_SendReceiveMap_Main)
    MenuItemRenderFunction_SendReceiveMap_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AC4C0, &OpenSHC::UI::MenuModalRenderFunction_ReceiveMapFrom)
    MenuModalRenderFunction_ReceiveMapFrom;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004AC650, &OpenSHC::UI::FUN_004ac650)
    FUN_004ac650;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AC6E0, &OpenSHC::UI::MenuModalRenderFunction_Allies)
    MenuModalRenderFunction_Allies;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004641A0,
        &OpenSHC::UI::MenuItemRenderFunction_Allies_Main)
    MenuItemRenderFunction_Allies_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AD2B0, &OpenSHC::UI::MenuModalRenderFunction_AlliesOrder)
    MenuModalRenderFunction_AlliesOrder;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004AD480,
        &OpenSHC::UI::MenuItemRenderFunction_AlliesOrder_Main)
    MenuItemRenderFunction_AlliesOrder_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AD780, &OpenSHC::UI::MenuModalRenderFunction_AlliesRequestGoods)
    MenuModalRenderFunction_AlliesRequestGoods;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int actionParam), false, Address::SHC_3BB0A8C1_0x004AD920,
        &OpenSHC::UI::MenuItemRenderFunction_AlliesSendAndRequestGoods_Main)
    MenuItemRenderFunction_AlliesSendAndRequestGoods_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004ADD90, &OpenSHC::UI::MenuModalRenderFunction_AlliesSendGoods)
    MenuModalRenderFunction_AlliesSendGoods;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AE070, &OpenSHC::UI::MenuModalRenderFunction_ChooseRandomNumberOfEnemies)
    MenuModalRenderFunction_ChooseRandomNumberOfEnemies;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AE0F0, &OpenSHC::UI::MenuModalRenderFunction_GreatestLord)
    MenuModalRenderFunction_GreatestLord;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004AE720,
        &OpenSHC::UI::MenuItemRenderFunction_GreatestLord_Main)
    MenuItemRenderFunction_GreatestLord_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004AE7D0,
        &OpenSHC::UI::MenuItemActionHandler_AiLordSelect_Main)
    MenuItemActionHandler_AiLordSelect_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004AE950,
        &OpenSHC::UI::MenuItemRenderFunction_AiLordSelect_Main)
    MenuItemRenderFunction_AiLordSelect_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004AEA50,
        &OpenSHC::UI::MenuItemActionHandler_Roundtable_Main)
    MenuItemActionHandler_Roundtable_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004AEF70,
        &OpenSHC::UI::MenuItemRenderFunction_Roundtable_Main)
    MenuItemRenderFunction_Roundtable_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004AF4C0, &OpenSHC::UI::MenuModalRenderFunction_DebugDataAivStateUnk)
    MenuModalRenderFunction_DebugDataAivStateUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B0F70,
        &OpenSHC::UI::MenuItemActionHandler_OverlaySlider_Deselect)
    MenuItemActionHandler_OverlaySlider_Deselect;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B1000,
        &OpenSHC::UI::MenuItemActionHandler_UnusedWinCondition_DeselectUnk)
    MenuItemActionHandler_UnusedWinCondition_DeselectUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B1090,
        &OpenSHC::UI::MenuItemActionHandler_UnusedWinCondition_Options)
    MenuItemActionHandler_UnusedWinCondition_Options;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B10D0,
        &OpenSHC::UI::MenuItemActionHandler_SendReceiveMap_Main)
    MenuItemActionHandler_SendReceiveMap_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B12D0,
        &OpenSHC::UI::MenuItemActionHandler_Allies_Main)
    MenuItemActionHandler_Allies_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B1410,
        &OpenSHC::UI::MenuItemActionHandler_AlliesOrder_Main)
    MenuItemActionHandler_AlliesOrder_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B14C0,
        &OpenSHC::UI::MenuItemActionHandler_AlliesSendAndRequestGoods_Main)
    MenuItemActionHandler_AlliesSendAndRequestGoods_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B18D0,
        &OpenSHC::UI::MenuItemActionHandler_ChooseRandomNumberOfEnemies_Main)
    MenuItemActionHandler_ChooseRandomNumberOfEnemies_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B1990,
        &OpenSHC::UI::MenuItemActionHandler_GreatestLord_Main)
    MenuItemActionHandler_GreatestLord_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004B19E0, &OpenSHC::UI::MenuModalRenderFunction_AiLordSelect)
    MenuModalRenderFunction_AiLordSelect;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004B1AC0, &OpenSHC::UI::MenuModalRenderFunction_Roundtable)
    MenuModalRenderFunction_Roundtable;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B6500,
        &OpenSHC::UI::MenuItemRenderFunction_InGameMenu_MapEventIconUnk)
    MenuItemRenderFunction_InGameMenu_MapEventIconUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B6530,
        &OpenSHC::UI::MenuItemActionHandler_InGameMenu_MapEventIconUnk)
    MenuItemActionHandler_InGameMenu_MapEventIconUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B65A0,
        &OpenSHC::UI::MenuItemRenderFunction_InGameMenu_KeepEnclosedSymbol)
    MenuItemRenderFunction_InGameMenu_KeepEnclosedSymbol;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B65F0,
        &OpenSHC::UI::MenuItemRenderFunction_InGameMenu_BikMessagePlayerShield)
    MenuItemRenderFunction_InGameMenu_BikMessagePlayerShield;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(uint param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004B7F60, &OpenSHC::UI::FUN_004b7f60)
    FUN_004b7f60;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004B8050,
        &OpenSHC::UI::MenuView_General_DoInitial_OnlySetMenuXY)
    MenuView_General_DoInitial_OnlySetMenuXY;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004B8080, &OpenSHC::UI::MenuView_EditScenario_DoEveryFrame)
    MenuView_EditScenario_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004B8210, &OpenSHC::UI::FUN_004b8210)
    FUN_004b8210;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B8220,
        &OpenSHC::UI::MenuItemActionHandler_EditScenario_BaseMenuButtons)
    MenuItemActionHandler_EditScenario_BaseMenuButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B8990,
        &OpenSHC::UI::MenuItemActionHandler_EditScenario_DateYearBox)
    MenuItemActionHandler_EditScenario_DateYearBox;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x004B8A50, &OpenSHC::UI::MenuItemActionHandler_EditScenario_Scrollbar)
    MenuItemActionHandler_EditScenario_Scrollbar;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B8B10,
        &OpenSHC::UI::MenuItemActionHandler_EditScenario_EventAndInvasionList)
    MenuItemActionHandler_EditScenario_EventAndInvasionList;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B8BF0,
        &OpenSHC::UI::MenuItemRenderFunction_EditScenario_EventAndInvasionList)
    MenuItemRenderFunction_EditScenario_EventAndInvasionList;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B9020,
        &OpenSHC::UI::MenuItemActionHandler_EditScenario_UpDownButtons)
    MenuItemActionHandler_EditScenario_UpDownButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B9060,
        &OpenSHC::UI::MenuItemRenderFunction_EditScenario_UpDownButtons)
    MenuItemRenderFunction_EditScenario_UpDownButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int unitTypeMenuID), false, Address::SHC_3BB0A8C1_0x004B9110,
        &OpenSHC::UI::MenuItemActionHandler_NewInvasion_UnitButtons)
    MenuItemActionHandler_NewInvasion_UnitButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B92D0,
        &OpenSHC::UI::MenuItemRenderFunction_NewInvasion_UnitButtons)
    MenuItemRenderFunction_NewInvasion_UnitButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x004B94A0, &OpenSHC::UI::MenuItemActionHandler_NewInvasion_RepeatSlider)
    MenuItemActionHandler_NewInvasion_RepeatSlider;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1, int thumbXPos, int sliderValue, int thumbWidth, BOOLEnum isDragged), false,
        Address::SHC_3BB0A8C1_0x004B9530, &OpenSHC::UI::MenuItemRenderFunction_NewInvasion_RepeatSlider)
    MenuItemRenderFunction_NewInvasion_RepeatSlider;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004B9610, &OpenSHC::UI::FUN_004b9610)
    FUN_004b9610;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B9620,
        &OpenSHC::UI::MenuItemActionHandler_NewEventCondition_Main)
    MenuItemActionHandler_NewEventCondition_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004B9C00,
        &OpenSHC::UI::MenuItemActionHandler_NewEventAction_Main)
    MenuItemActionHandler_NewEventAction_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x004B9E50, &OpenSHC::UI::MenuItemActionHandler_General_EventSlider)
    MenuItemActionHandler_General_EventSlider;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged),
        false, Address::SHC_3BB0A8C1_0x004BA3C0, &OpenSHC::UI::MenuItemRenderFunction_General_EventSlider)
    MenuItemRenderFunction_General_EventSlider;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int index), false, Address::SHC_3BB0A8C1_0x004BA560,
        &OpenSHC::UI::MenuItemActionHandler_UnusedCreateMessageEvent_Unknown)
    MenuItemActionHandler_UnusedCreateMessageEvent_Unknown;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BA5C0,
        &OpenSHC::UI::MenuItemActionHandler_SiegeAttackingForceAndStartGoods_Main)
    MenuItemActionHandler_SiegeAttackingForceAndStartGoods_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BA780,
        &OpenSHC::UI::MenuItemActionHandler_TraderSettings)
    MenuItemActionHandler_TraderSettings;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BA980,
        &OpenSHC::UI::MenuItemRenderFunction_UnusedCreateMessageEvent_Buttons)
    MenuItemRenderFunction_UnusedCreateMessageEvent_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BAC20,
        &OpenSHC::UI::MenuItemRenderFunction_EditScenario_StartDateMonth)
    MenuItemRenderFunction_EditScenario_StartDateMonth;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BAC90,
        &OpenSHC::UI::MenuItemRenderFunction_EditScenario_StartDate)
    MenuItemRenderFunction_EditScenario_StartDate;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x004BAD70, &OpenSHC::UI::MenuItemActionHandler_General_MessageScrollbar)
    MenuItemActionHandler_General_MessageScrollbar;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
        Address::SHC_3BB0A8C1_0x004BAE30, &OpenSHC::UI::MenuItemRenderFunction_General_Scrollbar)
    MenuItemRenderFunction_General_Scrollbar;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BAE80,
        &OpenSHC::UI::MenuItemRenderFunction_General_MessageScrollbarUpDown)
    MenuItemRenderFunction_General_MessageScrollbarUpDown;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BB0D0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAvailability_Buttons)
    MenuItemRenderFunction_BuildingAvailability_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BB2C0,
        &OpenSHC::UI::MenuItemActionHandler_BuildingAvailability_Buttons)
    MenuItemActionHandler_BuildingAvailability_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BB3E0,
        &OpenSHC::UI::MenuItemRenderFunction_BuildingAvailability_TableRows)
    MenuItemRenderFunction_BuildingAvailability_TableRows;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x004BB480, &OpenSHC::UI::MenuItemActionHandler_BuildingAvailability_Scrollbar)
    MenuItemActionHandler_BuildingAvailability_Scrollbar;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BB540,
        &OpenSHC::UI::MenuItemActionHandler_DisableEuroTroops_Main)
    MenuItemActionHandler_DisableEuroTroops_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BB570,
        &OpenSHC::UI::MenuItemRenderFunction_DisableEuroTroops_Main)
    MenuItemRenderFunction_DisableEuroTroops_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BB650,
        &OpenSHC::UI::MenuItemActionHandler_DisableArabTroops_Main)
    MenuItemActionHandler_DisableArabTroops_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BB680,
        &OpenSHC::UI::MenuItemRenderFunction_DisableArabTroops_Main)
    MenuItemRenderFunction_DisableArabTroops_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BB740,
        &OpenSHC::UI::MenuItemActionHandler_DisableWeapon_Main)
    MenuItemActionHandler_DisableWeapon_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BB7B0,
        &OpenSHC::UI::MenuItemRenderFunction_DisableWeapon_Main)
    MenuItemRenderFunction_DisableWeapon_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BBA60,
        &OpenSHC::UI::MenuItemRenderFunction_General_CreateEventCallbackFunction)
    MenuItemRenderFunction_General_CreateEventCallbackFunction;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BBD90,
        &OpenSHC::UI::MenuItemActionHandler_TriggerInvasion_Main)
    MenuItemActionHandler_TriggerInvasion_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BBF40,
        &OpenSHC::UI::MenuItemRenderFunction_TriggerInvasion_Main)
    MenuItemRenderFunction_TriggerInvasion_Main;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BC5F0, &OpenSHC::UI::FUN_004bc5f0)
    FUN_004bc5f0;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BC630, &OpenSHC::UI::FUN_004bc630)
    FUN_004bc630;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004BC6C0, &OpenSHC::UI::FUN_004bc6c0)
    FUN_004bc6c0;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004BC790, &OpenSHC::UI::FUN_004bc790)
    FUN_004bc790;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BC910, &OpenSHC::UI::FUN_004bc910)
    FUN_004bc910;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004BCBA0, &OpenSHC::UI::MenuModalRenderFunction_TutorialBox)
    MenuModalRenderFunction_TutorialBox;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BCEC0,
        &OpenSHC::UI::MenuItemActionHandler_TutorialBox_Main)
    MenuItemActionHandler_TutorialBox_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BD0F0,
        &OpenSHC::UI::MenuItemRenderFunction_TutorialBox_Main)
    MenuItemRenderFunction_TutorialBox_Main;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004BD1B0, &OpenSHC::UI::FUN_004bd1b0)
    FUN_004bd1b0;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004BEC10, &OpenSHC::UI::MenuView_EditScenario_Prepare)
    MenuView_EditScenario_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BEC40,
        &OpenSHC::UI::MenuItemRenderFunction_EditScenario_BaseMenuButtons)
    MenuItemRenderFunction_EditScenario_BaseMenuButtons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BF1D0,
        &OpenSHC::UI::MenuItemRenderFunction_EditScenario_TextBoxLike)
    MenuItemRenderFunction_EditScenario_TextBoxLike;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BF720,
        &OpenSHC::UI::MenuItemActionHandler_UnusedChooseMessageBox_Unknown)
    MenuItemActionHandler_UnusedChooseMessageBox_Unknown;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BF760,
        &OpenSHC::UI::MenuItemActionHandler_NewInvasion_Buttons)
    MenuItemActionHandler_NewInvasion_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BFA60,
        &OpenSHC::UI::MenuItemRenderFunction_NewInvasion_Buttons)
    MenuItemRenderFunction_NewInvasion_Buttons;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BFE20,
        &OpenSHC::UI::MenuItemActionHandler_UnusedCreateMessageEvent_SetTextUnk)
    MenuItemActionHandler_UnusedCreateMessageEvent_SetTextUnk;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BFFA0,
        &OpenSHC::UI::MenuItemRenderFunction_General_EventButtonAndData)
    MenuItemRenderFunction_General_EventButtonAndData;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004C0040,
        &OpenSHC::UI::MenuItemActionHandler_NewEvent_Main)
    MenuItemActionHandler_NewEvent_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004C01B0,
        &OpenSHC::UI::MenuItemRenderFunction_NewEventCondition_Main)
    MenuItemRenderFunction_NewEventCondition_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004C0860,
        &OpenSHC::UI::MenuItemRenderFunction_NewEventAction_Main)
    MenuItemRenderFunction_NewEventAction_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004C0CF0,
        &OpenSHC::UI::MenuItemRenderFunction_SiegeAttackingForceAndStartGoods_Main)
    MenuItemRenderFunction_SiegeAttackingForceAndStartGoods_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004C1070,
        &OpenSHC::UI::MenuItemRenderFunction_TraderSettings)
    MenuItemRenderFunction_TraderSettings;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004C1770,
        &OpenSHC::UI::MenuItemActionHandler_General_CreateEventCallbackFunction)
    MenuItemActionHandler_General_CreateEventCallbackFunction;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004D55D0, &OpenSHC::UI::MenuView_GameLost_Prepare)
    MenuView_GameLost_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D6BC0,
        &OpenSHC::UI::MenuItemActionHandler_MissionEndscreen_Main)
    MenuItemActionHandler_MissionEndscreen_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D6D20,
        &OpenSHC::UI::MenuItemRenderFunction_MissionEndscreen_Main)
    MenuItemRenderFunction_MissionEndscreen_Main;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004D6EF0, &OpenSHC::UI::MenuView_CampaignUnk_DoEveryFrame)
    MenuView_CampaignUnk_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D6F20,
        &OpenSHC::UI::MenuItemActionHandler_Unknown27CampaignUnk_Main)
    MenuItemActionHandler_Unknown27CampaignUnk_Main;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004D6F60, &OpenSHC::UI::FUN_004d6f60)
    FUN_004d6f60;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D8250,
        &OpenSHC::UI::MenuItemRenderFunction_ScenarioDescription_Main)
    MenuItemRenderFunction_ScenarioDescription_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D8570,
        &OpenSHC::UI::MenuItemActionHandler_ScenarioDescription_Main)
    MenuItemActionHandler_ScenarioDescription_Main;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(char* param_1), false, Address::SHC_3BB0A8C1_0x004D8A20, &OpenSHC::UI::FUN_004d8a20)
    FUN_004d8a20;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004D8AB0, &OpenSHC::UI::MenuView_CrusadeMissionIntro_Prepare)
    MenuView_CrusadeMissionIntro_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int imageID, int x, int y), false, Address::SHC_3BB0A8C1_0x004D8AE0,
        &OpenSHC::UI::RenderPlayerAvatars)
    RenderPlayerAvatars;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D8BB0,
        &OpenSHC::UI::MenuItemRenderFunction_CrusadeMissionIntro_Main)
    MenuItemRenderFunction_CrusadeMissionIntro_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D8C10,
        &OpenSHC::UI::MenuItemActionHandler_CrusadeMissionIntro_Main)
    MenuItemActionHandler_CrusadeMissionIntro_Main;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004D8CB0, &OpenSHC::UI::MenuView_CrusadeMap_Prepare)
    MenuView_CrusadeMap_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D8DF0,
        &OpenSHC::UI::MenuItemRenderFunction_General_CrusadeMapAndEndscreen)
    MenuItemRenderFunction_General_CrusadeMapAndEndscreen;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D8EC0,
        &OpenSHC::UI::MenuItemActionHandler_CrusadeMap_Main)
    MenuItemActionHandler_CrusadeMap_Main;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004D91D0, &OpenSHC::UI::MenuView_CrusadeEndscreen_DoInitial)
    MenuView_CrusadeEndscreen_DoInitial;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D9230,
        &OpenSHC::UI::MenuItemActionHandler_CrusadeEndscreen_Main)
    MenuItemActionHandler_CrusadeEndscreen_Main;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(undefined4 param_1), false, Address::SHC_3BB0A8C1_0x004D9270, &OpenSHC::UI::FUN_004d9270)
    FUN_004d9270;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004D9700, &OpenSHC::UI::MenuView_RankingGames_Prepare)
    MenuView_RankingGames_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D9730,
        &OpenSHC::UI::MenuItemActionHandler_RankingGames_Main)
    MenuItemActionHandler_RankingGames_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D99F0,
        &OpenSHC::UI::MenuItemRenderFunction_RankingGames_Main)
    MenuItemRenderFunction_RankingGames_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue),
        false, Address::SHC_3BB0A8C1_0x004D9B30, &OpenSHC::UI::MenuItemActionHandler_RankingGames_Scrollbar)
    MenuItemActionHandler_RankingGames_Scrollbar;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged), false,
        Address::SHC_3BB0A8C1_0x004D9C10, &OpenSHC::UI::MenuItemRenderFunction_RankingGames_Scrollbar)
    MenuItemRenderFunction_RankingGames_Scrollbar;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004D9CC0, &OpenSHC::UI::MenuModalRenderFunctionMenuModal_DeleteGameRecord)
    MenuModalRenderFunctionMenuModal_DeleteGameRecord;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D9D60,
        &OpenSHC::UI::MenuItemActionHandler_DeleteGameRecord_Main)
    MenuItemActionHandler_DeleteGameRecord_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int x, int y, int width, int height), false,
        Address::SHC_3BB0A8C1_0x004D9DB0, &OpenSHC::UI::MenuModalRenderFunction_TacticalPowerBar)
    MenuModalRenderFunction_TacticalPowerBar;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004D9EC0,
        &OpenSHC::UI::MenuItemRenderFunction_TacticalPowerBar_Main)
    MenuItemRenderFunction_TacticalPowerBar_Main;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004DA050,
        &OpenSHC::UI::MenuItemActionHandler_TacticalPowerBar_Main)
    MenuItemActionHandler_TacticalPowerBar_Main;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DA180, &OpenSHC::UI::FUN_004da180)
    FUN_004da180;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DA200, &OpenSHC::UI::FUN_004da200)
    FUN_004da200;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DA300, &OpenSHC::UI::resetCredits)
    resetCredits;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 param_1, undefined4 param_2), false,
        Address::SHC_3BB0A8C1_0x004DA7A0, &OpenSHC::UI::FUN_004da7a0)
    FUN_004da7a0;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(undefined4 param_1), false, Address::SHC_3BB0A8C1_0x004DA7E0, &OpenSHC::UI::FUN_004da7e0)
    FUN_004da7e0;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DA810, &OpenSHC::UI::FUN_004da810)
    FUN_004da810;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DA840, &OpenSHC::UI::FUN_004da840)
    FUN_004da840;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DA870, &OpenSHC::UI::FUN_004da870)
    FUN_004da870;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DA8A0, &OpenSHC::UI::FUN_004da8a0)
    FUN_004da8a0;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5), false,
        Address::SHC_3BB0A8C1_0x004DA8D0, &OpenSHC::UI::FUN_004da8d0)
    FUN_004da8d0;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004DA9A0, &OpenSHC::UI::FUN_004da9a0)
    FUN_004da9a0;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, undefined4 param_3, undefined4 param_4,
                                undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8),
        false, Address::SHC_3BB0A8C1_0x004DA9F0, &OpenSHC::UI::FUN_004da9f0)
    FUN_004da9f0;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 param_1, char* param_2, undefined4 param_3, undefined4 param_4,
                                undefined4 param_5, undefined4 param_6),
        false, Address::SHC_3BB0A8C1_0x004DAA80, &OpenSHC::UI::FUN_004daa80)
    FUN_004daa80;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, undefined4 param_2, undefined4 param_3), false,
        Address::SHC_3BB0A8C1_0x004DAB00, &OpenSHC::UI::FUN_004dab00)
    FUN_004dab00;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* param_1, undefined4 param_2, int param_3, undefined4 param_4), false,
        Address::SHC_3BB0A8C1_0x004DAB80, &OpenSHC::UI::FUN_004dab80)
    FUN_004dab80;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 param_1, undefined4 param_2), false,
        Address::SHC_3BB0A8C1_0x004DABF0, &OpenSHC::UI::FUN_004dabf0)
    FUN_004dabf0;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, undefined4 param_3, undefined4 param_4,
                                undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8),
        false, Address::SHC_3BB0A8C1_0x004DAC30, &OpenSHC::UI::FUN_004dac30)
    FUN_004dac30;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004DACF0, &OpenSHC::UI::FUN_004dacf0)
    FUN_004dacf0;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DAFB0, &OpenSHC::UI::FUN_004dafb0)
    FUN_004dafb0;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004DB0D0, &OpenSHC::UI::FUN_004db0d0)
    FUN_004db0d0;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 param_1, undefined4 param_2), false,
        Address::SHC_3BB0A8C1_0x004DB180, &OpenSHC::UI::FUN_004db180)
    FUN_004db180;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int storedMenuStringIndex, undefined4 param_2, undefined4 param_3,
                                int allowedWidth, undefined4 param_5, int fontSize),
        false, Address::SHC_3BB0A8C1_0x004DB300, &OpenSHC::UI::TrimStoredMenuString)
    TrimStoredMenuString;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(float param_1), false, Address::SHC_3BB0A8C1_0x004DB390, &OpenSHC::UI::FUN_004db390)
    FUN_004db390;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DB4F0,
        &OpenSHC::UI::MenuView_HistoricMissionPicture_Prepare)
    MenuView_HistoricMissionPicture_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DB5C0,
        &OpenSHC::UI::MenuView_General_DoInitial_BlackBorderAndGfx)
    MenuView_General_DoInitial_BlackBorderAndGfx;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DB600,
        &OpenSHC::UI::MenuView_HistoricMissionPicture_DoEveryFrame)
    MenuView_HistoricMissionPicture_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DB7B0,
        &OpenSHC::UI::MenuView_HistoricMissionIntro_Prepare)
    MenuView_HistoricMissionIntro_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DB8B0,
        &OpenSHC::UI::MenuView_HistoricMissionIntro_DoEveryFrame)
    MenuView_HistoricMissionIntro_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DBAF0,
        &OpenSHC::UI::MenuView_HistoricCampaignIntro_Prepare)
    MenuView_HistoricCampaignIntro_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DBBC0,
        &OpenSHC::UI::MenuView_HistoricCampaignIntro_DoEveryFrame)
    MenuView_HistoricCampaignIntro_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DBE30,
        &OpenSHC::UI::MenuView_HistoricCampaignOutro_Prepare)
    MenuView_HistoricCampaignOutro_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DBF00,
        &OpenSHC::UI::MenuView_HistoricCampaignOutro_DoEveryFrame)
    MenuView_HistoricCampaignOutro_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(
        undefined4(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DC140, &OpenSHC::UI::FUN_004dc140)
    FUN_004dc140;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DC1C0, &OpenSHC::UI::FUN_004dc1c0)
    FUN_004dc1c0;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DC500,
        &OpenSHC::UI::MenuView_MissionFinishedTransition_DoEveryFrame)
    MenuView_MissionFinishedTransition_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DC9E0, &OpenSHC::UI::MenuView_GameLost_DoEveryFrame)
    MenuView_GameLost_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DCC70,
        &OpenSHC::UI::MenuView_Unknown26_CampaignRelatedUnk_Prepare)
    MenuView_Unknown26_CampaignRelatedUnk_Prepare;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DCC90, &OpenSHC::UI::MenuView_CampaignUnk_Prepare)
    MenuView_CampaignUnk_Prepare;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DD0C0, &OpenSHC::UI::MenuView_CampaignUnk_DoInitial)
    MenuView_CampaignUnk_DoInitial;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DD100, &OpenSHC::UI::MenuView_ScenarioDescription_Prepare)
    MenuView_ScenarioDescription_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DD300,
        &OpenSHC::UI::MenuView_ScenarioDescription_DoInitial)
    MenuView_ScenarioDescription_DoInitial;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DD350,
        &OpenSHC::UI::MenuView_ScenarioDescription_DoEveryFrame)
    MenuView_ScenarioDescription_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DD750,
        &OpenSHC::UI::MenuView_General_DoInitial_CrusadeAndRankMenu)
    MenuView_General_DoInitial_CrusadeAndRankMenu;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DD7B0,
        &OpenSHC::UI::MenuView_CrusadeMissionIntro_DoEveryFrame)
    MenuView_CrusadeMissionIntro_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DE300, &OpenSHC::UI::MenuView_CrusadeMap_DoEveryFrame)
    MenuView_CrusadeMap_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DF2E0, &OpenSHC::UI::MenuView_CrusadeEndscreen_Prepare)
    MenuView_CrusadeEndscreen_Prepare;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DFB90, &OpenSHC::UI::MenuView_RankingGames_DoEveryFrame)
    MenuView_RankingGames_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004E1A20, &OpenSHC::UI::MenuView_UnusedExtremeAd_Prepare)
    MenuView_UnusedExtremeAd_Prepare;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004E1A50, &OpenSHC::UI::MenuView_UnusedExtremeAd_DoInitial)
    MenuView_UnusedExtremeAd_DoInitial;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004E1AA0,
        &OpenSHC::UI::MenuView_UnusedExtremeAd_DoEveryFrame)
    MenuView_UnusedExtremeAd_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004E1B30,
        &OpenSHC::UI::MenuView_MissionFinishedTransition_Prepare)
    MenuView_MissionFinishedTransition_Prepare;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004E1E30,
        &OpenSHC::UI::MenuView_Unknown26_CampaignRelatedUnk_DoInitial)
    MenuView_Unknown26_CampaignRelatedUnk_DoInitial;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004E1E70,
        &OpenSHC::UI::MenuView_Unknown26_CampaignRelatedUnk_DoEveryFrame)
    MenuView_Unknown26_CampaignRelatedUnk_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004E1F50,
        &OpenSHC::UI::MenuView_CrusadeEndscreen_DoEveryFrame)
    MenuView_CrusadeEndscreen_DoEveryFrame;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004F6A60,
        &OpenSHC::UI::MenuItemActionHandler_General_DisplayConditionalText)
    MenuItemActionHandler_General_DisplayConditionalText;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004F6A70,
        &OpenSHC::UI::MenuItemActionHandler_General_RemoveConditionalTextOrReleaseHoverUnk)
    MenuItemActionHandler_General_RemoveConditionalTextOrReleaseHoverUnk;

} // namespace UI_Func
} // namespace OpenSHC
