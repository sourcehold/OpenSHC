#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Menu.hpp"



#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

using OpenSHC::UI::Menu;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004B8050
void UI::MenuView_General_DoInitial_OnlySetMenuXY()

{
Menu *pMVar1;

DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
(DAT_MenuHandlerState::instance.currentMenu)->xPosition = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
return;
}


}