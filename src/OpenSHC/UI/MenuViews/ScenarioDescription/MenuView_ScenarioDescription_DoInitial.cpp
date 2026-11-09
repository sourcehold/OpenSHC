#include "../ScenarioDescription.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DD300
        void ScenarioDescription::MenuView_ScenarioDescription_DoInitial()
        {
            int const borderHeight = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int const borderWidth = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
            menu->xPosition = borderWidth;
            menu->yPosition = borderHeight;
            DAT_MenuHandlerState::instance.x = borderWidth;
            DAT_MenuHandlerState::instance.y = borderHeight;
            MACRO_CALL(UI::Helpers_Func::ColorEntireScreen)(COL_BLACK::instance.shortValue);
            MACRO_CALL(UI::Rendering_Func::DrawOuterMenuBorder)();
            MACRO_CALL(UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
        }

    }
}
}
