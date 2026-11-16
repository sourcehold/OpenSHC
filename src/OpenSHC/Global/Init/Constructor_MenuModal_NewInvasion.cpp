#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/CreateOrTriggerInvasion.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_NewInvasion.hpp"
#include "OpenSHC/Globals/Menu_NewInvasion.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BA20
    void Init::Constructor_MenuModal_NewInvasion()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_NewInvasion::ptr)(
            UI::Enums::MMT_NEW_INVASION, -1, -1, 700, 440, 512, 6,
            UI::MenuModals::CreateOrTriggerInvasion_Func::MenuModalRenderFunction_CreateOrTriggerInvasion::get(),
            Menu_NewInvasion::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_NewInvasion::get());
    }

}
}
