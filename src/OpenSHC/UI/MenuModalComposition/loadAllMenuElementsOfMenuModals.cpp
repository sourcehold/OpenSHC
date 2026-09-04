#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Menu.hpp"
#include "OpenSHC/UI/MenuModal.hpp"

#include "OpenSHC/Globals/DAT_ModalMenuArrayPointerToStackTop.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Menu;
    using OpenSHC::UI::MenuModal;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x004A9E80
    void MenuModalComposition::loadAllMenuElementsOfMenuModals()

    {
        MenuModal* pMVar1;

        for (pMVar1 = DAT_ModalMenuArrayPointerToStackTop::instance; pMVar1 != (MenuModal*)0x0;
            pMVar1 = pMVar1->pointerToNextModalMenu) {
            if (pMVar1->pointerToMenu != (Menu*)0x0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::loadMenuElements, pMVar1->pointerToMenu)(0);
            }
        }
        return;
    }

}
}
