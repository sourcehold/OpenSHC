#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/AlliesOrder.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_AlliesOrder.hpp"
#include "OpenSHC/Globals/Menu_AlliesOrder.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C1C0
    void Init::Constructor_MenuModal_AlliesOrder()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_AlliesOrder::ptr)(
            UI::Enums::MMT_ALLIES_ORDER, -1, -1, 768, 240, 512, COL_BLACK::instance.shortValue,
            UI::MenuModals::AlliesOrder_Func::MenuModalRenderFunction_AlliesOrder::get(), Menu_AlliesOrder::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_AlliesOrder::get());
    }

}
}
