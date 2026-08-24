#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"



#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::UI::Enums::MenuModalType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00427210
BOOLEnum Helpers::AModalDialogIsActiveButIsNotQuitting()

{
if ((((DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) &&
(DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT)) &&
(DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT)) &&
(DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_ROUNDTABLE)) {
return TRUE;
}
return FALSE;
}


}
}