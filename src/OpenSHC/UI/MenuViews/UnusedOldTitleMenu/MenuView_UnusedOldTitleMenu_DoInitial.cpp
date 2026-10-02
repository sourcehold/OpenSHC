#include "../UnusedOldTitleMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042DD00
        void UnusedOldTitleMenu::MenuView_UnusedOldTitleMenu_DoInitial()
        {
            Menu* pMVar1;
            int left;
            int top;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                0, DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY,
                (ushort)((int)(COL_BLACK::instance.shortValue)));
            DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            (DAT_MenuHandlerState::instance.currentMenu)->xPosition
                = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawPixelPattern4x4OverWholeScreen,
                DAT_PencilRenderCore::ptr)();
            top = (DAT_WindowAndDirectDraw::instance.resolutionY + -400) / 2;
            left = (DAT_WindowAndDirectDraw::instance.resolutionX + -600) / 2;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                left, top, left + 600, top + 400, (ushort)((int)(COL_WHITE::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                DAT_TextureRenderCoreObject::ptr)(0, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 100,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "FireFly\'s", DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xd2, OpenSHC::Text::TTA_LEFT, 0x80ff, 0xf,
                FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Crusader", DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xf8, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE,
                0);
        }

    }
}
}
