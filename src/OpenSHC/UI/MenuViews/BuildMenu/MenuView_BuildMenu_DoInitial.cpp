#include "../BuildMenu.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"

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
        using OpenSHC::UI::Enums::BuildMenuTabType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00431B60
        void BuildMenu::MenuView_BuildMenu_DoInitial()
        {
            Menu* pMVar1;
            int iVar2;
            char* pcVar3;
            DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.resolutionY + -600;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                (DAT_MenuHandlerState::instance.currentMenu)->xPosition = 0;
                pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
                DAT_MenuHandlerState::instance.x = 0;
            } else {
                (DAT_MenuHandlerState::instance.currentMenu)->xPosition
                    = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
            }
            if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    iVar2 = 8;
                } else {
                    iVar2 = 4;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                    DAT_TextureRenderCoreObject::ptr)(iVar2);
                if (DAT_WindowAndDirectDraw::instance.field37_0xdc == 0) {}
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(0, (int)((int)(DAT_MenuHandlerState::instance.y + 406)),
                    DAT_WindowAndDirectDraw::instance.resolutionX + -1,
                    (int)((int)(DAT_MenuHandlerState::instance.y + 471)),
                    (ushort)((int)(COL_MAGENTA::instance.shortValue)));
                DAT_WindowAndDirectDraw::instance.field37_0xdc = 0;
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge_military_1024l.tgx");
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        pcVar3 = "edge_military_1024l.tgx";
                    } else {
                        pcVar3 = "edge_military_1024r.tgx";
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        iVar2 = 0x380;
                    } else {
                        iVar2 = 0x390;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, iVar2, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge_military_1024l.tgx");
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        pcVar3 = "edge_military_1024l.tgx";
                    } else {
                        pcVar3 = "edge_military_1024r.tgx";
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        iVar2 = 0x380;
                    } else {
                        iVar2 = 0x390;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, iVar2, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge_military_1280l.tgx");
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = "edge_military_1280l.tgx";
                    } else {
                        pcVar3 = "edge_military_1280r.tgx";
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x410, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge_military_1600l.tgx");
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = "edge_military_1600l.tgx";
                    } else {
                        pcVar3 = "edge_military_1600r.tgx";
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x4b0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge_military_1280l.tgx");
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = "edge_military_1280l.tgx";
                    } else {
                        pcVar3 = "edge_military_1280r.tgx";
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x410, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge_military_1440l.tgx");
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = "edge_military_1440l.tgx";
                    } else {
                        pcVar3 = "edge_military_1440r.tgx";
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x460, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge_military_1920l.tgx");
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = "edge_military_1920l.tgx";
                    } else {
                        pcVar3 = "edge_military_1920r.tgx";
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x550, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge_military_1920l.tgx");
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = "edge_military_1920l.tgx";
                    } else {
                        pcVar3 = "edge_military_1920r.tgx";
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x550, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge_military_2560l.tgx");
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = "edge_military_2560l.tgx";
                    } else {
                        pcVar3 = "edge_military_2560r.tgx";
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x690, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge_military_2560l.tgx");
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = "edge_military_2560l.tgx";
                    } else {
                        pcVar3 = "edge_military_2560r.tgx";
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x690, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge_military_1366l.tgx");
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = "edge_military_1366l.tgx";
                    } else {
                        pcVar3 = "edge_military_1366r.tgx";
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x43a, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge_military_1360l.tgx");
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = "edge_military_1360l.tgx";
                    } else {
                        pcVar3 = "edge_military_1360r.tgx";
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x438, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge_military_1680l.tgx");
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = "edge_military_1680l.tgx";
                    } else {
                        pcVar3 = "edge_military_1680r.tgx";
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x4d8, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1600x900) {}
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("edge_military_1600l.tgx");
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    pcVar3 = "edge_military_1600l.tgx";
                } else {
                    pcVar3 = "edge_military_1600r.tgx";
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(pcVar3);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                iVar2 = 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height;
            } else {
                if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_MENU_HIDDEN) {}
                if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == ((OpenSHC::UI::Enums::BuildMenuTabType)0x3e)) {
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    iVar2 = 9;
                } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    iVar2 = 5;
                } else {
                    iVar2 = 0;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                    DAT_TextureRenderCoreObject::ptr)(iVar2);
                if (DAT_WindowAndDirectDraw::instance.field37_0xdc == 0) {}
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                    DAT_MenuHandlerState::instance.y + 0x196, DAT_WindowAndDirectDraw::instance.resolutionX + -1,
                    DAT_MenuHandlerState::instance.y + 0x1d7, (ushort)((int)(COL_MAGENTA::instance.shortValue)));
                DAT_WindowAndDirectDraw::instance.field37_0xdc = 0;
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1024l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1024l.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x390, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1024l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1024l.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x390, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1280l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1280l.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x410, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1600l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1600l.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x4b0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1280l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1280l.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x410, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1440l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1440l.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x460, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1920l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1920l.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x550, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1920l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1920l.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x550, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge2560l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge2560l.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x690, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge2560l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge2560l.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x690, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1366l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1366l.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x43a, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1360l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1360l.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x438, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1680l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1680l.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x4d8, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1600x900) {}
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge1600l.tgx");
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge1600l.tgx");
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    iVar2 = 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height;
                } else {
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1024l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1024r.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x390, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1024l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1024r.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x390, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1280l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1280r.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x410, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1600l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1600r.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x4b0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1280l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1280r.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x410, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1440l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1440r.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x460, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1920l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1920r.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x550, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1920l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1920r.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x550, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge2560l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge2560r.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x690, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge2560l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge2560r.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x690, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1366l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1366r.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x43a, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1360l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1360r.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x438, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1680l.tgx");
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)("edge1680r.tgx");
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x4d8, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1600x900) {}
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge1600l.tgx");
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)("edge1600r.tgx");
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    iVar2 = 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                DAT_TextureRenderCoreObject::ptr)(1, 0x4b0, iVar2);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
