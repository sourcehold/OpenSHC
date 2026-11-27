#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DisableWeapon.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_DisableWeapon.hpp"
#include "OpenSHC/Globals/Menu_DisableWeapon.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BC60
    void Init::Constructor_MenuModal_DisableWeapon()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DisableWeapon::ptr)(
            UI::Enums::MMT_DISABLE_WEAPON, -1, -1, 400, 240, 512, 6,
            UI::MenuModals::DisableWeapon_Func::MenuModalRenderFunction_DisableWeapon::get(), Menu_DisableWeapon::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_DisableWeapon::get());
    }

}
}
