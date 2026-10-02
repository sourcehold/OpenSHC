#include "../MapEditorLandscaping.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
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

        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00430CE0
        void MapEditorLandscaping::MenuView_MapEditorLandscaping_DoInitial()
        {
            Menu* pMVar1;
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
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                        0, 0x1b2, 799, 599, (ushort)((int)(COL_MAGENTA::instance.shortValue)));
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_MenuHandlerState::instance.x, 0x25a,
                        DAT_MenuHandlerState::instance.x + 799, 0x2ff,
                        (ushort)((int)(COL_MAGENTA::instance.shortValue)));
                }
            }
            if ((DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER)
                && (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                    DAT_TextureRenderCoreObject::ptr)(2);
            }
            if (DAT_WindowAndDirectDraw::instance.field37_0xdc != 0) {
                DAT_WindowAndDirectDraw::instance.field37_0xdc = 0;
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
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
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
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x4b0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
            }
        }

    }
}
}
