#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"

#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004398B0
        void BuildingAndStatusMenu::MenuView_BuildingAndStatusMenu_DoInitial()
        {
            Menu* pMVar1;
            int iVar2;
            int iVar3;
            char* pcVar4;
            int iVar5;
            DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.resolutionY + -600;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                (DAT_MenuHandlerState::instance.currentMenu)->xPosition = -0x2ba;
                pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
                DAT_MenuHandlerState::instance.x = -0x2ba;
            } else {
                (DAT_MenuHandlerState::instance.currentMenu)->xPosition
                    = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
            }
            if ((DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    iVar5 = 7;
                } else {
                    iVar5 = 3;
                }
            } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                iVar5 = 6;
            } else {
                iVar5 = 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                DAT_TextureRenderCoreObject::ptr)(iVar5);
            if (DAT_WindowAndDirectDraw::instance.field37_0xdc != 0) {
                DAT_WindowAndDirectDraw::instance.field37_0xdc = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                    DAT_MenuHandlerState::instance.y + 0x196, DAT_WindowAndDirectDraw::instance.resolutionX + -1,
                    DAT_MenuHandlerState::instance.y + 0x1d7, (ushort)((int)(COL_MAGENTA::instance.shortValue)));
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                        DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_1024l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_1024l.tgx";
                        } else {
                            pcVar4 = "edge_military_1024r.tgx";
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(pcVar4);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            iVar5, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            iVar2 = 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                            iVar3 = 0x380;
                        } else {
                            iVar2 = 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                            iVar3 = 0x390;
                        }
                    } else {
                        DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                        DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge1024l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge1024l.tgx";
                        } else {
                            pcVar4 = "edge1024r.tgx";
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(pcVar4);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            iVar5, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                        iVar2 = 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x390;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                        DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_1024l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_1024l.tgx";
                        } else {
                            pcVar4 = "edge_military_1024r.tgx";
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(pcVar4);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            iVar5, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            iVar2 = 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                            iVar3 = 0x380;
                        } else {
                            iVar2 = 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                            iVar3 = 0x390;
                        }
                    } else {
                        DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                        DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge1024l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge1024l.tgx";
                        } else {
                            pcVar4 = "edge1024r.tgx";
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(pcVar4);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            iVar5, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                        iVar2 = 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x390;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_1280l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_1280l.tgx";
                        } else {
                            pcVar4 = "edge_military_1280r.tgx";
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge1280l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge1280l.tgx";
                        } else {
                            pcVar4 = "edge1280r.tgx";
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x400;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x410;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, 0x400 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_1600l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_1600l.tgx";
                        } else {
                            pcVar4 = "edge_military_1600r.tgx";
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge1600l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge1600l.tgx";
                        } else {
                            pcVar4 = "edge1600r.tgx";
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x4a0;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x4b0;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, 0x4b0 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_1280l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_1280l.tgx";
                        } else {
                            pcVar4 = "edge_military_1280r.tgx";
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge1280l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge1280l.tgx";
                        } else {
                            pcVar4 = "edge1280r.tgx";
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x400;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x410;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, 0x2d0 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_1440l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_1440l.tgx";
                        } else {
                            pcVar4 = "edge_military_1440r.tgx";
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge1440l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge1440l.tgx";
                        } else {
                            pcVar4 = "edge1440r.tgx";
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x450;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x460;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, 900 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_1920l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_1920l.tgx";
                        } else {
                            pcVar4 = "edge_military_1920r.tgx";
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge1920l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge1920l.tgx";
                        } else {
                            pcVar4 = "edge1920r.tgx";
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x540;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x550;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, 0x438 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_1920l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_1920l.tgx";
                        } else {
                            pcVar4 = "edge_military_1920r.tgx";
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge1920l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge1920l.tgx";
                        } else {
                            pcVar4 = "edge1920r.tgx";
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x540;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x550;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, 0x4b0 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_2560l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_2560l.tgx";
                        } else {
                            pcVar4 = "edge_military_2560r.tgx";
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge2560l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge2560l.tgx";
                        } else {
                            pcVar4 = "edge2560r.tgx";
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x680;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x690;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, 0x5a0 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_2560l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_2560l.tgx";
                        } else {
                            pcVar4 = "edge_military_2560r.tgx";
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge2560l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge2560l.tgx";
                        } else {
                            pcVar4 = "edge2560r.tgx";
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x680;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x690;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, 0x640 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_1366l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_1366l.tgx";
                        } else {
                            pcVar4 = "edge_military_1366r.tgx";
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge1366l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge1366l.tgx";
                        } else {
                            pcVar4 = "edge1366r.tgx";
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x42a;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x43a;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, 0x300 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_1360l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_1360l.tgx";
                        } else {
                            pcVar4 = "edge_military_1360r.tgx";
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge1360l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge1360l.tgx";
                        } else {
                            pcVar4 = "edge1360r.tgx";
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x428;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x438;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, 0x300 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_1680l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_1680l.tgx";
                        } else {
                            pcVar4 = "edge_military_1680r.tgx";
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge1680l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge1680l.tgx";
                        } else {
                            pcVar4 = "edge1680r.tgx";
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x4c8;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x4d8;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, 0x41a - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge_military_1600l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge_military_1600l.tgx";
                        } else {
                            pcVar4 = "edge_military_1600r.tgx";
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)("edge1600l.tgx");
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = "edge1600l.tgx";
                        } else {
                            pcVar4 = "edge1600r.tgx";
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x4a0;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 + -1].height;
                        iVar3 = 0x4b0;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 + -1, iVar3, 900 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
            }
        }

    }
}
}
