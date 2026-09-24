#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004719E0
    void GameCore::switchToScenarioDescriptionMenuView()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::removeJesterAndLadyUnitsInCertainMissions, this)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
            OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
        DAT_GameCore::instance.field22_0x64 = 0;
    }

}
}
