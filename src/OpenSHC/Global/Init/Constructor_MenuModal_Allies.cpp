#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/Allies.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_Allies.hpp"
#include "OpenSHC/Globals/Menu_Allies.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C180
    void Init::Constructor_MenuModal_Allies()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_Allies::ptr)(UI::Enums::MMT_ALLIES, -1,
            -1, 696, 384, 512, COL_BLACK::instance.shortValue,
            UI::MenuModals::Allies_Func::MenuModalRenderFunction_Allies::get(), Menu_Allies::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_Allies::get());
    }

}
}
