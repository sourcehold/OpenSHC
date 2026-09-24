#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00471A80
    void GameCore::exitToScenarioDescriptionMenu()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::removeLadyAndJester, this)();
        this->field22_0x64 = 0;
        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, this)(
            OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
    }

}
}
