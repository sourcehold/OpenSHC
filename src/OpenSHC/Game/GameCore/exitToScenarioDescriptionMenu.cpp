#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"





namespace OpenSHC {
namespace Game {

using OpenSHC::UI::Enums::MenuViewType;


/* 
  Exits the current game view back to the scenario description screen. Calls
   Game::GameCore::removeLadyAndJester, clears field25_0x64 on GameCore, then switches to
   MVT_SCENARIO_DESCRIPTION via switchToMenuView. Likely triggered by a cancel or back button in a
   pre-game UI screen.
   
   renamed by: Claude Sonnet 4.6
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00471A80
void GameCore::exitToScenarioDescriptionMenu()

{
MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::removeLadyAndJester, this)();
this->field22_0x64 = 0;
MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, this)(OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
return;
}


}
}