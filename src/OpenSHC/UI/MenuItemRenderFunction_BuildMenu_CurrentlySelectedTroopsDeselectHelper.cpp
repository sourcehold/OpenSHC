#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00439390
void UI::MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroopsDeselectHelper(int param_1, ...)
{
    if ((DAT_UnitsState::instance.nHasOwnedUnitInSelection == 0)
        || (DAT_ButtonUnknownZero::instance = 0,
            ((int*)(&DAT_UnitsState::instance.selectionEngineers))[param_1] == -1)) {
        DAT_ButtonUnknownZero::instance = 1;
    }
}

}
