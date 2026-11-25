#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TutorialBox.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_TutorialBox.hpp"
#include "OpenSHC/Globals/Menu_TutorialBox.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BCA0
    void Init::Constructor_MenuModal_TutorialBox()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_TutorialBox::ptr)(
            UI::Enums::MMT_TUTORIAL_BOX, -1, 20, 600, 150, 2112, COL_WHITE::instance.shortValue,
            UI::MenuModals::TutorialBox_Func::MenuModalRenderFunction_TutorialBox_Thunk::get(), Menu_TutorialBox::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_TutorialBox::get());
    }

}
}
