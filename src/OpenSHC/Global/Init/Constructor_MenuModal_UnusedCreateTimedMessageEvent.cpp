#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/UnusedCreateTimedMessageEvent.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_UnusedCreateTimedMessageEvent.hpp"
#include "OpenSHC/Globals/Menu_UnusedCreateTimedMessageEvent.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BA60
    void Init::Constructor_MenuModal_UnusedCreateTimedMessageEvent()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_UnusedCreateTimedMessageEvent::ptr)(
            UI::Enums::MMT_UNUSED_CREATE_TIMED_MESSAGE_EVENT, -1, -1, 700, 510, 512, 6,
            UI::MenuModals::UnusedCreateTimedMessageEvent_Func::MenuModalRenderFunction_UnusedCreateTimedMessageEvent::
                get(),
            Menu_UnusedCreateTimedMessageEvent::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_UnusedCreateTimedMessageEvent::get());
    }

}
}
