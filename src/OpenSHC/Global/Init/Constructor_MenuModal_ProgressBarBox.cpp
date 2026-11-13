#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/ProgressBarBox.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_ProgressBarBox.hpp"
#include "OpenSHC/Globals/Menu_ProgressBarBox.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B6E0
    void Init::Constructor_MenuModal_ProgressBarBox()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_ProgressBarBox::ptr)(
            UI::Enums::MMT_PROGRESS_BAR_BOX, -1, 50, 400, 100, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::ProgressBarBox_Func::MenuModalRenderFunction_ProgressBarBox::get(),
            Menu_ProgressBarBox::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_ProgressBarBox::get());
    }

}
}
