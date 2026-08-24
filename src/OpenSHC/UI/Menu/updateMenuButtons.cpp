#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/MenuItem.hpp"
#include "OpenSHC/UI/Enums/MenuItemHandleState.hpp"



#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"

namespace OpenSHC {
namespace UI {

using OpenSHC::UI::MenuItem;
using OpenSHC::UI::Enums::MenuItemHandleState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004F6470
void Menu::updateMenuButtons()

{
if (this->hoveredItem == (MenuItem *)0x0) {
this->someMenuItemPtr_0x3c = (MenuItem *)0x0;
}
this->hoveredItem = (MenuItem *)0x0;
this->field16_0x40 = 0;
DAT_MenuHandlerState::instance.field18_0x3c = 0;
MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::handleMenuItems, this)(OpenSHC::UI::Enums::MIHS_HANDLE_INPUT_CALLBACKSUnk);
this->one = 0;
return;
}


}
}