#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModal.hpp"

#include "OpenSHC/Globals/DAT_ModalMenuArrayPointerToStackTop.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::MenuModal;
    using OpenSHC::UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004A9EB0
    MenuModal* MenuModalComposition::findModalMenu(MenuModalType menuModalID)
    {
        for (MenuModal* modal = DAT_ModalMenuArrayPointerToStackTop::instance; modal != NULL;
            modal = modal->pointerToNextModalMenu) {
            if (modal->menuModalID == menuModalID) {
                return modal;
            }
        }
        return NULL;
    }

}
}
