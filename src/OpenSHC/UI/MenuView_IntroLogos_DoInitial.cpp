#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Menu.hpp"

#include "OpenSHC/Globals/DAT_IntroTimestamp.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

using OpenSHC::UI::Menu;

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x00424770
void UI::MenuView_IntroLogos_DoInitial()

{
    Menu* _menuPtr;

    DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
    DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
    _menuPtr = DAT_MenuHandlerState::instance.currentMenu;
    (DAT_MenuHandlerState::instance.currentMenu)->xPosition = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
    _menuPtr->yPosition = DAT_MenuHandlerState::instance.y;
    DAT_IntroTimestamp::instance = timeGetTime();
    return;
}

}
