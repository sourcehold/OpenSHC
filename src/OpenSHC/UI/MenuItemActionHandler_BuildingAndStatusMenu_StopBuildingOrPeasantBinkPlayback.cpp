#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"



#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00439890
void UI::MenuItemActionHandler_BuildingAndStatusMenu_StopBuildingOrPeasantBinkPlayback()

{
if (DAT_BuildingsState::instance.DAT_IsBuildingOrPeasantBinkPlaying != FALSE) {
DAT_BuildingsState::instance.DAT_IsBuildingOrPeasantBinkPlaying = FALSE;
MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(0);
}
return;
}


}