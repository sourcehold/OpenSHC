#include "../BuildMenu.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x00431B60
        void BuildMenu::MenuView_BuildMenu_DoInitial()
        {
            // the build menu sits at the bottom of the screen, at its left edge at 640x480
            // y is set in each branch: one assignment before the test measures lower
            int y;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                y = DAT_WindowAndDirectDraw::instance.resolutionY - 600;
                Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
                menu->xPosition = 0;
                menu->yPosition = y;
                DAT_MenuHandlerState::instance.x = 0;
            } else {
                int const x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                y = DAT_WindowAndDirectDraw::instance.resolutionY - 600;
                Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
                menu->xPosition = x;
                menu->yPosition = y;
                DAT_MenuHandlerState::instance.x = x;
            }
            DAT_MenuHandlerState::instance.y = y;
            // the soldiers tab has its own menu picture and edge pictures
            if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                        DAT_TextureRenderCoreObject::ptr)(8);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                        DAT_TextureRenderCoreObject::ptr)(4);
                }
                if (!DAT_WindowAndDirectDraw::instance.pendingMenuRedraw) {
                    return;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                    DAT_MenuHandlerState::instance.y + 406, DAT_WindowAndDirectDraw::instance.resolutionX - 1,
                    DAT_MenuHandlerState::instance.y + 471, COL_MAGENTA::instance.shortValue);
                DAT_WindowAndDirectDraw::instance.pendingMenuRedraw = FALSE;
                // the edge pictures left and right of the menu, for this resolution
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_1024l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_1024l_tgx_005a25c0);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1024l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1024l_tgx_005a25c0);
                    } else {
                        // "edge_military_1024r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1024r_tgx_005a25a8);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 896, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 912, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_1024l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_1024l_tgx_005a25c0);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1024l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1024l_tgx_005a25c0);
                    } else {
                        // "edge_military_1024r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1024r_tgx_005a25a8);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 896, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 912, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                // fixme: from 1280x1024 on, editor and siege games reset the list before the second load, so slot 1 is
                // drawn without being loaded
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_1280l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_1280l_tgx_005a2590);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge_military_1280l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1280l_tgx_005a2590);
                    } else {
                        // "edge_military_1280r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1280r_tgx_005a2578);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 1024 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 1040, 1024 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_1600l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_1600l_tgx_005a2560);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge_military_1600l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1600l_tgx_005a2560);
                    } else {
                        // "edge_military_1600r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1600r_tgx_005a2548);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 1200, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_1280l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_1280l_tgx_005a2590);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge_military_1280l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1280l_tgx_005a2590);
                    } else {
                        // "edge_military_1280r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1280r_tgx_005a2578);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 720 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 1040, 720 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_1440l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_1440l_tgx_005a2530);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge_military_1440l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1440l_tgx_005a2530);
                    } else {
                        // "edge_military_1440r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1440r_tgx_005a2518);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 1120, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_1920l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_1920l_tgx_005a2500);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge_military_1920l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1920l_tgx_005a2500);
                    } else {
                        // "edge_military_1920r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1920r_tgx_005a24e8);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 1080 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 1360, 1080 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_1920l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_1920l_tgx_005a2500);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge_military_1920l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1920l_tgx_005a2500);
                    } else {
                        // "edge_military_1920r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1920r_tgx_005a24e8);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 1360, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_2560l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_2560l_tgx_005a24d0);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge_military_2560l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_2560l_tgx_005a24d0);
                    } else {
                        // "edge_military_2560r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_2560r_tgx_005a24b8);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 1440 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 1680, 1440 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_2560l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_2560l_tgx_005a24d0);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge_military_2560l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_2560l_tgx_005a24d0);
                    } else {
                        // "edge_military_2560r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_2560r_tgx_005a24b8);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 1600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 1680, 1600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_1366l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_1366l_tgx_005a24a0);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge_military_1366l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1366l_tgx_005a24a0);
                    } else {
                        // "edge_military_1366r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1366r_tgx_005a2488);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 1082, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_1360l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_1360l_tgx_005a2470);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge_military_1360l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1360l_tgx_005a2470);
                    } else {
                        // "edge_military_1360r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1360r_tgx_005a2458);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 1080, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_1680l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_1680l_tgx_005a2440);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge_military_1680l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1680l_tgx_005a2440);
                    } else {
                        // "edge_military_1680r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1680r_tgx_005a2428);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 1050 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 1240, 1050 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "edge_military_1600l.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_edge_military_1600l_tgx_005a2560);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge_military_1600l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1600l_tgx_005a2560);
                    } else {
                        // "edge_military_1600r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge_military_1600r_tgx_005a2548);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 1200, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
            } else {
                // no picture for a hidden menu or tab 62
                if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_MENU_HIDDEN
                    || DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_UNKNOWN_62) {
                    return;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                        DAT_TextureRenderCoreObject::ptr)(9);
                } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                        DAT_TextureRenderCoreObject::ptr)(5);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                        DAT_TextureRenderCoreObject::ptr)(0);
                }
                if (!DAT_WindowAndDirectDraw::instance.pendingMenuRedraw) {
                    return;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                    DAT_MenuHandlerState::instance.y + 406, DAT_WindowAndDirectDraw::instance.resolutionX - 1,
                    DAT_MenuHandlerState::instance.y + 471, COL_MAGENTA::instance.shortValue);
                DAT_WindowAndDirectDraw::instance.pendingMenuRedraw = FALSE;
                // the edge pictures left and right of the menu, for this resolution: the editor and siege games
                // show the left one on both sides
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                    || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1024l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1024l_tgx_005a2388);
                        // "edge1024l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1024l_tgx_005a2388);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 912, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1024l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1024l_tgx_005a2388);
                        // "edge1024l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1024l_tgx_005a2388);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 912, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    // fixme: from 1280x1024 on, editor and siege games reset the list before the second load, so slot 1
                    // is drawn without being loaded
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1280l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1280l_tgx_005a2378);
                        // "edge1280l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1280l_tgx_005a2378);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1024 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1040, 1024 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1600l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1600l_tgx_005a2368);
                        // "edge1600l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1600l_tgx_005a2368);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1200, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1280l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1280l_tgx_005a2378);
                        // "edge1280l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1280l_tgx_005a2378);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 720 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1040, 720 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1440l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1440l_tgx_005a2358);
                        // "edge1440l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1440l_tgx_005a2358);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1120, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1920l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1920l_tgx_005a2348);
                        // "edge1920l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1920l_tgx_005a2348);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1080 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1360, 1080 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1920l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1920l_tgx_005a2348);
                        // "edge1920l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1920l_tgx_005a2348);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1360, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge2560l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge2560l_tgx_005a2338);
                        // "edge2560l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge2560l_tgx_005a2338);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1440 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1680, 1440 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge2560l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge2560l_tgx_005a2338);
                        // "edge2560l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge2560l_tgx_005a2338);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1680, 1600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1366l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1366l_tgx_005a2328);
                        // "edge1366l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1366l_tgx_005a2328);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1082, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1360l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1360l_tgx_005a2318);
                        // "edge1360l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1360l_tgx_005a2318);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1080, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1680l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1680l_tgx_005a2308);
                        // "edge1680l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1680l_tgx_005a2308);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1050 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1240, 1050 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1600l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1600l_tgx_005a2368);
                        // "edge1600l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1600l_tgx_005a2368);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1200, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                } else {
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1024l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1024l_tgx_005a2388);
                        // "edge1024r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1024r_tgx_005a2418);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 912, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1024l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1024l_tgx_005a2388);
                        // "edge1024r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1024r_tgx_005a2418);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 912, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    // fixme: from 1280x1024 on, editor and siege games reset the list before the second load, so slot 1
                    // is drawn without being loaded
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1280l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1280l_tgx_005a2378);
                        // "edge1280r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1280r_tgx_005a2408);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1024 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1040, 1024 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1600l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1600l_tgx_005a2368);
                        // "edge1600r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1600r_tgx_005a23f8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1200, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1280l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1280l_tgx_005a2378);
                        // "edge1280r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1280r_tgx_005a2408);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 720 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1040, 720 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1440l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1440l_tgx_005a2358);
                        // "edge1440r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1440r_tgx_005a23e8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1120, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1920l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1920l_tgx_005a2348);
                        // "edge1920r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1920r_tgx_005a23d8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1080 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1360, 1080 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1920l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1920l_tgx_005a2348);
                        // "edge1920r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1920r_tgx_005a23d8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1360, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge2560l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge2560l_tgx_005a2338);
                        // "edge2560r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge2560r_tgx_005a23c8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1440 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1680, 1440 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge2560l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge2560l_tgx_005a2338);
                        // "edge2560r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge2560r_tgx_005a23c8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1680, 1600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1366l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1366l_tgx_005a2328);
                        // "edge1366r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1366r_tgx_005a23b8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1082, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1360l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1360l_tgx_005a2318);
                        // "edge1360r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1360r_tgx_005a23a8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1080, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1680l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1680l_tgx_005a2308);
                        // "edge1680r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1680r_tgx_005a2398);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 1050 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1240, 1050 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "edge1600l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1600l_tgx_005a2368);
                        // "edge1600r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_edge1600r_tgx_005a23f8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 1200, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                }
            }
        }

    }
}
}
