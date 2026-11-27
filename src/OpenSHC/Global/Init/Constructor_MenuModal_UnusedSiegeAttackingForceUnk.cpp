#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/UnusedSiegeAttackingForceUnk.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_UnusedSiegeAttackingForceUnk.hpp"
#include "OpenSHC/Globals/Menu_UnusedSiegeAttackingForceUnk.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B9E0
    void Init::Constructor_MenuModal_UnusedSiegeAttackingForceUnk()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_UnusedSiegeAttackingForceUnk::ptr)(
            UI::Enums::MMT_UNUSED_SIEGE_ATTACKING_FORCEUnk, -1, -1, 600, 440, 512, 6,
            UI::MenuModals::UnusedSiegeAttackingForceUnk_Func::MenuModalRenderFunction_UnusedSiegeAttackingForceUnk::
                get(),
            Menu_UnusedSiegeAttackingForceUnk::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_UnusedSiegeAttackingForceUnk::get());
    }

}
}
