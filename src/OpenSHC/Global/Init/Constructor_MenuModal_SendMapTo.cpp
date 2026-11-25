#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/SendMapTo.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_SendMapTo.hpp"
#include "OpenSHC/Globals/Menu_SendMapTo.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C020
    void Init::Constructor_MenuModal_SendMapTo()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_SendMapTo::ptr)(
            UI::Enums::MMT_SEND_MAP_TO, -1, 50, 504, 348, 512, 6,
            UI::MenuModals::SendMapTo_Func::MenuModalRenderFunction_SendMapTo::get(), Menu_SendMapTo::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_SendMapTo::get());
    }

}
}
