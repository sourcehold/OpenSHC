#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/NewEvent.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_NewEvent.hpp"
#include "OpenSHC/Globals/Menu_NewEvent.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BAA0
    void Init::Constructor_MenuModal_NewEvent()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_NewEvent::ptr)(UI::Enums::MMT_NEW_EVENT,
            -1, -1, 600, 470, 512, 6, UI::MenuModals::NewEvent_Func::MenuModalRenderFunction_NewEvent::get(),
            Menu_NewEvent::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_NewEvent::get());
    }

}
}
