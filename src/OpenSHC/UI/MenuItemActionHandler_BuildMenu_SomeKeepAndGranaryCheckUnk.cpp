#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {

using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
using OpenSHC::UI::Enums::BuildMenuTabType;
using OpenSHC::UI::Enums::MenuViewType;

// FUNCTION: STRONGHOLDCRUSADER 0x00433200
void UI::MenuItemActionHandler_BuildMenu_SomeKeepAndGranaryCheckUnk(int param_1, ...)
{
    if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == ((BuildMenuTabType)0x31)) {
        if (0 < MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::singlePlayerHasKeepAndGranaryCheck, DAT_GameState::ptr)()) {
            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
        }
    }
}

}
