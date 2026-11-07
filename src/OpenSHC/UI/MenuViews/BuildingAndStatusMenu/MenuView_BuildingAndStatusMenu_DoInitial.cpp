#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x004398B0
        void BuildingAndStatusMenu::MenuView_BuildingAndStatusMenu_DoInitial()
        {
            // the menu sits at the bottom of the screen, pushed off its left edge at 640x480
            int const y = DAT_WindowAndDirectDraw::instance.resolutionY - 600;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
                menu->xPosition = -698;
                menu->yPosition = y;
                DAT_MenuHandlerState::instance.x = -698;
            } else {
                int const x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
                menu->xPosition = x;
                menu->yPosition = y;
                DAT_MenuHandlerState::instance.x = x;
            }
            DAT_MenuHandlerState::instance.y = y;
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                        DAT_TextureRenderCoreObject::ptr)(7);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                        DAT_TextureRenderCoreObject::ptr)(3);
                }
            } else if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                        DAT_TextureRenderCoreObject::ptr)(7);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                        DAT_TextureRenderCoreObject::ptr)(3);
                }
            } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                    DAT_TextureRenderCoreObject::ptr)(6);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                    DAT_TextureRenderCoreObject::ptr)(1);
            }
            if (DAT_WindowAndDirectDraw::instance.pendingMenuRedraw == 0) {
                return;
            }
            DAT_WindowAndDirectDraw::instance.pendingMenuRedraw = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                DAT_MenuHandlerState::instance.y + 406, DAT_WindowAndDirectDraw::instance.resolutionX - 1,
                DAT_MenuHandlerState::instance.y + 471, COL_MAGENTA::instance.shortValue);
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                int leftGfx;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    // "edge_military_1024l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1024l_tgx_005a25c0);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1024l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1024l_tgx_005a25c0);
                    } else {
                        // "edge_military_1024r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1024r_tgx_005a25a8);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        leftGfx, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 896,
                            768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 912,
                            768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                    }
                } else {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    // "edge1024l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge1024l_tgx_005a2388);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge1024l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1024l_tgx_005a2388);
                    } else {
                        // "edge1024r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1024r_tgx_005a2418);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        leftGfx, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 912,
                        768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                int leftGfx;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    // "edge_military_1024l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1024l_tgx_005a25c0);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1024l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1024l_tgx_005a25c0);
                    } else {
                        // "edge_military_1024r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1024r_tgx_005a25a8);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        leftGfx, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 896,
                            600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 912,
                            600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                    }
                } else {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    // "edge1024l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge1024l_tgx_005a2388);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge1024l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1024l_tgx_005a2388);
                    } else {
                        // "edge1024r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1024r_tgx_005a2418);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        leftGfx, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 912,
                        600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                int leftGfx;
                DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    // "edge_military_1280l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1280l_tgx_005a2590);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1280l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1280l_tgx_005a2590);
                    } else {
                        // "edge_military_1280r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1280r_tgx_005a2578);
                    }
                } else {
                    // "edge1280l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge1280l_tgx_005a2378);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge1280l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1280l_tgx_005a2378);
                    } else {
                        // "edge1280r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1280r_tgx_005a2408);
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    leftGfx, 0, 1024 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1024,
                        1024 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1040,
                        1024 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                int leftGfx;
                DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    // "edge_military_1600l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1600l_tgx_005a2560);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1600l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1600l_tgx_005a2560);
                    } else {
                        // "edge_military_1600r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1600r_tgx_005a2548);
                    }
                } else {
                    // "edge1600l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge1600l_tgx_005a2368);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge1600l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1600l_tgx_005a2368);
                    } else {
                        // "edge1600r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1600r_tgx_005a23f8);
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    leftGfx, 0, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1184,
                        1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1200,
                        1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                int leftGfx;
                DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    // "edge_military_1280l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1280l_tgx_005a2590);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1280l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1280l_tgx_005a2590);
                    } else {
                        // "edge_military_1280r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1280r_tgx_005a2578);
                    }
                } else {
                    // "edge1280l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge1280l_tgx_005a2378);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge1280l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1280l_tgx_005a2378);
                    } else {
                        // "edge1280r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1280r_tgx_005a2408);
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    leftGfx, 0, 720 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1024,
                        720 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1040,
                        720 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                int leftGfx;
                DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    // "edge_military_1440l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1440l_tgx_005a2530);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1440l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1440l_tgx_005a2530);
                    } else {
                        // "edge_military_1440r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1440r_tgx_005a2518);
                    }
                } else {
                    // "edge1440l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge1440l_tgx_005a2358);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge1440l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1440l_tgx_005a2358);
                    } else {
                        // "edge1440r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1440r_tgx_005a23e8);
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    leftGfx, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1104,
                        900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1120,
                        900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                int leftGfx;
                DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    // "edge_military_1920l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1920l_tgx_005a2500);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1920l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1920l_tgx_005a2500);
                    } else {
                        // "edge_military_1920r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1920r_tgx_005a24e8);
                    }
                } else {
                    // "edge1920l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge1920l_tgx_005a2348);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge1920l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1920l_tgx_005a2348);
                    } else {
                        // "edge1920r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1920r_tgx_005a23d8);
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    leftGfx, 0, 1080 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1344,
                        1080 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1360,
                        1080 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                int leftGfx;
                DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    // "edge_military_1920l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1920l_tgx_005a2500);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1920l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1920l_tgx_005a2500);
                    } else {
                        // "edge_military_1920r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1920r_tgx_005a24e8);
                    }
                } else {
                    // "edge1920l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge1920l_tgx_005a2348);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge1920l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1920l_tgx_005a2348);
                    } else {
                        // "edge1920r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1920r_tgx_005a23d8);
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    leftGfx, 0, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1344,
                        1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1360,
                        1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                int leftGfx;
                DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    // "edge_military_2560l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_2560l_tgx_005a24d0);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_2560l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_2560l_tgx_005a24d0);
                    } else {
                        // "edge_military_2560r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_2560r_tgx_005a24b8);
                    }
                } else {
                    // "edge2560l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge2560l_tgx_005a2338);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge2560l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge2560l_tgx_005a2338);
                    } else {
                        // "edge2560r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge2560r_tgx_005a23c8);
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    leftGfx, 0, 1440 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1664,
                        1440 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1680,
                        1440 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                int leftGfx;
                DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    // "edge_military_2560l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_2560l_tgx_005a24d0);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_2560l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_2560l_tgx_005a24d0);
                    } else {
                        // "edge_military_2560r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_2560r_tgx_005a24b8);
                    }
                } else {
                    // "edge2560l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge2560l_tgx_005a2338);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge2560l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge2560l_tgx_005a2338);
                    } else {
                        // "edge2560r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge2560r_tgx_005a23c8);
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    leftGfx, 0, 1600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1664,
                        1600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1680,
                        1600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                int leftGfx;
                DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    // "edge_military_1366l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1366l_tgx_005a24a0);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1366l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1366l_tgx_005a24a0);
                    } else {
                        // "edge_military_1366r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1366r_tgx_005a2488);
                    }
                } else {
                    // "edge1366l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge1366l_tgx_005a2328);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge1366l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1366l_tgx_005a2328);
                    } else {
                        // "edge1366r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1366r_tgx_005a23b8);
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    leftGfx, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1066,
                        768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1082,
                        768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                int leftGfx;
                DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    // "edge_military_1360l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1360l_tgx_005a2470);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1360l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1360l_tgx_005a2470);
                    } else {
                        // "edge_military_1360r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1360r_tgx_005a2458);
                    }
                } else {
                    // "edge1360l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge1360l_tgx_005a2318);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge1360l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1360l_tgx_005a2318);
                    } else {
                        // "edge1360r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1360r_tgx_005a23a8);
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    leftGfx, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1064,
                        768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1080,
                        768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                int leftGfx;
                DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    // "edge_military_1680l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1680l_tgx_005a2440);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1680l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1680l_tgx_005a2440);
                    } else {
                        // "edge_military_1680r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1680r_tgx_005a2428);
                    }
                } else {
                    // "edge1680l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge1680l_tgx_005a2308);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge1680l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1680l_tgx_005a2308);
                    } else {
                        // "edge1680r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1680r_tgx_005a2398);
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    leftGfx, 0, 1050 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1224,
                        1050 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1240,
                        1050 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
                int leftGfx;
                DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                    // "edge_military_1600l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1600l_tgx_005a2560);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge_military_1600l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1600l_tgx_005a2560);
                    } else {
                        // "edge_military_1600r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge_military_1600r_tgx_005a2548);
                    }
                } else {
                    // "edge1600l.tgx"
                    leftGfx = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)((char*)s_edge1600l_tgx_005a2368);
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        // "edge1600l.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1600l_tgx_005a2368);
                    } else {
                        // "edge1600r.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)((char*)s_edge1600r_tgx_005a23f8);
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    leftGfx, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx].height);
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1184,
                        900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(leftGfx - 1, 1200,
                        900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[leftGfx - 1].height);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
        }

    }
}
}
