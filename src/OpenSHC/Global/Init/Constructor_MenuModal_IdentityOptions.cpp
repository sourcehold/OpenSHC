#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/IdentityOptions.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_IdentityOptions.hpp"
#include "OpenSHC/Globals/Menu_IdentityOptions.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B660
    void Init::Constructor_MenuModal_IdentityOptions()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_IdentityOptions::ptr)(
            UI::Enums::MMT_IDENTITY_OPTIONS, -1, -1, 500, 400, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::IdentityOptions_Func::MenuModalRenderFunction_IdentityOptions::get(),
            Menu_IdentityOptions::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_IdentityOptions::get());
    }

}
}
