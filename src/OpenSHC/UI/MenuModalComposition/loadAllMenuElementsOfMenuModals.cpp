#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Menu.hpp"
#include "OpenSHC/UI/MenuModal.hpp"

#include "OpenSHC/Globals/DAT_ModalMenuArrayPointerToStackTop.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Menu;
    using OpenSHC::UI::MenuModal;

    // FUNCTION: STRONGHOLDCRUSADER 0x004A9E80
    void MenuModalComposition::loadAllMenuElementsOfMenuModals()
    {
        for (MenuModal* modal = DAT_ModalMenuArrayPointerToStackTop::instance; modal != NULL;
            modal = modal->pointerToNextModalMenu) {
            if (modal->pointerToMenu != NULL) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::loadMenuElements, modal->pointerToMenu)(0);
            }
        }
    }

}
}
