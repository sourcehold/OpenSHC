#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Menu.hpp"

#include "OpenSHC/Globals/DAT_IntroTimestamp.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

using OpenSHC::UI::Menu;

// FUNCTION: STRONGHOLDCRUSADER 0x00424770
void UI::MenuView_IntroLogos_DoInitial()
{
    DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
    DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
    DAT_MenuHandlerState::instance.currentMenu->yPosition = DAT_MenuHandlerState::instance.y;
    DAT_MenuHandlerState::instance.currentMenu->xPosition = DAT_MenuHandlerState::instance.x;

    DAT_IntroTimestamp::instance = timeGetTime();
}

}
