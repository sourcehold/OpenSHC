#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/ReceiveMapFrom.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_ReceiveMapFrom.hpp"
#include "OpenSHC/Globals/Menu_ReceiveMapFrom.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C060
    void Init::Constructor_MenuModal_ReceiveMapFrom()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_ReceiveMapFrom::ptr)(
            UI::Enums::MMT_RECEIVE_MAP_FROM, -1, -1, 408, 200, 512, 6,
            UI::MenuModals::ReceiveMapFrom_Func::MenuModalRenderFunction_ReceiveMapFrom::get(),
            Menu_ReceiveMapFrom::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_ReceiveMapFromUnk::get());
    }

}
}
