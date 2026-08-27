#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {

using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;

// FUNCTION: STRONGHOLDCRUSADER 0x0043A880
void UI::MenuItemRenderFunction_BuildingAndStatusMenu_BuildingHelpTextButton(int param_1, ...)
{
    DAT_ButtonUnknownZero::instance = 0;
    if ((DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
        DAT_ButtonUnknownZero::instance = 1;
    } else if (DAT_BuildingsState::instance.field24_0x18e04c != 0) {
        MACRO_CALL(OpenSHC::UI_Func::
                MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
    }
}

}
