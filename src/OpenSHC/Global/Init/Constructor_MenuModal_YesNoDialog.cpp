#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/YesNoDialog.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_YesNoDialog.hpp"
#include "OpenSHC/Globals/Menu_YesNoDialog.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B520
    void Init::Constructor_MenuModal_YesNoDialog()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_YesNoDialog::ptr)(
            UI::Enums::MMT_YES_NO_DIALOG, -1, -1, 450, 150, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::YesNoDialog_Func::MenuModalRenderFunction_YesNoDialog::get(), Menu_YesNoDialog::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_YesNoDialog::get());
    }

}
}
