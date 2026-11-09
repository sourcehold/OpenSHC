#include "../UnusedOldTitleMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042DD00
        void UnusedOldTitleMenu::MenuView_UnusedOldTitleMenu_DoInitial()
        {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0, 0,
                DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY,
                COL_BLACK::instance.shortValue);
            int const borderHeight = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int const borderWidth = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
            menu->xPosition = borderWidth;
            menu->yPosition = borderHeight;
            DAT_MenuHandlerState::instance.x = borderWidth;
            DAT_MenuHandlerState::instance.y = borderHeight;
            MACRO_CALL_MEMBER(
                UI::Rendering::PencilRenderCore_Func::drawPixelPattern4x4OverWholeScreen, DAT_PencilRenderCore::ptr)();
            int const top = (DAT_WindowAndDirectDraw::instance.resolutionY - 400) / 2;
            int const left = (DAT_WindowAndDirectDraw::instance.resolutionX - 600) / 2;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                left, top, left + 600, top + 400, COL_WHITE::instance.shortValue);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                0, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 100,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100);
            // "FireFly's"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_FireFly_s_005a22c4, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 210, Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 15, FALSE, 0);
            // "Crusader"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Crusader_005a22b8, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 248, Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_000000, 17, FALSE, 0);
        }

    }
}
}
