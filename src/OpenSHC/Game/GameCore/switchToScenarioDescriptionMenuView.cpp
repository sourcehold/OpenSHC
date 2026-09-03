#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004719E0
    void GameCore::switchToScenarioDescriptionMenuView()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::removeJesterAndLadyUnitsInCertainMissions, this)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, this)(
            OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
        this->field22_0x64 = 0;
    }

}
}
