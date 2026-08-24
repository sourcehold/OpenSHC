#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Rendering.func.hpp"



#include "OpenSHC/Globals/DAT_00ed278c.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"

namespace OpenSHC {

using OpenSHC::UI::Enums::MenuModalType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004E1A20
void UI::MenuView_UnusedExtremeAd_Prepare()

{
MACRO_CALL(OpenSHC::UI_Func::ResetCredits)();
MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
MACRO_CALL(OpenSHC::UI_Func::BuildExtremeDemoIntroScript)();
MACRO_CALL(OpenSHC::Rendering_Func::TicksStartCounter)();
DAT_00ed278c::instance = 0;
return;
}


}