#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {

using OpenSHC::UI::Enums::MenuViewType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004D6EF0
void UI::MenuView_CampaignUnk_DoEveryFrame()

{
int iVar1;

iVar1 = MACRO_CALL(OpenSHC::UI_Func::TicksSinceCounterStart)();
if (iVar1 != 0) {
if (DAT_GameCore::instance.missionNumber1to20 == 1) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
return;
}
MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(OpenSHC::UI::Enums::MVT_UNKNOWN_26_CAMPAIGN_RELATEDUnk, 0);
}
return;
}


}