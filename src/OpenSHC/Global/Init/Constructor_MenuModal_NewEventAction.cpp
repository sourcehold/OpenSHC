#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/NewEventAction.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_NewEventAction.hpp"
#include "OpenSHC/Globals/Menu_NewEventAction.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BB20
    void Init::Constructor_MenuModal_NewEventAction()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_NewEventAction::ptr)(
            UI::Enums::MMT_NEW_EVENT_ACTION, -1, -1, 760, 540, 512, 6,
            UI::MenuModals::NewEventAction_Func::MenuModalRenderFunction_NewEventAction::get(),
            Menu_NewEventAction::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_NewEventAction::get());
    }

}
}
