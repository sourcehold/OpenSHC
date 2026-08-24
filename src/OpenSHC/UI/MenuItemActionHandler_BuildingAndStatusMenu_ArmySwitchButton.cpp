#include "OpenSHC/UI.func.hpp"



#include "OpenSHC/Globals/DAT_00b95b68.hpp"

namespace OpenSHC {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0043FC80
void UI::MenuItemActionHandler_BuildingAndStatusMenu_ArmySwitchButton()

{
DAT_00b95b68::instance = DAT_00b95b68::instance + 1;
if (2 < DAT_00b95b68::instance) {
DAT_00b95b68::instance = 0;
}
return;
}


}