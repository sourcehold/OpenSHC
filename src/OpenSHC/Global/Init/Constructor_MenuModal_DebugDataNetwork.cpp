#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataNetwork.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_DebugDataNetwork.hpp"
#include "OpenSHC/Globals/Menu_DebugModals.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B2A0
    void Init::Constructor_MenuModal_DebugDataNetwork()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DebugDataNetwork::ptr)(
            UI::Enums::MMT_DEBUG_DATA_NETWORK, 167, 3, 500, 200, 14, COL_WHITE::instance.shortValue,
            UI::MenuModals::DebugDataNetwork_Func::MenuModalRenderFunction_DebugDataNetwork::get(),
            Menu_DebugModals::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_DebugDataNetwork::get());
    }

}
}
