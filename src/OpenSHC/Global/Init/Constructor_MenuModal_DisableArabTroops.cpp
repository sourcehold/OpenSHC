#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DisableTroops.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_DisableArabTroops.hpp"
#include "OpenSHC/Globals/Menu_DisableArabTroops.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BC20
    void Init::Constructor_MenuModal_DisableArabTroops()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DisableArabTroops::ptr)(
            UI::Enums::MMT_DISABLE_ARAB_TROOPS, -1, -1, 400, 240, 512, 6,
            UI::MenuModals::DisableTroops_Func::MenuModalRenderFunction_DisableTroops::get(),
            Menu_DisableArabTroops::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_DisableArabTroops::get());
    }

}
}
