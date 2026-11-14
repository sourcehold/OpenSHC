#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/CreateOrTriggerInvasion.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_TriggerInvasion.hpp"
#include "OpenSHC/Globals/Menu_TriggerInvasion.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BF20
    void Init::Constructor_MenuModal_TriggerInvasion()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_TriggerInvasion::ptr)(
            UI::Enums::MMT_CREATE_OR_TRIGGER_INVASION, -1, -1, 700, 440, 512, 6,
            UI::MenuModals::CreateOrTriggerInvasion_Func::MenuModalRenderFunction_CreateOrTriggerInvasion::get(),
            Menu_TriggerInvasion::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_TriggerInvasion::get());
    }

}
}
