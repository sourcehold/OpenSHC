#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/Rendering.func.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004DCC70
void UI::MenuView_Unknown26_CampaignRelatedUnk_Prepare()

{
MACRO_CALL(OpenSHC::UI_Func::ResetCredits)();
MACRO_CALL(OpenSHC::UI_Func::BuildIntroLogoSequence)(DAT_GameCore::instance.missionNumber1to20, (undefined4)((int)(DAT_GameCore::instance.section1066)));
MACRO_CALL(OpenSHC::Rendering_Func::TicksStartCounter)();
return;
}


}