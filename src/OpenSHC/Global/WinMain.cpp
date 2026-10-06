#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO.func.hpp"
#include "OpenSHC/IO/BitMapState.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/IO/SettingsFileState.func.hpp"
#include "OpenSHC/Input/ModifierKeyState.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/HoveredState.func.hpp"
#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/MenuHandlerState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/UI/ScrollingHandler.func.hpp"
#include "OpenSHC/Util/Timing/Stopwatch.func.hpp"
#include "OpenSHC/DE/SHCDE/eMusicIDs.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuItemHandleState.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/UI/Menu.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_BitMapState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameLoopStopwatch.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_HoveredState.hpp"
#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_ModifierKeyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderMiniMapOrBinkFlag.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_SettingsFileState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/FLAG_JokeAIMessageArray.hpp"
#include "OpenSHC/Globals/TIME_2.hpp"
#include "OpenSHC/Globals/TIME_ReceivedMessage_1.hpp"
#include "OpenSHC/Globals/TIME_ReceivedMessage_2.hpp"
#include "OpenSHC/Globals/TIME_Sum_1.hpp"

namespace OpenSHC {

using OpenSHC::DE::SHCDE::eMusicIDs;
using OpenSHC::Game::GameMode;
using OpenSHC::Game::GameMode2;
using OpenSHC::Rendering::ScreenResolutionEnum;
using OpenSHC::UI::Menu;
using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
using OpenSHC::UI::Enums::MenuItemHandleState;
using OpenSHC::UI::Enums::MenuViewType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;

inline static void renderCurrentMenu(Menu* menu)
{
    MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::handleMenuItems, menu)(OpenSHC::UI::Enums::MIHS_PREPARE_AND_RENDER);
    MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::renderConstructionMenu, menu)();
}

