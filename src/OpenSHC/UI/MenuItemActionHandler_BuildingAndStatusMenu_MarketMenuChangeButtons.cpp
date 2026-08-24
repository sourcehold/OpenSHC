#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {

using OpenSHC::UI::Enums::MenuViewType;

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x00465920
void UI::MenuItemActionHandler_BuildingAndStatusMenu_MarketMenuChangeButtons(int param_1, ...)

{
    DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = param_1;
    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
        OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
    DAT_GameCore::instance.field61_0x100 = param_1;
    return;
}

}
