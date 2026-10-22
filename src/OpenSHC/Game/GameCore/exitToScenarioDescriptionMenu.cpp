#include "../GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471A80
    void GameCore::exitToScenarioDescriptionMenu()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::removeLadyAndJester, this)();
        DAT_GameCore::instance.gameSuspended = 0;
        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
            OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
    }

}
}