// FUNCTION: STRONGHOLDCRUSADER 0x0057BE10
int __stdcall Global::WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    CHAR executablePath[260];

    GetModuleFileNameA(NULL, executablePath, 260);
    // Cut the executable name off, leaving the directory
    for (int separatorIndex = (int)(strlen(executablePath) - 1); separatorIndex >= 0; separatorIndex--) {
        if (executablePath[separatorIndex] == '\\') {
            executablePath[separatorIndex] = '\0';
            break;
        }
    }
    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::loadConfigPathTxt, DAT_ResourceManager::ptr)();
    if (DAT_TextureRenderCoreObject::instance.bufferAllocStateUnk_0x0) {
        return -1;
    }

    void* singleInstanceMutex = CreateMutexA(NULL, 0, s_Global_FireflyStrongholdCrusader_005abf6c);
    // Only go here if Crusader is already running
    if (singleInstanceMutex && (GetLastError() == 183)) {
        CloseHandle(singleInstanceMutex);
        MessageBoxA(NULL, s_Stronghold_Crusader_is_already_r_005abf28, s_Stronghold_Crusader_Error_005abf50, 0);
        return -1;
    }

    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::loadCRTex, DAT_TextManagerObject::ptr)();
    DAT_GameCore::instance.directDrawStatus = MACRO_CALL(OpenSHC::Global_Func::DetectDXVersionByLoadingDDRAW)();
    UINT timerResolution;
    BOOL timerResolutionSet = 0;
    TIMECAPS timerCaps;
    if (!timeGetDevCaps(&timerCaps, 8)) {
        timerResolutionSet = 1;
        timerResolution = min(max(timerCaps.wPeriodMin, 1), timerCaps.wPeriodMax);
        timeBeginPeriod(timerResolution);
    }
    MACRO_CALL_MEMBER(OpenSHC::IO::SettingsFileState_Func::readUserConfig, DAT_SettingsFileState::ptr)();
    MACRO_CALL(OpenSHC::IO_Func::ReadSkMasters2)();
    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::createCrusaderWindow,
        DAT_WindowAndDirectDraw::ptr)(hInstance, s_Crusader_005a22b8, 0x65);
    DAT_MouseState::instance.waitCursorToggle = 1;
    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
    MACRO_CALL_MEMBER(
        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::prepareWindowAndDDraw_2Unk, DAT_WindowAndDirectDraw::ptr)(
        TRUE, (ScreenResolutionEnum)DAT_WindowAndDirectDraw::instance.currentGameResolution);
    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::initMiles, DAT_SoundSystemState::ptr)();
    MACRO_CALL_MEMBER(OpenSHC::IO::BitMapState_Func::loadFacesBMP, DAT_BitMapState::ptr)();
    MACRO_CALL_MEMBER(OpenSHC::AI::AIVState_Func::setAvailableAIV, DAT_AIVState::ptr)();
    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::loadAndSetCursor, DAT_MouseState::ptr)(
        0x68, 0x69, 0x72, 0, 0, 0, 0, 0);
    DAT_GameCore::instance.canBeginMainLoop = 0;
    MACRO_CALL_MEMBER(OpenSHC::UI::MenuHandlerState_Func::initializeUI, DAT_MenuHandlerState::ptr)(
        DAT_RenderingDefinedData::instance.MenuViewIDMenuMapping,
        (OpenSHC::UI::UC*)DAT_RenderingDefinedData::instance.UCArray, (char*)s_stronghold_uc_005ab8e4);
    MACRO_CALL_MEMBER(OpenSHC::UI::MenuHandlerState_Func::setupBuildMenuState, DAT_MenuHandlerState::ptr)(17, 516);
    /*
      setup the load menu
     */

    MACRO_CALL_MEMBER(OpenSHC::UI::MenuHandlerState_Func::setupMenuForRendering, DAT_MenuHandlerState::ptr)(
        OpenSHC::UI::Enums::MVT_INTRO_LOGOS);
    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
        s_frontend_loading_tgx_005abf10);
    /*
      processExtremeTrailCsv
     */

    // The original passes the AICState as this to the empty function
    ((void(__fastcall*)(OpenSHC::AI::AICState*))MACRO_CALL(OpenSHC::Global_Func::DoNothing))(DAT_AICState::ptr);
    int mainMenuBorderHeight = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
    int mainMenuBorderWidth = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
    Menu* loadingMenu = DAT_MenuHandlerState::instance.currentMenu;
    loadingMenu->yPosition = mainMenuBorderHeight;
    loadingMenu->xPosition = mainMenuBorderWidth;
    DAT_MenuHandlerState::instance.y = mainMenuBorderHeight;
    DAT_MenuHandlerState::instance.x = mainMenuBorderWidth;
    MACRO_CALL_MEMBER(
        OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface, DAT_TextureRenderCoreObject::ptr)(0,
        (DAT_WindowAndDirectDraw::instance.resolutionX - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
            / 2,
        (DAT_WindowAndDirectDraw::instance.resolutionY - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
            / 2);
    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
        DAT_MenuHandlerState::instance.x + 0xe7, DAT_MenuHandlerState::instance.y + 0x236,
        DAT_MenuHandlerState::instance.x + 0x239, DAT_MenuHandlerState::instance.y + 0x248, 0x14);
    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
        DAT_MenuHandlerState::instance.x + 0xe7, DAT_MenuHandlerState::instance.y + 0x236,
        DAT_MenuHandlerState::instance.x + 0x239, DAT_MenuHandlerState::instance.y + 0x248,
        COL_BLACK::instance.shortValue);
    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::renderBltAndFlip, DAT_WindowAndDirectDraw::ptr)(
        0);
    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID, DAT_SoundSystemState::ptr)(
        OpenSHC::DE::SHCDE::MUSIC_TUNE_CHOIR2);
    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::playRandomAmbientMusic, DAT_SoundSystemState::ptr)();
    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGmFiles, DAT_TextureRenderCoreObject::ptr)(
        DAT_MapDefinedData::instance.GMNameArray[0]);
    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::setupFontSizeClassObjects, DAT_TextManagerObject::ptr)();
    DAT_GameCore::instance.missionNumber1to20 = 1000;
    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
        OpenSHC::UI::Enums::MVT_INTRO_LOGOS, 0);
    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::handleCommandLineArguments,
        DAT_GameSynchronyState::ptr)(lpCmdLine);
    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::loadSFX, DAT_SFXState::ptr)(0);
    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::loadMapHeaders, DAT_ResourceManager::ptr)(TRUE);
    if (!DAT_GameSynchronyState::instance.useTCPIP) {
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
    }
    DAT_TileMapState::instance.mapSize = 400;
    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetHeightAndMapBorders, DAT_TileMapState::ptr)(400);
    DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerForEachBuildingAtEachTile,
        DAT_PathFindingState::ptr)();
    MACRO_CALL_MEMBER(
        OpenSHC::Map::Navigation::PathFindingState_Func::updateSeparateAreaTileMap, DAT_PathFindingState::ptr)(1);
    MACRO_CALL_MEMBER(
        OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageLayerForAllBuildings, DAT_BuildingsState::ptr)();
    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::forceFullTileMapRedraw, DAT_TileMapState::ptr)();
    MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize, DAT_MinimapViewState::ptr)(
        0, 100);
    MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize, DAT_MinimapViewState::ptr)(
        0, 100);
    MACRO_CALL_MEMBER(
        OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, DAT_ViewportRenderState::ptr)();
    TIME_Sum_1::instance = timeGetTime();
    TIME_2::instance = TIME_Sum_1::instance;
    for (int messageIndex = 0; messageIndex < 17; messageIndex++) {
        FLAG_JokeAIMessageArray::instance[messageIndex] = FALSE;
    }
    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::initBuildingCosts, DAT_BuildingsState::ptr)();
    DAT_GameCore::instance.canBeginMainLoop = 1;
    DAT_MouseState::instance.waitCursorToggle = 0;
    if (!DAT_WindowAndDirectDraw::instance.postWindowCloseMessage) {
        while (true) {
            /*
              game loop start
             */
            tagMSG windowMessage;
            if (PeekMessageA(&windowMessage, NULL, 0, 0, 0)) {
                if (!GetMessageA(&windowMessage, NULL, 0, 0))
                    break; // Break the game loop
                TranslateMessage(&windowMessage);
                DispatchMessageA(&windowMessage);
            } else {
                if ((!DAT_WindowAndDirectDraw::instance.isNotProcessingInputEvents
                        && DAT_WindowAndDirectDraw::instance.gameFocused)
                    || ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                        && (DAT_GameSynchronyState::instance.currentGameMode
                            != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)))) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::PlayJokeVideoBasedOnCurrentTimeAndPlayTime)();
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::someChatMessageSelection, DAT_AICState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Util::Timing::Stopwatch_Func::start, DAT_GameLoopStopwatch::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Input::ModifierKeyState_Func::updateCtrlShiftAltKeyStateMemory,
                        DAT_ModifierKeyState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::processMenuViewSwitch, DAT_GameCore::ptr)();
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::MSS::SoundSystem_Func::playRandomAmbientMusic, DAT_SoundSystemState::ptr)();
                    /*
                      receive commands when in multiplayer
                     */

                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::receiveAllTransmittedCommands,
                        DAT_GameSynchronyState::ptr)();
                    if (!DAT_WindowAndDirectDraw::instance.isNotProcessingInputEvents
                        && DAT_WindowAndDirectDraw::instance.gameFocused) {
                        MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::updateMouseStateBasedOnCursorAndTime,
                            DAT_MouseState::ptr)();
                        MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
                    }
                    DAT_GameCore::instance.gameTicksLastLoop = DAT_GameCore::instance.gameTicksThisLoop;
                    DAT_GameCore::instance.gameTicksThisLoop
                        = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::determineGameTicksToPerform,
                            DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueSynchronizedAutosaveProtocol,
                        DAT_GameSynchronyState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::viewportAndScrollingRelated, DAT_GameCore::ptr)();
                    if (DAT_GameCore::instance.gameTicksThisLoop) {
                        DAT_GameCore::instance.timeBeforeRunningGameTicksThisLoop = timeGetTime();
                    }
                    for (DAT_GameCore::instance.performedGameTicksThisLoop = 0;
                        (int)DAT_GameCore::instance.performedGameTicksThisLoop
                        < (int)DAT_GameCore::instance.gameTicksThisLoop;
                        DAT_GameCore::instance.performedGameTicksThisLoop++) {
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::processWaitingCommands,
                            DAT_GameSynchronyState::ptr)();
                        /*
                          game ticks are done here
                         */

                        MACRO_CALL_MEMBER(
                            OpenSHC::Game::GameStateStructures_Func::processGameTick, DAT_GameState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::receiveAllTransmittedCommands,
                            DAT_GameSynchronyState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::processBinkFrames,
                            DAT_BinkControlState::ptr)();
                        MACRO_CALL(OpenSHC::UI::Helpers_Func::TacticalPowersFill)();
                        if (DAT_GameSynchronyState::instance.DAT_GameHalted) {
                            break;
                        }
                    }
                    if (DAT_GameCore::instance.gameTicksThisLoop) {
                        DAT_GameCore::instance.averageTimePerGameTick
                            = (timeGetTime() - DAT_GameCore::instance.timeBeforeRunningGameTicksThisLoop)
                            / DAT_GameCore::instance.gameTicksThisLoop;
                    }
                    if (MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::checkMultiplayerLaggingPlayers,
                            DAT_GameSynchronyState::ptr)();
                    }
                    if (!DAT_WindowAndDirectDraw::instance.isNotProcessingInputEvents
                        && DAT_WindowAndDirectDraw::instance.gameFocused) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::ScrollingHandler_Func::handleScrolling, DAT_ScrollingHandler::ptr)();
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::MenuModalComposition_Func::update, DAT_MenuModalComposition2::ptr)();
                        if (!DAT_MenuModalComposition2::instance.minus1
                            && (MACRO_CALL_MEMBER(
                                    OpenSHC::UI::MenuModalComposition_Func::update, DAT_MenuModalComposition3::ptr)(),
                                !DAT_MenuModalComposition3::instance.minus1)) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::UI::MenuModalComposition_Func::update, DAT_MenuModalComposition1::ptr)();
                        }
                        if ((((!DAT_MenuModalComposition1::instance.minus1
                                  && !DAT_MenuModalComposition2::instance.minus1)
                                 && !DAT_MenuModalComposition3::instance.minus1)
                                && !DAT_GameCore::instance.hasMenuRenderedUnk)
                            || DAT_BinkControlState::instance.unknown01_zero[1]) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::updateMenuButtons,
                                DAT_MenuHandlerState::instance.currentMenu)();
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::HoveredState_Func::calculateHoveredTile, DAT_HoveredState::ptr)();
                        if (MACRO_CALL_MEMBER(
                                OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
                            if (((DAT_GameCore::instance.activeMenuTab.tabType
                                     != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER)
                                    && (DAT_GameCore::instance.activeMenuTab.tabType
                                        != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD))
                                || (DAT_WindowAndDirectDraw::instance.mbr_0xd0 = 2,
                                    DAT_GameCore::instance.currentMenuViewType
                                        == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU)) {
                                DAT_WindowAndDirectDraw::instance.mbr_0xd0 = 1;
                            }
                            DAT_GameCore::instance.currentlyInGameUnk_0xa4 = TRUE;
                            MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderMap,
                                DAT_ViewportRenderState::ptr)();
                            MACRO_CALL(OpenSHC::UI::DisplayElements_Func::RenderDisplayElementsUnk)();
                            MACRO_CALL_MEMBER(
                                OpenSHC::Rendering::ViewportRenderState_Func::updateBuildingPreviewPosition,
                                DAT_ViewportRenderState::ptr)(
                                DAT_MouseState::instance.screenSpaceX, ((DAT_MouseState::instance.screenSpaceY)));
                            MACRO_CALL_MEMBER(
                                OpenSHC::Input::MouseState_Func::drawMouseBasedBox, DAT_MouseState::ptr)();
                            MACRO_CALL_MEMBER(
                                OpenSHC::Input::MouseState_Func::renderPreviewAtMouseLocation, DAT_MouseState::ptr)();
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::processBinkFrames,
                            DAT_BinkControlState::ptr)();
                        DAT_GameCore::instance.hasMenuRenderedUnk = 0;
                        if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL)
                                || DAT_GameCore::instance.countdown)
                            || (((DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial
                                     || (((!MACRO_CALL_MEMBER(
                                               OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
                                              || DAT_MenuHandlerState::instance.isBuildMenuTransitioning_0x18)
                                         || DAT_GameState::instance.mapAndTime.weekChanged)))
                                || (MACRO_CALL_MEMBER(
                                    OpenSHC::Game::GameCore_Func::isInBuildingTab, DAT_GameCore::ptr)())))) {
                            if (MACRO_CALL_MEMBER(
                                    OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
                                DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::copyBinkToVideoBuffer,
                                DAT_BinkControlState::ptr)(2);
                            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentMenuView)();
                            MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::copyBinkToVideoBuffer,
                                DAT_BinkControlState::ptr)(1);
                            renderCurrentMenu(DAT_MenuHandlerState::instance.currentMenu);
                        } else if (DAT_GameCore::instance.currentMenuViewType
                            == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                            if (DAT_GameCore::instance.activeMenuTab.tabType
                                != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER) {
                                DAT_MinimapViewState::instance.field0_0x0 = 1;
                                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapLandscaping,
                                    DAT_MinimapViewState::ptr)(DAT_MenuHandlerState::instance.x + 664,
                                    ((DAT_MenuHandlerState::instance.y + 464)), ((128)), ((128)));
                                DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 4;
                            }
                        } else if (((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU)
                                       && (DAT_GameCore::instance.activeMenuTab.tabType
                                           != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER)
                                       && (DAT_GameCore::instance.activeMenuTab.tabType
                                           != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD))
                            || (DAT_GameCore::instance.currentMenuViewType
                                == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU)) {
                            if (!DAT_BinkControlState::instance.binkObjPtrArray[0]
                                && (!DAT_BinkControlState::instance.binkObjPtrArray[1]
                                    && !DAT_GameCore::instance.isBinkVideoPlaying)) {
                                DAT_RenderMiniMapOrBinkFlag::instance = DAT_RenderMiniMapOrBinkFlag::instance ^ TRUE;
                                if (DAT_RenderMiniMapOrBinkFlag::instance) {
                                    DAT_MinimapViewState::instance.field0_0x0 = 1;
                                    MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapMain,
                                        DAT_MinimapViewState::ptr)();
                                    DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 3;
                                }
                            } else {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Rendering::Bink::BinkControlClass_Func::copyBinkToVideoBuffer,
                                    DAT_BinkControlState::ptr)(1);
                                DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 3;
                                DAT_RenderMiniMapOrBinkFlag::instance = FALSE;
                            }
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Menu_Func::handleMenuItems, DAT_MenuHandlerState::instance.currentMenu)(
                            OpenSHC::UI::Enums::MIHS_PREPARE_AND_RENDER_FOR_FLAG_0X800000);
                        /*
                          draw modal dialogs
                         */

                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::MenuModalComposition_Func::renderMenuModal, DAT_MenuModalComposition1::ptr)();
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::MenuModalComposition_Func::renderMenuModal, DAT_MenuModalComposition3::ptr)();
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::MenuModalComposition_Func::renderMenuModal, DAT_MenuModalComposition2::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::copyBinkToVideoBuffer,
                            DAT_BinkControlState::ptr)(0);
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::moveOverlappingMenuPartsToMapSurface,
                            DAT_TextureRenderCoreObject::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::soundRelatedMethod1, DAT_SFXState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::renderBltAndFlip,
                            DAT_WindowAndDirectDraw::ptr)(0);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Util::Timing::Stopwatch_Func::stop, DAT_GameLoopStopwatch::ptr)();
                    if ((!DAT_GameCore::instance.gamePausedLogical
                            && !MACRO_CALL_MEMBER(
                                OpenSHC::Game::GameCore_Func::isGameHaltingMenuOpen, DAT_GameCore::ptr)())
                        && (MACRO_CALL_MEMBER(
                            OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)())) {
                        if (TIME_ReceivedMessage_2::instance) {
                            int pausedDuration = timeGetTime() - TIME_ReceivedMessage_2::instance;
                            TIME_ReceivedMessage_2::instance = 0;
                            DAT_GameCore::instance.timeSum_2 = DAT_GameCore::instance.timeSum_2 + pausedDuration;
                        }
                    } else if (!TIME_ReceivedMessage_2::instance) {
                        TIME_ReceivedMessage_2::instance = timeGetTime();
                    }
                    if (TIME_ReceivedMessage_1::instance) {
                        int unfocusedDuration = timeGetTime() - TIME_ReceivedMessage_1::instance;
                        TIME_ReceivedMessage_1::instance = 0;
                        TIME_Sum_1::instance = TIME_Sum_1::instance + unfocusedDuration;
                    }
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::soundRelatedMethod1, DAT_SFXState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::receiveAllTransmittedCommands,
                        DAT_GameSynchronyState::ptr)();
                    WaitMessage();
                    if (!TIME_ReceivedMessage_1::instance) {
                        TIME_ReceivedMessage_1::instance = timeGetTime();
                    }
                    if (!TIME_ReceivedMessage_2::instance) {
                        TIME_ReceivedMessage_2::instance = timeGetTime();
                    }
                }
            }
            if (DAT_WindowAndDirectDraw::instance.postWindowCloseMessage == 1) {
                PostMessageA(DAT_WindowAndDirectDraw::instance.windowHandle, WM_CLOSE, 0, 0);
                DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 0;
            }
        }
    }

    /*
      game loop end
     */

    if (timerResolutionSet == 1) {
        timeEndPeriod(timerResolution);
    }
    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::disconnectDPlay, DAT_GameSynchronyState::ptr)();
    MACRO_CALL_MEMBER(OpenSHC::IO::SettingsFileState_Func::writeUserConfig, DAT_SettingsFileState::ptr)();
    MACRO_CALL(OpenSHC::IO_Func::WriteSkMasters2)();
    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::shutdownSoundSystem, DAT_SoundSystemState::ptr)();
    MACRO_CALL_MEMBER(
        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::finalizeDirectDrawShutdown, DAT_WindowAndDirectDraw::ptr)();
    if (DAT_GameSynchronyState::instance.openOnClose) {
        ShellExecuteA(NULL, s_open_005abef4, DAT_GameSynchronyState::instance.shellExecuteTarget,
            s__svc_strongholdce_005abefc, NULL, 1);
    }
    // _exit is declared noreturn, so there is no stack cleanup and no epilogue after the call
    MACRO_CALL(OpenSHC::OS_Func::_exit)(0);
    __assume(0);
}

}
