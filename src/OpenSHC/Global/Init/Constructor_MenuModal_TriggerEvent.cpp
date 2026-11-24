#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TriggerEvent.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_TriggerEvent.hpp"
#include "OpenSHC/Globals/Menu_TriggerEvent.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BF60
    void Init::Constructor_MenuModal_TriggerEvent()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_TriggerEvent::ptr)(
            UI::Enums::MMT_TRIGGER_EVENT, -1, -1, 408, 442, 512, 6,
            UI::MenuModals::TriggerEvent_Func::MenuModalRenderFunction_TriggerEvent::get(), Menu_TriggerEvent::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_TriggerEvent::get());
    }

}
}
