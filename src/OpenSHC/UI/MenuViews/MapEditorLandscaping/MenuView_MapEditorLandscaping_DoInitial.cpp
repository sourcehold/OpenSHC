#include "../MapEditorLandscaping.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x00430CE0
        void MapEditorLandscaping::MenuView_MapEditorLandscaping_DoInitial()
        {
            // the menu sits at the bottom of the screen, at its left edge at 640x480
            int const y = DAT_WindowAndDirectDraw::instance.resolutionY - 600;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
                menu->xPosition = 0;
                menu->yPosition = y;
                DAT_MenuHandlerState::instance.x = 0;
                DAT_MenuHandlerState::instance.y = y;
            } else {
                int const x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
                menu->xPosition = x;
                menu->yPosition = y;
                DAT_MenuHandlerState::instance.x = x;
                DAT_MenuHandlerState::instance.y = y;
                // a magenta box under the menu panel at 800x600 and 1024x768
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(0, 434, 799, 599, COL_MAGENTA::instance.shortValue);
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_MenuHandlerState::instance.x, 602,
                        DAT_MenuHandlerState::instance.x + 799, 767, COL_MAGENTA::instance.shortValue);
                }
            }
            if (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER
                && DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                    DAT_TextureRenderCoreObject::ptr)(2);
            }
            if (!DAT_WindowAndDirectDraw::instance.pendingMenuRedraw) {
                return;
            }
            DAT_WindowAndDirectDraw::instance.pendingMenuRedraw = FALSE;
            // the edge pictures left and right of the menu, for this resolution
            // fixme: the original loads the left edge picture for both sides (the r pictures exist, other views use
            // them)
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge1024l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1024l_tgx_005a2388);
                // "edge1024l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1024l_tgx_005a2388);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 912, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge1024l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1024l_tgx_005a2388);
                // "edge1024l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1024l_tgx_005a2388);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 912, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge1280l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1280l_tgx_005a2378);
                // "edge1280l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1280l_tgx_005a2378);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 1024 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 1040, 1024 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge1600l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1600l_tgx_005a2368);
                // "edge1600l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1600l_tgx_005a2368);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 1200, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge1280l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1280l_tgx_005a2378);
                // "edge1280l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1280l_tgx_005a2378);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 720 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 1040, 720 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge1440l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1440l_tgx_005a2358);
                // "edge1440l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1440l_tgx_005a2358);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 1120, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge1920l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1920l_tgx_005a2348);
                // "edge1920l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1920l_tgx_005a2348);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 1080 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 1360, 1080 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge1920l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1920l_tgx_005a2348);
                // "edge1920l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1920l_tgx_005a2348);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 1360, 1200 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge2560l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge2560l_tgx_005a2338);
                // "edge2560l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge2560l_tgx_005a2338);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 1440 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 1680, 1440 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge2560l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge2560l_tgx_005a2338);
                // "edge2560l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge2560l_tgx_005a2338);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 1600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 1680, 1600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge1366l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1366l_tgx_005a2328);
                // "edge1366l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1366l_tgx_005a2328);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 1082, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge1360l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1360l_tgx_005a2318);
                // "edge1360l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1360l_tgx_005a2318);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 1080, 768 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge1680l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1680l_tgx_005a2308);
                // "edge1680l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1680l_tgx_005a2308);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 1050 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 1240, 1050 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "edge1600l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1600l_tgx_005a2368);
                // "edge1600l.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_edge1600l_tgx_005a2368);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, 1200, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
        }

    }
}
}
