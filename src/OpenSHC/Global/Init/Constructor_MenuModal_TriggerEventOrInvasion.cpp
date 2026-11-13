#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_TriggerEventOrInvasion.hpp"
#include "OpenSHC/Globals/Menu_TriggerEventOrInvasion.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BFA0
    void Init::Constructor_MenuModal_TriggerEventOrInvasion()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_TriggerEventOrInvasion::ptr)(
            UI::Enums::MMT_TRIGGER_EVENT_OR_INVASION, -1, -1, 408, 144, 512, 6,
            (UI::MenuModalRenderFunction*)Global_Func::DoNothing::get(), Menu_TriggerEventOrInvasion::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_TriggerEventOrInvasion::get());
    }

}
}
