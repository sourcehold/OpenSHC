#include "../GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Game {

    /*
      Exits the current game view back to the scenario description screen. Calls
      Game::GameCore::removeLadyAndJester, clears field22_0x64 on GameCore, then switches to
      MVT_SCENARIO_DESCRIPTION via switchToMenuView. Likely triggered by a cancel or back button in a
      pre-game UI screen.

      renamed by: Claude Sonnet 4.6
    */

    // FUNCTION: STRONGHOLDCRUSADER 0x00471A80
    void GameCore::exitToScenarioDescriptionMenu()
    {
        MACRO_CALL_MEMBER(GameCore_Func::removeLadyAndJester, this)();
        DAT_GameCore::instance.field22_0x64 = 0;
        MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
    }

}
}
