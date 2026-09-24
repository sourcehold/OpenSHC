#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/Menu.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace General {

            using OpenSHC::UI::Menu;

            // FUNCTION: STRONGHOLDCRUSADER 0x004B8050
            void MenuView_General_DoInitial_OnlySetMenuXY()
            {
                int const y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                int const x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
                menu->xPosition = x;
                menu->yPosition = y;
                DAT_MenuHandlerState::instance.x = x;
                DAT_MenuHandlerState::instance.y = y;
            }

        }
    }
}
}
