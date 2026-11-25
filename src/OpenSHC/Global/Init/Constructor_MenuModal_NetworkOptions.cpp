#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/NetworkOptions.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_NetworkOptions.hpp"
#include "OpenSHC/Globals/Menu_NetworkOptions.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B460
    void Init::Constructor_MenuModal_NetworkOptions()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_NetworkOptions::ptr)(
            UI::Enums::MMT_NETWORK_OPTIONS, -1, -1, 500, 357, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::NetworkOptions_Func::MenuModalRenderFunction_NetworkOptions::get(),
            Menu_NetworkOptions::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_NetworkOptions::get());
    }

}
}
