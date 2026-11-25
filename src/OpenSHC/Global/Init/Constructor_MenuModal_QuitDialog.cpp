#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/YesNoDialog.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_QuitDialog.hpp"
#include "OpenSHC/Globals/Menu_QuitDialog.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B560
    void Init::Constructor_MenuModal_QuitDialog()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_QuitDialog::ptr)(
            UI::Enums::MMT_QUIT_DIALOG, -1, -1, 500, 150, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::YesNoDialog_Func::MenuModalRenderFunction_YesNoDialog::get(), Menu_QuitDialog::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_QuitDialog::get());
    }

}
}
