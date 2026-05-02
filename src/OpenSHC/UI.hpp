/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/UI/ChooseNetworkServiceProvider/ChooseNetworkServiceProviderButtonActionsInt.hpp"
#include "OpenSHC/UI/Enums/SoundMenuClickTypeInt.hpp"
#include "OpenSHC/UI/Multiplayer/FindingNetworkSessions_ButtonParametersInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"
namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::CommandBuildingTypeInt;
    using OpenSHC::Game::Resources::ResourceTypeInt;
    using OpenSHC::UI::ChooseNetworkServiceProvider::ChooseNetworkServiceProviderButtonActionsInt;
    using OpenSHC::UI::Enums::SoundMenuClickTypeInt;
    using OpenSHC::UI::Multiplayer::FindingNetworkSessions_ButtonParametersInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    void __stdcall MenuView_IntroLogos_Prepare();

    void __stdcall MenuView_IntroLogos_DoInitial();

    void __stdcall MenuView_IntroLogos_DoEveryFrame();

    void __cdecl MenuItemActionHandler_IntroLogos_General(int unused);

    void __stdcall MenuView_IntroVideo_Prepare();

    void __stdcall MenuView_IntroVideo_DoEveryFrame();

    void __stdcall MenuView_GameStartEnterName_DoEveryFrame();

    void __stdcall MenuView_MainMenu_Prepare();

    void __stdcall MenuView_MainMenu_DoInitial();

    void __stdcall MenuView_MainMenu_DoEveryFrame();

    void __cdecl MenuItemRenderFunction_MainMenu_Main(int param_1);

    void __cdecl MenuItemActionHandler_MainMenu_Main(int param_1);

    void __stdcall MenuView_HistoricCampaignSelect_Prepare();

    void __stdcall MenuView_HistoricCampaignSelect_DoEveryFrame();

    void __cdecl MenuItemRenderFunction_HistoricCampaignSelect_Main(int param_1);

    void __cdecl MenuItemActionHandler_HistoricCampaignSelect_Main(int param_1);

    void __stdcall MenuView_UnusedEconomicGametypeSelect_Prepare();

    void __stdcall MenuView_UnusedEconomicGametypeSelect_DoInitial();

    void __cdecl MenuItemRenderFunction_UnusedEconomicGametypeSelect_Main(int param_1);

    void __cdecl MenuItemActionHandler_UnusedEconomicGametypeSelect_Main(int param_1);

    void __stdcall MenuView_CustomScenarios_Prepare();

    void __stdcall MenuView_General_DoInitial_BlackBoxDefaultBorderAndPicture();

    void __stdcall MenuView_CustomScenarios_DoEveryFrame();

    void __cdecl MenuItemRenderFunction_CustomScenarios_Main(int param_1);

    void __stdcall MenuView_Credits_Prepare();

    void __stdcall MenuView_Credits_DoInitial();

    void __stdcall MenuView_Credits_DoEveryFrame();

    void __stdcall MenuView_UnusedDemoBuyItScreen_Prepare();

    void __stdcall MenuView_UnusedDemoBuyItScreen_DoInitial();

    void __stdcall MenuView_UnusedDemoBuyItScreen_DoEveryFrame();

    void __cdecl MenuModalRenderFunction_UnusedSetName(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_UnusedSetName_ButtonsUnk(int param_1);

    void __cdecl MenuItemActionHandler_UnusedSetName_ButtonsUnk(int param_1);

    void __stdcall MenuView_HistoricMissionSelect_Prepare();

    void __stdcall MenuView_MissionSelect_DoEveryFrame();

    void __cdecl MenuItemRenderFunction_HistoricMissionSelect_MissionRows(int param_1);

    void __cdecl MenuItemActionHandler_HistoricMissionSelect_General(int param_1);

    void __stdcall MenuView_UnusedEconomicMissionSelect_Prepare();

    void __cdecl MenuItemRenderFunction_HistoricAndEconomicMissionSelect_NextAndBackHands(int param_1);

    void __cdecl MenuItemRenderFunction_UnusedEconomicMissionSelect_MissionSelect(int param_1);

    void __cdecl MenuItemActionHandler_UnusedEconomicMissionSelect_General(int param_1);

    void __stdcall MenuView_UnusedSomeMissionStartUnk_Prepare();

    void __cdecl MenuItemRenderFunction_UnusedSomeMissionStartUnk_General(int param_1);

    void __cdecl MenuItemActionHandler_UnusedSomeMissionStartUnk_General(int param_1);

    void __stdcall MenuView_MpConnection_Prepare();

    void __stdcall MenuView_General_DoEveryFrame_FirstGfxCentered();

    void __stdcall MenuView_Unknown61ReturnToSkrimishMenuUnk_DoInitial();

    void __stdcall MenuView_Unknown61ReturnToSkrimishMenuUnk_DoEveryFrame();

    void __stdcall MenuView_LobbyMenu_Prepare();

    void __stdcall MenuView_General_DoInitial_DefaultMainMenuStructure();

    void __cdecl MenuItemRenderFunction_LobbyMenu_MapSelectHeader(int param_1);

    void __cdecl MenuItemRenderFunction_LobbyMenu_PlayerListAndNpcButtons(int param_1);

    void __cdecl MenuItemRenderFunction_General_MenuMiniMap(int param_1);

    void __cdecl MenuItemRenderFunction_LobbyMenu_MapDesc(int param_1);

    void __cdecl MenuItemActionHandler_LobbyMenu_MapDescScrollbar(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_LobbyMenu_MapDescScrollbar(
        int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

    void __cdecl MenuItemRenderFunction_General_AdvancedGameOptions(int param_1);

    void __cdecl MenuItemActionHandler_General_AdvancedGameOptions(int param_1);

    void __cdecl MenuItemRenderFunction_LobbyMenu_SkirmishTypeAndBalance(int param_1);

    void __cdecl MenuItemActionHandler_LobbyMenu_SkirmishTypeAndBalance(int param_1);

    void __cdecl MenuItemRenderFunction_LobbyMenu_Unknown(int param_1);

    void __cdecl MenuItemRenderFunction_LobbyMenu_ChatBox(int param_1);

    void __cdecl MenuItemRenderFunction_LobbyMenu_NonBoxedButtons(int param_1);

    void __cdecl MenuItemActionHandler_LobbyMenu_MapSelectTable(int param_1);

    void __cdecl MenuItemRenderFunction_LobbyMenu_MapSelectTable(int param_1);

    void __cdecl MenuItemActionHandler_LobbyMenu_MapSelectScrollbar(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_LobbyMenu_MapSelectScrollbar(
        int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

    void __stdcall MenuView_UnusedSelectRandomNumberOfEnemies_DoEveryFrame();

    void __cdecl MenuItemActionHandler_UnusedSelectRandomNumberOfEnemies_Main(int param_1);

    void __stdcall MenuView_General_Prepare_SwordShieldAndBorder();

    void __stdcall MenuView_SelectCrusade_DoInitial();

    void __stdcall MenuView_SelectCrusade_DoEveryFrame();

    void __cdecl MenuItemActionHandler_SelectCrusade_Main(int param_1);

    void __cdecl MenuItemRenderFunction_SelectCrusade_Main(int param_1);

    void __stdcall MenuView_Unknown33_DoEveryFrame();

    void __cdecl MenuItemRenderFunction_SingleplayerMapChoice_ButtonsAndHands(int param_1);

    void __cdecl MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands(int param_1);

    void __cdecl MenuItemRenderFunction_SingleplayerMapChoice_MapTable(int param_1);

    void __cdecl MenuItemRenderFunction_SingleplayerMapChoice_MapTableHeader(int param_1);

    void __cdecl MenuItemRenderFunction_SingleplayerMapChoice_Scrollbar(
        int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

    void __stdcall MenuView_UnusedOldTitleMenu_Prepare();

    void __stdcall MenuView_UnusedOldTitleMenu_DoInitial();

    void __cdecl MenuItemRenderFunction_UnusedOldTitleMenu_ExitButton(int param_1);

    void __cdecl MenuItemRenderFunction_UnusedOldTitleMenu_ContinueButton(int param_1);

    void __cdecl MenuItemRenderFunction_UnusedOldTitleMenu_TestMapButton(int param_1);

    void __stdcall MenuView_MapEditorProperties_Prepare();

    void __stdcall MenuView_MapEditorProperties_DoEveryFrame();

    void __cdecl MenuItemRenderFunction_MapEditorProperties_MainButtons(int param_1);

    void __cdecl MenuItemRenderFunction_MapEditorProperties_MapDescriptionBox(int param_1);

    void __cdecl MenuItemActionHandler_MapEditorProperties_MapDescriptionBox();

    void __cdecl MenuItemActionHandler_MapEditorProperties_MapDescriptionScrollbar(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_MapEditorProperties_MapDescriptionScrollbar(
        int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

    void __stdcall MenuView_NewMapMaptype_Prepare();

    void __cdecl MenuItemRenderFunction_NewMapMaptype_Buttons(int param_1);

    void __cdecl MenuItemActionHandler_NewMapMaptype_Buttons(int param_1);

    void __stdcall MenuView_NewMapMapsize_Prepare();

    void __stdcall MenuView_NewMapMapsize_DoEveryFrame();

    void __cdecl MenuItemRenderFunction_NewMapMapsize_Buttons(int param_1);

    void __cdecl MenuItemActionHandler_NewMapMapsize_Buttons(int param_1);

    void __stdcall MenuView_UnusedChooseAvailableKeeps_Prepare();

    void __stdcall MenuView_UnusedChooseAvailableKeeps_DoEveryFrame();

    void __cdecl MenuItemRenderFunction_UnusedChooseAvailableKeeps_Main(int param_1);

    void __cdecl MenuItemActionHandler_UnusedChooseAvailableKeeps_Main(int param_1);

    void __stdcall MenuView_General_DoInitial_ScreenToBlack();

    void __stdcall MenuView_UnusedChooseGameType_DoEveryFrame();

    void __cdecl MenuItemRenderFunctio_UnusedChooseGameType_Mainn(int param_1);

    void __cdecl MenuItemActionHandler_UnusedChooseGameType_Main(int param_1);

    void __stdcall MenuView_UnusedCreateSiege_Prepare();

    void __stdcall MenuView_UnusedCreateSiege_DoEveryFrame();

    void __cdecl MenuItemRenderFunction_UnusedCreateSiege_SiegeThat(int param_1);

    void __stdcall MenuView_MapEditorLandscaping_Prepare();

    void __stdcall MenuView_MapEditorLandscaping_DoInitial();

    void __stdcall MenuView_MapEditorLandscaping_DoEveryFrame();

    void __cdecl MenuItemActionHandler_MapEditorLandscaping_CategoryButtons(int param_1);

    void __cdecl MenuItemActionHandler_MapEditorLandscaping_GeneralButtons(CommandBuildingTypeInt param_1);

    void __stdcall MenuView_BuildMenu_Prepare();

    void __stdcall MenuView_BuildMenu_DoInitial();

    void __stdcall MenuView_BuildMenu_DoEveryFrame();

    void __cdecl MenuItemActionHandler_BuildMenu_SomeKeepAndGranaryCheckUnk(int param_1);

    void __cdecl MenuItemActionHandler_InGameMenu_UnknownBinkRelated(int param_1);

    void __stdcall RenderScribeFrame();

    void __cdecl MenuItemActionHandler_InGameMenu_ProcessScribeAnimationChange(int param_1);

    void __cdecl MenuItemActionHandler_InGameMenu_ViewToKeeps(int param_1);

    void __stdcall RenderGoldValue();

    void __cdecl MenuItemActionHandler_InGameMenu_Scrolling(int param_1);

    void __cdecl MenuItemRenderFunction_BuildMenu_BuildingKeepSubcategoryButton(int param_1);

    void __cdecl MenuItemActionHandler_General_Unknown2(int param_1);

    void __cdecl MenuItemActionHandler_InGameMenu_MiniMapInteraction(int param_1);

    void __cdecl MenuItemRenderFunction_BuildMenu_MiniMapInteraction(int param_1);

    void __cdecl MenuItemActionHandler_InGameMenu_PeasantBuildAndRightClickMenuSelection(int param_1);

    void __cdecl MenuItemActionHandler_InGameMenu_UnitSelectionAndControlsUnk(int param_1);

    void __stdcall MenuItemActionHandler_InGameMenu_TriggerPlaceWallCommand();

    void __cdecl MenuItemActionHandler_BuildMenu_DeleteAction(int param_1);

    void __cdecl MenuItemActionHandler_InGameMenu_RightClickMenuAndMaybeResets(int param_1);

    void __cdecl MenuItemRenderFunction_BuildMenu_UnitActionButtons(int mapperValue);

    void __cdecl MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroops(int param_1);

    void __cdecl MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroopsDeselectHelper(int param_1);

    void __cdecl MenuItemActionHandler_BuildMenu_CurrentlySelectedTroops(int slotID);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_StopBuildingOrPeasantBinkPlayback();

    void __stdcall MenuView_BuildingAndStatusMenu_DoInitial();

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_Unknown_Countdown();

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_BuildingHelpTextButton();

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_BuildingHelpTextButton(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_BarracksAndMercenaryPostHelpText(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_AvailablePeasantsTextUpperRight(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_AvailablePeasantsTextDownRight(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_StatusMenuButtons(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_StatusMainMenuButtons(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_PopularityMenuSwitchButtonUnk();

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_PopularityMenuSwitchButton(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_DisableFoodType(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_DisableFoodType(int foodType);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_ArmySwitchButton();

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_ArmyStatusSwitchButton();

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_ArmyStatusReturn(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_ReturnToBuildMenu(int param_1);

    void __stdcall FUN_00440360();

    void __stdcall MenuView_UnusedHelpTextEditor_Prepare();

    void __stdcall MenuView_UnusedHelpTextEditor_DoEveryFrame();

    void __cdecl MenuItemFunction_General_Unknown(int param_1);

    void __cdecl MenuItemActionHandler_UnusedOldTitleMenu_General(int param_1);

    void __cdecl MenuView_GameStartEnterName_Prepare(void* param_1);

    void __stdcall MenuView_GameStartEnterName_DoInitial();

    void __cdecl MenuItemActionHandler_CustomScenarios_Main(int param_1);

    void __stdcall MenuView_Unknown61ReturnToSkrimishMenuUnk_Prepare();

    void __cdecl MenuItemActionHandler_LobbyMenu_MapSelectHeader(int param_1);

    void __cdecl MenuItemActionHandler_LobbyMenu_PlayerListAndNpcButtons(int param_1);

    void __cdecl MenuItemActionHandler_LobbyMenu_LobbyscreenStartButtonClick(int param_1);

    void __cdecl MenuItemActionHandler_SingleplayerMapChoice_MapTable(int param_1);

    void __cdecl MenuItemActionHandler_SingleplayerMapChoice_Scrollbar(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemActionHandler_MapEditorProperties_MainButtons(int param_1);

    void __cdecl MenuItemActionHandler_UnusedCreateSiege_SiegeThat(int param_1);

    void __cdecl MenuItemActionHandler_MapEditorLandscaping_QueueCommandCallback();

    void __cdecl MenuItemActionHandler_General_ToolbarButtonPressed(CommandBuildingTypeInt buttonID);

    void __cdecl MenuItemActionHandler_InGameMenu_MainButtons(int param_1);

    void __cdecl MenuItemActionHandler_InGameMenu_TriggerPlaceBuildingCommand(int param_1);

    void __cdecl MenuItemActionHandler_BuildMenu_UnitActionButtons(int param_1);

    void __stdcall MenuView_BuildingAndStatusMenu_Prepare();

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_BuildingWorkStatus(int param_1);

    void __stdcall MenuView_LobbyMenu_DoEveryFrame();

    void __stdcall MenuView_SingleplayerMapChoice_Prepare();

    void __stdcall MenuView_SingleplayerMapChoice_DoEveryFrame();

    void __cdecl MenuItemActionHandler_SingleplayerMapChoice_MapTableHeader(int param_1);

    void __stdcall MenuView_BuildingAndStatusMenu_DoEveryFrame();

    void __cdecl MenuItemRenderFunction_TextEditor_Buttons(int param_1);

    void __cdecl MenuItemActionHandler_TextEditor_Scrollbar(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_TextEditor_Scrollbar(
        int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

    void __cdecl MenuItemRenderFunction_DisplayScenarioHelpText_AnotherButtonUnk(int param_1);

    void __cdecl MenuItemActionHandler_TextEditor_TextInputRelatedUnk();

    void __cdecl MenuItemActionHandler_TextEditor_Buttons(int param_1);

    void __cdecl MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface();

    void __cdecl MenuItemRenderFunction_ChooseRandomNumberOfEnemies_Main(int param_1);

    void __cdecl MenuItemRenderFunction_InGameMenu_MainButtons(int param_1);

    void __cdecl MenuItemRenderFunction_MapEditorLandscaping_GeneralButtons(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_Unknown_Min1();

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_BarracksWeaponAvailability(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_UnknownMin1Unk();

    BOOLEnum __cdecl HasEnoughGold(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_WorkshopWeaponSelection(ResourceTypeInt _weapon);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_WorkshopWeaponSelection(ResourceTypeInt weapon);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_DrawbridgeOpenClose(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_DrawbridgeOpenClose(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_GatehouseOpenClose(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_GatehouseOpenClose(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_TaxSlider(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_HorizontalSlider(
        int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_TaxArrowButtons(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_TaxArrowButtons(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_ChangeRations(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_GeneralButtonRender(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_MarketMenuChangeButtons(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_SelectBuySellGoods(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_SelectBuySellGoods(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_BuySellMenuButtonsAndHands(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_BuildingSleep();

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_RepairBuildingButton();

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_RepairBuildingButton(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_OutpostUnitSelection(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_OutpostUnitSelection(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_OutpostSliderSize(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_OutpostSliderDelay(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_BuildMenu_BuildingIcons(int param_1);

    void __cdecl MenuItemRenderFunction_BuildMenu_BuildingSubcategoryButton(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_BarrackUnitPortraits(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_MercenaryPostPortraits(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_EngineerAndMonkPortraits(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_TunnelerPortrait(int param_1);

    void __cdecl DisableMercPostPortraits();

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_EngineerAndMonkPortraits(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_TunnelerPortrait(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_BuySellMenuButtonsAndHands(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_BarrackMenuClick(int barrackUnitIdUnk);

    void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_MercenaryPostPortraits(int param_1);

    undefined4 __cdecl TicksSinceCounterStart();

    void __stdcall FUN_00471a80();

    void __cdecl MenuItemRenderFunction_NetworkSessions_Buttons(int param_1);

    void __cdecl MenuModalRenderFunction_ChooseNetworkServiceProvider(int x, int y, int width, int height);

    void __cdecl MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderScrollbarUnk(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_ChooseNetworkServiceProvider_ProviderTableRows(int param_1);

    void __cdecl MenuItemActionHandler_General_TextInputDisplay(int param_1);

    void __cdecl MenuItemRenderFunction_General_TextInputDisplay(int param_1);

    void __cdecl MenuItemRenderFunction_ChooseNetworkServiceProvider_InputLabels(int param_1);

    void __cdecl MenuItemRenderFunction_ChooseNetworkServiceProvider_YourIpDisplay(int param_1);

    void __cdecl MenuItemActionHandler_ChooseNetworkServiceProvider_ModemScrollbarUnk(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemActionHandler_ChooseNetworkServiceProvider_ModemTableRows(int param_1);

    void __cdecl MenuItemRenderFunction_ChooseNetworkServiceProvider_ModemTableRows(int param_1);

    void __cdecl MenuModalRenderFunction_FindingNetworkSessions(int x, int y, int width, int height);

    void __cdecl MenuItemActionHandler_FindingNetworkSessions_Scrollbar(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemActionHandler_FindingNetworkSessions_TableRows(int param_1);

    void __cdecl MenuItemRenderFunction_FindingNetworkSessions_TableRows(int param_1);

    void __cdecl MenuModalRenderFunction_WaitingForHost(int x, int y, int width, int height);

    void __cdecl MenuItemActionHandler_WaitingForHost_Button(int param_1);

    void __cdecl MenuItemRenderFunction_WaitingForHost_Button(int param_1);

    void __cdecl MenuItemRenderFunction_Chat_MostButtons(int param_1);

    void __cdecl MenuItemActionHandler_Chat_SendMessageToPlayer(int param_1);

    void __cdecl MenuItemRenderFunction_Chat_TauntButtons(int param_1);

    void __cdecl MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderTableRows(int param_1);

    void __cdecl MenuItemActionHandler_FindingNetworkSessions_EnumerateDPlaySessions(int param_1);

    void __cdecl MenuItemActionHandler_Chat_MostButtons(int param_1);

    void __cdecl MenuItemActionHandler_Chat_TauntButtons(int param_1);

    void __cdecl MenuItemActionHandler_ChooseNetworkServiceProvider_Buttons(
        ChooseNetworkServiceProviderButtonActionsInt param_1);

    void __cdecl MenuItemActionHandler_FindingNetworkSessions_Buttons(
        FindingNetworkSessions_ButtonParametersInt param_1);

    void __cdecl MenuItemActionHandler_WaitingForHost_ConnectToLobby();

    void __cdecl MenuModalRenderFunction_OptionsMenu(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_OptionsMenu_Buttons(int param_1);

    void __cdecl MenuItemRenderFunction_OptionsMenu_SubOptionsButtons(int param_1);

    void __cdecl MenuModalRenderFunction_IdentityOptions(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_EnterTitleOnGameStart(int x, int y, int width, int height);

    void __cdecl MenuItemActionHandler_EnterTitleOnGameStart_Button(int param_1);

    void __cdecl MenuItemRenderFunction_EnterTitleOnGameStart_Button(int param_1);

    void __cdecl MenuItemActionHandler_IdentityOptions_LordIcons(int param_1);

    void __cdecl MenuItemRenderFunction_IdentityOptions_LordIcons(int param_1);

    void __cdecl MenuModalRenderFunction_GameplayOptions(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_GameplayOptions_Buttons(int param_1);

    void __cdecl MenuItemActionHandler_GameplayOptions_SpeedSlider(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_GameplayOptions_SpeedSlider(
        int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

    void __cdecl MenuModalRenderFunction_VideoOptions(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_VideoOptions_Main(int param_1);

    void __cdecl MenuModalRenderFunction_SoundOptions(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_SoundOptions_Buttons(int param_1);

    void __cdecl MenuItemActionHandler_SoundOptions_VolumeSlider(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_SoundOptions_VolumeSlider(
        int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

    void __cdecl MenuModalRenderFunction_NetworkOptions(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_SaveLoadMap_Buttons(int param_1);

    void __cdecl MenuItemActionHandler_SaveLoadMap_Scrollbar(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_SaveLoadMap_Scrollbar(
        int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

    void __cdecl MenuItemRenderFunction_SaveLoadMap_TableContent(int param_1);

    void __cdecl MenuItemActionHandler_SaveLoadMap_TableHeader(int param_1);

    void __cdecl MenuItemRenderFunction_SaveLoadMap_TableHeader(int param_1);

    void __cdecl MenuModalRenderFunction_SaveMap(int x, int y, int width, int height);

    void __cdecl MenuItemActionHandler_SaveMap_TableContent(int param_1);

    void __cdecl MenuItemRenderFunction_SaveMap_InputTextDisplay(int param_1);

    void __cdecl MenuModalRenderFunction_YesNoDialog(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_General_GameOptionsTextButton(int param_1);

    void __cdecl MenuModalRenderFunction_ProgressBarBox(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_OnlineQuitGame(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_OnlineVoteQuitGame(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_OnlineVoteQuitAndQuitGame_Main(int param_1);

    void __cdecl MenuItemActionHandler_OptionsMenu_SubOptionsButtons(int param_1);

    void __cdecl MenuItemActionHandler_IdentityOptions_Confirm(int param_1);

    void __cdecl MenuItemActionHandler_GameplayOptions_Buttons(int param_1);

    void __cdecl MenuItemActionHandler_VideoOptions_Main(int param_1);

    void __cdecl MenuItemActionHandler_SoundOptions_Buttons(SoundMenuClickTypeInt param_1);

    void __cdecl MenuItemActionHandler_NetworkOptions_LeaveButtonUnk(int param_1);

    void __cdecl MenuModalRenderFunction_LoadMap(int x, int y, int width, int height);

    void __cdecl MenuItemActionHandler_SaveLoadMap_Buttons(int param_1);

    void __cdecl MenuItemActionHandler_LoadMap_TableContent(int param_1);

    void __cdecl MenuItemActionHandler_SaveMap_ReturnKeySave(int param_1);

    void __cdecl MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk(int param_1);

    void __cdecl MenuItemActionHandler_ProgressBarBox_LoadAndSaveGameButtonLogic(int param_1);

    void __cdecl FUN_00495800(int param_1);

    void __cdecl MenuItemActionHandler_OnlineVoteQuitAndQuitGame_Main(int param_1);

    void __cdecl MenuItemActionHandler_OptionsMenu_Buttons(int param_1);

    void __cdecl MenuModalRenderFunction_OverlaySlider(int x, int y, int width, int height);

    void __cdecl MenuItemActionHandler_OverlaySlider_Slider(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_OverlaySlider_Slider(
        int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

    void __cdecl MenuItemRenderFunction_UnusedWinCondition_Options(int param_1);

    void __cdecl MenuModalRenderFunction_DebugDataCurrentPlayerData(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_DebugDataAiInfo(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_DebugDataUnitData(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_DebugDataZoneDataUnk(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_DebugDataMousePointing(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_DebugDataNetwork(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_DebugDataSplitInfo(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_DebugDataMapData(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_TextEditor(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_CreditsScroll(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_DisplayAiLordMessage(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_UnusedChooseMessageBox(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_TraderSettings(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_StartGoods(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_UnusedSiegeAttackingForceUnk(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_CreateOrTriggerInvasion(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_UnusedCreateTimedMessageEvent(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_UnusedCreateMessageEvent(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_NewEvent(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_NewEventCondition(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_NewEventAction(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_BuildingAvailability(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_DisableTroops(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_DisableWeapon(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_TutorialBox_Thunk(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_Chat(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_SkirmishConnectionOptions(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_SkirmishPlayOptions(int x, int y, int width, int height);

    void __cdecl MenuItemActionHandler_EditorMapTypeQuickChange_Main(int param_1);

    void __cdecl MenuItemRenderFunction_EditorMapTypeQuickChange_Main(int param_1);

    void __cdecl MenuModalRenderFunction_TriggerEvent(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_TriggerEventSlider(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_SendMapTo(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_SendReceiveMap_Main(int param_1);

    void __cdecl MenuModalRenderFunction_ReceiveMapFrom(int x, int y, int width, int height);

    void __stdcall FUN_004ac650();

    void __cdecl MenuModalRenderFunction_Allies(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_Allies_Main(int param_1);

    void __cdecl MenuModalRenderFunction_AlliesOrder(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_AlliesOrder_Main(int param_1);

    void __cdecl MenuModalRenderFunction_AlliesRequestGoods(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_AlliesSendAndRequestGoods_Main(int actionParam);

    void __cdecl MenuModalRenderFunction_AlliesSendGoods(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_ChooseRandomNumberOfEnemies(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_GreatestLord(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_GreatestLord_Main(int param_1);

    void __cdecl MenuItemActionHandler_AiLordSelect_Main(int param_1);

    void __cdecl MenuItemRenderFunction_AiLordSelect_Main(int param_1);

    void __cdecl MenuItemActionHandler_Roundtable_Main(int param_1);

    void __cdecl MenuItemRenderFunction_Roundtable_Main(int param_1);

    void __cdecl MenuModalRenderFunction_DebugDataAivStateUnk(int x, int y, int width, int height);

    void __cdecl MenuItemActionHandler_OverlaySlider_Deselect(int param_1);

    void __cdecl MenuItemActionHandler_UnusedWinCondition_DeselectUnk(int param_1);

    void __cdecl MenuItemActionHandler_UnusedWinCondition_Options(int param_1);

    void __cdecl MenuItemActionHandler_SendReceiveMap_Main(int param_1);

    void __cdecl MenuItemActionHandler_Allies_Main(int param_1);

    void __cdecl MenuItemActionHandler_AlliesOrder_Main(int param_1);

    void __cdecl MenuItemActionHandler_AlliesSendAndRequestGoods_Main(int param_1);

    void __cdecl MenuItemActionHandler_ChooseRandomNumberOfEnemies_Main(int param_1);

    void __cdecl MenuItemActionHandler_GreatestLord_Main(int param_1);

    void __cdecl MenuModalRenderFunction_AiLordSelect(int x, int y, int width, int height);

    void __cdecl MenuModalRenderFunction_Roundtable(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_InGameMenu_MapEventIconUnk(int param_1);

    void __cdecl MenuItemActionHandler_InGameMenu_MapEventIconUnk(int param_1);

    void __cdecl MenuItemRenderFunction_InGameMenu_KeepEnclosedSymbol(int param_1);

    void __cdecl MenuItemRenderFunction_InGameMenu_BikMessagePlayerShield(int param_1);

    void __cdecl FUN_004b7f60(uint param_1, int param_2);

    void __stdcall MenuView_General_DoInitial_OnlySetMenuXY();

    void __stdcall MenuView_EditScenario_DoEveryFrame();

    void __stdcall FUN_004b8210();

    void __cdecl MenuItemActionHandler_EditScenario_BaseMenuButtons(int param_1);

    void __cdecl MenuItemActionHandler_EditScenario_DateYearBox(int param_1);

    void __cdecl MenuItemActionHandler_EditScenario_Scrollbar(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemActionHandler_EditScenario_EventAndInvasionList(int param_1);

    void __cdecl MenuItemRenderFunction_EditScenario_EventAndInvasionList(int param_1);

    void __cdecl MenuItemActionHandler_EditScenario_UpDownButtons(int param_1);

    void __cdecl MenuItemRenderFunction_EditScenario_UpDownButtons(int param_1);

    void __cdecl MenuItemActionHandler_NewInvasion_UnitButtons(int unitTypeMenuID);

    void __cdecl MenuItemRenderFunction_NewInvasion_UnitButtons(int param_1);

    void __cdecl MenuItemActionHandler_NewInvasion_RepeatSlider(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_NewInvasion_RepeatSlider(
        int param_1, int thumbXPos, int sliderValue, int thumbWidth, BOOLEnum isDragged);

    void __stdcall FUN_004b9610();

    void __cdecl MenuItemActionHandler_NewEventCondition_Main(int param_1);

    void __cdecl MenuItemActionHandler_NewEventAction_Main(int param_1);

    void __cdecl MenuItemActionHandler_General_EventSlider(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_General_EventSlider(
        int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

    void __cdecl MenuItemActionHandler_UnusedCreateMessageEvent_Unknown(int index);

    void __cdecl MenuItemActionHandler_SiegeAttackingForceAndStartGoods_Main(int param_1);

    void __cdecl MenuItemActionHandler_TraderSettings(int param_1);

    void __cdecl MenuItemRenderFunction_UnusedCreateMessageEvent_Buttons(int param_1);

    void __cdecl MenuItemRenderFunction_EditScenario_StartDateMonth(int param_1);

    void __cdecl MenuItemRenderFunction_EditScenario_StartDate(int param_1);

    void __cdecl MenuItemActionHandler_General_MessageScrollbar(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_General_Scrollbar(
        int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

    void __cdecl MenuItemRenderFunction_General_MessageScrollbarUpDown(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAvailability_Buttons(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAvailability_Buttons(int param_1);

    void __cdecl MenuItemRenderFunction_BuildingAvailability_TableRows(int param_1);

    void __cdecl MenuItemActionHandler_BuildingAvailability_Scrollbar(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemActionHandler_DisableEuroTroops_Main(int param_1);

    void __cdecl MenuItemRenderFunction_DisableEuroTroops_Main(int param_1);

    void __cdecl MenuItemActionHandler_DisableArabTroops_Main(int param_1);

    void __cdecl MenuItemRenderFunction_DisableArabTroops_Main(int param_1);

    void __cdecl MenuItemActionHandler_DisableWeapon_Main(int param_1);

    void __cdecl MenuItemRenderFunction_DisableWeapon_Main(int param_1);

    void __cdecl MenuItemRenderFunction_General_CreateEventCallbackFunction(int param_1);

    void __cdecl MenuItemActionHandler_TriggerInvasion_Main(int param_1);

    void __cdecl MenuItemRenderFunction_TriggerInvasion_Main(int param_1);

    void __cdecl FUN_004bc5f0(int param_1);

    void __cdecl FUN_004bc630(int param_1);

    void __stdcall FUN_004bc6c0();

    void __cdecl FUN_004bc790(int param_1, int param_2);

    void __cdecl FUN_004bc910(int param_1);

    void __cdecl MenuModalRenderFunction_TutorialBox(int x, int y, int width, int height);

    void __cdecl MenuItemActionHandler_TutorialBox_Main(int param_1);

    void __cdecl MenuItemRenderFunction_TutorialBox_Main(int param_1);

    void __stdcall FUN_004bd1b0();

    void __stdcall MenuView_EditScenario_Prepare();

    void __cdecl MenuItemRenderFunction_EditScenario_BaseMenuButtons(int param_1);

    void __cdecl MenuItemRenderFunction_EditScenario_TextBoxLike(int param_1);

    void __cdecl MenuItemActionHandler_UnusedChooseMessageBox_Unknown(int param_1);

    void __cdecl MenuItemActionHandler_NewInvasion_Buttons(int param_1);

    void __cdecl MenuItemRenderFunction_NewInvasion_Buttons(int param_1);

    void __cdecl MenuItemActionHandler_UnusedCreateMessageEvent_SetTextUnk(int param_1);

    void __cdecl MenuItemRenderFunction_General_EventButtonAndData(int param_1);

    void __cdecl MenuItemActionHandler_NewEvent_Main(int param_1);

    void __cdecl MenuItemRenderFunction_NewEventCondition_Main(int param_1);

    void __cdecl MenuItemRenderFunction_NewEventAction_Main(int param_1);

    void __cdecl MenuItemRenderFunction_SiegeAttackingForceAndStartGoods_Main(int param_1);

    void __cdecl MenuItemRenderFunction_TraderSettings(int param_1);

    void __cdecl MenuItemActionHandler_General_CreateEventCallbackFunction(int param_1);

    void __stdcall MenuView_GameLost_Prepare();

    void __cdecl MenuItemActionHandler_MissionEndscreen_Main(int param_1);

    void __cdecl MenuItemRenderFunction_MissionEndscreen_Main(int param_1);

    void __stdcall MenuView_CampaignUnk_DoEveryFrame();

    void __cdecl MenuItemActionHandler_Unknown27CampaignUnk_Main(int param_1);

    void __stdcall FUN_004d6f60();

    void __cdecl MenuItemRenderFunction_ScenarioDescription_Main(int param_1);

    void __cdecl MenuItemActionHandler_ScenarioDescription_Main(int param_1);

    void __cdecl FUN_004d8a20(char* param_1);

    void __stdcall MenuView_CrusadeMissionIntro_Prepare();

    void __cdecl RenderPlayerAvatars(int imageID, int x, int y);

    void __cdecl MenuItemRenderFunction_CrusadeMissionIntro_Main(int param_1);

    void __cdecl MenuItemActionHandler_CrusadeMissionIntro_Main(int param_1);

    void __stdcall MenuView_CrusadeMap_Prepare();

    void __cdecl MenuItemRenderFunction_General_CrusadeMapAndEndscreen(int param_1);

    void __cdecl MenuItemActionHandler_CrusadeMap_Main(int param_1);

    void __stdcall MenuView_CrusadeEndscreen_DoInitial();

    void __cdecl MenuItemActionHandler_CrusadeEndscreen_Main(int param_1);

    void __cdecl FUN_004d9270(undefined4 param_1);

    void __stdcall MenuView_RankingGames_Prepare();

    void __cdecl MenuItemActionHandler_RankingGames_Main(int param_1);

    void __cdecl MenuItemRenderFunction_RankingGames_Main(int param_1);

    void __cdecl MenuItemActionHandler_RankingGames_Scrollbar(
        int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

    void __cdecl MenuItemRenderFunction_RankingGames_Scrollbar(
        int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged);

    void __cdecl MenuModalRenderFunctionMenuModal_DeleteGameRecord(int x, int y, int width, int height);

    void __cdecl MenuItemActionHandler_DeleteGameRecord_Main(int param_1);

    void __cdecl MenuModalRenderFunction_TacticalPowerBar(int x, int y, int width, int height);

    void __cdecl MenuItemRenderFunction_TacticalPowerBar_Main(int param_1);

    void __cdecl MenuItemActionHandler_TacticalPowerBar_Main(int param_1);

    void __stdcall FUN_004da180();

    void __stdcall FUN_004da200();

    void __stdcall resetCredits();

    void __cdecl FUN_004da7a0(undefined4 param_1, undefined4 param_2);

    void __cdecl FUN_004da7e0(undefined4 param_1);

    void __stdcall FUN_004da810();

    void __stdcall FUN_004da840();

    void __stdcall FUN_004da870();

    void __stdcall FUN_004da8a0();

    void __cdecl FUN_004da8d0(int param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5);

    void __cdecl FUN_004da9a0(int param_1, int param_2);

    void __cdecl FUN_004da9f0(int param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5,
        undefined4 param_6, undefined4 param_7, undefined4 param_8);

    void __cdecl FUN_004daa80(undefined4 param_1, char* param_2, undefined4 param_3, undefined4 param_4,
        undefined4 param_5, undefined4 param_6);

    void __cdecl FUN_004dab00(int param_1, undefined4 param_2, undefined4 param_3);

    void __cdecl FUN_004dab80(char* param_1, undefined4 param_2, int param_3, undefined4 param_4);

    void __cdecl FUN_004dabf0(undefined4 param_1, undefined4 param_2);

    void __cdecl FUN_004dac30(int param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5,
        undefined4 param_6, undefined4 param_7, undefined4 param_8);

    void __cdecl FUN_004dacf0(int param_1, int param_2);

    void __stdcall FUN_004dafb0();

    void __cdecl FUN_004db0d0(int param_1);

    void __cdecl FUN_004db180(undefined4 param_1, undefined4 param_2);

    void __cdecl TrimStoredMenuString(int storedMenuStringIndex, undefined4 param_2, undefined4 param_3,
        int allowedWidth, undefined4 param_5, int fontSize);

    void __cdecl FUN_004db390(float param_1);

    void __stdcall MenuView_HistoricMissionPicture_Prepare();

    void __stdcall MenuView_General_DoInitial_BlackBorderAndGfx();

    void __stdcall MenuView_HistoricMissionPicture_DoEveryFrame();

    void __stdcall MenuView_HistoricMissionIntro_Prepare();

    void __stdcall MenuView_HistoricMissionIntro_DoEveryFrame();

    void __stdcall MenuView_HistoricCampaignIntro_Prepare();

    void __stdcall MenuView_HistoricCampaignIntro_DoEveryFrame();

    void __stdcall MenuView_HistoricCampaignOutro_Prepare();

    void __stdcall MenuView_HistoricCampaignOutro_DoEveryFrame();

    undefined4 __stdcall FUN_004dc140();

    void __stdcall FUN_004dc1c0();

    void __stdcall MenuView_MissionFinishedTransition_DoEveryFrame();

    void __stdcall MenuView_GameLost_DoEveryFrame();

    void __stdcall MenuView_Unknown26_CampaignRelatedUnk_Prepare();

    void __stdcall MenuView_CampaignUnk_Prepare();

    void __stdcall MenuView_CampaignUnk_DoInitial();

    void __stdcall MenuView_ScenarioDescription_Prepare();

    void __stdcall MenuView_ScenarioDescription_DoInitial();

    void __stdcall MenuView_ScenarioDescription_DoEveryFrame();

    void __stdcall MenuView_General_DoInitial_CrusadeAndRankMenu();

    void __stdcall MenuView_CrusadeMissionIntro_DoEveryFrame();

    void __stdcall MenuView_CrusadeMap_DoEveryFrame();

    void __stdcall MenuView_CrusadeEndscreen_Prepare();

    void __stdcall MenuView_RankingGames_DoEveryFrame();

    void __stdcall MenuView_UnusedExtremeAd_Prepare();

    void __stdcall MenuView_UnusedExtremeAd_DoInitial();

    void __stdcall MenuView_UnusedExtremeAd_DoEveryFrame();

    void __stdcall MenuView_MissionFinishedTransition_Prepare();

    void __stdcall MenuView_Unknown26_CampaignRelatedUnk_DoInitial();

    void __stdcall MenuView_Unknown26_CampaignRelatedUnk_DoEveryFrame();

    void __stdcall MenuView_CrusadeEndscreen_DoEveryFrame();

    void __cdecl MenuItemActionHandler_General_DisplayConditionalText(int param_1);

    void __cdecl MenuItemActionHandler_General_RemoveConditionalTextOrReleaseHoverUnk(int param_1);

} // namespace UI
} // namespace OpenSHC
