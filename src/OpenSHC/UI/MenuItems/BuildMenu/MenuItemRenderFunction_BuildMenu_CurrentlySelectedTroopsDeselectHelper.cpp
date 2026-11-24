#include "../BuildMenu.func.hpp"

#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00439390
            void MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroopsDeselectHelper(int slotID, ...)
            {
                if (DAT_UnitsState::instance.nHasOwnedUnitInSelection == 0) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                DAT_ButtonUnknownZero::instance = FALSE;
                // the deselect buttons are slot IDs 20 to 27
                if (DAT_UnitsState::instance.selectionSlots[slotID - 20] == -1) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                }
            }

        }
    }
}
}
