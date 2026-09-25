#include "OpenSHC/UI/MenuViews/IntroLogos.func.hpp"
#include "OpenSHC/UI/Menu.hpp"

#include "OpenSHC/Globals/DAT_IntroTimestamp.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace IntroLogos {

            using OpenSHC::UI::Menu;

            // FUNCTION: STRONGHOLDCRUSADER 0x00424770
            void MenuView_IntroLogos_DoInitial()
            {
                int const y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                int const x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
                menu->xPosition = x;
                menu->yPosition = y;
                DAT_MenuHandlerState::instance.x = x;
                DAT_MenuHandlerState::instance.y = y;
                DAT_IntroTimestamp::instance = timeGetTime();
            }

        }
    }
}
}
