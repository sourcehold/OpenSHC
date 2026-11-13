#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/WaitingForHost.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_WaitingForHost.hpp"
#include "OpenSHC/Globals/Menu_WaitingForHost.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B8A0
    void Init::Constructor_MenuModal_WaitingForHost()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_WaitingForHost::ptr)(
            UI::Enums::MMT_WAITING_FOR_HOST, -1, -1, 500, 100, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::WaitingForHost_Func::MenuModalRenderFunction_WaitingForHost::get(),
            Menu_WaitingForHost::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_WaitingForHost::get());
    }

}
}
