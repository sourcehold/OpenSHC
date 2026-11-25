#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/UnusedChooseMessageBox.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_UnusedChooseMessageBox.hpp"
#include "OpenSHC/Globals/Menu_UnusedChooseMessageBox.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B920
    void Init::Constructor_MenuModal_UnusedChooseMessageBox()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_UnusedChooseMessageBox::ptr)(
            UI::Enums::MMT_UNUSED_CHOOSE_MESSAGE_BOX, -1, -1, 663, 440, 512, 6,
            UI::MenuModals::UnusedChooseMessageBox_Func::MenuModalRenderFunction_UnusedChooseMessageBox::get(),
            Menu_UnusedChooseMessageBox::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_UnusedChooseMessageBox::get());
    }

}
}
