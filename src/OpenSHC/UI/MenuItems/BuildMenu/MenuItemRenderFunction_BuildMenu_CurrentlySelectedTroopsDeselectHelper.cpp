#include "OpenSHC/UI/MenuItems/BuildMenu.func.hpp"

#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00439390
            void MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroopsDeselectHelper(int selectionIndex, ...)
            {
                if (DAT_UnitsState::instance.nHasOwnedUnitInSelection == 0) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                DAT_ButtonUnknownZero::instance = 0;
                if ((&DAT_UnitsState::instance.selectionEngineers)[selectionIndex] == -1) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
            }

        }
    }
}
}
